INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/interfaces/ILayerManagerResource.h \
    $$PWD/implementations/CLayerManagerEventProvider.h \
    $$PWD/implementations/CLayerManagerResourceImpl.h

SOURCES += \
    $$PWD/implementations/CLayerManagerEventProvider.cpp \
    $$PWD/implementations/CLayerManagerResourceImpl.cpp
