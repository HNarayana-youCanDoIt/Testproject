!include(PhoneConnectionManagerResource/PhoneConnectionManagerResource.pri){
    error("Could not load PhoneConnectionManagerResource");
}

!include(PhoneCallManagerResource/PhoneCallManagerResource.pri){
    error("Could not load PhoneCallManagerResource");
}

!include(PhonePIMDBResource/PhonePIMDBResource.pri){
    error("Could not load PhonePIMDBResource");
}

!include(BtPluginResource/BtPluginResource.pri){
    error("Could not load BtPluginResource");
}

INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/CPhoneResourceData.h \
    $$PWD/CPhoneResourceEnums.h
