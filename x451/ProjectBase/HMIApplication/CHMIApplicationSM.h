#ifndef CHMIAPPLICATIONSM_H
#define CHMIAPPLICATIONSM_H

#include "HMIIncludes.h"
#include "CHMIApplication.h"

class CHMIApplicationSM: public TML_HMI_SM::SCI_Ui_OCB
{
public:
    CHMIApplicationSM(CHMIApplication& parent);
    virtual ~CHMIApplicationSM();

    // SCI_Ui_OCB interface
public:
    void initHmi() override;
    void initUI() override;
    void initMediaOff() override;
    void initStartup() override;
    void initHome() override;
    void initMedia() override;
    void initTuner() override;
    void initSetup() override;
    void initPhone() override;
    void initEnggMenu() override;
    void initDrawers() override;
    void initAndroidAuto() override;
    void initCarPlay() override;
    void initSAL() override;
    void initSoftwareUpdate() override;
    void exitUI() override;

private:
    CHMIApplication& rHMIAppMain;
};

#endif // CHMIAPPLICATIONSM_H
