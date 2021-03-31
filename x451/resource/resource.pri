!include(Tuner/Tuner.pri){
    error("Could not load Tuner");
}

!include(capi/capi.pri){
    error("Could not load capi");
}

!include(AudioResource/AudioResource.pri){
    error("Could not load AudioResource");
}

!include(MediaResource/MediaResource.pri){
    error("Could not load MediaResource");
}

!include(HardkeyResource/HardkeyResource.pri){
    error("Could not load HardkeyResource");
}
!include(EnggMenuResource/EnggMenuResource.pri){
    error("Could not load EnggMenuResource");
}

!include(SoftwareUpdateResource/SoftwareUpdateResource.pri){
    error("Could not load SoftwareUpdateResource");
}

!include(ProjectionResource/ProjectionResource.pri){
    error("Could not load ProjectionResource");
}

!include(PowerModeResource/PowerModeResource.pri){
    error("Could not load PowerModeResource");
}

!include(HVACResource/HVACResource.pri){
    error("Could not load HVACResource");
}

!include(DisplayManagerResource/DisplayManagerResource.pri){
    error("Could not load DisplayManagerResource");
}

!include(PhoneResource/PhoneResource.pri){
    error("Could not load PhoneResource");
}

!include(VehicleResource/VehicleResource.pri){
    error("Could not load VehicleResource");
}

!include(ParkAssistResource/ParkAssistResource.pri){
    error("Could not load ParkAssistResource");
}

!include(DateAndTimeResource/DateAndTimeResource.pri){
    error("Could not load DateAndTimeResource");
}

!include(DiagnosticResource/DiagnosticResource.pri){
    error("Could not load DiagnosticResource");
}
!include(IntrospectionStubResource/IntrospectionStubResource.pri){
    error("Could not load IntrospectionStubResource");
}

!include(VoiceAlerts/VoiceAlerts.pri){
    error("Could not load VoiceAlerts Resource");
}

!include(VersionManagerResource/VersionManagerResource.pri){
    error("Could not load VersionManagerResource");
}

!include(VRStubResource/VRStubResource.pri){
    error("Could not load VRStubResource");
}

!include(LayerManagerResource/LayerManagerResource.pri){
    error("Could not load LayerManagerResource");
}

!include(VRProxyResource/VRProxyResource.pri){
    error("Could not load VRProxyResource");
}

!include(VariantControlResource/VariantControlResource.pri){
    error("Could not load VariantControlResource");
}

!include(RCAResource/RCAResource.pri){
    error("Could not load RCAResource");
}

!include(ICCastResource/ICCastResource.pri){
    error("Could not load ICCastResource");
}

!include(DriveNextResource/DriveNextResource.pri){
    error("Could not load DriveNextResource");
}

# Confiuration for the Linux target OS
linux-oe-g++ {
    !include(NanoMsgService/NanoMsgService.pri){
        error("Could not load NanoMsgService");
    }
}

!include(W3WResource/W3WResource.pri){
    error("Could not load W3WResource");
}

!include(DoodleResource/DoodleResource.pri){
    error("Could not load DoodleResource");
}

HEADERS += \
    $$PWD/ResourceDeploymentConfig.h \
    $$PWD/ResourceFactory.hpp \
    $$PWD/ResourceMaster.h

SOURCES += \
    $$PWD/ResourceDeploymentConfig.cpp \
    $$PWD/ResourceFactory.cpp \
    $$PWD/ResourceMaster.cpp

DISTFILES +=
