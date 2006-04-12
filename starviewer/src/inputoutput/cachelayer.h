/***************************************************************************
 *   Copyright (C) 2005 by Grup de Gr�fics de Girona                       *
 *   http://iiia.udg.es/GGG/index.html?langu=uk                            *
 *                                                                         *
 *   Universitat de Girona                                                 *
 ***************************************************************************/
#ifndef UDGCACHELAYER_H
#define UDGCACHELAYER_H

#include <QObject>
#include "status.h"

namespace udg {

/**     Aquesta classe afegeix un nivell d'abstracio sobre la classe CachePacs, permetent realitzar operacions sobre la cache, i utilitzar elements de la interfcie
	@author Grup de Gr�fics de Girona  ( GGG ) <vismed@ima.udg.es>
*/
class CacheLayer : public QObject
{


Q_OBJECT
public:
    /** Constructor de la classe
      */
    CacheLayer(QObject *parent = 0);
    
    /** Neteja la cache de l'aplicacio, Mostra un QProgressDialog amb el progress de la neteja
      */
    Status clearCache();
    
    /** Esborra els estudis vells que superen el temps maxim que poden estar a la cache especificats per a l'usuari
      */
    Status deleteOldStudies();
    
    /** Esborra els estudis vells, fins alliberar a la cache la quantitat d'espai en Mb passat per parametres. 
      * Aquest metode s'utilitzara quant al descarregar un estudi es detecti, que no hi ha suficient espai lliure a la cache o en el disc per descarregar un nou estudi. Invocant aquest metode allibararem l'espai passat per parametre
      *         @param nombre de Mb d'estudis vells a esborrar
      *         @return estat de l'operacio
      */
    Status deleteOldStudies(int MbytesToErase);
    
    /**Destructor de la classe
      */
    ~CacheLayer();

};

}

#endif
