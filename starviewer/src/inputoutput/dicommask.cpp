#include "dicommask.h"

#include <QStringList>
#include <QDateTime>
#include <QDate>
#include <dcsequen.h>
#include <dimse.h> // provide the structure DcmDataSet
#include <dcdeftag.h> //provide the information for the tags
#include <ofcond.h> //provide the OFcondition structure and his members
#include <QString>

#include "errordcmtk.h"
#include "status.h"

namespace udg{

DicomMask::DicomMask()
{
}

/************************* PATIENT  *********************************************************************/

void DicomMask::setPatientId(const QString &patientId)
{
    m_patientId = patientId;
}

void DicomMask::setPatientName(const QString &patientName)
{
    m_patientName = patientName;
}

void DicomMask::setPatientBirth(const QString &patientBirth)
{
    m_patientBirth = patientBirth;
}

void DicomMask::setPatientSex(const QString &patientSex)
{
    m_patientSex = patientSex;
}

void DicomMask::setPatientAge(const QString &patientAge)
{
    m_patientAge = patientAge;
}


QString DicomMask::getPatientId() const
{
    return m_patientId;
}

QString DicomMask::getPatientName() const
{
    return m_patientName;
}

QString DicomMask::getPatientBirth() const
{
    return m_patientBirth;
}

QString DicomMask::getPatientSex() const
{
    return m_patientSex;
}

QString DicomMask::getPatientAge() const
{
    return m_patientAge;
}

/****************************************** STUDY *****************************************************/

void DicomMask::setStudyId(const QString &studyId)
{
    m_studyId = studyId;
}

void DicomMask::setStudyDate(const QString &studyDate)
{
    m_studyDate = studyDate;
}

void DicomMask::setStudyDescription(const QString &studyDescription)
{
    m_studyDescription = studyDescription;
}

void DicomMask::setStudyModality(const QString &studyModality)
{
    m_studyModality = studyModality;
}

void DicomMask::setStudyTime(const QString &studyTime)
{
    m_studyTime = studyTime;
}

void DicomMask::setStudyUID(const QString &studyUID)
{
    m_studyUID = studyUID;
}

void DicomMask::setAccessionNumber(const QString &accessionNumber)
{
    m_accessionNumber = accessionNumber;
}

void DicomMask::setReferringPhysiciansName(const QString &referringPhysiciansName)
{
    m_referringPhysiciansName = referringPhysiciansName;
}

/***************************************************************   GET **********************************************/

QString DicomMask::getStudyUID() const
{
    return m_studyUID;
}

QString DicomMask::getStudyId() const
{
    return m_studyId;
}

QString DicomMask::getStudyDate() const
{
    return m_studyDate;
}

QString DicomMask::getStudyDescription() const
{
    return m_studyDescription;
}

QString DicomMask::getStudyTime() const
{
    return m_studyTime;
}

QString DicomMask::getStudyModality() const
{
    return m_studyModality;
}

QString DicomMask::getAccessionNumber() const
{
    return m_accessionNumber;
}

QString DicomMask::getReferringPhysiciansName() const
{
    return m_referringPhysiciansName;
}

/************************************** SERIES *************************************************/

void DicomMask::setSeriesNumber(const QString &seriesNumber)
{
    m_seriesNumber = seriesNumber;
}

void DicomMask::setSeriesDate(const QString &seriesDate)
{
    m_seriesDate = seriesDate;
}

void DicomMask::setSeriesDescription(const QString &seriesDescription)
{
    m_seriesDescription = seriesDescription;
}

void DicomMask::setSeriesModality(const QString &seriesModality)
{
    m_seriesModality = seriesModality;
}

void DicomMask::setSeriesTime(const QString &seriesTime)
{
    m_seriesTime = seriesTime;
}

void DicomMask::setSeriesUID(const QString &seriesUID)
{
    m_seriesUID = seriesUID;
}

void DicomMask::setSeriesProtocolName(const QString &seriesProtocolName)
{
    m_seriesProtocolName = seriesProtocolName;
}

void DicomMask::setRequestAttributeSequence(const QString &requestedProcedureID, const QString &scheduledProcedureStepID)
{
    m_requestedProcedureID = requestedProcedureID;
    m_scheduledProcedureStepID = scheduledProcedureStepID;
}

void DicomMask::setPPSStartDate(const QString &PPPSStartDate)
{
    m_PPSStartDate = PPPSStartDate;
}

void DicomMask::setPPStartTime(const QString &PPSStartTime)
{
    m_PPSStartTime = PPSStartTime;
}

/************************************************ GET **************************************************************/

QString DicomMask::getSeriesNumber() const
{
    return m_seriesNumber;
}

QString DicomMask::getSeriesDate() const
{
    return m_seriesDate;
}

QString DicomMask::getSeriesTime() const
{
    return m_seriesTime;
}

QString DicomMask::getSeriesDescription() const
{
    return m_seriesDescription;
}

QString DicomMask::getSeriesModality() const
{
    return m_seriesModality;
}


QString DicomMask::getSeriesProtocolName() const
{
    return m_seriesProtocolName;
}

QString DicomMask::getSeriesUID() const
{
    return m_seriesUID;
}

QString DicomMask::getRequestedProcedureID() const
{
    return m_requestedProcedureID;
}

QString DicomMask::getScheduledProcedureStepID() const
{
    return m_scheduledProcedureStepID;
}

QString DicomMask::getPPSStartDate() const
{
    return m_PPSStartDate;
}

QString DicomMask::getPPSStartTime() const
{
    return m_PPSStartTime;
}

/********************************************** IMAGE **************************************/

void DicomMask::setImageNumber(const QString &imageNumber)
{
    m_imageNumber = imageNumber;
}

void DicomMask::setSOPInstanceUID(const QString &SOPInstanceUID)
{
    m_SOPInstanceUID = SOPInstanceUID;
}

QString DicomMask::getImageNumber() const
{
    return m_imageNumber;
}

QString DicomMask::getSOPInstanceUID() const
{
    return m_SOPInstanceUID;
}

DcmDataset* DicomMask::getDicomMask()
{
    DcmDataset *maskDcmDataset = new DcmDataset();

    /*Especifiquem que per defecte l'Specific character set utilitzat per fer les consultes cap al PACS serà ISO_IR 100, és a dir Latin 1, ja que els PACS 
     que utilitza l'IDI utilitzen aquesta codificació (és el que suporta dcm4chee), a més amb Latin1 és la codificació que utilitzen
     la majoria de països europeus. Per dubtes consultar C.12.1.1.2 on s'especifiquen quins Specific characters set, també és important
     consultar el conformance statement del PACS contra el que consultem per saber quin Specific character set suporta. Com que el character set és Latin1 haurem d
     transformar tots el tags dicom que siguin string (SH, LO, ST, PN, LT, UT) a Latin1
*/

    DcmElement *elemSpecificCharacterSet = newDicomElement(DCM_SpecificCharacterSet);
    elemSpecificCharacterSet->putString("ISO_IR 100"); //ISO_IR 100 és Latin1
    maskDcmDataset->insert(elemSpecificCharacterSet, OFTrue);

    /*Especifiquem a quin nivell es fa el QueryRetrieve, a través del mètode getQueryRetrieveLevel, que ens retorna el nivell en funció dels camps de la màscara*/
    DcmElement *elem = newDicomElement(DCM_QueryRetrieveLevel);
    elem->putString(qPrintable(getQueryRetrieveLevel()));
    maskDcmDataset->insert(elem , OFTrue);

    if (!getPatientId().isNull())
    {
        DcmElement *elem = newDicomElement(DCM_PatientID);
        elem->putString(getPatientId().toLatin1().data());
        maskDcmDataset->insert(elem, OFTrue);
    }

    if (!getPatientName().isNull())
    {
        DcmElement *elem = newDicomElement(DCM_PatientsName);
        elem->putString(getPatientName().toLatin1().data());
        maskDcmDataset->insert(elem, OFTrue);
    }

    if (!getPatientBirth().isNull())
    {
        DcmElement *elem = newDicomElement(DCM_PatientsBirthDate);
        elem->putString(qPrintable(getPatientBirth()));
        maskDcmDataset->insert(elem , OFTrue);
    }

    if (!getPatientSex().isNull())
    {
        DcmElement *elem = newDicomElement(DCM_PatientsSex);
        elem->putString(qPrintable(getPatientSex()));
        maskDcmDataset->insert(elem , OFTrue);
    }

    if (!getPatientAge().isNull())
    {
        DcmElement *elem = newDicomElement(DCM_PatientsAge);
        elem->putString(qPrintable(getPatientAge()));
        maskDcmDataset->insert(elem , OFTrue);
    }

    if (!getStudyId().isNull())
    {
        DcmElement *elem = newDicomElement(DCM_StudyID);
        elem->putString(getStudyId().toLatin1().data());
        maskDcmDataset->insert(elem , OFTrue);
    }

    if (!getStudyDescription().isNull())
    {
        DcmElement *elem = newDicomElement(DCM_StudyDescription);
        elem->putString(getStudyDescription().toLatin1().data());
        maskDcmDataset->insert(elem , OFTrue);
    }

    if (!getStudyModality().isNull())
    {
        DcmElement *elem = newDicomElement(DCM_ModalitiesInStudy);
        elem->putString(qPrintable(getStudyModality()));
        maskDcmDataset->insert(elem , OFTrue);
    }

    if (!getStudyDate().isNull())
    {
        DcmElement *elem = newDicomElement(DCM_StudyDate);
        elem->putString(qPrintable(getStudyDate()));
        maskDcmDataset->insert(elem , OFTrue);
    }

    if (!getStudyTime().isNull())
    {
        DcmElement *elem = newDicomElement(DCM_StudyTime);
        elem->putString(qPrintable(getStudyTime()));
        maskDcmDataset->insert(elem , OFTrue);
    }

    if (!getAccessionNumber().isNull())
    {
        DcmElement *elem = newDicomElement(DCM_AccessionNumber);
        elem->putString(getAccessionNumber().toLatin1().data());
        maskDcmDataset->insert(elem , OFTrue);
    }

    if (!getReferringPhysiciansName().isNull())
    {
        DcmElement *elem = newDicomElement(DCM_ReferringPhysiciansName);
        elem->putString(getReferringPhysiciansName().toLatin1().data());
        maskDcmDataset->insert(elem , OFTrue);
    }

    if (!getStudyUID().isNull())
    {
        DcmElement *elem = newDicomElement(DCM_StudyInstanceUID);
        elem->putString(qPrintable(getStudyUID()));
        maskDcmDataset->insert(elem , OFTrue);
    }

    if (!getSeriesNumber().isNull())
    {
        DcmElement *elem = newDicomElement(DCM_SeriesNumber);
        elem->putString(qPrintable(getSeriesNumber()));
        maskDcmDataset->insert(elem , OFTrue);
    }

    if (!getSeriesDate().isNull())
    {
        DcmElement *elem = newDicomElement(DCM_SeriesDate);
        elem->putString(qPrintable(getSeriesDate()));
        maskDcmDataset->insert(elem , OFTrue);
    }

    if (!getSeriesModality().isNull())
    {
        DcmElement *elem = newDicomElement(DCM_Modality);
        elem->putString(qPrintable(getSeriesModality()));
        maskDcmDataset->insert(elem , OFTrue);
    }

    if (!getSeriesTime().isNull())
    {
        DcmElement *elem = newDicomElement(DCM_SeriesTime);
        elem->putString(qPrintable(getSeriesTime()));
        maskDcmDataset->insert(elem , OFTrue);
    }

    if (!getSeriesDescription().isNull())
    {
        DcmElement *elem = newDicomElement(DCM_SeriesDescription);
        elem->putString(getSeriesDescription().toLatin1().data());
        maskDcmDataset->insert(elem , OFTrue);
    }

    if (!getSeriesProtocolName().isNull())
    {
        DcmElement *elem = newDicomElement(DCM_ProtocolName);
        elem->putString(getSeriesProtocolName().toLatin1().data());
        maskDcmDataset->insert(elem , OFTrue);
    }

    if (!getSeriesUID().isNull())
    {
        DcmElement *elem = newDicomElement(DCM_SeriesInstanceUID);
        elem->putString(qPrintable(getSeriesUID()));
        maskDcmDataset->insert(elem , OFTrue);
    }

    if (!getRequestedProcedureID().isNull() || !getScheduledProcedureStepID().isNull())
    {
        DcmSequenceOfItems *requestedAttributeSequence = new DcmSequenceOfItems(DCM_RequestAttributesSequence);

        DcmItem *requestedAttributeSequenceItem = new DcmItem(DCM_Item);
        requestedAttributeSequenceItem->putAndInsertString(DCM_RequestedProcedureID, getRequestedProcedureID().toLatin1().data());

        requestedAttributeSequenceItem->putAndInsertString(DCM_ScheduledProcedureStepID, getScheduledProcedureStepID().toLatin1().data());

        requestedAttributeSequence->insert(requestedAttributeSequenceItem);
        maskDcmDataset->insert(requestedAttributeSequence, OFTrue);
    }

    if (!getPPSStartDate().isNull())
    {
        DcmElement *elem = newDicomElement(DCM_PerformedProcedureStepStartDate);
        elem->putString(qPrintable(getPPSStartDate()));
        maskDcmDataset->insert(elem , OFTrue);
    }

    if (!getPPSStartTime().isNull())
    {
        DcmElement *elem = newDicomElement(DCM_PerformedProcedureStepStartTime);
        elem->putString(qPrintable(getPPSStartTime()));
        maskDcmDataset->insert(elem , OFTrue);
    }

    if (!getSOPInstanceUID().isNull())
    {
        DcmElement *elem = newDicomElement(DCM_SOPInstanceUID);
        elem->putString(qPrintable(getSOPInstanceUID()));
        maskDcmDataset->insert(elem , OFTrue);
    }

    if (!getImageNumber().isNull())
    {
        DcmElement *elem = newDicomElement(DCM_InstanceNumber);
        elem->putString(qPrintable(getImageNumber()));
        maskDcmDataset->insert(elem , OFTrue);
    }

    return maskDcmDataset;
}

bool DicomMask::operator ==(const DicomMask &mask)
{
    if(   getStudyUID() == mask.getStudyUID()
        && getPatientId() == mask.getPatientId()
        && getPatientName() == mask.getPatientName()
        && getPatientBirth() == mask.getPatientBirth()
        && getPatientAge() == mask.getPatientAge()
        && getPatientSex() == mask.getPatientSex()
        && getStudyId() == mask.getStudyId()
        && getStudyDate() == mask.getStudyDate()
        && getStudyDescription() == mask.getStudyDescription()
        && getStudyModality() == mask.getStudyModality()
        && getStudyTime() == mask.getStudyTime()
        && getAccessionNumber() == mask.getAccessionNumber()
        && getReferringPhysiciansName() == mask.getReferringPhysiciansName()
        && getSeriesNumber() == mask.getSeriesNumber()
        && getSeriesDate() == mask.getSeriesDate()
        && getSeriesTime() == mask.getSeriesTime()
        && getSeriesDescription() == mask.getSeriesDescription()
        && getSeriesModality() == mask.getSeriesModality()
        && getSeriesProtocolName() == mask.getSeriesProtocolName()
        && getSeriesUID() == mask.getSeriesUID()
        && getRequestedProcedureID() == mask.getRequestedProcedureID()
        && getScheduledProcedureStepID() == mask.getScheduledProcedureStepID()
        && getPPSStartDate() == mask.getPPSStartDate()
        && getPPSStartTime() == mask.getPPSStartTime()
        && getImageNumber() == mask.getImageNumber()
        && getSOPInstanceUID() == mask.getSOPInstanceUID()
   )
        return true;
    else
        return false;
}

DicomMask DicomMask::operator +(const DicomMask &mask)
{
    DicomMask returnDicomMask = * this;

    /* L'operador + no fa que cerquem pels dos valors, sinó que per la màscara this, totes les seves propietats que siguin empties,
     * s'emplenaran amb el valor de la màscara passada per paràmetre
     */

    if (!mask.getPatientAge().isNull() && getPatientAge().isEmpty()) returnDicomMask.setPatientAge(mask.getPatientAge());
    if (!mask.getPatientBirth().isNull() && getPatientBirth().isEmpty()) returnDicomMask.setPatientBirth(mask.getPatientBirth());
    if (!mask.getPatientId().isNull() && getPatientId().isEmpty()) returnDicomMask.setPatientId(mask.getPatientId());
    if (!mask.getPatientName().isNull() && getPatientName().isEmpty()) returnDicomMask.setPatientName(mask.getPatientName());
    if (!mask.getPatientSex().isNull() && getPatientSex().isEmpty()) returnDicomMask.setPatientSex(mask.getPatientSex());

    if (!mask.getStudyId().isNull() && getStudyId().isEmpty()) returnDicomMask.setStudyId(mask.getStudyId());
    if (!mask.getStudyDate().isNull() && getStudyDate().isEmpty()) returnDicomMask.setStudyDate(mask.getStudyDate());
    if (!mask.getStudyDescription().isNull() && getStudyDescription().isEmpty()) returnDicomMask.setStudyDescription(mask.getStudyDescription());
    if (!mask.getStudyModality().isNull() && getStudyModality().isEmpty()) returnDicomMask.setStudyModality(mask.getStudyModality());
    if (!mask.getStudyTime().isNull() && getStudyTime().isEmpty()) returnDicomMask.setStudyTime(mask.getStudyTime());
    if (!mask.getStudyUID().isNull() && getStudyUID().isEmpty()) returnDicomMask.setStudyUID(mask.getStudyUID());
    if (!mask.getReferringPhysiciansName().isNull() && getReferringPhysiciansName().isEmpty()) returnDicomMask.setReferringPhysiciansName(mask.getReferringPhysiciansName());
    if (!mask.getAccessionNumber().isNull() && getAccessionNumber().isEmpty()) returnDicomMask.setAccessionNumber(mask.getAccessionNumber());

    if (!mask.getSeriesDate().isNull() &&getSeriesDate().isEmpty()) returnDicomMask.setSeriesDate(mask.getSeriesDate());
    if (!mask.getSeriesDescription().isNull() && getSeriesDescription().isEmpty()) returnDicomMask.setSeriesDescription(mask.getSeriesDescription());
    if (!mask.getSeriesModality().isNull() && getSeriesModality().isEmpty()) returnDicomMask.setSeriesModality(mask.getSeriesModality());
    if (!mask.getSeriesNumber().isNull() && getSeriesNumber().isEmpty()) returnDicomMask.setSeriesNumber(mask.getSeriesNumber());
    if (!mask.getSeriesProtocolName().isNull() && getSeriesProtocolName().isEmpty()) returnDicomMask.setSeriesProtocolName(mask.getSeriesProtocolName());
    if (!mask.getSeriesTime().isNull() && getSeriesTime().isEmpty()) returnDicomMask.setSeriesTime(mask.getSeriesTime());
    if (!mask.getSeriesUID().isNull() && getSeriesUID().isEmpty()) returnDicomMask.setSeriesUID(mask.getSeriesUID());
    if (!mask.getRequestedProcedureID().isNull() && getRequestedProcedureID().isEmpty() &&
        !mask.getScheduledProcedureStepID().isNull() && getScheduledProcedureStepID().isEmpty()) 
    {
        returnDicomMask.setRequestAttributeSequence(mask.getRequestedProcedureID(), mask.getScheduledProcedureStepID());
    }

    if (!mask.getPPSStartDate().isNull() && getPPSStartDate().isEmpty()) returnDicomMask.setPPSStartDate(mask.getPPSStartDate());
    if (!mask.getPPSStartTime().isNull() && getPPSStartTime().isEmpty()) returnDicomMask.setPPStartTime(mask.getPPSStartTime());

    if (!mask.getSOPInstanceUID().isNull() && getSOPInstanceUID().isEmpty()) returnDicomMask.setSOPInstanceUID(mask.getScheduledProcedureStepID());
    if (!mask.getImageNumber().isNull() && getImageNumber().isEmpty()) returnDicomMask.setImageNumber(mask.getImageNumber());

    return returnDicomMask;

}

bool DicomMask::isAHeavyQuery()
{
    //en aquest QStringList hi posarem els noms. cognoms i strings que són potencialment candidats a donar cerques pesades
    QStringList heavyWords;
    
    //\TODO per fer-ho correctament aquest "diccionari" de paraules candidates a fer cerques pesades hauria d'estar en un fitxer, de manera que l'usuari no hagi de manipular codi per afegir un nou terme.
//     heavyWords << "joan" << "juan" << "josep" << "jose" << "ana" << "antoni" << "antonio" << "garcia" << "ez";
    
    bool longPeriod = false;
    
    QString studyDate = getStudyDate();
    QString patientName = getPatientName();
    
    /// Condicions que determinen si una query és pesada:
    /// SENSE DATA D'ESTUDI ESPECIFICADA (ANY DATE)
    bool anyDate = studyDate.length() == 0;
    
    /// SENSE ESPECIFICAR NOM
    bool noName = patientName == "*";
        
    /// SENSE ID DE PACIENT
    bool noID = getPatientId() == "*";
    
    /// PERÍODE RELATIVAMENT LLARG 
    if (studyDate.length() > 8)
    {
        QDateTime begin(QDate(studyDate.mid(0, 4).toInt(), studyDate.mid(4, 2).toInt(), studyDate.mid(6, 2).toInt()));
        QDateTime end(QDate(studyDate.mid(10, 4).toInt(), studyDate.mid(14, 2).toInt(), studyDate.mid(16, 2).toInt()));
        
        //consederem com a període llarg a partir d'una setmana
        longPeriod = end.daysTo(begin) > 7;
    }

    ///NOM CURT
    QString nameWithoutAst =  patientName.remove(QChar('*'));
    bool shortName = (nameWithoutAst.length() < 4);
    
    //EL NOM ÉS UN STRING DELS DETERMINATS COM A PESATS A L'INICI DEL MÈTODE
    //no ho tenim en compte perquè en un hospital seran uns noms i en un altre hospital seran uns altres
    //bool heavyName = singleWordAsName && heavyWords.contains (nameWithoutAst, Qt::CaseInsensitive); 
    
    ///EL NÚMERO D'ESTUDI ÉS CURT
    QString idWithoutAst =  getPatientId().remove(QChar('*'));
    bool shortID = idWithoutAst.length() < 3;
    
    //Construïm les condicions que fan que una query pugui ser pesada
    bool noIDOrName = (noName && noID) || (shortName && shortID);
    
    bool heavyMask =  (anyDate  && noIDOrName) || (longPeriod && noIDOrName);
    
    return heavyMask;
}

QString DicomMask::getQueryRetrieveLevel()
{
    bool isImageLevel = !getSOPInstanceUID().isNull() || !getImageNumber().isNull();
    bool isSeriesLevel = !getSeriesDescription().isNull()  || !getSeriesDate().isNull() || !getSeriesModality().isNull() ||
                         !getSeriesNumber().isNull() || !getSeriesProtocolName().isNull() || !getSeriesTime().isNull() ||
                         !getSeriesUID().isNull() || !getRequestedProcedureID().isNull() || !getScheduledProcedureStepID().isNull() ||
                         !getPPSStartDate().isNull() || !getPPSStartTime().isNull();

    if (isImageLevel)
    {
        return "IMAGE";
    }
    else if (isSeriesLevel)
    {
        return "SERIES";
    }
    else return "STUDY"; //PER DEFECTE DEL DICOM COM A MÍNIM SON A NIVELL D'ESTUDI
}

QString DicomMask::getFilledMaskFields() const
{
    QString maskFields;
    
    if( !QString(m_patientId).remove("*").isEmpty() )
        maskFields += "Patient_ID=[#*#] ";
    if( !QString(m_patientName).remove("*").isEmpty() )
        maskFields += "Patient_Name=[#*#] ";
    if( !QString(m_patientBirth).remove("*").isEmpty() )
        maskFields += "Patient_Birth=[#*#] ";
    if( !QString(m_patientSex).remove("*").isEmpty() )
        maskFields += "Patient_Sex=[" + m_patientSex + "] ";
    if( !QString(m_patientAge).remove("*").isEmpty() )
        maskFields += "Patient_Age=[" + m_patientAge + "] ";
    if( !QString(m_studyId).remove("*").isEmpty() )
        maskFields += "Study_ID=[#*#] ";
    if( !QString(m_studyDate).remove("*").isEmpty() )
        maskFields += "Study_Date=[" + m_studyDate + "] ";
    if( !QString(m_studyTime).remove("*").isEmpty() )
        maskFields += "Study_Time=[" + m_studyTime + "] ";
    if( !QString(m_studyDescription).remove("*").isEmpty() )
        maskFields += "Study_Description=[" + m_studyDescription + "] ";
    if( !QString(m_studyModality).remove("*").isEmpty() )
        maskFields += "Study_Modality=[" + m_studyModality + "] ";
    if( !QString(m_studyUID).remove("*").isEmpty() )
        maskFields += "Study_UID=[#*#] ";
    if( !QString(m_accessionNumber).remove("*").isEmpty() )
        maskFields += "Accession_Number=[#*#] ";
    if( !QString(m_referringPhysiciansName).remove("*").isEmpty() )
        maskFields += "Referring_PhysiciansName=[#*#] ";
    if( !QString(m_seriesNumber).remove("*").isEmpty() )
        maskFields += "Series_Number=[#*#] ";
    if( !QString(m_seriesDate).remove("*").isEmpty() )
        maskFields += "Series_Date=[" + m_seriesDate + "] ";
    if( !QString(m_seriesTime).remove("*").isEmpty() )
        maskFields += "Series_Time=[" + m_seriesTime + "] ";
    if( !QString(m_seriesModality).remove("*").isEmpty() )
        maskFields += "Series_Modality=[" + m_seriesModality + "] ";
    if( !QString(m_seriesDescription).remove("*").isEmpty() )
        maskFields += "Series_Description=[" + m_seriesDescription + "] ";
    if( !QString(m_seriesProtocolName).remove("*").isEmpty() )
        maskFields += "Series_Protocol_Name=[" + m_seriesProtocolName + "] ";
    if( !QString(m_seriesUID).remove("*").isEmpty() )
        maskFields += "Series_UID=[#*#] ";
    if( !QString(m_requestedProcedureID).remove("*").isEmpty() )
        maskFields += "Requested_Procedure_ID=[#*#] ";
    if( !QString(m_scheduledProcedureStepID).remove("*").isEmpty() )
        maskFields += "Scheduled_Procedure_Step_ID=[#*#] ";
    if( !QString(m_PPSStartDate).remove("*").isEmpty() )
        maskFields += "PPS_Start_Date=[#*#] ";
    if( !QString(m_PPSStartTime).remove("*").isEmpty() )
        maskFields += "PPS_Start_Time=[#*#] ";
    if( !QString(m_SOPInstanceUID).remove("*").isEmpty() )
        maskFields += "SOP_Instance_UID=[#*#] ";
    if( !QString(m_imageNumber).remove("*").isEmpty() )
        maskFields += "Image_Number=[" + m_imageNumber + "] ";

    return maskFields;
}

};

