HEADERS +=\
    $$PWD/CHMIApplication.h \
    $$PWD/CHMIApplicationSM.h \
    $$PWD/CHMIApplicationEnums.h
	
SOURCES +=\
    $$PWD/CHMIApplication.cpp \
    $$PWD/CHMIApplicationSM.cpp

contains(DEFINES, USE_WAYLAND_IVI){
    QT += gui-private
    HEADERS += $$PWD/WaylandIVIController.h
    SOURCES += $$PWD/WaylandIVIController.cpp
}
