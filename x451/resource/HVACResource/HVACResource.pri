INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/interfaces/IHVACResource.h \
    $$PWD/implementations/CHVACEventProvider.h \
    $$PWD/implementations/CHVACResourceImpl.h \
    $$PWD/implementations/CHVACData.h

SOURCES += \
    $$PWD/implementations/CHVACEventProvider.cpp \
    $$PWD/implementations/CHVACResourceImpl.cpp
