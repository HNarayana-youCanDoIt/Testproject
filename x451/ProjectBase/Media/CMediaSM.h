/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CMediaSM.h
* @ingroup      HMIComponent
* @author       Rahul Madan
* CMediaSM      Class to implement Media SCT Interface
*/
#ifndef CMEDIASM_H
#define CMEDIASM_H

#include "Media/CMediaApplication.h"
#include "StateMachine_TML_HMI_SM.h"

/**
 * @class CMediaSM
 * @brief Class to implement Media SCT Interface (TML_HMI_SM::SCI_Media_OCB)
 */
class CMediaSM: public TML_HMI_SM::SCI_Media_OCB
{
public:
    CMediaSM(CMediaApplication& mediaApp);
    ~CMediaSM();

    // Methods overriden from Media SM interface
public:
    /**
     * @brief Call Back function inherited from SCI_Media_OCB for entering Media Module
     * @param void
     * @return void
     */
    virtual void enterMedia() override;

    /**
     * @brief Call Back function inherited from SCI_Media_OCB for exiting Media Module
     * @param void
     * @return void
     */
    virtual void exitMedia() override;

    /**
     * @brief Call Back function inherited from SCI_Media_OCB for entering into a Media loading state (screen) when no audio content info is yet received from media service
     * @param void
     * @return void
     */
    virtual void enterMediaLoadingScn() override;

    /**
     * @brief Call Back function inherited from SCI_Media_OCB for exiting Media loading screen when valid media audio content is received
     * @param void
     * @return void
     */
    virtual void exitMediaLoadingScn() override;

    /**
     * @brief Call Back function inherited from SCI_Media_OCB for entering Media Main screen when the media type is songs
     * @param void
     * @return void
     */
    virtual void enterMediaMainScn() override;

    /**
     * @brief Call Back function inherited from SCI_Media_OCB for exiting Media Main screen
     * @param void
     * @return void
     */
    virtual void exitMediaMainScn() override;

    /**
     * @brief Call Back function inherited from SCI_Media_OCB for entering Media Video screen when the media type is Video
     * @param void
     * @return void
     */
    virtual void enterMediaVideoViewerScn() override;

    /**
     * @brief Call Back function inherited from SCI_Media_OCB for exiting Media Video screen
     * @param void
     * @return void
     */
    virtual void exitMediaVideoViewerScn() override;

    /**
     * @brief Call Back function inherited from SCI_Media_OCB for entering the Media Browse main state
     * @param void
     * @return void
     */
    virtual void enterMediaBrowseMain() override;

    /**
     * @brief Call Back function inherited from SCI_Media_OCB for exiting Media Browse main state
     * @param void
     * @return void
     */
    virtual void exitMediaBrowseMain() override;

    /**
     * @brief Call Back function inherited from SCI_Media_OCB for entering the Media Browse screen which shall display all media categories to the user
     * @param void
     * @return void
     */
    virtual void enterMediaBrowseScn() override;

    /**
     * @brief Call Back function inherited from SCI_Media_OCB for exiting Media Browse screen
     * @param void
     * @return void
     */
    virtual void exitMediaBrowseScn() override;

    /**
     * @brief Call Back function inherited from SCI_Media_OCB for entering Media Browse Category screen which shall display list of items in the selected category
     * @param void
     * @return void
     */
    virtual void enterMediaBrowseCategoryScn() override;

    /**
     * @brief Call Back function inherited from SCI_Media_OCB for exiting Media Browse Category screen
     * @param void
     * @return void
     */
    virtual void exitMediaBrowseCategoryScn() override;

    /**
     * @brief Call Back function inherited from SCI_Media_OCB for entering the Media Picture viewer screen
     * @param void
     * @return void
     */
    virtual void enterMediaPictureViewerScn() override;

    /**
     * @brief Call Back function inherited from SCI_Media_OCB for exiting Media Picture viewer screen
     * @param void
     * @return void
     */
    virtual void exitMediaPictureViewerScn() override;

    /**
     * @brief Call Back function inherited from SCI_Media_OCB for entering the Media AUX screen
     * @param void
     * @return void
     */
    virtual void enterMediaAuxScn() override;

    /**
     * @brief Call Back function inherited from SCI_Media_OCB for exiting Media AUX screen
     * @param void
     * @return void
     */
    virtual void exitMediaAuxScn() override;

    /**
     * @brief Call Back function inherited from SCI_Media_OCB for
     *        entering Media AUXInGain screen.
     * @param void
     * @return void
     */
    void enterAUXInGainScn() override;

    /**
     * @brief Call Back function inherited from SCI_Media_OCB for
     *        exiting Media AUXInGain screen.
     * @param void
     * @return void
     */
    void exitAUXInGainScn() override;

private:
    // Parent class pointer
    /**
     * Reference to Media Application class object
     */
    CMediaApplication& mMediaApp;
};

#endif // CMEDIASM_H
