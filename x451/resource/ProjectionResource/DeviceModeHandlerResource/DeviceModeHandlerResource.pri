INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/implementations/CDeviceModeHandlerEventProvider.h \
    $$PWD/implementations/CDeviceModeHandlerResourceImpl.h \
    $$PWD/interfaces/IDeviceModeHandlerResource.h \
    $$PWD/implementations/CDeviceModeHandlerResourceResourceEnums.h \
    $$PWD/implementations/CDeviceModeHandlerResourceData.h

SOURCES += \
    $$PWD/implementations/CDeviceModeHandlerResourceImpl.cpp \
    $$PWD/implementations/CDeviceModeHandlerEventProvider.cpp
