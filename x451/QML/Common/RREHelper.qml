import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import com.harman.qml.hardkeyenum 1.0



/*
 * the generic rre helper qml which will provide rre focus image to any Item which has rre image and the related property(rreIndex and RREVisible) when the list of items is provided to the component
 * It will handle the RRE current index, rotary update and rotary pressed events
 * To use it, just make a component of this qml and provide the list of items for which rotary needs to be implemented
 */

Item {

    /**
      * Property to hold current index for rotary update
      **/
    readonly property alias prCurrentRREIndex: rreHelperItem.prCurrentRREIndex

    /**
      * Property to determine if the rre helper is getting used by a popup
      **/
    property bool isPopup: false

    Item
    {
        id: rreHelperItem
        property list<Item> prItemList
        property int prCurrentRREIndex: -1
    }

    function resetItemList()
    {
        cppUIBase.qmlLog("resetItemList , length of list: " + rreHelperItem.prItemList.length + "curr index" + rreHelperItem.prCurrentRREIndex)
        rreHelperItem.prItemList = []
        rreHelperItem.prCurrentRREIndex = -1
    }

    function setItemList(btnList)
    {
        rreHelperItem.prItemList = btnList;
        cppUIBase.qmlLog("setItemList , length of list: " + rreHelperItem.prItemList.length)
        for(var ind=0; ind < rreHelperItem.prItemList.length; ind++)
        {
            rreHelperItem.prItemList[ind].prRREIndex = ind;
        }
    }

    function setCurrentRreIndex(newIndex)
    {
        cppUIBase.qmlLog("setCurrentRreIndex , current index: " + rreHelperItem.prCurrentRREIndex + "new index" + newIndex)
        if(rreHelperItem.prCurrentRREIndex !== newIndex)
        {
            if((newIndex >= -1) && (newIndex <  rreHelperItem.prItemList.length))
            {
                if(newIndex !== -1)
                {
                    if((rreHelperItem.prCurrentRREIndex !== -1) && (rreHelperItem.prItemList[rreHelperItem.prCurrentRREIndex].prRREVisible))
                    {
                        rreHelperItem.prItemList[rreHelperItem.prCurrentRREIndex].prRREVisible = false
                    }

                    rreHelperItem.prItemList[newIndex].prRREVisible = true
                }
                else
                {
                    rreHelperItem.prItemList[rreHelperItem.prCurrentRREIndex].prRREVisible = false
                }

                rreHelperItem.prCurrentRREIndex = newIndex
            }
            else
            {
                cppUIBase.qmlLog("setCurrentRreIndex: newIndex out of bounds ")
            }
        }
        else
        {
            cppUIBase.qmlLog("setCurrentRreIndex: newIndex same as currentRREIndex ")
        }
    }

    function rreCurrentIndex(iPrevIndex, bIsLeftRotate)
    {
        cppUIBase.qmlLog("rreCurrentIndex iPrevIndex" + iPrevIndex + "bIsLeftRotate" + bIsLeftRotate)
        if(bIsLeftRotate)
        {
            do{
                iPrevIndex--;

            } while((iPrevIndex > -1) && ( (rreHelperItem.prItemList[iPrevIndex].enabled)? ((rreHelperItem.prItemList[iPrevIndex].visible)? false : true): true));

            if(iPrevIndex > -1)
            {
                setCurrentRreIndex(iPrevIndex);
            }
        }
        else
        {
            do{
                iPrevIndex++;
            }
            while((iPrevIndex < rreHelperItem.prItemList.length) && ( (rreHelperItem.prItemList[iPrevIndex].enabled)? ((rreHelperItem.prItemList[iPrevIndex].visible)? false : true): true));


            if(iPrevIndex < rreHelperItem.prItemList.length)
            {
                setCurrentRreIndex(iPrevIndex);
            }
        }
    }

    Connections{
        target: (isPopup) ? PopupManager : cppHardkeyAdaptor

        onSigRotaryUpdate:{
            cppUIBase.qmlLog("RreFocus.qml: sigRotaryUpdate: iKeyState: "
                             + iKeyState + " iKeyCode : " + iKeyCode)
            var prPreviousRREIndex = rreHelperItem.prCurrentRREIndex

            if(HardkeyEnum.KEYCODEHK_MENUROTARY_KNOB === iKeyCode){
                if(HardkeyEnum.HKEY_STATE_ROTATE_LEFT === iKeyState){
                    rreCurrentIndex(prPreviousRREIndex, true)
                }
                else if(HardkeyEnum.HKEY_STATE_ROTATE_RIGHT === iKeyState){
                    rreCurrentIndex(prPreviousRREIndex, false)
                }
            }
        }

        onSigRotaryPressed:{
            cppUIBase.qmlLog("RreFocus.qml: onRotaryPressed: "+iKeyState)
            if(HardkeyEnum.KEYCODEHK_MENUROTARY === iKeyCode){
                if ((HardkeyEnum.HKEY_STATE_RELEASED === iKeyState) || (HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState))
                {
                    if(rreHelperItem.prCurrentRREIndex != -1)
                    {
                        rreHelperItem.prItemList[rreHelperItem.prCurrentRREIndex].released()
                        setCurrentRreIndex(-1)
                    }
                }
            }
        }

        onSigRotaryUpdatePopup:{
            cppUIBase.qmlLog("RreFocus.qml: onSigRotaryUpdatePopup: iKeyState: "
                             + iKeyState + " iKeyCode : " + iKey)
            PopupManager.invResetPopupTimer()
            var prPreviousRREIndex = rreHelperItem.prCurrentRREIndex

            if(HardkeyEnum.KEYCODEHK_MENUROTARY_KNOB === iKey){
                if(HardkeyEnum.HKEY_STATE_ROTATE_LEFT === iKeyState){
                    rreCurrentIndex(prPreviousRREIndex, true)
                }
                else if(HardkeyEnum.HKEY_STATE_ROTATE_RIGHT === iKeyState){
                    rreCurrentIndex(prPreviousRREIndex, false)
                }
            }
        }

        onSigRotaryPressedPopup:{
            cppUIBase.qmlLog("RreFocus.qml: onRotaryPressed: "+iKeyState)
            if(HardkeyEnum.KEYCODEHK_MENUROTARY === iKey){
                if ((HardkeyEnum.HKEY_STATE_RELEASED === iKeyState) || (HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState))
                {
                    if(rreHelperItem.prCurrentRREIndex != -1)
                    {
                        rreHelperItem.prItemList[rreHelperItem.prCurrentRREIndex].released()
                        setCurrentRreIndex(-1)
                    }
                }
            }
        }

    }
}
