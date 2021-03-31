!include(AndroidAutoResource/AndroidAutoResource.pri){
    error("Could not load AndroidAutoResource");
}

!include(DeviceModeHandlerResource/DeviceModeHandlerResource.pri){
    error("Could not load DevPressResource");
}

!include(AppleCarPlayResource/AppleCarPlayResource.pri){
    error("Could not load AppleCarPlayResource");
}
