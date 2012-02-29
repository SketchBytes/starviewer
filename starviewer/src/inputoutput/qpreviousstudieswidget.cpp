#include "qpreviousstudieswidget.h"

#include "logging.h"
#include "study.h"
#include "patient.h"
#include "previousstudiesmanager.h"
#include "queryscreen.h"
#include "singleton.h"
#include "screenmanager.h"
#include "qtreewidgetwithseparatorline.h"

#include <QVBoxLayout>
#include <QMovie>
#include <QTreeWidgetItem>
#include <QScrollBar>

namespace udg {

QPreviousStudiesWidget::QPreviousStudiesWidget(QWidget *parent)
   : QFrame(parent)
{
    setWindowFlags(Qt::Popup);
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);

    m_lookingForStudiesWidget = new QWidget(this);
    m_previousStudiesTree = new QTreeWidgetWithSeparatorLine(this);
    m_previousStudiesManager = new PreviousStudiesManager();
    m_signalMapper = new QSignalMapper(this);
    m_queryScreen = SingletonPointer<QueryScreen>::instance();
    m_numberOfDownloadingStudies = 0;

    m_noPreviousStudiesLabel = new QLabel(this);
    m_noPreviousStudiesLabel->setText(tr("No related studies found."));

    initializeLookingForStudiesWidget();
    initializeTree();

    verticalLayout->addWidget(m_lookingForStudiesWidget);
    verticalLayout->addWidget(m_noPreviousStudiesLabel);
    verticalLayout->addWidget(m_previousStudiesTree);

    createConnections();

    m_lookingForStudiesWidget->setVisible(false);
    m_noPreviousStudiesLabel->setVisible(false);
    m_previousStudiesTree->setVisible(false);
}

QPreviousStudiesWidget::~QPreviousStudiesWidget()
{
    delete m_previousStudiesTree;
    foreach (QString key, m_infomationPerStudy.keys())
    {
        delete m_infomationPerStudy.take(key);
    }
    delete m_previousStudiesManager;
    delete m_lookingForStudiesWidget;
    delete m_signalMapper;
    delete m_noPreviousStudiesLabel;
}

void QPreviousStudiesWidget::updateList()
{
    if (!m_infomationPerStudy.isEmpty())
    {
        foreach (Study *study, m_patient->getStudies())
        {
            StudyInfo *studyInfo = m_infomationPerStudy[study->getInstanceUID()];

            if (studyInfo != NULL)
            {
                if (studyInfo->status == Downloading)
                {
                    this->decreaseNumberOfDownladingStudies();
                }
                studyInfo->status = Finished;
                studyInfo->statusIcon->setPixmap(QPixmap(":/images/button_ok.png"));
                studyInfo->downloadButton->setEnabled(false);
            }
        }
    }
}

void QPreviousStudiesWidget::searchPreviousStudiesOf(Study *study)
{
    Q_ASSERT(study);

    initializeSearch();
    m_patient = study->getParentPatient();
    m_previousStudiesManager->queryMergedPreviousStudies(study);
    m_modalitiesOfStudiesToHighlight = removeNonImageModalities(study->getModalities());
}

void QPreviousStudiesWidget::searchStudiesOf(Patient *patient)
{
    Q_ASSERT(patient);

    initializeSearch();
    m_patient = patient;
    m_previousStudiesManager->queryMergedStudies(patient);

    foreach(Study *study, patient->getStudies())
    {
        m_modalitiesOfStudiesToHighlight.append(study->getModalities());
    }
}

void QPreviousStudiesWidget::initializeSearch()
{
    m_lookingForStudiesWidget->setVisible(true);
    m_noPreviousStudiesLabel->setVisible(false);
    m_previousStudiesTree->setVisible(false);

    int items = m_previousStudiesTree->topLevelItemCount();
    for (int i = 0; i < items; i++)
    {
        delete m_previousStudiesTree->takeTopLevelItem(0);
    }
    foreach (QString key, m_infomationPerStudy.keys())
    {
        delete m_infomationPerStudy.take(key);
    }
}

void QPreviousStudiesWidget::createConnections()
{
    connect(m_previousStudiesManager, SIGNAL(queryStudiesFinished(QList<Study*>)), this, SLOT(insertStudiesToTree(QList<Study*>)));
    connect(m_signalMapper, SIGNAL(mapped(const QString&)), this, SLOT(retrieveAndLoadStudy(const QString&)));
    connect(m_queryScreen, SIGNAL(studyRetrieveStarted(QString)), this, SLOT(studyRetrieveStarted(QString)));
    connect(m_queryScreen, SIGNAL(studyRetrieveFinished(QString)), this, SLOT(studyRetrieveFinished(QString)));
    connect(m_queryScreen, SIGNAL(studyRetrieveFailed(QString)), this, SLOT(studyRetrieveFailed(QString)));
}

void QPreviousStudiesWidget::initializeTree()
{

    // Inicialitzem la capçalera
    QStringList labels;
    labels << "" << "" << tr("Modality") << tr("Description") << tr("Date") << tr("Name");
    m_previousStudiesTree->setHeaderLabels(labels);

    // Fem 8 columnes perquè la primera l'amagarem
    m_previousStudiesTree->setColumnCount(6);
    m_previousStudiesTree->setRootIsDecorated(false);
    m_previousStudiesTree->setItemsExpandable(false);
    m_previousStudiesTree->header()->setResizeMode(DownloadingStatus, QHeaderView::Fixed);
    m_previousStudiesTree->header()->setResizeMode(DownloadButton, QHeaderView::Fixed);
    m_previousStudiesTree->header()->setMovable(false);
    m_previousStudiesTree->setUniformRowHeights(true);
    m_previousStudiesTree->setSortingEnabled(true);

    // Ordenem els estudis per data i hora
    m_previousStudiesTree->sortItems(Date, Qt::DescendingOrder);

    // El farem visible quan rebem la llista d'estudis previs
    m_previousStudiesTree->setVisible(false);
}

void QPreviousStudiesWidget::initializeLookingForStudiesWidget()
{
    QHBoxLayout *horizontalLayout = new QHBoxLayout(m_lookingForStudiesWidget);

    QLabel *downloadigAnimation = new QLabel();
    QMovie *operationAnimation = new QMovie();
    operationAnimation->setFileName(":/images/loader.gif");
    downloadigAnimation->setMovie(operationAnimation);
    operationAnimation->start();

    horizontalLayout->addWidget(downloadigAnimation);
    horizontalLayout->addWidget(new QLabel(tr("Looking for related studies...")));

}

void QPreviousStudiesWidget::insertStudyToTree(Study *study)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();

    // Afegim l'item al widget
    m_previousStudiesTree->addTopLevelItem(item);
    item->setFlags(Qt::ItemIsEnabled);

    item->setText(Name, study->getParentPatient()->getFullName());
    item->setText(Date, study->getDate().toString(Qt::ISODate) + "   " + study->getTimeAsString());
    item->setText(Modality, study->getModalitiesAsSingleString());
    item->setText(Description, study->getDescription());

    QWidget *statusWidget = new QWidget(m_previousStudiesTree);
    QHBoxLayout *statusLayout = new QHBoxLayout(statusWidget);
    QLabel *status = new QLabel(statusWidget);
    statusLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding));
    statusLayout->addWidget(status);
    statusLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding));
    statusLayout->setMargin(0);

    m_previousStudiesTree->setItemWidget(item, DownloadingStatus, statusWidget);

    // Posem el botó en un Layout amb Margin 2 per a que els Items del QTreeWidget no estiguin tant junts i el control sigui més llegible
    QIcon dowloadIcon(QString(":/images/view.png"));
    QPushButton *downloadButton = new QPushButton(dowloadIcon, QString(""));
    QWidget *downloadButtonWidget = new QWidget(m_previousStudiesTree);
    QVBoxLayout *downloadButtonLayout = new QVBoxLayout(downloadButtonWidget);
    //Apliquem 1px més de layout per la línia separadora 
    downloadButtonLayout->setContentsMargins(0, 2, 0, 1);
    downloadButtonLayout->addWidget(downloadButton);

    connect(downloadButton, SIGNAL(clicked()), m_signalMapper, SLOT(map()));
    m_signalMapper->setMapping(downloadButton, study->getInstanceUID());

    if (hasToHighlightStudy(study))
    {
        highlightQTreeWidgetItem(item);
    }

    m_previousStudiesTree->setItemWidget(item, DownloadButton, downloadButtonWidget);

    // Guardem informació relacionada amb l'estudi per facilitar la feina
    StudyInfo *relatedStudyInfo = new StudyInfo;
    relatedStudyInfo->item = item;
    relatedStudyInfo->study = study;
    relatedStudyInfo->downloadButton = downloadButton;
    relatedStudyInfo->statusIcon = status;
    relatedStudyInfo->status = Initialized;
    m_infomationPerStudy.insert(study->getInstanceUID(), relatedStudyInfo);
}

void QPreviousStudiesWidget::highlightQTreeWidgetItem(QTreeWidgetItem *item)
{
    for (int index = 0; index < item->columnCount(); index++)
    {
        item->setBackground(index, QColor(149, 206, 236, 255));
    }
}

void QPreviousStudiesWidget::updateWidthTree()
{
    int fixedSize = 0;
    for (int i = 0; i < m_previousStudiesTree->columnCount(); i++)
    {
        m_previousStudiesTree->resizeColumnToContents(i);
        fixedSize += m_previousStudiesTree->columnWidth(i);
    }
    m_previousStudiesTree->setFixedWidth(fixedSize + 20);
}

void QPreviousStudiesWidget::updateHeightTree()
{
    ScreenManager screen;
    int screenAvailableHeight = screen.getAvailableScreenGeometry(screen.getIdOfScreen(this)).height();
    int topAndMargins = this->geometry().top() + m_previousStudiesTree->geometry().top() * 2; // Es multiplica per 2 pel marge inferior.
    int maxHeight = screenAvailableHeight - topAndMargins;
    int minHeight = m_previousStudiesTree->sizeHint().height();
    int contentHeight = minHeight;
    bool found = false;
    while (!found && contentHeight < maxHeight)
    {
        m_previousStudiesTree->setFixedHeight(contentHeight);
        found = m_previousStudiesTree->verticalScrollBar()->maximum() <= m_previousStudiesTree->verticalScrollBar()->minimum();
        contentHeight += 5;
    }
}

void QPreviousStudiesWidget::insertStudiesToTree(QList<Study*> studiesList)
{
    if (studiesList.size() > 0)
    {
        foreach (Study *study, studiesList)
        {
            if (study->getDICOMSource().getRetrievePACS().count() > 0)
            {
                //Sempre hauria de ser més gran de 0
                insertStudyToTree(study);
            }
        }

        updateList();

        m_previousStudiesTree->setVisible(true);

        updateWidthTree();
        updateHeightTree();
    }
    else
    {
        m_noPreviousStudiesLabel->setVisible(true);
    }

    m_lookingForStudiesWidget->setVisible(false);

    this->adjustSize();
}

void QPreviousStudiesWidget::retrieveAndLoadStudy(const QString &studyInstanceUID)
{
    StudyInfo *studyInfo = m_infomationPerStudy[studyInstanceUID];

    studyInfo->downloadButton->setEnabled(false);

    m_queryScreen->retrieveStudy(QInputOutputPacsWidget::Load, studyInfo->study->getDICOMSource().getRetrievePACS().at(0).getID() , studyInfo->study);

    studyInfo->status = Pending;

    QMovie *statusAnimation = new QMovie();
    studyInfo->statusIcon->setMovie(statusAnimation);
    statusAnimation->setFileName(":/images/loader.gif");
    statusAnimation->start();

    this->increaseNumberOfDownladingStudies();
}

void QPreviousStudiesWidget::studyRetrieveStarted(QString studyInstanceUID)
{
    StudyInfo *studyInfo = m_infomationPerStudy[studyInstanceUID];

    // Comprovem que el signal capturat de QueryScreen sigui nostre
    if (studyInfo != NULL)
    {
        if (studyInfo->status == Pending)
        {
            studyInfo->status = Downloading;
        }
    }
}

void QPreviousStudiesWidget::studyRetrieveFinished(QString studyInstanceUID)
{
    StudyInfo *studyInfo = m_infomationPerStudy[studyInstanceUID];

    // Comprovem que el signal capturat de QueryScreen sigui nostre
    if (studyInfo != NULL)
    {
        if (studyInfo->status == Downloading)
        {
            studyInfo->status = Finished;
            studyInfo->statusIcon->setPixmap(QPixmap(":/images/button_ok.png"));

            this->decreaseNumberOfDownladingStudies();
        }
    }

}

void QPreviousStudiesWidget::studyRetrieveFailed(QString studyInstanceUID)
{
    StudyInfo *studyInfo = m_infomationPerStudy[studyInstanceUID];

    // Comprovem que el signal capturat de QueryScreen sigui nostre
    if (studyInfo != NULL)
    {
        if (studyInfo->status == Downloading)
        {
            studyInfo->status = Failed;
            studyInfo->statusIcon->setPixmap(QPixmap(":/images/cancel.png"));
            studyInfo->downloadButton->setEnabled(true);

            this->decreaseNumberOfDownladingStudies();
        }
    }
}

void QPreviousStudiesWidget::increaseNumberOfDownladingStudies()
{
    m_numberOfDownloadingStudies++;
    if (m_numberOfDownloadingStudies == 1)
    {
        emit downloadingStudies();
    }
}

void QPreviousStudiesWidget::decreaseNumberOfDownladingStudies()
{
    m_numberOfDownloadingStudies--;
    if (m_numberOfDownloadingStudies == 0)
    {
        emit studiesDownloaded();
    }
}

void QPreviousStudiesWidget::setVisible(bool visible)
{
    QFrame::setVisible(visible);
    if (visible)
    {
        updateHeightTree();
        this->adjustSize();
    }
}

QStringList QPreviousStudiesWidget::removeNonImageModalities(const QStringList &studiesModalities)
{
    QStringList studiesModalitiesToReturn(studiesModalities);
    studiesModalitiesToReturn.removeAll("KO");
    studiesModalitiesToReturn.removeAll("PR");
    studiesModalitiesToReturn.removeAll("SR");

    return studiesModalities;
}

bool QPreviousStudiesWidget::hasToHighlightStudy(Study *study)
{
    foreach (QString modality, study->getModalities())
    {
        if (m_modalitiesOfStudiesToHighlight.contains(modality))
        {
            return true;
        }
    }

    return false;
}

}
