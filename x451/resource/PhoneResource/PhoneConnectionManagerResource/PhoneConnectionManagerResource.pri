INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/interfaces/IPhoneConnectionManagerResource.h \
    $$PWD/implementations/CPhoneConnectionManagerEventProvider.h \
    $$PWD/implementations/CPhoneConnectionManagerResourceImpl.h

SOURCES += \
    $$PWD/implementations/CPhoneConnectionManagerEventProvider.cpp \
    $$PWD/implementations/CPhoneConnectionManagerResourceImpl.cpp
