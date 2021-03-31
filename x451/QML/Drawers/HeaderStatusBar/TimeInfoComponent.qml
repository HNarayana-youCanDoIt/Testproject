import QtQuick 2.7
import "../../Common"
import com.harman.qml.thememanager 1.0

Item {
    id: idTimeInfoItem

    /*
     * Text Item to show the time.
     */
    HBText {
        id: idTimeText

        anchors.verticalCenter: parent.verticalCenter

        text: formatNumberLength(cppDateAndTimeAdaptor.hour) + ":" + formatNumberLength(cppDateAndTimeAdaptor.minute) +
             " "+((cppDateAndTimeAdaptor.is24HrFormatStatus) ? "" : cppDateAndTimeAdaptor.amOrPm )
        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
    }

    //Function to check if there is single digit then append 0 at the beginning else return the same number.
    function formatNumberLength(num) {
        if (num < 10) {
            num = "0" + num;
        }
        return num;
    }

}
