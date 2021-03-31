/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CGenericListModel.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CGenericListModel, a list generic list model,
 * Used to handle element position and dynamically add remove elements in list,
 */
//____________________________________________________________________________

#ifndef CGENERICLISTMODEL_H
#define CGENERICLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>

//____________________________________________________________________________
/*!
 * @class   CGenericListModel
 * @brief   This class shall implement generic list data model flow.
 */
class CGenericListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    /** ***********************************************************************
     ** @category    ENUMS
     ** ***********************************************************************/

    /*!
     * @enum    EGenericListModelRoles
     * @brief   This enum shall hold the values that shall be used by generic list model
     * to update the data in the qml view.
     */
    enum EGenericListModelRoles
    {
        // This role holds the Item type of the list item.
        LIST_ITEM_TYPE_ROLE = Qt::UserRole + 1
    };

public:

    /** ***********************************************************************
     ** @category    METHODS of CGenericListModel class
     ** ***********************************************************************/

    /**
    * @brief    CGenericListModel constructor for CGenericListModel class.
    * @param    QObject. The pointer of parent class.
    * @return   NA.
    **/
    CGenericListModel(QObject* pParent = nullptr);
    //____________________________________________________________________________
    /**
    * @brief    ~CGenericListModel destructor for CGenericListModel class.
    * @param    NA.
    * @return   NA.
    **/
    ~CGenericListModel();
    //____________________________________________________________________________
    /**
    * @brief    resetListModel: function to reset list model.
    * @param    void.
    * @return   void.
    **/
    void resetListModel();
    //____________________________________________________________________________
    /**
    * @brief    getIndexForElementType: function to get index for list element with given type.
    * @param    int type for list element.
    * @return   int index for list element.
    **/
    int getIndexForElementType(int iListElementType);
    //____________________________________________________________________________
    /**
    * @brief    tryAddListElementTypeAtStart: function to add list element given for given type at start of list.
    * @param    int type for list element to add.
    * @return   int index position where list element is added, -1 when fail to add.
    **/
    int tryAddListElementTypeAtStart(int iListElementType);
    //____________________________________________________________________________
    /**
    * @brief    tryAddListElementTypeAtEnd: function to add list element given for given type at end of list.
    * @param    int type for list element to add.
    * @return   int index position where list element is added, -1 when fail to add.
    **/
    int tryAddListElementTypeAtEnd(int iListElementType);
    //____________________________________________________________________________
    /**
    * @brief    tryAddListElementTypeAtIndex: function to add list element given for given type at given index.
    * @param    int type for list element to add.
    * @param    int index position to add list element at.
    * @return   int index position where list element is added, -1 when fail to add.
    **/
    int tryAddListElementTypeAtIndex(int iListElementType, int iIndex);
    //____________________________________________________________________________
    /**
    * @brief    tryAddListElementTypeBeforeElement: function to add list element given for given type before mentioned list element.
    * @param    int type for list element to add.
    * @param    int previous list element.
    * @return   int index position where list element is added, -1 if add flow fails.
    **/
    int tryAddListElementTypeBeforeElement(int iListElementType, int iListPrevElementType);
    //____________________________________________________________________________
    /**
    * @brief    tryAddListElementTypeAfterElement: function to add list element given for given type after mentioned list element.
    * @param    int type for list element to add.
    * @param    int next list element.
    * @return   int index position where list element is added, -1 when fail to add.
    **/
    int tryAddListElementTypeAfterElement(int iListElementType, int iListNextElementType);
    //____________________________________________________________________________
    /**
    * @brief    tryRemoveListElementType: function to remove list element given for given type.
    * @param    int type for list element to remove.
    * @return   bool TRUE when list element added, otherwise FALSE.
    **/
    bool tryRemoveListElementType(int iListElementType);

    /** ***********************************************************************
     ** @category    OVERRIDEN METHODS of QAbstractListModel class
     ** ***********************************************************************/

    /**
    * @brief    roleNames: function inherited from QAbstractListModel,
    *  Used to get role names
    * @param    void.
    * @return   QHash<int, QByteArray> : holds model's role names
    **/
    QHash<int, QByteArray> roleNames() const override;
    //____________________________________________________________________________
    /**
    * @brief    rowCount: function inherited from QAbstractListModel,
    * Used to get row count.
    * @param    QModelIndex : The index is used to locate an item in the model.
    * @return   int : holds row count.
    **/
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    //____________________________________________________________________________
    /**
    * @brief    data: function inherited from QAbstractListModel,
    * Used to get data linked to given role and present at given index.
    * @param    (index)QModelIndex : The index is used to locate an item in the model.
    * (role)int : holds the role name of data to be extract from QModelIndex item.
    * @return   QVariant : data stored under the given role for the item referred to by the index.
    **/
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    //____________________________________________________________________________
    /**
     * @brief   setData: Sets the role data for the item at index to value
     * @param   index: The index for which value to be set
     * @param   value: The value to be set for the role
     * @param   role: The role data to be modified
     * @return  Returns true if successful; otherwise returns false.
     */
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    //____________________________________________________________________________

private:
    /**
    * @brief m_listGenericModellist: int List to hold the information of each item in generic list.
    */
    QList<int> m_listGenericModellist;
};

#endif // CGENERICLISTMODEL_H
