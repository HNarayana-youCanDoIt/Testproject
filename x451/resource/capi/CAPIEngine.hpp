#ifndef CAPIENGINE_HPP
#define CAPIENGINE_HPP

#include <CommonAPI/CommonAPI.hpp>
#include <QObject>
#include <QSocketNotifier>
#include <QLinkedList>
#include <unordered_map>
#ifdef usleep
#undef usleep
#endif

using namespace CommonAPI;

Q_DECLARE_METATYPE(Watch*)

class CAPIEngine : public QObject
{
Q_OBJECT


private :

    CAPIEngine();

    struct watchHandler{
        QSocketNotifier*    mSn;
        Watch*              mWatch;
    };

    void regWatch( Watch* watch_, const DispatchPriority dispatchPriority) ;
    void deregWatch( Watch* watch);

public :

    static CAPIEngine& getCAPIEngine();
    static std::shared_ptr<CommonAPI::MainLoopContext> getMainLoop();

signals :
    void onWatchAdded(Watch* watch);
    void onWatchRemoved(Watch* watch);

public slots:
    void doWatchAdded(Watch* watch);
    void doWatchRemoved(Watch* watch);
    void onSocketDataAvailable(int fd);

private :

    static CAPIEngine* m_pSelf;
    std::shared_ptr<CommonAPI::MainLoopContext> mainloopContext;
    std::unordered_map<int, struct watchHandler> mWatchMap;

};

#endif // CAPIENGINE_HPP
