#ifndef RESOURCEMASTER_H
#define RESOURCEMASTER_H

#include <QObject>
#include "CommonAPI/CommonAPI.hpp"

#define SUBSCRIBE(A,B,C,...) { A->B.subscribe( std::bind (C,this, ## __VA_ARGS__) ); }
#define UNSUBSCRIBE(A,B,C) A->B.unsubscribe(C);

class ResourceMaster:public QObject
{
    Q_OBJECT
    static ResourceMaster *s_instance;
    ResourceMaster();

public:
    ~ResourceMaster()
    {

    }

    static ResourceMaster* getInstance();

    std::shared_ptr<CommonAPI::Runtime> getRuntime();

    std::shared_ptr<CommonAPI::Runtime> runtimePtr ;
};


#endif // RESOURCEMASTER_H
