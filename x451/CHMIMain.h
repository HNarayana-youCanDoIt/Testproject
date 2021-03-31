#ifndef CHMIMAIN_H
#define CHMIMAIN_H

#include "HMIIncludes.h"
#include <AudioResource/interfaces/IAudioResource.h>
#include <Tuner/interfaces/ITunerResource.h>
#include <HardkeyResource/interfaces/IHardkeyResource.h>
#include <EnggMenuResource/interfaces/IEnggMenuResource.h>
#include <VehicleResource/interfaces/IVehicleResource.h>
#include <ParkAssistResource/interfaces/IParkAssistResource.h>
#include <QObject>

class CHMIApplication;
class HBTimer;

class CHMIMain : public QObject
{
    Q_OBJECT
public :
    virtual ~CHMIMain();
    static void startHMIApp();
    static CHMIMain* getInstance();
    static TML_HMI_SM *getSM();

    /**
     * @brief getScreenWidth: Used to get Screen Width
     * @param void
     * @return int Screen Width.
     */
    int getScreenWidth();

    /**
     * @brief getScreenHeight: Used to get Screen Height
     * @param void
     * @return int Screen Height.
     */
    int getScreenHeight();

private:
    CHMIMain(QObject* pParent = nullptr);

    /**
     * @brief initResources - Loading resource layer module into application.
     * @param void
     * @return void
     */
    void initResources();

    /**
     * @brief registerQMLEnums
     */
    void registerQMLEnums();

    /**
     * @brief initWindow - Initialize qt window to render HMI Application.
     * @param void
     * @return void
     */
    void initWindow();


    CHMIApplication* m_pHMIApplication;
    static CHMIMain* _instance;
    static TML_HMI_SM* m_pStatemachine;
    bool m_bIsInitialStartup;
    /**
     * Instance of class TMLTimer
     */
    HBTimer* m_pTMLTimer;   
};

#endif // CHMIMAIN_H
