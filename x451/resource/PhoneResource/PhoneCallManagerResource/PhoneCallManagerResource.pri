INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/interfaces/IPhoneCallManagerResource.h \
    $$PWD/implementations/CPhoneCallManagerResourceImpl.h \
    $$PWD/implementations/CPhoneCallManagerEventProvider.h

SOURCES += \
    $$PWD/implementations/CPhoneCallManagerResourceImpl.cpp \
    $$PWD/implementations/CPhoneCallManagerEventProvider.cpp
