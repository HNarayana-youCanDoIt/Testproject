#include "CSkeletonSM.h"

CSkeletonSM::CSkeletonSM(CSkelectonApplication& skeletonApp):
    mSkeletonApp(skeletonApp)
{

}

CSkeletonSM::~CSkeletonSM()
{

}

void CSkeletonSM::enterState()
{
    mSkeletonApp.loadScreen("qrc:/QML/SkeletonQML/SkeletonMain.qml");
}

void CSkeletonSM::exitState()
{

}

void CSkeletonSM::exampleRequest()
{

}
