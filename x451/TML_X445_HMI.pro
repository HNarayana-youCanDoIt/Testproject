# Pro file for the Tata X445 HMI

QT += qml quick

# Target binary name for the TML HMI application
TARGET = TMLHMI

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# To specify this is X445 variant.
DEFINES += TATA_X445

# Confiuration for the Windows OS
win32 {
    message ("Bulding for win32")
    PLATFORM = win
    CONFIG += c++11
    # To avoid high usage of memory consumption during compiling for windows.
    CONFIG += resources_big
    COMMONAPI_INCLUDE=$$clean_path("$$PWD/deliveries/commonapi/include")
    DEFINES += PLATFORM_WIN32
    DEFINES += QT_NO_ACCESSIBILITY
    DEFINES += WIN32_LEAN_AND_MEAN

# Adding dependent library
    LIBS +=-lws2_32
}

# Confiuration for the Linux X86 OS
linux-g++ {
    message ("Bulding for linux-g++")
    PLATFORM = linux
    CONFIG += c++11 qtquickcompiler
    COMMONAPI_INCLUDE=$$(PKG_CONFIG_SYSROOT_DIR)/usr/include/CommonAPI-3.1/
    DEFINES += PLATFORM_LINUX_X86

# Adding dependent library
    LIBS += -ldlt
    LIBS += -lsystemd
    LIBS += -L$$clean_path("$$PWD/deploy/linux/lib/x86/") -lTML_HMI_tml_hmi_types_static_stub
}

# Confiuration for the Linux target OS
linux-oe-g++ {
    message ("Bulding for linux-oe-g++")
    DEFINES += USE_WAYLAND_IVI
    PLATFORM = linux
    CONFIG += c++11 qtquickcompiler wayland-compositor wayland-egl
    COMMONAPI_INCLUDE=$$(PKG_CONFIG_SYSROOT_DIR)/usr/include/CommonAPI-3.1/
    CONFIG += resources_big
# Adding dependent library
    LIBS += -ldlt
    LIBS += -lsystemd
    LIBS += -lilmControl -lilmClient -lilmInput -lilmCommon
    LIBS += -lpersistence_client_library -lnanomsg
}

# The various pri files that constitutes the components within the HMI application
# The Qt base framework used by the HMI
!include(Framework/Framework.pri){
    error("Could not include Framework");
}

# The various modules within the HMI application
!include(ProjectBase/ProjectBase.pri){
    error("Could not include Project Base");
}

# Include the auto generated Yakindu based state machine
!include(StateMachine_X445/StateMachine.pri){
    error("Could not include StateMachine");
}

# The resource layer for the various modules that interact with the PresCtrl or proxies
!include(resource/resource.pri){
    error("Could not include resource");
}

SERVICE_PROXY_INCLUDES=$$clean_path("$$PWD/TML_X0_FIDL/HMI/src-gen/consumes")
SERVICE_STUB_INCLUDES=$$clean_path("$$PWD/TML_X0_FIDL/HMI/src-gen/provides")
FRAMEWORK_DEPLOY = $$clean_path("$$PWD/deploy/$$PLATFORM")
FRAMEWORK_LIB = "$$FRAMEWORK_DEPLOY/lib"
FRAMEWORK_BIN = "$$FRAMEWORK_DEPLOY/bin"

# Header files to be include within the project
HEADERS += \
    CHMIMain.h \
    StateMachine_HBTimer.h \
    StateMachine_TML_HMI_SM.h

# Source files to be include within the project
SOURCES += main.cpp \
    CHMIMain.cpp

# The below translation files would be created when lupdate is run on the pro file
TRANSLATIONS += \
    languages/en_IN.ts \
    languages/en_US.ts

# Defines the qrc resource files used for the project
RESOURCES += qml.qrc \
        qml_X445.qrc \
        qml_X104_VAVE.qrc \
        qml_W3W_Flags.qrc

# The various include paths used by the project
QMAKE_INCDIR += $$clean_path("$$PWD/ProjectBase")
QMAKE_INCDIR += $$clean_path("$$PWD/resource")
QMAKE_INCDIR += $$COMMONAPI_INCLUDE
QMAKE_INCDIR += $$SERVICE_PROXY_INCLUDES
QMAKE_INCDIR += $$SERVICE_STUB_INCLUDES

QMAKE_RPATHLINKDIR += $$FRAMEWORK_LIB
#Common dependent libraries
LIBS += -L$$QMAKE_RPATHLINKDIR
LIBS += -lCommonAPI
LIBS += -L$$clean_path($$FRAMEWORK_LIB) -lTML_HMI_tml_hmi_types_static_stub

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/hmi/
!isEmpty(target.path): INSTALLS += target

# Output/Intermediate Dirs
OBJECTS_DIR = ./objs
OBJMOC = ./objs
MOC_DIR = ./objs
UI_DIR = ./objs
RCC_DIR = ./objs
