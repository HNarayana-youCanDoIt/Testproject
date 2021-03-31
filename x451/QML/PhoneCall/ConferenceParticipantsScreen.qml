import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.hardkeyenum 1.0
import "../Common"

BaseUI
{
    id: idConfParticipantMain

    // TODO: Language string id should be added instead of static text.
    // Title of conference participants screen.
    HBTitleWithBackButton
    {
        prTitle: qsTr("TEXT_PHONE_ACTIVE_CALL") + cppThemeMgr.languageChanged
    }

    // Delegate of conference participant list item component
    Component
    {
        id: idConfParticipantListItemDelegate
        Column
        {
            enabled: endParticpiantCallRole

            ListItemWithButton
            {
                id: idConfParticipantListItem
                width: idConfParticipantList.idList.width
                height: idConfParticipantList.prItemHeight - idConfParticipantItemSeparator.height
                prItemText: participantNameRole
                prButtonItem.visible: endParticpiantCallRole

                prButtonItem.defaultImageURL:"qrc:/image/PhoneCall/incomingCallPopup/Ph_Btn_EndCallSmall_7in_n-assets/Ph_Btn_EndCallSmall_n.png"
                prButtonItem.pressedImageURL: "qrc:/image/PhoneCall/incomingCallPopup/Ph_Btn_EndCallSmall_7in_n-assets/Ph_Btn_EndCallSmall_nf.png"
                prButtonItem.disabledImageURL: "qrc:/image/PhoneCall/incomingCallPopup/Ph_Btn_EndCallSmall_7in_n-assets/Ph_Btn_EndCallSmall_nd.png"

                onReleased:
                {
                    cppPhoneApp.qmlLog("ConferenceParticipantsScreen.qml: participant selected")
                    //Initiate end particiapnt call by id flow
                    cppPhoneAdaptor.invEndCall(callerIdRole)
                }

                prButtonItem.onReleased:
                {
                    //Initiate end particiapnt call by id flow
                    cppPhoneApp.qmlLog("ConferenceParticipantsScreen.qml: end call selected for participant")
                    cppPhoneAdaptor.invEndCall(callerIdRole)
                }
            }

            //Handling RRE HK for conference participant list items
            Connections
            {
                target: cppHardkeyAdaptor
                onSigRotaryPressed:
                {
                    cppPhoneApp.qmlLog("ConferenceParticipantsScreen: onRotaryUpdate: key state is: " + iKeyState)
                    if(iKeyState === HardkeyEnum.HKEY_STATE_RELEASED || iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED)
                    {
                        if(idConfParticipantList.idList.currentIndex === index)
                        {
                            cppPhoneApp.qmlLog("ConferenceParticipantsScreen.qml - itemIndex is: " + index)
                            cppPhoneAdaptor.invEndCall(callerIdRole)
                        }
                    }
                }
            }

            ListItemSeparator
            {
                id: idConfParticipantItemSeparator
            }
        }
    }

    // conference participant list.
    GenericList
    {
        id: idConfParticipantList
        rowShownPerPage: 4
        height: idConfParticipantList.prItemHeight * rowShownPerPage
        anchors
        {
            top: parent.top
            topMargin: 155
        }
        idList.model: cppPhoneAdaptor.confParticipantsListModel
        idList.delegate: idConfParticipantListItemDelegate
    }
}
