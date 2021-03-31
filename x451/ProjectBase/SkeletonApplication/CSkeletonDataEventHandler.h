#ifndef CSKELETONDATAEVENTHANDLER_H
#define CSKELETONDATAEVENTHANDLER_H

#include <QObject>

///
/// \brief The CSkeletonDataEventHandler class
/// The class listens for the signals raised by the resource layer provider class
/// It has the implementation of the corresponding slots
///

class CSkeletonDataEventHandler: public QObject
{
    Q_OBJECT
public:
    CSkeletonDataEventHandler(QObject* parent = 0);
    ~CSkeletonDataEventHandler();

public slots:
    // Declare the slots that would be invoked on the resource layer events signals
    void sltHardKeyEvent(int eventType);
    void sltUpdateDataType(int type);

private:
    void connectSignals();
};

#endif // CSKELETONDATAEVENTHANDLER_H
