INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/interfaces/IVRProxyResource.h \
    $$PWD/implementations/CVRProxyResImpl.h \
    $$PWD/implementations/CVRProxyEventProvider.h

SOURCES += \
    $$PWD/implementations/CVRProxyResImpl.cpp \
    $$PWD/implementations/CVRProxyEventProvider.cpp
