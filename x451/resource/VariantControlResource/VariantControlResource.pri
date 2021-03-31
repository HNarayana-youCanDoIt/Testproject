INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/interfaces/IVariantControlResource.h \
    $$PWD/implementations/CVariantControlEventProvider.h \
    $$PWD/implementations/CVariantControlResourceImpl.h \
    $$PWD/implementations/CVariantControlResourceEnums.h

SOURCES += \
    $$PWD/implementations/CVariantControlEventProvider.cpp \
    $$PWD/implementations/CVariantControlResourceImpl.cpp
