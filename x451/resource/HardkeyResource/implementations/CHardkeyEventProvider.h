/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CHardkeyEventProvider.h
* @ingroup      HMIComponent
* @author       Prashantkumar Raut
* CHardkeyEventProvider, Class to send signals to HardkeyHandler on KeyPress Resource events
*/
#ifndef CHARDKEYEVENTPROVIDER_H
#define CHARDKEYEVENTPROVIDER_H

#include <QObject>
#include "implementations/CHardkeyEnums.h"

class CHardkeyEventProvider: public QObject
{
    Q_OBJECT

public:
    CHardkeyEventProvider(QObject* parent = 0);
    ~CHardkeyEventProvider();

signals:
    /**
     * Define the various signals in this section
     */

    /**
     * @brief sigHardKeyEvent All events (hardkey, VR etc) received from the below layers need to propagated
     *  to the upper layers. This would be done via Qt signals.
     * @param eKey - keycode of the hard key pressed.
     * @param eState State of the key
     * @return void
     */
    void sigHardKeyEvent(EHardKeys eKey,EHardKeyState eState);

public:
     /**
     * @brief Method called from CMediaResourceImpl to emit sigNowPlayingDataUpdateEvent
     * @param ekey - key code received from keyPress
     * @param eState - key state received from keyPress
     * @return void
     */
    void onKeyEvent( EHardKeys eKey,EHardKeyState eState );

};

#endif // CHARDKEYEVENTPROVIDER_H
