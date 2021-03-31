/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         IHardkeyResource.h
* @ingroup      HMIComponent
* @author       Prashantkumar Raut
* IHardkeyResource, an interface for KeyPress Resource Implementaion in HMI for
* all the HardKeys and SWCKeys inputs.
*/

#ifndef HARDKEYRESOURCE_H
#define HARDKEYRESOURCE_H

#include <string>
#include <QString>
#include <QObject>
#include <QVariant>

///
/// \brief The IHardkeyResource class
/// This interfaces provides functionality which interacts with the KeyPress PresCtrl.
/// It also provides functionality via which data can be provided to the upper HMI UI layer.
/// It also propagates various events (Hard key, VR, etc) to the upper layers. This is done via Qt Signals
///

class IHardkeyResource
{

public:
    virtual ~IHardkeyResource(){}

    /*****  Request METHODS  ****************************/

    /*****  CALL BACK METHODS  ****************************/    
};

#endif // HARDKEYRESOURCE_H
