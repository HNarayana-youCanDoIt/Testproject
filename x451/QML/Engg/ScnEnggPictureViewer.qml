import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.mediaenum 1.0

BaseUI
{
    id: idPictureViewer
    property int prCurrentImageIndex         : 0//MediaAdaptor.currentImageIndex
    property int prTotalImageCount           : MediaAdaptor.totalImageCount

    HBTitleWithBackButton {
        //Screen Title
        prTitle : qsTr("TEXT_ENGG_MENU_PICTURE_VIEWER_CAPTION") + cppThemeMgr.languageChanged;
    }

    Image {
        id: idImage
        anchors.centerIn: parent
        source: ""//MediaAdaptor.currentImagePath
        fillMode: Image.Pad
    }

    MouseArea {
        id: idPictureViewerLeftArea
        width: parent.width/3
        height: parent.height
        anchors.left: parent.left
        onPressed: {
            cppUIBase.qmlLog("PictureViewerLeftArea: CurrentImageIndex:" + (prCurrentImageIndex - 1))
            if(prCurrentImageIndex > 0) {
                //MediaAdaptor.setCurrentImageIndex((prCurrentImageIndex - 1))
            }
        }
    }

    MouseArea {
        id: idPictureViewerRightArea
        width: parent.width/3
        height: parent.height
        anchors.right: parent.right
        onPressed: {
            cppUIBase.qmlLog("PictureViewerRightArea: CurrentImageIndex:" + (prCurrentImageIndex + 1))
            if(prCurrentImageIndex < (prTotalImageCount - 1)) {
                //MediaAdaptor.setCurrentImageIndex((prCurrentImageIndex + 1))
            }
        }
    }

    Component.onCompleted: {
        cppUIBase.qmlLog("PictureViewer: TotalImageCount:" + prTotalImageCount)
        MediaAdaptor.getCategoryRoot(MediaEnum.BROWSEITEM_PICTURE)
    }


}
