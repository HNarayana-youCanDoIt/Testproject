INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/interfaces/IICCastResource.h \
    $$PWD/implementations/CICCastResourceImpl.h \
    $$PWD/implementations/CICCastEventProvider.h \
    $$PWD/implementations/CICCastEnum.h

SOURCES += \
    $$PWD/implementations/CICCastResourceImpl.cpp \
    $$PWD/implementations/CICCastEventProvider.cpp
