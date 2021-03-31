import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import com.harman.qml.thememanager 1.0
import QtQuick.Controls.Styles 1.4
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.setupenums 1.0
import QtGraphicalEffects 1.0
import "../Common/"

BaseUI
{
    id:idSetDateAndTime
    /* this property will hold the number of days that has to be in a particular month of that selected year. */
    property int prValidateDays: 30
    /**
     * This property will help to sync between the user touch and Hardkey rotary.
     * Lets say after opening date and time screen user touches any tumbler, then the focus should navigate as per the pathway even
     * if user operates it with rotary.And if user navigates through Rotary on entering date and time screen, it should navigate as per
     * the given pathway. This property choose whether user has touched or used rotary after entering the date and time screen.
    */
    property bool prIsFirstActionCanBeTakenOnRRERotation: true
    /*
    This property will hold the value of the day which user wants to set.
    */
    property int prDay
    /*
    This property will hold the value of the Month which user wants to set.
    */
    property int prMonth
    /*
    This property will hold the value of the Year which user wants to set.
    */
    property int prYear
    /*
    This property will hold the value of the Hour which user wants to set.
    */
    property int prHour
    /*
    This property will hold the value of the Minute which user wants to set.
    */
    property int prMinute
    /*
    This property will hold the value of the Sec which user wants to set.
    */
    property int prSec : 0
    /*
    This property will hold the value of the AM/PM which user wants to set.
    */
    property string prAMorPm : ""

    /* Since all the components are in a single qml so, screen has been divided into 3 parts
      SetupEnums.SETUP_COMPONENT_DATE : date component ,
      SetupEnums.SETUP_COMPONENT_TIME_24_HR : time component 24 hours  format
      SetupEnums.SETUP_COMPONENT_TIME_12_HR : time Component 12 hours format
      */
    property int prDateTimeScreenType : SetupEnums.SETUP_COMPONENT_DATE

    /*
     * This property will hold the value for 24Hr Format.
    */
    property bool prIs24HrFormatStatus: cppDateAndTimeAdaptor.is24HrFormatStatus

    /*
     * This property will hold the checkbox status whether user is on Checkbox. This will help the user to move through the rotary
      and focus on the required component .
    */
    property bool prIsCheckBoxClickedStatus: false
    /**
      Constant Property  which will hold the starting year
    **/
    property int prStartingYearValue: 2018


    /* this function will send the value of selected date and time data to adaptor */
    function setDateAndTime()
    {
        cppDateAndTimeAdaptor.setDateAndTime(prMinute, prHour, prDay, prMonth, prYear, prAMorPm,prSec)
        cppSetupApp.raiseSMEvent("SetDateAndTime", "Back")
    }



    HBTitleWithBackButton
    {
        prTitle: qsTr("TEXT_SETTING_GENERAL_SET_TIME_AND_DATE")+ cppThemeMgr.languageChanged
    }

    Item
    {
        id: idCheckboxWithTitleItem
        height: idCheckboxfor24HrFormat.height
        width: id24HrText.implicitWidth + idCheckboxfor24HrFormat.width

        visible: (SetupEnums.SETUP_COMPONENT_DATE !== prDateTimeScreenType)

        anchors
        {
            left:parent.left
            leftMargin:170
            top:parent.top
            topMargin:396
        }

        Image {
            id: idCheckboxFocusImage
            source: idCheckboxfor24HrFormat.focus ? "qrc:/image/Set_Ico_Checkbox_7in_n-assets/Set_Checkbox_Focus_nf.png" : ""
        }

        Image
        {
            id:idCheckboxfor24HrFormat
            width: 76
            height: 68
            enabled: cppDateAndTimeAdaptor.timeFormatChangeReqStatus
            source: enabled ? (prIs24HrFormatStatus
                               ? "qrc:/image/Set_Ico_Checkbox_7in_n-assets/Set_Checkbox_na.png"
                               : "qrc:/image/Set_Ico_Checkbox_7in_n-assets/Set_Checkbox_n.png")
                            : (prIs24HrFormatStatus
                               ? "qrc:/image/Set_Ico_Checkbox_7in_n-assets/Set_Ico_Checkbox_On_7in_nd.png"
                               : "qrc:/image/Set_Ico_Checkbox_7in_n-assets/Set_Ico_Checkbox_7in_nd.png")
        }

        HBText
        {
            id:id24HrText
            text: qsTr("24 Hours")
            fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
            anchors
            {
                left: parent.left
                leftMargin: 76
                top: parent.top
                topMargin: 20
            }
        }


        MouseArea
        {
            anchors.fill: parent
            onPressed:
            {
                idCheckboxfor24HrFormat.forceActiveFocus()
            }
            onReleased:
            {

                cppDateAndTimeAdaptor.invSetTimeFormat(!prIs24HrFormatStatus)
                prIsCheckBoxClickedStatus = true
            }
        }

        Connections
        {

            target : (idCheckboxfor24HrFormat.activeFocus) ? cppHardkeyAdaptor : null
            onSigRotaryUpdate:
            {
                if(HardkeyEnum.HKEY_STATE_ROTATE_RIGHT === iKeyState)
                {
                    idCancelBtnDate.forceActiveFocus()
                }
                else if(HardkeyEnum.HKEY_STATE_ROTATE_LEFT === iKeyState)
                {
                    //Do Nothing.
                }
            }

            onSigRotaryPressed:
            {
                if(iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED
                        || iKeyState === HardkeyEnum.HKEY_STATE_RELEASED)
                {
                    cppSetupApp.qmlLog("GeneralSetupSetDateAndTime.qml::onSigRotaryPressed")
                    cppDateAndTimeAdaptor.invSetTimeFormat(!prIs24HrFormatStatus)
                    prIsCheckBoxClickedStatus = true
                }
                else
                {
                    //Do Nothing.
                }
            }
        }
    }

    onPrIs24HrFormatStatusChanged: {

        if (SetupEnums.SETUP_COMPONENT_DATE !== prDateTimeScreenType)
        {
            prDateTimeScreenType = (prIs24HrFormatStatus ? SetupEnums.SETUP_COMPONENT_TIME_24_HR
                                                         : SetupEnums.SETUP_COMPONENT_TIME_12_HR)
        }
        else
        {
            //Do Nothing.
        }

    }

    Row{

        spacing: 12
        anchors
        {
            left:parent.left
            leftMargin: 544
            top:parent.top
            topMargin:396
        }

        GenericButton{
            id: idCancelBtnDate
            width: 76
            height: 76
            defaultImageURL: "qrc:/image/Setup/Set_Btn_BgCancel_7in_n-assets/Set_Btn_BgCancel_n.png"
            pressedImageURL: "qrc:/image/Setup/Set_Btn_BgCancel_7in_n-assets/Set_Btn_BgCancel_nf.png"
            onReleased:
            {
                cppSetupApp.qmlLog("GeneralSetupSetDateAndTime.qml::Cancel button clicked.")
                cppSetupApp.raiseSMEvent("SetDateAndTime", "Back")

            }
            /* This focus will be visible when cancel button gets focus */
            Image {
                id: idCancelBtnHardKeyFocusImage

                anchors.fill: parent
                visible: parent.activeFocus
                source: "qrc:/image/Setup/Set_Btn_BgCancel_7in_n-assets/Set_Btn_BgCancel_nf.png"
            }

            Connections
            {

                target : ( idCancelBtnDate.activeFocus ? cppHardkeyAdaptor : null )
                onSigRotaryUpdate:
                {
                    if(HardkeyEnum.HKEY_STATE_ROTATE_RIGHT === iKeyState
                            && iKeyCode === HardkeyEnum.KEYCODEHK_MENUROTARY_KNOB)
                    {
                        idNextBtnDate.forceActiveFocus()
                    }
                    if(HardkeyEnum.HKEY_STATE_ROTATE_LEFT === iKeyState
                            && iKeyCode === HardkeyEnum.KEYCODEHK_MENUROTARY_KNOB)
                    {
                        if (SetupEnums.SETUP_COMPONENT_DATE === prDateTimeScreenType)
                        {
                            //Do Nothing.
                        }
                        else
                        {
                            idCheckboxfor24HrFormat.forceActiveFocus()
                        }
                    }
                }

                onSigRotaryPressed:
                {
                    if(iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED
                            || iKeyState === HardkeyEnum.HKEY_STATE_RELEASED)
                    {
                        cppSetupApp.qmlLog("GeneralSetupSetDateAndTime.qml::Cancel button clicked.")
                        cppSetupApp.raiseSMEvent("SetDateAndTime", "Back")
                        idCancelBtnDate.focus = false
                    }
                    else
                    {
                        //Do Nothing.
                    }
                }
            }


        }


        /** This button acts as a next button as well as save button .
         *  For Date Screen it's Next button and for Time Screen its Save and Apply Button
         **/
        GenericButton{
            id: idNextBtnDate
            width: 76
            height: 76
            defaultImageURL:(SetupEnums.SETUP_COMPONENT_DATE === prDateTimeScreenType)
                            ? "qrc:/image/Setup/Set_Btn_Next_7in_n-assets/Set_Btn_Next_n.png"
                            : "qrc:/image/Setup/Set_Btn_ApplySetting_7in_n-assets/Set_Btn_ApplySetting_n.png"

            pressedImageURL: (SetupEnums.SETUP_COMPONENT_DATE === prDateTimeScreenType)
                             ? "qrc:/image/Setup/Set_Btn_Next_7in_n-assets/Set_Btn_Next_nf.png"
                             : "qrc:/image/Setup/Set_Btn_ApplySetting_7in_n-assets/Set_Btn_ApplySetting_nf.png"
            onReleased: {

                if (SetupEnums.SETUP_COMPONENT_DATE === prDateTimeScreenType)
                {

                    prDateTimeScreenType = (prIs24HrFormatStatus ? SetupEnums.SETUP_COMPONENT_TIME_24_HR
                                                                 : SetupEnums.SETUP_COMPONENT_TIME_12_HR)
                }
                else
                {
                    setDateAndTime()
                }

                idNextBtnDate.focus = false
            }
            /* This focus image will be visible when next button gets focus. */
            Image {
                id: idnextBtnHardKeyFocusImage
                anchors.fill: parent

                visible: parent.activeFocus
                source: (SetupEnums.SETUP_COMPONENT_DATE === prDateTimeScreenType)
                        ? "qrc:/image/Setup/Set_Btn_Next_7in_n-assets/Set_Btn_Next_nf.png"
                        : "qrc:/image/Setup/Set_Btn_ApplySetting_7in_n-assets/Set_Btn_ApplySetting_nf.png"
            }

            Connections
            {
                target : ( idNextBtnDate.activeFocus ? cppHardkeyAdaptor : null )
                onSigRotaryUpdate:
                {
                    if(HardkeyEnum.HKEY_STATE_ROTATE_LEFT === iKeyState
                            && iKeyCode === HardkeyEnum.KEYCODEHK_MENUROTARY_KNOB)
                    {
                        idCancelBtnDate.forceActiveFocus()
                    }
                }

                onSigRotaryPressed:
                {
                    if(iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED
                            || iKeyState === HardkeyEnum.HKEY_STATE_RELEASED || iKeyState === HardkeyEnum.HKEY_STATE_PRESSED)
                    {
                        if (SetupEnums.SETUP_COMPONENT_DATE === prDateTimeScreenType)
                        {
                            prDateTimeScreenType = (prIs24HrFormatStatus ? SetupEnums.SETUP_COMPONENT_TIME_24_HR
                                                                         : SetupEnums.SETUP_COMPONENT_TIME_12_HR)
                        }
                        else
                        {
                            setDateAndTime()
                        }
                    }
                    else
                    {
                        //Do Nothing.
                        cppSetupApp.qmlLog("GeneralSetupSetDateAndTime.qml::onSigRotaryPressed Of Next Button, iKeyState: " + iKeyState)
                    }

                    idNextBtnDate.focus = false
                }
            }
        }
    }



    Loader{
        sourceComponent: ((SetupEnums.SETUP_COMPONENT_DATE === prDateTimeScreenType)
                          ? idSetDateComponent
                          :((SetupEnums.SETUP_COMPONENT_TIME_12_HR === prDateTimeScreenType)
                            ? idSetTime12HrsFormatComponent
                            :idSetTime24HrsFormatComponent))

        anchors.fill: parent
        onSourceComponentChanged: {
            prIsFirstActionCanBeTakenOnRRERotation = true
        }
    }


    /* Time component if user has selected 12 hours format */
    Component{
        id:idSetTime12HrsFormatComponent
        FocusScope{
            anchors.fill: parent

            Row{
                spacing: 3
                anchors
                {
                    left:parent.left
                    leftMargin:246
                    top:parent.top
                    topMargin:125
                }


                /* Hour component for  12 hours format */
                TumblerWithButtonComponent
                {
                    id:idHourTumbler12hr
                    width: 97
                    tumbler.model: 12
                    prStartingNumber: 1
                    prTumblerCurrentItemFocusImage: "qrc:/image/Set_Gfx_Date&TimeBg_n.png/Set_Gfx_Date&TimeBg_1_n.png"
                    prTumblerWidth: 97
                    onSigTumblerCurrentItemChanged:{
                        prHour = (tumbler.currentIndex +1)
                    }
                    Component.onCompleted: {
                        tumbler.currentIndex = (prHour - 1)
                        tumbler.contentItem.positionViewAtIndex((prHour - 1) , PathView.Center)
                    }
                    onPrIsTouchOnTumblerChanged: {
                        prIsFirstActionCanBeTakenOnRRERotation = false
                    }


                    Connections
                    {

                        target : ( idHourTumbler12hr.activeFocus ? cppHardkeyAdaptor : null )
                        onSigRotaryUpdate:
                        {
                            if(HardkeyEnum.HKEY_STATE_ROTATE_RIGHT === iKeyState)
                            {
                                idHourTumbler12hr.tumbler.contentItem.incrementCurrentIndex()
                            }
                            else if(HardkeyEnum.HKEY_STATE_ROTATE_LEFT === iKeyState)
                            {
                                idHourTumbler12hr.tumbler.contentItem.decrementCurrentIndex()
                            }
                        }

                        onSigRotaryPressed:
                        {
                            if(iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED
                                    || iKeyState === HardkeyEnum.HKEY_STATE_RELEASED)
                            {
                                cppSetupApp.qmlLog("GeneralSetupSetDateAndTime.qml::onSigRotaryPressed")
                                idMinTumbler12hr.forceActiveFocus()
                            }
                            else
                            {
                                //Do Nothing.
                            }
                        }
                    }

                }

                /* Minute component for  12 hours format */
                TumblerWithButtonComponent
                {
                    id:idMinTumbler12hr
                    width: 123
                    tumbler.model: 60
                    prIsModelNumeric: false
                    prStartingNumber: 0
                    prTumblerCurrentItemFocusImage: "qrc:/image/Set_Gfx_Date&TimeBg_n.png/Set_Gfx_Date&TimeBg_2_n.png"
                    prTumblerWidth: 123
                    onSigTumblerCurrentItemChanged: {
                        prMinute = tumbler.currentIndex
                    }
                    Component.onCompleted: {
                        tumbler.currentIndex = prMinute
                        tumbler.contentItem.positionViewAtIndex(prMinute, PathView.Center)
                    }
                    onPrIsTouchOnTumblerChanged: {
                        prIsFirstActionCanBeTakenOnRRERotation = false
                    }


                    Connections
                    {

                        target : ( idMinTumbler12hr.activeFocus ? cppHardkeyAdaptor : null )
                        onSigRotaryUpdate:
                        {
                            if(HardkeyEnum.HKEY_STATE_ROTATE_RIGHT === iKeyState)
                            {
                                idMinTumbler12hr.tumbler.contentItem.incrementCurrentIndex()
                            }
                            else if(HardkeyEnum.HKEY_STATE_ROTATE_LEFT === iKeyState)
                            {
                                idMinTumbler12hr.tumbler.contentItem.decrementCurrentIndex()
                            }
                        }

                        onSigRotaryPressed:
                        {
                            if(iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED
                                    || iKeyState === HardkeyEnum.HKEY_STATE_RELEASED)
                            {
                                cppSetupApp.qmlLog("GeneralSetupSetDateAndTime.qml::onSigRotaryPressed")
                                idAMOrPMTumbler12hr.forceActiveFocus()
                            }
                            else
                            {
                                //Do Nothing.
                            }
                        }
                    }
                }


                /* AM or PM component for  12 hours format */
                TumblerWithButtonComponent
                {
                    id:idAMOrPMTumbler12hr

                    width: 135
                    tumbler.model: ["AM","PM","AM","PM"]

                    prTumblerVisibleItemCount: 3
                    prIsModelNumeric: false
                    prTumblerCurrentItemFocusImage: "qrc:/image/Set_Gfx_Date&TimeBg_n.png/Set_Gfx_Date&TimeBg_3_n.png"
                    prTumblerWidth: 135

                    onSigTumblerCurrentItemChanged:{
                        prAMorPm = (tumbler.currentIndex % 2 === 0) ? "AM" : "PM"
                    }

                    Component.onCompleted: {
                        tumbler.currentIndex = ((prAMorPm == "AM") ? 0 : 1)
                        tumbler.contentItem.positionViewAtIndex(((prAMorPm == "AM") ? 0 : 1), PathView.Center)
                    }
                    onPrIsTouchOnTumblerChanged: {
                        prIsFirstActionCanBeTakenOnRRERotation = false
                    }


                    Connections
                    {

                        target : ( idAMOrPMTumbler12hr.activeFocus ? cppHardkeyAdaptor : null )
                        onSigRotaryUpdate:
                        {
                            if(HardkeyEnum.HKEY_STATE_ROTATE_RIGHT === iKeyState)
                            {
                                idAMOrPMTumbler12hr.tumbler.contentItem.incrementCurrentIndex()
                            }
                            else if(HardkeyEnum.HKEY_STATE_ROTATE_LEFT === iKeyState)
                            {
                                idAMOrPMTumbler12hr.tumbler.contentItem.decrementCurrentIndex()
                            }
                        }

                        onSigRotaryPressed:
                        {
                            if(iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED
                                    || iKeyState === HardkeyEnum.HKEY_STATE_RELEASED)
                            {
                                cppSetupApp.qmlLog("GeneralSetupSetDateAndTime.qml::onSigRotaryPressed")
                                idAMOrPMTumbler12hr.focus = false
                                idCheckboxfor24HrFormat.forceActiveFocus()
                            }
                            else
                            {
                                //Do Nothing.
                            }
                        }
                    }
                }

                Connections
                {
                    target : ( prIsFirstActionCanBeTakenOnRRERotation ) ? cppHardkeyAdaptor : null
                    onSigRotaryUpdate:
                    {
                        cppSetupApp.qmlLog("prIsCheckBoxClickedStatus: "+ prIsCheckBoxClickedStatus)
                        if(!prIsCheckBoxClickedStatus)
                        {
                            if(HardkeyEnum.HKEY_STATE_ROTATE_RIGHT === iKeyState || HardkeyEnum.HKEY_STATE_ROTATE_LEFT === iKeyState)
                            {
                                idHourTumbler12hr.forceActiveFocus()
                                prIsFirstActionCanBeTakenOnRRERotation = false
                            }
                        }
                        else
                        {
                            //Do Nothing. Focus will remain on Checkbox.
                        }
                    }
                }
            }
        }
    }


    /* Time component if user has selected 24 hours format */
    Component{
        id:idSetTime24HrsFormatComponent

        FocusScope{
            anchors.fill: parent

            Row{
                spacing: 3
                anchors
                {
                    left:parent.left
                    leftMargin:295
                    top:parent.top
                    topMargin:125
                }


                /* Hour component if user has selected 24 hours format */
                TumblerWithButtonComponent
                {
                    id:idHourTumbler24hr

                    width: 97
                    tumbler.model: 24

                    prStartingNumber: 0
                    prTumblerCurrentItemFocusImage: "qrc:/image/Set_Gfx_Date&TimeBg_n.png/Set_Gfx_Date&TimeBg_1_n.png"
                    prTumblerWidth: 97

                    onSigTumblerCurrentItemChanged:{
                        prHour = tumbler.currentIndex
                        prAMorPm = (prHour < 12) ? "AM" : "PM"
                    }

                    Component.onCompleted: {

                        tumbler.currentIndex = ((prAMorPm === "AM") ? (prHour % 12) : ((prHour % 12) + 12))
                        tumbler.contentItem.positionViewAtIndex(((prAMorPm === "AM") ? (prHour % 12) : ((prHour % 12) + 12)),
                                                                PathView.Center)
                    }

                    onPrIsTouchOnTumblerChanged: {
                        prIsFirstActionCanBeTakenOnRRERotation = false
                    }



                    Connections
                    {

                        target : ( idHourTumbler24hr.focus? cppHardkeyAdaptor : null )
                        onSigRotaryUpdate:
                        {
                            if(HardkeyEnum.HKEY_STATE_ROTATE_RIGHT === iKeyState)
                            {
                                idHourTumbler24hr.tumbler.contentItem.incrementCurrentIndex()
                            }
                            else if(HardkeyEnum.HKEY_STATE_ROTATE_LEFT === iKeyState)
                            {
                                idHourTumbler24hr.tumbler.contentItem.decrementCurrentIndex()
                            }
                        }

                        onSigRotaryPressed:
                        {
                            if(iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED
                                    || iKeyState === HardkeyEnum.HKEY_STATE_RELEASED)
                            {
                                cppSetupApp.qmlLog("GeneralSetupSetDateAndTime.qml::onSigRotaryPressed")
                                idMinTumbler24hr.forceActiveFocus()
                            }
                            else
                            {
                                //Do Nothing
                            }
                        }
                    }

                }


                /* Minute component if user has selected 12 hours format */
                TumblerWithButtonComponent
                {
                    id:idMinTumbler24hr

                    width: 123
                    tumbler.model: 60

                    prIsModelNumeric: false
                    prStartingNumber: 0
                    prTumblerCurrentItemFocusImage: "qrc:/image/Set_Gfx_Date&TimeBg_n.png/Set_Gfx_Date&TimeBg_3_n.png"
                    prTumblerWidth: 123

                    onSigTumblerCurrentItemChanged: {
                        prMinute = tumbler.currentIndex
                    }

                    Component.onCompleted: {
                        tumbler.currentIndex = prMinute
                        tumbler.contentItem.positionViewAtIndex(prMinute, PathView.Center)
                    }

                    onPrIsTouchOnTumblerChanged: {
                        prIsFirstActionCanBeTakenOnRRERotation = false
                    }


                    Connections
                    {
                        target : ( idMinTumbler24hr.focus? cppHardkeyAdaptor : null )
                        onSigRotaryUpdate:
                        {
                            if(HardkeyEnum.HKEY_STATE_ROTATE_RIGHT === iKeyState)
                            {
                                idMinTumbler24hr.tumbler.contentItem.incrementCurrentIndex()
                            }
                            else if(HardkeyEnum.HKEY_STATE_ROTATE_LEFT === iKeyState)
                            {
                                idMinTumbler24hr.tumbler.contentItem.decrementCurrentIndex()
                            }
                        }

                        onSigRotaryPressed:
                        {
                            if(iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED
                                    || iKeyState === HardkeyEnum.HKEY_STATE_RELEASED)
                            {
                                cppSetupApp.qmlLog("GeneralSetupSetDateAndTime.qml::onSigRotaryPressed")
                                idMinTumbler24hr.focus = false
                                idCheckboxfor24HrFormat.forceActiveFocus()
                            }
                            else
                            {
                                //Do nothing.
                            }
                        }
                    }
                }


                Connections
                {
                    target : ( prIsFirstActionCanBeTakenOnRRERotation) ? cppHardkeyAdaptor : null
                    onSigRotaryUpdate:
                    {
                        if(!prIsCheckBoxClickedStatus)
                        {
                            if(HardkeyEnum.HKEY_STATE_ROTATE_RIGHT === iKeyState || HardkeyEnum.HKEY_STATE_ROTATE_LEFT === iKeyState)
                            {
                                idHourTumbler24hr.forceActiveFocus()
                                prIsFirstActionCanBeTakenOnRRERotation = false
                            }
                        }
                        else
                        {
                            //Do Nothing.
                        }
                    }
                }
            }
        }
    }


    /* Date  component  */
    Component{
        id:idSetDateComponent

        FocusScope{
            anchors.fill: parent

            Row{
                id:idRow
                spacing: 3

                anchors
                {
                    left:parent.left
                    leftMargin:246
                    top:parent.top
                    topMargin:125
                }

                /* Date component to set day */
                TumblerWithButtonComponent
                {
                    id:idSetDay

                    width: 97
                    tumbler.model: 30

                    prStartingNumber: 1
                    prTumblerCurrentItemFocusImage: "qrc:/image/Set_Gfx_Date&TimeBg_n.png/Set_Gfx_Date&TimeBg_1_n.png"
                    prTumblerWidth: 97

                    onSigTumblerCurrentItemChanged:{
                        prDay = (tumbler.currentIndex + 1)
                    }

                    Component.onCompleted: {
                        tumbler.currentIndex = (cppDateAndTimeAdaptor.day - 1)
                        tumbler.contentItem.positionViewAtIndex((cppDateAndTimeAdaptor.day - 1), PathView.Center)
                    }
                    onPrIsTouchOnTumblerChanged: {
                        prIsFirstActionCanBeTakenOnRRERotation = false
                    }


                    Connections
                    {

                        target: ( idSetDay.activeFocus ? cppHardkeyAdaptor : null )
                        onSigRotaryUpdate:
                        {
                            if(HardkeyEnum.HKEY_STATE_ROTATE_RIGHT === iKeyState)
                            {
                                idSetDay.tumbler.contentItem.incrementCurrentIndex()
                            }
                            else if(HardkeyEnum.HKEY_STATE_ROTATE_LEFT === iKeyState)
                            {
                                idSetDay.tumbler.contentItem.decrementCurrentIndex()
                            }
                        }

                        onSigRotaryPressed:
                        {
                            if(iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED
                                    || iKeyState === HardkeyEnum.HKEY_STATE_RELEASED)
                            {
                                cppSetupApp.qmlLog("GeneralSetupSetDateAndTime.qml::onSigRotaryPressed")
                                idSetMonth.forceActiveFocus()
                            }
                            else
                            {
                                //Do Nothing
                            }
                        }
                    }

                }

                /* Date component to set Month */
                TumblerWithButtonComponent
                {
                    id:idSetMonth
                    width: 123
                    tumbler.model: [qsTr("Jan"), qsTr("Feb"), qsTr("Mar"), qsTr("Apr"),
                        qsTr("May"), qsTr("June"), qsTr("July"), qsTr("Aug"), qsTr("Sept"),
                        qsTr("Oct"), qsTr("Nov"), qsTr("Dec") ]
                    prIsModelNumeric: false
                    prTumblerCurrentItemFocusImage: "qrc:/image/Set_Gfx_Date&TimeBg_n.png/Set_Gfx_Date&TimeBg_2_n.png"
                    prTumblerWidth: 123
                    onSigTumblerCurrentItemChanged:{
                        prMonth = tumbler.currentIndex + 1
                        var iOldIndex = idSetDay.tumbler.currentIndex
                        var newDayCount = cppDateAndTimeAdaptor.validateTotalDays(prMonth, prYear)
                        idSetDay.tumbler.model = newDayCount

                        if(iOldIndex > newDayCount - 1)
                        {
                            iOldIndex = newDayCount - 1
                        }

                        idSetDay.tumbler.currentIndex = iOldIndex
                        idSetDay.tumbler.contentItem.positionViewAtIndex(iOldIndex, PathView.Center)
                    }
                    Component.onCompleted: {
                        tumbler.currentIndex = cppDateAndTimeAdaptor.month
                        tumbler.contentItem.positionViewAtIndex(cppDateAndTimeAdaptor.month, PathView.Center)
                    }

                    onPrIsTouchOnTumblerChanged: {
                        prIsFirstActionCanBeTakenOnRRERotation = false
                    }

                    Connections
                    {
                        target : ( idSetMonth.activeFocus ? cppHardkeyAdaptor : null )
                        onSigRotaryUpdate:
                        {
                            if(HardkeyEnum.HKEY_STATE_ROTATE_RIGHT === iKeyState)
                            {
                                idSetMonth.tumbler.contentItem.incrementCurrentIndex()
                            }
                            else if(HardkeyEnum.HKEY_STATE_ROTATE_LEFT === iKeyState)
                            {
                                idSetMonth.tumbler.contentItem.decrementCurrentIndex()
                            }
                        }

                        onSigRotaryPressed:
                        {
                            if(iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED
                                    || iKeyState === HardkeyEnum.HKEY_STATE_RELEASED)
                            {
                                idSetYear.forceActiveFocus()
                            }
                            else
                            {
                                //Do Nothing
                            }
                        }
                    }
                }


                /* Date component to set year */
                TumblerWithButtonComponent
                {
                    id:idSetYear

                    width: 135
                    tumbler.model: 18

                    prStartingNumber: prStartingYearValue
                    prTumblerCurrentItemFocusImage: "qrc:/image/Set_Gfx_Date&TimeBg_n.png/Set_Gfx_Date&TimeBg_3_n.png"
                    prTumblerWidth: 135

                    onSigTumblerCurrentItemChanged:{
                        prYear = (tumbler.currentIndex + prStartingYearValue)
                        var iOldIndex = idSetDay.tumbler.currentIndex
                        idSetDay.tumbler.model = cppDateAndTimeAdaptor.validateTotalDays(prMonth,prYear)
                        idSetDay.tumbler.contentItem.positionViewAtIndex(iOldIndex, PathView.Center)
                    }
                    Component.onCompleted: {
                        tumbler.currentIndex = (cppDateAndTimeAdaptor.year - prStartingYearValue)
                        tumbler.contentItem.positionViewAtIndex((cppDateAndTimeAdaptor.year - prStartingYearValue), PathView.Center)
                    }

                    onPrIsTouchOnTumblerChanged: {
                        prIsFirstActionCanBeTakenOnRRERotation = false
                    }

                    Connections
                    {
                        target : (idSetYear.activeFocus ? cppHardkeyAdaptor : null )
                        onSigRotaryUpdate:
                        {
                            if(HardkeyEnum.HKEY_STATE_ROTATE_RIGHT === iKeyState)
                            {
                                idSetYear.tumbler.contentItem.incrementCurrentIndex()
                            }
                            else if(HardkeyEnum.HKEY_STATE_ROTATE_LEFT === iKeyState)
                            {
                                idSetYear.tumbler.contentItem.decrementCurrentIndex()
                            }
                        }
                        onSigRotaryPressed:
                        {
                            /** To put each Component one at a time on screen, i have to false this component and active another focus.
                             *  else two components will be active focus.
                            **/
                            if(iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED
                                    || iKeyState === HardkeyEnum.HKEY_STATE_RELEASED)
                            {
                                idSetYear.focus = false
                                idCancelBtnDate.forceActiveFocus()
                            }
                            else
                            {
                                //Do Nothing.
                            }
                        }
                    }
                }
                Connections
                {
                    target : ( (prIsFirstActionCanBeTakenOnRRERotation) ? cppHardkeyAdaptor : null )
                    onSigRotaryUpdate:
                    {
                        if(HardkeyEnum.HKEY_STATE_ROTATE_RIGHT === iKeyState
                                || (HardkeyEnum.HKEY_STATE_ROTATE_LEFT === iKeyState))
                        {
                            idSetDay.forceActiveFocus()
                            prIsFirstActionCanBeTakenOnRRERotation = false
                        }
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        prHour = cppDateAndTimeAdaptor.hour
        prMinute = cppDateAndTimeAdaptor.minute
        prAMorPm = cppDateAndTimeAdaptor.amOrPm
    }
}
