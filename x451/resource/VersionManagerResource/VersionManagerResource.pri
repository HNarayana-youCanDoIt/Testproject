INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/interfaces/IVersionManagerResource.h \
    $$PWD/implementations/CVersionManagerEventProvider.h \
    $$PWD/implementations/CVersionManagerResourceImpl.h

SOURCES += \
    $$PWD/implementations/CVersionManagerEventProvider.cpp \
    $$PWD/implementations/CVersionManagerResourceImpl.cpp
