#ifndef RESOURCEFACTORY_HPP
#define RESOURCEFACTORY_HPP

#include "HardkeyResource/interfaces/IHardkeyResource.h"
#include "Tuner/interfaces/ITunerResource.h"
#include "AudioResource/interfaces/IAudioResource.h"
#include "interfaces/IMediaResource.h"
#include "EnggMenuResource/interfaces/IEnggMenuResource.h"
#include "SoftwareUpdateResource/interfaces/ISoftwareUpdateResource.h"
#include "PowerModeResource/interfaces/IPowerModeResource.h"
#include "HVACResource/interfaces/IHVACResource.h"
#include "VehicleResource/interfaces/IVehicleResource.h"
#include "ParkAssistResource/interfaces/IParkAssistResource.h"
#include "DateAndTimeResource/interfaces/IDateAndTimeResource.h"
#include "VoiceAlerts/interfaces/IVoiceAlerts.h"
#include "VersionManagerResource/interfaces/IVersionManagerResource.h"
#include "VRStubResource/CVRStubResource.h"
#include "DiagnosticResource/interfaces/IDiagnosticResource.h"
#include "IntrospectionStubResource/CIntrospectionStubResource.h"
#include "ICCastResource/interfaces/IICCastResource.h"

//! @category FORWARD DECLERATIONS
class ITunerResource;
class IPhoneConnectionManagerResource;
class IPhonePIMDBResource;
class IPhoneConnectionManagerResource;
class IDeviceModeHandlerResource;
class IAndroidAutoResource;
class IDisplayManagerResource;
class IPhoneCallManagerResource;
class IAppleCarPlayResource;
class IPhonePIMDBResource;
class IVersionManagerResource;
class IBtPluginResource;
class IDiagnosticResource;
class ILayerManagerResource;
class IVRProxyResource;
class IVariantControlResource;
class IHardkeyResource;
class IMediaResource;
class IEnggMenuResource;
class ISoftwareUpdateResource;
class IPowerModeResource;
class IHVACResource;
class IAudioResource;
class IVehicleResource;
class IParkAssistResource;
class IDateAndTimeResource;
class IVoiceAlerts;
class CIntrospectionStubResource;
class CVRStubResource;
class IRCAResource;
class IICCastResource;
class IDriveNextResource;
class IW3WResource;
class IDoodleResource;

class ResourceFactory
{
public :

    /**
    * @brief	This function will initialize tuner resource.
    * @param	void
    * @return	void
    */
    static void initTunerResource();

    /**
    * @brief	This function will return audio resource object.
    * @param	void
    * @return	void
    */
    static ITunerResource* getTunerResource();

    /**
     * @brief Method to deallocate the memory created for CTunerResourceImpl class instance
     * @param void
     * @return void
     */
    static void deleteTunerRsource();

    /**
    * @brief	This function will initialize audio resource.
    * @param	void
    * @return	void
    */
    static void initAudioResource();

    /**
    * @brief	This function will return audio resource object.
    * @param	void.
    * @return	void
    */
    static IAudioResource* getAudioResource();

    /**
     * @brief Method to deallocate the memory created for CAudioResourceImpl class instance
     * @param void
     * @return void
     */
    static void deleteAudioRsource();

    /**
     * @brief Method to initialize Media Resource Object
     * @param void
     * @return void
     */
    static void initMediaResource();

    /**
     * @brief Method to deallocate the memory created for CMediaResourceImple class instance
     * @param void
     * @return void
     */
    static void deleteMediaResource();

    /**
     * @brief Method to return Media Resource Object
     * @param void
     * @return void
     */
    static IMediaResource* getMediaResource();

    /**
     * @brief Method to initialize HardKey Resource Object
     * @param void
     * @return void
     */
    static void initHardkeyResource();

    /**
     * @brief Method to return Hardkey Resource Object
     * @param void
     * @return void
     */
    static IHardkeyResource *getHardkeyResource();

    /**
     * @brief Method to deallocate the memory created for CHardKeyResourceImpl class instance
     * @param void
     * @return void
     */
    static void deleteHardkeyResource();

    /*!
     * @brief   Method to create instance of CPhoneConnectionManagerResourceImpl class.
     * @param   void.
     * @return  void.
     */
    static void initPhoneConnectionManagerResource();

    /*!
     * @brief   Method to deallocate the memory created for CPhoneConnectionManagerResourceImpl class instance.
     * @param   void.
     * @return  void.
     */
    static void disposePhoneConnectionManagerResource();

    /*!
     * @brief   Method to get the instance of CPhoneConnectionManagerResourceImpl class.
     * @param   void.
     * @return  pointer to the object of CPhoneConnectionManagerResourceImpl class.
     */
    static IPhoneConnectionManagerResource* getPhoneConnectionManagerResource();

    /*!
     * @brief   Method to create instance of CDeviceModeHandlerResourceImpl class.
     * @param   void.
     * @return  void.
     */
    static void initDeviceModeHandlerResource();

    /*!
     * @brief   Method to deallocate the memory created for CDeviceModeHandlerResourceImpl class instance.
     * @param   void.
     * @return  void.
     */
    static void disposeDeviceModeHandlerResource();

    /*!
     * @brief   Method to get the instance of CDeviceModeHandlerResourceImpl class.
     * @param   void.
     * @return  pointer to the object of CDeviceModeHandlerResourceImpl class.
     */
    static IDeviceModeHandlerResource* getDeviceModeHandlerResource();

    /*!
     * @brief   Method to create instance of CAndroidAutoResourceImpl class.
     * @param   void.
     * @return  void.
     */
    static void initAndroidAutoResource();

    /*!
     * @brief   Method to deallocate the memory created for
     *          CAndroidAutoResourceImpl class instance.
     * @param   void.
     * @return  void.
     */
    static void deleteAndroidAutoResource();

    /*!
     * @brief   Method to get the instance of CAndroidAutoResourceImpl class.
     * @param   void.
     * @return  pointer to the object of CAndroidAutoResourceImpl class.
     */
    static IAndroidAutoResource* getAndroidAutoResource();

    /*!
     * @brief   Method to create instance of CPhoneCallManagerResourceImpl class.
     * @param   void.
     * @return  void.
     */
    static void initPhoneCallManagerResource();

    /*!
     * @brief   Method to deallocate the memory created for CPhoneCallManagerResourceImpl class instance.
     * @param   void.
     * @return  void.
     */
    static void disposePhoneCallManagerResource();

    /*!
     * @brief   Method to get the instance of CPhoneCallManagerResourceImpl class.
     * @param   void.
     * @return  pointer to the object of CPhoneCallManagerResourceImpl class.
     */
    static IPhoneCallManagerResource* getPhoneCallManagerResource();

    /*!
     * @brief   Method to create instance of CPhonePIMDBResourceImpl class.
     * @param   void.
     * @return  void.
     */
    static void initPhonePIMDBResource();

    /*!
     * @brief   Method to deallocate the memory created for CPhonePIMDBResourceImpl class instance.
     * @param   void.
     * @return  void.
     */
    static void disposePhonePIMDBResource();

    /*!
     * @brief   Method to get the instance of CPhonePIMDBResourceImpl class.
     * @param   void.
     * @return  pointer to the object of CPhonePIMDBResourceImpl class.
     */
    static IPhonePIMDBResource *getPhonePIMDBResource();

    /**
    * @brief	This function will initialize EnggMenu resource.
    * @param	IEnggMenuResource.
    * @return	void
    */
    static void initEnggMenuResource();

    /**
    * @brief	This function will return EnggMenu resource object.
    * @param	void.
    * @return	void
    */
    static IEnggMenuResource* getEnggMenuResource();

    /*!
     * @brief   Method to deallocate the memory created for CEnggMenuResourceImpl class instance.
     * @param   void.
     * @return  void.
     */
    static void deleteEnggMenuResource();

    /**
     * @brief Method to initialize Software Update Resource Object
     * @param void
     * @return void
     */
    static void initSoftwareUpdateResource();
    /**
     * @brief Method to deallocate the memory created for CSoftwareUpdateResourceImple class instance
     * @param void
     * @return void
     */
    static void deleteSoftwareUpdateResource();
    /**
     * @brief Method to return Software Update Resource Object
     * @param void
     * @return void
     */
    static ISoftwareUpdateResource* getSoftwareUpdateResource();

    /**
     * @brief Method to initialize powerMode Resource Object
     * @param void
     * @return void
     */
    static void initPowerModeResource();

    /**
     * @brief Method to return powerMode Resource Object
     * @param void
     * @return void
     */
    static IPowerModeResource* getPowerModeResource();

    /**
     * @brief Method to deallocate the memmory allocated for powerMode Resource Object
     * @param void
     * @return void
     */
    static void deletePowerModeResource();

    /**
     * @brief Method to initialize HVAC (ccmHu) Resource Object
     * @param void
     * @return void
     */
    static void initHVACResource();

    /**
     * @brief Method to deallocate the memory created for CHVACResourceImpl class instance
     * @param void
     * @return void
     */
    static void deleteHVACResource();
    /**
     * @brief Method to get HVAC Resource Object
     * @param void
     * @return IHVACResource: pointer to the HVAC resource implementation
     */
    static IHVACResource* getHVACResource();

    /**
     * @brief Method to initialize Display Manager Resource Object
     * @param void
     * @return void
     */
    static void initDisplayManagerResource();

    /**
     * @brief Method to deallocate the memory created for
     *        CDisplayManagerResourceImpl class instance.
     * @param void
     * @return void
     */
    static void deleteDisplayManagerResource();

    /**
     * @brief Method to get DisplayManager Resource Object
     * @param void
     * @return IDisplayManagerResource: pointer to the DisplayManager
     *         resource implementation
     */
    static IDisplayManagerResource* getDisplayManagerResource();

    /*!
     * @brief   Method to create instance of CAppleCarPlayResourceImpl class.
     * @param   void.
     * @return  void.
     */
    static void initAppleCarPlayResource();

    /*!
     * @brief   Method to deallocate the memory created for
     *          CAppleCarPlayResourceImpl class instance.
     * @param   void.
     * @return  void.
     */
    static void deleteAppleCarPlayResource();

    /*!
     * @brief   Method to get the instance of CAppleCarPlayResourceImpl class.
     * @param   void.
     * @return  pointer to the object of CAppleCarPlayResourceImpl class.
     */
    static IAppleCarPlayResource* getAppleCarPlayResource();

    /**
    * @brief	This function will initialize Vehicle menu resource.
    * @param	void
    * @return	void
    */
    static void initVehicleResource();

    /**
    * @brief	This function will return vehicle resource object.
    * @param	void.
    * @return	void
    */
    static IVehicleResource* getVehicleResource();

    /**
     * @brief Method to deallocate the memory created for
     *        CVehicleResourceImpl class instance.
     * @param void
     * @return void
     */
    static void deleteVehicleResource();

    /**
    * @brief	This function will initialize Park Assist menu resource.
    * @param	void
    * @return	void
    */
    static void initParkAssistResource( );

    /**
    * @brief	This function will return Park Assist resource object.
    * @param	void.
    * @return	void
    */
    static IParkAssistResource* getParkAssistResource();

    /**
     * @brief Method to deallocate the memory created for
     *        CParkAssistResourceImpl class instance.
     * @param void
     * @return void
     */
    static void deleteParkAssistResource();

    /**
     * @brief	This function will initialize Time manager resource.
     * @param	void.
     * @return	void
     */
    static void initDateAndTimeResource();

    /**
     * @brief Method to deallocate the memory created for CDateAndTimeResourceImpl class instance
     * @param void
     * @return void
     */
    static void deleteDateAndTimeResource();

    /**
    * @brief	This function will return Date And Time resource object.
    * @param	void.
    * @return	IDateAndTimeResource , pointer of DateAndTimeResource
    */
    static IDateAndTimeResource *getDateAndTimeResource();

    /*!
     * @brief   Method to create instance of CIntrospectionStubResource class.
     * @param   void.
     * @return  void.
     */
    static void initIntrospectionStubResource();

    /*!
     * @brief   Method to deallocate the memory created for CIntrospectionStubResource class instance.
     * @param   void.
     * @return  void.
     */
    static void disposeIntrospectionStubResource();

    /*!
     * @brief   Method to get the instance of CIntrospectionStubResource class.
     * @param   void.
     * @return  pointer to the object of CIntrospectionStubResource class.
     */
    static CIntrospectionStubResource *getIntrospectionStubResource();

    /**
     * @brief initVoiceAlertsResource Method to initialize resource class for
     * voice alerts
     * @param void.
     * @return void.
     */
    static void initVoiceAlertsResource();

    /**
     * @brief disposeVoiceAlertsResource- Delete voice alert resource
     * @param void.
     * @return void.
     */
    static void disposeVoiceAlertsResource();

    /**
     * @brief getVoiceAlertResource Method to get the instance of voice alerts resource
     * @param void.
     * @return pointer to voice alerts resource implementation class
     */
    static IVoiceAlerts *getVoiceAlertResource();

    /**
     * @brief	initVersionManagerResource: This function will initialize Version Manager resource.
     *  @param	void
     *  @return	void
     */
    static void initVersionManagerResource();

    /**
     * @brief  deleteVersionManagerResource: Method to deallocate the memory created for CVersionManagerResourceImpl class instance
     * @param  void
     * @return void
     */
    static void deleteVersionManagerResource();

    /**
    * @brief  getVersionManagerResource: This function will return Version Manager resource object.
    * @param  void.
    * @return IVersionManagerResource: pointer of IVersionManagerResource
    */
    static IVersionManagerResource *getVersionManagerResource();

    /*!
     * @brief   Method to create instance of CVRStubResource class.
     * @param   void.
     * @return  void.
     */
    static void initVRStubResource();

    /*!
     * @brief   Method to deallocate the memory created for CVRStubResource class instance.
     * @param   void.
     * @return  void.
     */
    static void disposeVRStubResource();

    /*!
     * @brief   Method to get the instance of CVRStubResource class.
     * @param   void.
     * @return  pointer to the object of CVRStubResource class.
     */
    static CVRStubResource *getVRStubResource();

    /*!
     * @brief   Method to create instance of CBtPluginResourceImpl class.
     * @param   void.
     * @return  void.
     */
    static void initBtPluginResource();

    /*!
     * @brief   Method to deallocate the memory created for CBtPluginResourceImpl class instance.
     * @param   void.
     * @return  void.
     */
    static void disposeBtPluginResource();

    /*!
     * @brief   Method to get the instance of CBtPluginResourceImpl class.
     * @param   void.
     * @return  pointer to the object of CBtPluginResourceImpl class.
     */
    static IBtPluginResource *getBtPluginResource();

    /*! @brief	initDiagnosticResource: This function will initialize Diagnostic resource.
     *  @param	void
     *  @return	void
     */
    static void initDiagnosticResource();

    /*!
     * @brief  deleteDiagnosticResource: Method to deallocate the memory created for CDiagnosticResourceImpl class instance
     * @param  void
     * @return void
     */
    static void deleteDiagnosticResource();

    /**
    * @brief  IDiagnosticResource: This function will return Diagnostic resource object.
    * @param  void.
    * @return IDiagnosticResource, pointer of IDiagnosticResource.
    */
    static IDiagnosticResource *getDiagnosticResource();

    /**
     * @brief Method to initialize layer manager Resource Object
     * @param void
     * @return void
     */
    static void initLayerManagerResource();
    /**
     * @brief Method to deallocate the memory created for CLayerManagerResourceImpl class instance
     * @param void
     * @return void
     */
    static void deleteLayerManagerResource();
    /**
     * @brief Method to get layer manager Resource Object
     * @param void
     * @return ILayerManagerResource: pointer to the Layer manager resource implementation
     */
    static ILayerManagerResource* getLayerManagerResource();

    /**
     * @brief initRCAResource, Method to initialize RCA Resource Object
     * @param void
     * @return void
     */
    static void initRCAResource();

    /**
     * @brief deleteRCAResource, Method to deallocate the memory created for CRCAResourceImpl class instance
     * @param void
     * @return void
     */
    static void deleteRCAResource();

    /**
     * @brief getRCAResource, Method to get RCA Resource Object
     * @param void
     * @return IRCAResource: pointer to the RCA resource object
     */
    static IRCAResource* getRCAResource();

    /**
     * @brief initICCastResource, Method to initialize ICCast Resource Object
     * @param void
     * @return void
     */
    static void initICCastResource();

    /**
     * @brief deleteICCastResource, Method to deallocate the memory created for CICCastResourceImpl class instance
     * @param void
     * @return void
     */
    static void deleteICCastResource();

    /**
     * @brief getICCastResource, Method to get ICCast Resource Object
     * @param void
     * @return IICCastResource: pointer to the ICCast resource object
     */
    static IICCastResource *getICCastResource();

    /**
     * @brief initDriveNextResource, Method to initialize DriveNext Resource Object
     * @param void
     * @return void
     */
    static void initDriveNextResource();

    /**
     * @brief deleteDriveNextResource, Method to deallocate the memory created for CDriveNextResourceImpl class instance
     * @param void
     * @return void
     */
    static void deleteDriveNextResource();

    /**
     * @brief getDriveNextResource, Method to get DriveNext Resource Object
     * @param void
     * @return CDriveNextResourceImpl: pointer to the DriveNext resource object
     */
    static IDriveNextResource *getDriveNextResource();

    /*!
     * @brief   initVRProxyResource: Method to create instance of CVRProxyResImpl class.
     * @param   void.
     * @return  void.
     */
    static void initVRProxyResource();

    /*!
     * @brief   disposeVRProxyResource: Method to deallocate the memory created for CVRProxyResImpl class instance.
     * @param   void.
     * @return  void.
     */
    static void disposeVRProxyResource();

    /*!
     * @brief   getVRProxyResource: Method to get the instance of CVRProxyResImpl class.
     * @param   void.
     * @return  pointer to the object of CVRProxyResImpl class.
     */
    static IVRProxyResource *getVRProxyResource();

    /**
     * @brief initVariantControlResource: Method to initialize Variant Control Resource Object
     * @param void
     * @return void
     */
    static void initVariantControlResource();
    /**
     * @brief deleteVariantControlResource: Method to deallocate the memory created for CVariantControlResourceImpl class instance
     * @param void
     * @return void
     */
    static void deleteVariantControlResource();
    /**
     * @brief getVariantControlResource: Method to get Variant Control Resource Object
     * @param void
     * @return IVariantControlResource: pointer to the Variant Control resource implementation
     */
    static IVariantControlResource* getVariantControlResource();

    /**
     * @brief initW3WResource, Method to initialize W3W Resource Object
     * @param void
     * @return void
     */
    static void initW3WResource();

    /**
     * @brief deleteW3WResource, Method to deallocate the memory created for CW3WResourceImpl class instance
     * @param void
     * @return void
     */
    static void deleteW3WResource();

    /**
     * @brief getW3WResource, Method to get W3W Resource Object
     * @param void
     * @return IW3WResource: pointer to the W3W resource object
     */
    static IW3WResource *getW3WResource();

    /**
     * @brief initDoodleResource, Method to initialize Doodle Resource Object
     * @param void
     * @return void
     */
    static void initDoodleResource();

    /**
     * @brief deleteDoodleResource, Method to deallocate the memory created for CDoodleResourceImpl class instance
     * @param void
     * @return void
     */
    static void deleteDoodleResource();

    /**
     * @brief getDoodleResource, Method to get Doodle Resource Object
     * @param void
     * @return CDoodleResourceImpl: pointer to the Doodle resource object
     */
    static IDoodleResource *getDoodleResource();

private :
    ResourceFactory();

    static IAudioResource*          m_pAudioResource;
    /**
     * Pointer to Media Resource object
     */
    static IMediaResource*          m_pMediaResource;
    static ITunerResource*          m_pTuner;
    static ISoftwareUpdateResource* m_pSoftwareUpdateResource;
    static IHardkeyResource*        m_pHardkeyResource;
    static IEnggMenuResource*       m_pEnggMenuResource;
    static IVehicleResource*        m_pVehicleResource;
    static IParkAssistResource*     m_pParkAssistResource;

    /*!
     * @brief Pointer of IPhoneConnectionManagerResource class to create instance
     * of CPhoneConnectionManagerResourceImpl class.
     */
    static IPhoneConnectionManagerResource* m_pPhoneConnectionManagerResource;

    /*!
     * @brief Pointer of IDeviceModeHandlerResource class to create instance
     * of IDeviceModeHandlerResourceImpl class.
     */
    static IDeviceModeHandlerResource* m_pDeviceModeHandlerResource;

    /*!
     * @brief Pointer of IAndroidAutoResource class to create instance
     * of CAndroidAutoResourceImpl class.
     */
    static IAndroidAutoResource* m_pAndroidAutoResource;

    /*!
     * @brief Pointer of IPhoneCallManagerResource class to create instance
     * of CPhoneCallManagerResourceImpl class.
     */
    static IPhoneCallManagerResource* m_pPhoneCallManagerResource;

    /**
     * Pointer of IPhonePIMDBResource class to create instance of CPhonePIMDBrResourceImpl class.
     */
    static IPhonePIMDBResource* m_pPhonePimDbResource;

    /**
     * Pointer of IPowerModeResource class to create instance of CPowerModeResourceImpl class.
     */
    static IPowerModeResource*      m_pPowerModeResource;

    /**
      * Pointer to the HVAC (ccmHu) resource object
      */
    static IHVACResource*           m_pHVACResource;

    /**
      * Pointer to the DisplayManage resource object
      */
    static IDisplayManagerResource*           m_pDisplayManagerResource;

    /**
     * @brief Pointer of IAppleCarPlayResource class to create instance
     * of CAppleCarPlayResourceImpl class.
     */
    static IAppleCarPlayResource* m_pAppleCarPlayResource;

    /*!
     * @brief Pointer of IDateAndTimeResource class to create instance
     * of CDateAndTimeResourceImpl class.
     */
    static IDateAndTimeResource*    m_pDateAndTimeResource;

    /*!
     * @brief static object of CIntrospectionStubResource class
     */
    static CIntrospectionStubResource*  m_pIntrospectionStubResource;

    /**
     * @brief m_pVoiceAlertsResource static object of voice alert reosurce used
     * to initialize voice alerts resource layer implementation.
     */
    static IVoiceAlerts* m_pVoiceAlertsResource;
    /**
     * @brief m_pVersionManagerResource: Pointer of IVersionManagerResource class to create instance
     * of CVersionManagerResourceImpl class.
     */
    static IVersionManagerResource* m_pVersionManagerResource;

    /*!
     * @brief static pointer of CVRStubResource type to create instance of CVRStubResource class.
     */
    static CVRStubResource*     m_pVRStubResource;

    /*!
     * @brief static pointer of IBtPluginResource type to create instance of CBtPluginResourceImpl class.
     */
    static IBtPluginResource*   m_pBtPluginResource;

    /**
     * @brief Pointer of IDiagnosticResource class to create instance
     * of CDiagnosticResourceImpl class.
     */
    static IDiagnosticResource* m_pDiagnosticResource;

    /**
     * @brief m_pLayerManagerResource: Pointer to the layer manager resource object
     */
    static ILayerManagerResource*           m_pLayerManagerResource;


    /**
     * @brief m_pVariantControlResource: Pointer of IVariantControlResource class to create instance
     * of CVariantControlResourceImpl class.
     */
    static IVariantControlResource* m_pVariantControlResource;
    /*!
     * @brief static pointer of IVRProxyResource type to create instance of CVRProxyResImpl class.
     */
    static IVRProxyResource*    m_pVRProxyResource;

    /**
     * @brief m_pRCAResource Pointer to the RCA resource object
     */
    static IRCAResource*           m_pRCAResource;

    /*!
     * @brief m_pICCastResource Pointer of IICCastResource class to create instance
     * of CICCastResourceImpl class.
     */
    static IICCastResource* m_pICCastResource;

    /*!
     * @brief m_pDriveNextResource Pointer of IDriveNextResource class to create instance
     * of CDriveNextResourceImpl class.
     */
    static IDriveNextResource* m_pDriveNextResource;

    /*!
     * @brief m_pW3WResource Pointer of IW3WResource class to create instance
     * of CW3WResourceImpl class.
     */
    static IW3WResource* m_pW3WResource;

    /*!
     * @brief m_pDoodleResource Pointer of IDoodleResource class to create instance
     * of CDoodleResourceImpl class.
     */
    static IDoodleResource* m_pDoodleResource;
};

#endif // RESOURCEFACTORY_HPP
