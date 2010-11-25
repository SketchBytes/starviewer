/***************************************************************************
 *   Copyright (C) 2005-2007 by Grup de Gràfics de Girona                  *
 *   http://iiia.udg.es/GGG/index.html?langu=uk                            *
 *                                                                         *
 *   Universitat de Girona                                                 *
 ***************************************************************************/

#ifndef UDGLISTENRISREQUEST_H
#define UDGLISTENRISREQUEST_H

#include <QObject>
#include <QThread>

#include "dicommask.h"

class QTcpServer;
class QTcpSocket;

namespace udg {

/** Classe que s'encarrega d'escolta per un port especificat a la configuració peticions d'un RIS i atendre les peticions d'aquests
 *
	@author Grup de Gràfics de Girona  ( GGG ) <vismed@ima.udg.es>
*/

class ListenRISRequestThread: public QThread
{
Q_OBJECT
public:

    enum ListenRISRequestThreadError { RisPortInUse, UnknownNetworkError };

    ListenRISRequestThread(QObject *parent = 0);
    ~ListenRISRequestThread();

    ///Inicia l'escolta de peticions del RIS a través del port que s'ha establet a la configuració
    void listen();

    ///Indica si s'estant escoltant peticions
    bool isListen();

signals:
    ///Signal que indica que s'ha fet una petició per descarregar un estudi
    void requestRetrieveStudy(DicomMask mask);
    
    ///Signal que s'emet indicant que s'ha produït un error escoltant peticions al RIS
    void errorListening(ListenRISRequestThread::ListenRISRequestThreadError );

private slots:
    void run();

private :
    /// Indiquem el temps d'espera (en mil·lisegons) per llegir la petició del RIS, sinó arriba en aquest temps fem time out
    static const int TimeOutToReadData;

    ///Processa la petició rebuda del RIS
    void processRequest(QString risRequestData);

    //Fa un signal del mètode error indicant el tipus d'error que s'ha produït
    void networkError(QTcpServer *tcpRISServer);
};

}

#endif