/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CFunctor.h
* @ingroup      HMIComponent
* @author       Guru Alingal
* @brief A generic functor defnition that can be used for call backs.
*/

template<class T>
class CFunctor
{
private:
    /**
     *@brief pointer to a funtion
     */
    void (T::*m_funcPtr)(void);

    /**
     * @brief m_objPtr pointer to a class whose method needs to be invoked using m_funcPtr
     */
    T* m_objPtr;

public:
    /**
     * @brief CFunctor Constructor of the functor
     * @param obj - pointer to the class whose method needs to be invoked.
     * @param funcPtr - pointer to a function that needs to be invoked.
     */
    CFunctor(T* obj, void (T::*funcPtr)(void))
    {
        m_objPtr = obj;
        m_funcPtr = funcPtr;
    }

    /**
     * @brief update the ponters stored in m_objPtr and m_funcPtr
     * @param obj - pointer to the class whose method needs to be invoked.
     * @param funcPtr - pointer to a function that needs to be invoked.
     */
    void update(T* obj, void (T::*funcPtr)(void))
    {
        m_objPtr = obj;
        m_funcPtr = funcPtr;
    }

    /**
     * @brief operator () - Overloaded operator () to make the function calls.
     * @param void
     * @return void
     */
    void operator ()()
    {
        if((NULL != m_objPtr) &&
                ( NULL != m_funcPtr) )
        {
            (m_objPtr->*m_funcPtr)();
        }
    }

};
