#ifndef CWINDOWINGHELPER_H
#define CWINDOWINGHELPER_H

#include <QObject>
#include <QVector>
#include <functional>

using namespace std;

enum EPageRequestType
{
    PAGE_REQUESTED,
    PAGE_NOT_REQUESTED
};

/**
 * Structure of page data which have pageId, pageSize and PageRequestType
 **/
struct SPageData
{
    /** Start Id of the page **/
    int m_iPageID;
    /** Total items in a page **/
    int m_iPageSize;
    /** Request type of the page whether requested or pending to be requested **/
    EPageRequestType m_ePageRequestType;

    SPageData()
    {
        m_iPageID = -1;
        m_iPageSize = 0;
        m_ePageRequestType = PAGE_NOT_REQUESTED;
    }

    void reset()
    {
        m_iPageID = -1;
        m_iPageSize = 0;
        m_ePageRequestType = PAGE_NOT_REQUESTED;
    }
};

/**
 * @class CWindowingHelper
 * @brief Helper class which will have windowing mechanism, each screen which needs to implement
 *        windowing mechanism will have the object of this class. This helper class will provide
 *        the interfaces which the parent class can use, it will maintain an array for pending
 *        page request. Pending page request array will be priority based array,
 *        always the current requested page will be having the highest priority. Parent class will be able to
 *        set windowing param, reset windowing param, request page and request for next page. Page here
 *        corresponds to a window, each window will have a size which parent class will set.
 */
class CWindowingHelper : public QObject
{
    Q_OBJECT

public:
    CWindowingHelper();
    ~CWindowingHelper();

    /**
     * @brief initializeWindowingParam- Method to be called to initialize the windowing parameters in the starting
     *		                            after receiving the total items or whenever there is change in the total
     *		                            items. Whenever the parent class calls this method on change of the total items,
     *		                            buffer size should not be changed. total items might changed dynamically based
     *		                            on the requirement but buffer size once set with the limit should not be changed...
     * @param objPageRequestHandler - handler which points to parent class callback method which
     *			                      will be called whenever any page is to be fetched
     * @param iBufferSize - size of the buffer, the number of pages should be created
     *			            using buffer size
     * @param iTotalItems - total items that the parent class array contains.
     * @param iCurrentItem - item index which the parent screen want to get fetch first,
     *			             default value is 0, i.e the fetching will start from the first window.
     * @return void
     */
    void initializeWindowingParam(const std::function<void(SPageData)> &objPageRequestHandler, int iBufferSize, int iTotalItems, int iCurrentItem = 0);

    /**
     * @brief resetWindowingParam - Method to be called to reset the windowing parameters to default
     * @param void
     * @return void
     */
    void resetWindowingParam();

    /**
     * @brief requestPage- Method to be called to request for the page which the passed item belongs to,
     *			           parent screen can use the value returned to request for the data from service.
     *			           This method should be called whenever there is change in top item, like when the
     *			           user drags the scrollbar, or on swipe of the list or on fast scrolling via RRE,
     *			           in all these cases this method should be called
     * @param iItem - item index for which the page request needs to be sent.
     * @return void
     */
    void requestPage(const int iItem);

    /**
     * @brief requestNextPage - Method to be called whenever parent screen wants to request  service for
     *			                next page. Usually this method should be called from the parent screen whenever
     *			                the fetch is complete or the fetch complete is received from the service with data.
     * @param iReceivedDataStartIndex - iReceivedDataStartIndex - start index of the data received in the response/signal
     *			                        of the request send to service by parent screen
     * @return void
     */
    void requestNextPage(const int iReceivedDataStartIndex);

    /**
     * @brief requestFailed - Method to be called whenever a request for page is failed and data for the page is not received.
     *                        The respective page is marked as PAGE_NOT_REQUESTED, so that it can be fetched in again.
     * @param iReceivedDataStartIndex - start index of Page for which request was failed
     * @return void
     */
    void requestFailed(const int iReceivedDataStartIndex);

protected:

private:
    /**
     * @brief findingPendingPageAndRequest - Internal method to find if there is any page request pending. Start index from where the page request
     *			                             queue traversal should start is set based upon the last requested page id, if the last requested id's
     *			                             curent index is the last index of the queue then search should begin from begining other wise the search
     *			                             starts from the next index. During the traversal from the next index, if no page is found then again the
     *			                             search starts from begining till last requested page id's current index. After we find the pending page,
     *			                             request for the same using callback handler.
     * @param void
     * @return void
     */
    void findingPendingPageAndRequest();

    /**
     * @brief getPageIndexWRTPageID: Internal method to get the page index in the queue with respect to the
     *		  given page id. The index of a given page id in the array might change due
     *		  to the removal of pages from the array for which the data response have
     *		  been received
     * @param iPageId: data stored in the queue, it states the start id of the page.
     * @return index of the page in the queue
     */
    int getPageIndexWRTPageID(const int iPageId);

private:

    /**
    * Queue which will hold the index of first item of each page/window which are waiting to be fetched. This
    * will be a priority queue, based upon the request from parent class for the page/winodw it will be priortize
    **/
    QVector<SPageData> m_qPendingPageRequest;

    /* Start index of the data which currently needs to be fetched, it can also be said as window/page id */
    int m_iRequestedPageID;

    /* Buffer size to create pages */
    int m_iBufferSize;

    /* Last page ID stored in the page queue*/
    int m_iLastPageID;

    /* Total items in the parent array */
    int m_iTotalItems;

    /* std::function that will hold the callback funtion of the class that is using this class */
    std::function<void(SPageData)> m_objPageRequestHandler;

};

#endif // CWINDOWINGHELPER_H
