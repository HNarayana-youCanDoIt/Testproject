INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/implementations/CDriveNextEventProvider.h \
    $$PWD/implementations/CDriveNextResourceImpl.h \
    $$PWD/interfaces/IDriveNextResource.h \
    $$PWD/implementations/CDriveNextResourceData.h \
    $$PWD/implementations/CDriveNextResourceEnum.h \
    $$PWD/implementations/CDriveNextModerator.h

SOURCES += \
    $$PWD/implementations/CDriveNextEventProvider.cpp \
    $$PWD/implementations/CDriveNextResourceImpl.cpp \
    $$PWD/implementations/CDriveNextResourceData.cpp \
    $$PWD/implementations/CDriveNextModerator.cpp
