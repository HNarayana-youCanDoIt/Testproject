INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/interfaces/IDiagnosticResource.h \
    $$PWD/implementations/CDiagnosticEventProvider.h \
    $$PWD/implementations/CDiagnosticResourceImpl.h

SOURCES += \
    $$PWD/implementations/CDiagnosticEventProvider.cpp \
    $$PWD/implementations/CDiagnosticResourceImpl.cpp
