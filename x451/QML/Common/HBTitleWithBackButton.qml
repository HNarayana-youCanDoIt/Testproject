/* This component contains screen title with back button. The object of this item should be created by the
 * qml which want to show title with back button. Also the object of this item should be created before creating
 * any other items.
 */
import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common/"
import com.harman.qml.thememanager 1.0

Item {
    id: idTitleWithBackButton

    /**
      This property has the reference of the visiblity of the back button.
      */
    property alias prBackButtonVisible: idBackButton.visible

    /** Property that shall be used by QML(screens) to set the title text **/
    property string prTitle: ""

    width: 398
    height: 76

    anchors{

        top: parent.top
        topMargin: 50
        right: parent.right
        rightMargin: 128
    }


    /** HB text to show screen title with properties and implemetation as per X451 UI flow**/
    HBText {
        id: idScreenTitle

        height: 76

        anchors {
            right: idBackButton.left
            rightMargin: 40
        }

        fontType: ThemeMgr.FONTTYPE_T45_C1
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        text: prTitle

        onImplicitWidthChanged:
        {
            cppUIBase.qmlLog("prTitle: "+ prTitle + " ImpliciWidth: " + idScreenTitle.implicitWidth)
            if( idScreenTitle.implicitWidth > 450)
            {
                idScreenTitle.width = 450
            }

            else if(idScreenTitle.implicitWidth > 300)
            {
                idScreenTitle.width = idScreenTitle.implicitWidth
            }
            else
            {
                idScreenTitle.width = 308
            }

            idTitleWithBackButton.width = idScreenTitle.width + idBackButton.width
        }

    }

    /** Generic button to show back button with properties and implemetation as per X451 UI flow**/
    GenericButton {
        id: idBackButton

        width: 76
        height: 76
        anchors {
            right: idTitleWithBackButton.right
            top: parent.top
        }

        visible: true

        defaultImageURL: "qrc:/image/Gen_Ico_Back_7in_n/Gen_Ico_Back_n.png"
        pressedImageURL: "qrc:/image/Gen_Ico_Back_7in_n/Gen_Ico_Back_np.png"
        disabledImageURL: "qrc:/image/Gen_Ico_Back_7in_n/Gen_Ico_Back_nd.png"

        onReleased: {
            cppUIBase.qmlLog("HBTitleWithBackButton.qml: back button clicked.")
            cppUIBase.raiseSMEvent("back", "")
        }
    }
}
