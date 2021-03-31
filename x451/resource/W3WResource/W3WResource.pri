INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/interfaces/IW3WResource.h \
    $$PWD/implementations/CW3WResourceImpl.h \
    $$PWD/implementations/CW3WEventProvider.h \
    $$PWD/implementations/CW3WResourceData.h

SOURCES += \
    $$PWD/implementations/CW3WResourceImpl.cpp \
    $$PWD/implementations/CW3WEventProvider.cpp
