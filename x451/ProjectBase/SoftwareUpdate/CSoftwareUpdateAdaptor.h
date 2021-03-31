/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CSoftwareUpdateAdaptor.h
 * @ingroup         HMIComponent
 * @author          Nishant Khandagale
 * CSoftwareUpdateAdaptor, an Adaptor for Software Update module,
 * CSoftwareUpdateAdaptor used to communicate between QML and Resource Layer.
 */

#ifndef CSOFTWAREUPDATEADAPTOR_H
#define CSOFTWAREUPDATEADAPTOR_H

#include <QObject>
#include "implementations/CSoftwareUpdateEnumsResource.h"
#include "Test/SoftwareUpdate/CSoftwareUpdateAdaptorTest.h"

class ISoftwareUpdateResource;

/**
 * @brief The CSoftwareUpdateAdaptor class: This singleton class contains methods to handle Software Update related functionality
 */
class CSoftwareUpdateAdaptor : public QObject
{
    Q_OBJECT

    //Properties

    /* Software Update Service availability (true : Available, false: Not Available) */
    Q_PROPERTY(bool swUpdateAvailability READ swUpdateAvailability NOTIFY sigSwUpdateAvailabilityChanged)

    /* Busy indicator visibility shown in Update button in Software Download screen (true : Visible, false: Not Visible) */
    Q_PROPERTY(bool busyIndicatorVisibility READ busyIndicatorVisibility WRITE setBusyIndicatorVisibility NOTIFY sigBusyIndicatorVisibilityChanged)

    /* To get ISO List */
    Q_PROPERTY(QStringList swISOList READ swISOList NOTIFY sigSWISOListChanged)

    /* To get name of the selected ISO File from ISO List screen */
    Q_PROPERTY(QString selectedISOName READ selectedISOName NOTIFY sigISONameSelected)

    /* To get index of the selected ISO File from ISO List screen */
    Q_PROPERTY(int selectedISOIndex READ selectedISOIndex NOTIFY sigSelectedISOIndexChanged)

public:

    /**
    * @brief	This function will return the software availibitity status and based on that
    *           status, Update button will be enabled/disabled
    * @param	void
    * @return	bool
    */
    bool swUpdateAvailability();

    /**
    * @brief	This function will update the software update service availibitity status
    *           and based on that status, Update button will be enabled/disabled
    * @param	bool availability : Software Update service availability
    * @return	void
    */
    void setSwUpdateAvailability(bool availability);

    /**
    * @brief	This function will return the busy indicator visibility.
    *           Busy indicator is shown on Update button release in Software Download screen.
    * @param	void
    * @return	bool (true : Visible, false : Not visible)
    */
    bool busyIndicatorVisibility();

    /**
    * @brief	This function will update the busy indicator visibility status.
    *           Busy indicator will be displayed on release of Update button and displayed till
    *           ISO List screen launches or any error popup disapears in Software Update screen
    * @param	bool visibility : Busy indicator visibility (true : Visible, false : Not visible)
    * @return	void
    */
    void setBusyIndicatorVisibility(bool visibility);

    /**
    * @brief	This function will return list of valid software update images
    * @param	void
    * @return	QStringList: list of valid software update images
    */
    QStringList swISOList();

    /**
    * @brief	This function will set list of valid software update images
    * @param	QStringList: list of valid software update images
    * @return	void
    */
    void setSWISOList(QStringList val);

    /**
    * @brief	This function will be called on recieving list of valid software update images
    * @param	void
    * @return	void
    */
    void swISOListReceived();

    /**
    * @brief	This function will be called from ISO File Confirmation screen to get name of the
    *           selected ISO file in ISO List screen
    * @param	void
    * @return	QString : Name of the selected ISO file in ISO List screen
    */
    QString selectedISOName();

    /**
    * @brief	This function will be called to set the selected ISO file name, which is selected
    *           from ISO List file
    * @param	QString selectedISOName : Name of the selected ISO file in ISO List screen
    * @return	void
    */
    void setSelectedISOName(QString selectedISOName);

    /**
    * @brief	This function will be called from ISO File Confirmation screen to get index of the
    *           selected ISO file in ISO List screen
    * @param	void
    * @return	int : index of the selected ISO file in ISO List screen
    */
    int selectedISOIndex();

    /**
    * @brief	This function will be called to set the selected ISO file index, which is selected
    *           from ISO List file
    * @param	int selectedISOIndex : index of the selected ISO file in ISO List screen
    * @return	void
    */
    void setSelectedISOIndex(int selectedISOIndex);

    /**
    * @brief	This function will be called from ISOList.qml to show the software update confirmation popup for the
    *           selected ISO file
    * @param	int index : index of the selected ISO file in ISO List screen
    * @param	QString &strPackageName : name of the selected ISO file in ISO List screen
    * @return	void
    */
    Q_INVOKABLE void showISOFileConfirmPopup(int index, QString strPackageName);

    /**
     * @brief	invErrorVerMismatchUpdate This function will be called from qml file to check whether there are any errors avaiable during version mismatch update
     * @param	int- specifies the kind of error
     * @return	void
     */
    Q_INVOKABLE int invErrorVerMismatchUpdate();

    /**
    * @brief	This function will be called from any error popup closure
    * @param	enum ESoftwareUpdateCancelType
    * @return	void
    */
    void cancelUpdateOnError(ESoftwareUpdateCancelType eCancelType);

    /**
     * @brief	This function will be called to show the software update error messages
     * @param	uint type of error message
     * @return	void
     */
    Q_INVOKABLE void invShowErrorMessage(uint type);

    /**
      * @brief	This function will be called to show the software update  availability error messages
      * @param	uint uiSwAvailabilityErrorType type of update message
      * @return	void
      */
    void showAvailabilityErrorMessage(uint uiSwAvailabilityErrorType );

    /**
    * @brief	This function will be called from qml file to check whether there are any updates avaiable
    * @param	void
    * @return	void
    */
    Q_INVOKABLE void checkForUpdateAttribute();

    /**
    * @brief	This function will be called from qml file to check whether there are any updates avaiable
    * @param	int index : Valid software update index to install
    * @return	void
    */
    Q_INVOKABLE void requestInstallPackageAttribute(int index);

    /**
    * @brief	This function get the instance of adaptor class.
    * @param	void
    * @return   pointer to CSoftwareUpdateAdaptor
    */
    static CSoftwareUpdateAdaptor* getInstance();

    static void releaseInstance();

    FRIEND_TEST(CSoftwareUpdateAdaptorTest, CheckIfSWAvailabilityVarIsInitializedToDefault);
    FRIEND_TEST(CSoftwareUpdateAdaptorTest, CheckSoftwareUpdateAdaptorInitializedVariables);
    FRIEND_TEST(CSoftwareUpdateAdaptorTest, coverage);
    /**
    * @brief	Destructor
    * @param	void
    * @return   None
    */
    ~CSoftwareUpdateAdaptor();

    /**
    * @brief	requestInstallOnVerMismatch: This method will install the updates on getting version mismatch event
    * @param	typeVerMismatch: type of version mismatch
    * @return	void
    */
    void requestInstallOnVerMismatch(uint uiTypeVersionMismatch);


signals:

    /**
    * @brief	This signal will emit Software Update Availability status
    * @param	void
    * @return	void
    */
    Q_SIGNAL void sigSwUpdateAvailabilityChanged();

    /**
    * @brief	This signal will emit busy indicator visibility status and will be used in
    *           Software Download screen to update busy indicator
    * @param	void
    * @return	void
    */
    Q_SIGNAL void sigBusyIndicatorVisibilityChanged();

    /**
    * @brief	This signal will emit ISO List on receiving ISO List
    * @param	void
    * @return	void
    */
    Q_SIGNAL void sigSWISOListChanged();

    /**
    * @brief	This signal will emit selected ISO file name after selection in ISO List screen
    * @param	void
    * @return	void
    */
    Q_SIGNAL void sigISONameSelected();

    /**
    * @brief	This signal will emit selected ISO file name after selection in ISO List screen
    * @param	void
    * @return	void
    */
    Q_SIGNAL void sigSelectedISOIndexChanged();

public slots:

private:
    /**
    * @brief	Constructor
    * @param	QObject *parent : Parent class instance
    * @return   None
    */
    explicit CSoftwareUpdateAdaptor(QObject *parent = nullptr);

    /* Static pointer for CSoftwareUpdateAdaptor instance */
    static CSoftwareUpdateAdaptor* m_pSoftwareUpdateAdaptor;

    /* Pointer to ISoftwareUpdateResource instance */
    ISoftwareUpdateResource* m_pSoftwareUpdateResource;

    /* This variable holds the ISO List */
    QStringList m_SWISOList;
    /* This variable holds the selected package name from ISO List screen */
    QString m_strSelectedISOName;
    /* This variable holds the selected package index from ISO List screen */
    int m_iSelectedISOIndex;

    /* Software Update Service availability (true : Available, false: Not Available) */
    bool m_bSwUpdateAvailability;

    /* Busy indicator visibility shown in Update button in Software Download screen (true : Visible, false: Not Visible) */
    bool m_bBusyIndicatorVisibility;

};

#endif // CSOFTWAREUPDATEADAPTOR_H
