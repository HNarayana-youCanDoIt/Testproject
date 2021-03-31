#ifndef CSKELETONDATAEVENTPROVIDER_H
#define CSKELETONDATAEVENTPROVIDER_H

#include <QObject>

class CSkeletonDataEventProvider: public QObject
{
    Q_OBJECT

public:
    CSkeletonDataEventProvider(QObject* parent = 0);
    ~CSkeletonDataEventProvider();

signals:
    /*
     * All events (hardkey, VR etc) received from the below layers need to propagated to the upper layers.
     * This would be done via Qt signals
     * Define the various signals in this section
     */
    void sigHardKeyEvent(int eventType);

    //Type to be replaced by the various data information that needs to be updated by the resource layer
    void sigUpdateDataType(int type);


public:
    //Declare the functions that would be used by the Resource layer to indirectly emit signals to the upper layers
    void hardkeyEvent(int eventType);
    void updateDataType(int type);

};

#endif // CSKELETONDATAEVENTPROVIDER_H
