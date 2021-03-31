INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/implementations/CHardkeyEnums.h \
    $$PWD/implementations/CHardkeyEventProvider.h \
    $$PWD/implementations/CHardkeyResourceImpl.h \
    $$PWD/interfaces/IHardkeyResource.h

SOURCES += \
    $$PWD/implementations/CHardkeyResourceImpl.cpp \
    $$PWD/implementations/CHardkeyEventProvider.cpp
