!include(VersionManager/VersionManager.pri){
    error("Could not include VersionManager");
}

!include(SoftwareUpdate/SoftwareUpdate.pri){
    error("Could not include SoftwareUpdate");
}
