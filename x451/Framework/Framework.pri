!include(BaseApplication/BaseApplication.pri){
    error("Could not include BaseApplication");
}

!include(Logging/Logging.pri){
    error("Could not include Logging");
}

!include(PopupManager/PopupManager.pri){
    error("Could not include PopupManager");
}

!include(ThemeManager/ThemeManager.pri){
    error("Could not include ThemeManager");
}

!include(Helper/Helper.pri){
    error("Could not include Helper");
}

