/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CHardkeyResourceImpl.h
* @ingroup      HMIComponent
* @author       Prashantkumar Raut
* CHardkeyResourceImpl, Resource Implementation for HardkeyHandler.
*/
#ifndef CHARDKEYRESOURCEIMPL_H
#define CHARDKEYRESOURCEIMPL_H

#include <memory>
#include "v1/com/harman/pres/keypresProxy.hpp"
#include "v0/com/harman/keypres/KeyPresPluginProxy.hpp"
#include <capi/CAPIClientAbstraction.hpp>

#include "interfaces/IHardkeyResource.h"
#include "CHardkeyEventProvider.h"

using namespace std;
using namespace v1::com::harman::pres;
using namespace v0::com::harman::keypres;
//Include the headers related to PresCtrl

/**
 * @brief The CHardkeyResourceImpl class.
 * This class implements the CHardkeyResourceImpl interface.
 */

class CHardkeyResourceImpl: public IHardkeyResource
{
private:
    const string KEY_PRESS;// "press"
    const string KEY_LONGPRESS;// "longpress"
    const string KEY_RELEASE;// "release"
    const string KEY_ROTATE_RIGHT; //"right"
    const string KEY_ROTATE_LEFT; //"leftt"
    const string KEY_STUCK; //"stuck"

public:

    virtual ~CHardkeyResourceImpl();


public:

    /**
     * @brief getHardkeyDataEventProvider method to return the instance of CHardkeyEventProvider
     * @param void
     * @return pointer to an instance of CHardkeyEventProvider
     */
    CHardkeyEventProvider* getHardkeyDataEventProvider();

    /**
     * @brief sendKeyCodeToKeyPresPluginProxy method used to send key code info to KeyPresPluginProxy
     * @param KeyPresPlugin::eKeyCodeId : key ID
     * @param KeyPresPlugin::eKeyState : key state
     * @param KeyPresPlugin::CallStatus : key call status
     * @return void
     */
    void sendKeyCodeToKeyPresPluginProxy(const KeyPresPlugin::eKeyCodeId _keyCode, const KeyPresPlugin::eKeyState _keystate, CommonAPI::CallStatus _internalCallStatus);

    /**
     * @brief sendSliderStateAsyncToKeyPresPluginProxy method used to send Slider State info to KeyPresPluginProxy
     * @param KeyPresPlugin::eKeyCodeId : key ID
     * @param KeyPresPlugin::eKeyState : key state
     * @param KeyPresPlugin::int : steps
     * @return void
     */
    void sendSliderStateAsyncToKeyPresPluginProxy(const KeyPresPlugin::eKeyCodeId _keyCode, const KeyPresPlugin::eKeyState _keystate, const int _steps);

     /*****  CALL BACK METHODS  ****************************/
private:
    /**
     * @brief Adding ResourceFactory class as friend class so that
     * ResourceFactory shall be able to create the instance of this class.
     */
    friend class ResourceFactory;

    CHardkeyResourceImpl();

    //Create an instance of the CHardkeyEventProvider to emit signals to the upper layer
    CHardkeyEventProvider* m_pHardkeyEventProvider;

    /**
     * @brief CallBack method to get notified about the availability status of keyPress Proxy
     * @param eStatus - status of keyPress proxy whether available or not
     * @return void
     */
    void keyPressServiceStatusCb( CommonAPI::AvailabilityStatus eStatus );

    /**
     * @brief Method to subscribe CallBack methods to events provided by keyPressProxy
     * @param void
     * @return void
     */
    void subscribe();

    /**
     * @brief CallBack Method to update the keyEvents
     * @param key - reference to structure which gives "key" details
     * @return void
     */
    void keyCtrlEventCb(const shared_ptr<keyprestypes::tKey>& key);

    /**
     * @brief CallBack Method for Slider State change response
     * @param status: callstatus holding the API call status
     * @param result: callResult holding the API call result
     * @return void
     */
    void sendSliderStateAsyncCb(const CommonAPI::CallStatus& eCallStatus, const KeyPresPlugin::eCallResult& eCallResult);


    /**
     * keypresProxy class object to access KeyPress functionalities
     */
    CAPIClientAbstraction<keypresProxy> m_objHardKeyProxy;

    /**
     * KeyPresPluginProxy class object to access KeyPressPlugin functionalities
     */
    CAPIClientAbstraction<KeyPresPluginProxy> m_objHardKeyPluginProxy;

    /**
     * @brief listLongPressedKeys to store the key code of keys that are currently long pressed.
     * This is required to handle multiple hard key releases.
     */
    list<int> m_listLongPressedKeys;
};

#endif // CHARDKEYRESOURCEIMPL_H
