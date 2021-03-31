INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/interfaces/ISoftwareUpdateResource.h \
    $$PWD/implementations/CSoftwareUpdateEventProvider.h \
    $$PWD/implementations/CSoftwareUpdateResourceImpl.h \
    $$PWD/implementations/CSoftwareUpdateEnumsResource.h

SOURCES += \
    $$PWD/implementations/CSoftwareUpdateEventProvider.cpp \
    $$PWD/implementations/CSoftwareUpdateResourceImpl.cpp
