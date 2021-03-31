/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CHardkeyEventHandler.h
* @ingroup      HMIComponent
* @author       Prashantkumar Raut
* CHardkeyEventHandler, Class has the slots for all the Signals sent by CHardkeyEventProvider
*                         which informs Hardkey Adaptor about keyPress Resource Events
*/
#ifndef CHARDKEYEVENTHANDLER_H
#define CHARDKEYEVENTHANDLER_H

#include <QObject>
#include "implementations/CHardkeyEnums.h"

class CHardkeyAdaptor;

/**
 * @class CHardkeyEventHandler
 * @brief Class has the slots for all the Signals sent by CHardkeyEventProvider
 *        which informs Hardkey Adaptor about keyPress Resource Events
 */
class CHardkeyEventHandler: public QObject
{
    Q_OBJECT
public:
    CHardkeyEventHandler(QObject* parent = 0);
    ~CHardkeyEventHandler();

public slots:
    // Slots that would be invoked on the resource layer events signals
    /**
     * @brief Method to inform Hardkey Adaptor that hard key event is triggerred
     * @param eKey - Key code,
     * @param eState - current state of hard key key press / long press / release state
     * @return void
     */
    void sltHardKeyEvent(EHardKeys eKey,EHardKeyState eState);

private:

    // refrence to hardkey adaptor instance
    CHardkeyAdaptor& m_HardkeyAdaptor;

    /**
     * @brief Method to connect CHardkeyEventProvider signals to slots
     * @param void
     * @return void
     */
    void connectSignals();

    /**
     * @brief isRotary - to check if the hard key pressed is a rotary key or not.
     * Currently we are considering only rotary keys as of now.
     * @param eKeyCode - key code of the hard key.
     * @return true if hard key is a rotary hard key else false.
     */
    bool isRotary(EHardKeys eKeyCode);
};

#endif // CHARDKEYEVENTHANDLER_H
