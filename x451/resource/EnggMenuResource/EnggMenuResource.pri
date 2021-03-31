
INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/interfaces/IEnggMenuResource.h \
    $$PWD/interfaces/CDataEnggMenu.h\
    $$PWD/implementations\CEnggMenuEventProvider.h \
    $$PWD/implementations\CEnggMenuResourceImpl.h


SOURCES += \
    $$PWD/implementations/CEnggMenuResourceImpl.cpp \
    $$PWD/implementations/CEnggMenuEventProvider.cpp
