INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/implementations/CDoodleResourceEnum.h \
    $$PWD/implementations/CDoodleResourceData.h \
    $$PWD/implementations/CDoodleEventProvider.h \
    $$PWD/implementations/CDoodleResourceImpl.h \
    $$PWD/interfaces/IDoodleResource.h

SOURCES += \
    $$PWD/implementations/CDoodleResourceData.cpp \
    $$PWD/implementations/CDoodleEventProvider.cpp \
    $$PWD/implementations/CDoodleResourceImpl.cpp
