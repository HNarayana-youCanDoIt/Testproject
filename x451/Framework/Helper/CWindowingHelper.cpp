#include "CWindowingHelper.h"
#include "logging.h"

CWindowingHelper::CWindowingHelper():m_iRequestedPageID(-1),
    m_iBufferSize(-1),
    m_iLastPageID(-1),
    m_iTotalItems(0),
    m_objPageRequestHandler(nullptr)
{

}

CWindowingHelper::~CWindowingHelper()
{

}

void CWindowingHelper::initializeWindowingParam(const std::function<void(SPageData)> &objPageRequestHandler, int iBufferSize, int iTotalItems, int iCurrentItem)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s iBufferSize:%d iTotalItems:%d iCurrentItem:%d",__FUNCTION__,iBufferSize,iTotalItems,iCurrentItem);

    m_iBufferSize = iBufferSize;
    m_objPageRequestHandler = objPageRequestHandler;

    int iIndex = -1;
    int iTotalPages = 0;
    int iStartIndexOfData = -1;
    SPageData objPageData;

    /**
    * First time entry, total items will be set for the first time
    **/
    if(0 == m_iTotalItems)
    {
        iStartIndexOfData = 0;
        iIndex = iStartIndexOfData;
    }
    /**
    * Next time entry which means that total items are changed and we
    * have to rearrange the pending page request queue to create next set of pages and add them in the queue
    **/
    else
    {
        int iLastPageIndex = getPageIndexWRTPageID((m_iLastPageID));

        /**
        * If we have to create a new pages to add items received in new total items
        **/
        if((iTotalItems / iBufferSize) > (m_iTotalItems / iBufferSize))
        {
            /**
            * If last page of previous total items is already in the page request queue
            **/
            if( -1 != iLastPageIndex)
            {
                /**
                * Check if page request is already sent for the last page, if it is sent then change the request
                * type of page from PAGE_REQUESTED to PAGE_NOT_REQUESTED, so that we can sent the page request again
                * to fetch the remaining items
                **/
                if(PAGE_REQUESTED == m_qPendingPageRequest.at(iLastPageIndex).m_ePageRequestType)
                {
                    objPageData.reset();
                    objPageData.m_iPageID = m_qPendingPageRequest.at(iLastPageIndex).m_iPageID;
                    objPageData.m_iPageSize = m_qPendingPageRequest.at(iLastPageIndex).m_iPageSize;
                    objPageData.m_ePageRequestType = PAGE_NOT_REQUESTED;

                    m_qPendingPageRequest.replace(iLastPageIndex,objPageData);
                }

                /**
                * Set the page id to the next id to the queue's last page so that we can start adding
                * the new page id in the queue
                **/
                iIndex = (m_iTotalItems / iBufferSize) + 1;
            }
            /**
            * If last page of previous total items is not in the queue that means we have already sent the request for
            * the last page and we have also got the response of it, so add the last page again in the queue to fetch
            * the items again. Set the page id to last page so that we can start adding from the there in the queue
            **/
            else
            {
                iIndex = (m_iTotalItems / iBufferSize);
            }
            iStartIndexOfData = iIndex * iBufferSize;
        }
        else
        {
            /**
            * If last page of previous total items is already in the page request queue
            **/
            if(-1 != iLastPageIndex)
            {
                /**
                * Check if page request is already sent for the last page, if it is sent then change the request
                * type of page from PAGE_REQUESTED to PAGE_NOT_REQUESTED, so that we can sent the page request again
                * to fetch the remaining items
                **/
                if(PAGE_REQUESTED == m_qPendingPageRequest.at(iLastPageIndex).m_ePageRequestType)
                {
                    objPageData.reset();
                    objPageData.m_iPageID = m_qPendingPageRequest.at(iLastPageIndex).m_iPageID;
                    objPageData.m_iPageSize = m_qPendingPageRequest.at(iLastPageIndex).m_iPageSize;
                    objPageData.m_ePageRequestType = PAGE_NOT_REQUESTED;

                    m_qPendingPageRequest.replace(iLastPageIndex,objPageData);
                }
            }
            /**
            * If last page of previous total items is not in the queue that means we have already sent the request for
            * the last page and we have also got the response of it, so add the last page again in the queue to fetch
            * the items again.
            **/
            else
            {
                iIndex = (m_iTotalItems / iBufferSize);
                iStartIndexOfData = iIndex * iBufferSize;
            }
        }
    }

    iTotalPages = iTotalItems / iBufferSize;
    m_iTotalItems = iTotalItems;

    /**
    * First check if page id is set, if it is not set then there is not point adding the pages in the queue, it indicates that they already exist
    **/
    if(-1 != iStartIndexOfData)
    {
        while(iIndex < iTotalPages)
        {
            objPageData.reset();
            objPageData.m_iPageID = iStartIndexOfData;
            objPageData.m_iPageSize = iBufferSize;
            m_qPendingPageRequest.append(objPageData);
            iStartIndexOfData += iBufferSize;
            iIndex++;
        }

        /**
        * For the case where last page does not contain same item as the buffer size, store that many items in more page.
        * Page size can differ from buffer size in one scenario when each page does not contain items that are equal to buffer
        * size. There can be a scenario where total items are 1022 and buffer size given is 100. In this scenario there will
        * be 10 pages with item as same as buffer size but the last page will contain only 22 items. So when parent class request
        * for last page it should know that it only have to request for 22 items and not for 100 items
        **/
        if((iTotalItems % iBufferSize) > 0)
        {
            objPageData.reset();
            objPageData.m_iPageID = iStartIndexOfData;
            objPageData.m_iPageSize = iTotalItems % iBufferSize;
            m_qPendingPageRequest.append(objPageData);
        }

        m_iLastPageID = iStartIndexOfData;
    }

    if(-1 == m_iRequestedPageID)
    {
        /**
        * This is for the first time where windowing parameters are getting initialized for the first time
        **/
        if(m_objPageRequestHandler)
        {
            objPageData.reset();
            objPageData.m_iPageID = m_qPendingPageRequest.at(iCurrentItem).m_iPageID;
            objPageData.m_iPageSize = m_qPendingPageRequest.at(iCurrentItem).m_iPageSize;
            objPageData.m_ePageRequestType = PAGE_REQUESTED;

            m_qPendingPageRequest.replace(iCurrentItem,objPageData);

            m_iRequestedPageID = m_qPendingPageRequest.at(iCurrentItem).m_iPageID;
            m_objPageRequestHandler(m_qPendingPageRequest.at(iCurrentItem));
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s: m_objPageRequestHandler is NULL",__FUNCTION__);
        }
    }
    else
    {
        /**
        * Find if there is any page request pending for the pages in the queue and request
        **/
        findingPendingPageAndRequest();
    }

}

void CWindowingHelper::resetWindowingParam()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s",__FUNCTION__);
    m_iBufferSize = -1;
    m_iTotalItems = 0;
    m_iRequestedPageID = -1;
    m_iLastPageID = -1;
    m_objPageRequestHandler = NULL;
    m_qPendingPageRequest.clear();
}

void CWindowingHelper::requestPage(const int iItem)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s iItem: %d",__FUNCTION__,iItem);

    /**
     * First check whether we still have some items in the pending page request queue, if the queue is empty then return -1
     **/
    if(m_qPendingPageRequest.size() > 0)
    {
        //Find the page ID of the sent item
        int iPageID = (iItem / m_iBufferSize) * m_iBufferSize;

        //Find the index in the array to which this page id belongs to
        int iIndex = getPageIndexWRTPageID(iPageID);

        /**
         * Check whether the page request has already been sent, if not then set the page type as requested
         * and return the page id marking it as a requested page id else return -1
         **/
        if(m_objPageRequestHandler)
        {
            if(iIndex >= 0)
            {
                if(PAGE_NOT_REQUESTED == m_qPendingPageRequest.at(iIndex).m_ePageRequestType)
                {
                    SPageData objPageData;
                    objPageData.m_iPageID = m_qPendingPageRequest.at(iIndex).m_iPageID;
                    objPageData.m_iPageSize = m_qPendingPageRequest.at(iIndex).m_iPageSize;
                    objPageData.m_ePageRequestType = PAGE_REQUESTED;

                    m_qPendingPageRequest.replace(iIndex,objPageData);

                    m_iRequestedPageID = m_qPendingPageRequest.at(iIndex).m_iPageID;
                    m_objPageRequestHandler(m_qPendingPageRequest.at(iIndex));
                }
                else
                {
                    //Recheck the background loading progress and initiate getItems for pages which are not fetched yet
                    findingPendingPageAndRequest();
                }
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s: iIndex:%d out of bounds",__FUNCTION__,iIndex);
            }
        }
        else
        {
            //Recheck the background loading progress and initiate getItems for pages which are not fetched yet
            findingPendingPageAndRequest();
        }
    }
}

void CWindowingHelper::requestNextPage(const int iReceivedDataStartIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s iReceivedDataStartIndex: %d",__FUNCTION__,iReceivedDataStartIndex);

    /**
     * First check whether we still have some items in the pending page request queue, if the queue is empty then return -1
     **/
    if(m_qPendingPageRequest.size() > 0)
    {
        /**
         * Find if there is any page request pending for the pages in the queue and request
         **/
        findingPendingPageAndRequest();

        /** Find the index in the array to which received page id belongs to **/
        int iReceivedPageIndex = getPageIndexWRTPageID(iReceivedDataStartIndex);
        /** Remove received page from m_aryPendingPageRequest **/
        if((iReceivedPageIndex >= 0) && (iReceivedPageIndex < m_qPendingPageRequest.size()))
        {
            m_qPendingPageRequest.remove(iReceivedPageIndex);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s: iReceivedPageIndex:%d out of range",__FUNCTION__,iReceivedPageIndex);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s: No pending pages left in the queue",__FUNCTION__);
    }
}

void CWindowingHelper::requestFailed(const int iReceivedDataStartIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s",__FUNCTION__);

    /** Find the index in the array to which received page id belongs to **/
    int iReceivedPageIndex = getPageIndexWRTPageID(iReceivedDataStartIndex);

    /** Marking the page as PAGE_NOT_REQUESTED for which request was failed **/
    if(iReceivedPageIndex >= 0)
    {
        SPageData objPageData;
        objPageData.m_iPageID = m_qPendingPageRequest.at(iReceivedPageIndex).m_iPageID;
        objPageData.m_iPageSize = m_qPendingPageRequest.at(iReceivedPageIndex).m_iPageSize;
        m_qPendingPageRequest.replace(iReceivedPageIndex,objPageData);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s: iReceivedPageIndex:%d out of range",__FUNCTION__,iReceivedPageIndex);
    }

}

void CWindowingHelper::findingPendingPageAndRequest()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s",__FUNCTION__);

    /** Find the index in the array to which requested  page id belongs to **/
    int iRequestedPageIndex = getPageIndexWRTPageID(m_iRequestedPageID);
    bool bPageFound = false;
    SPageData objPageData;
    /** start search from next page **/
    int iStartIndex = iRequestedPageIndex + 1;

    while(iStartIndex < m_qPendingPageRequest.size())
    {
        if(m_objPageRequestHandler)
        {
            if(PAGE_NOT_REQUESTED == m_qPendingPageRequest.at((iStartIndex)).m_ePageRequestType)
            {
                objPageData.reset();
                objPageData.m_iPageID = m_qPendingPageRequest.at(iStartIndex).m_iPageID;
                objPageData.m_iPageSize = m_qPendingPageRequest.at(iStartIndex).m_iPageSize;
                objPageData.m_ePageRequestType = PAGE_REQUESTED;
                m_qPendingPageRequest.replace(iStartIndex,objPageData);

                m_iRequestedPageID = m_qPendingPageRequest.at(iStartIndex).m_iPageID;
                bPageFound = true;
                m_objPageRequestHandler(m_qPendingPageRequest.at(iStartIndex));
                break;
            }
            else
            {
                //Do Nothing
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s: m_objPageRequestHandler is NULL",__FUNCTION__);
        }
        iStartIndex++;
    }

    /**
     * This condition is only for the case where the next page is not last page and we are not able to find any page for which the request
     * has still not been sent, in this scenario, begin the search from begining of the array till the last requested page index
     **/
    if(bPageFound == false)
    {
        for(iStartIndex = 0; iStartIndex < iRequestedPageIndex; iStartIndex++)
        {
            if(m_objPageRequestHandler)
            {
                if(PAGE_NOT_REQUESTED == m_qPendingPageRequest.at(iStartIndex).m_ePageRequestType)
                {
                    objPageData.reset();
                    objPageData.m_iPageID = m_qPendingPageRequest.at(iStartIndex).m_iPageID;
                    objPageData.m_iPageSize = m_qPendingPageRequest.at(iStartIndex).m_iPageSize;
                    objPageData.m_ePageRequestType = PAGE_REQUESTED;
                    m_qPendingPageRequest.replace(iStartIndex,objPageData);

                    m_iRequestedPageID = m_qPendingPageRequest.at(iStartIndex).m_iPageID;
                    m_objPageRequestHandler(m_qPendingPageRequest.at(iStartIndex));
                    break;
                }
                else
                {
                    //Do Nothing
                }
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s: m_objPageRequestHandler is NULL",__FUNCTION__);
            }
        }
    }
}

int CWindowingHelper::getPageIndexWRTPageID(const int iPageId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,"%s iPageId: %d",__FUNCTION__,iPageId);

    int bFoundPageIndex = -1;

    for(int iIndex = 0; iIndex < m_qPendingPageRequest.size(); iIndex++)
    {
        if(m_qPendingPageRequest.at(iIndex).m_iPageID == iPageId)
        {
            bFoundPageIndex = iIndex;
            break;
        }
        else
        {
            //Do Nothing
        }
    }

    return bFoundPageIndex;
}
