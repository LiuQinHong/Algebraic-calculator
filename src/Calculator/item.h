#ifndef ITEM_H
#define ITEM_H

#include <QList>
#include <QVector>
#include <QString>


class Item;

enum MathSymbolType {
    NUMBER				= 0,
    ADDITION			= 1,	// +
    SUBTRACTION         = 2,	// -
    MULTIPLICATION		= 3,	// *
    DIVISIONMETHOD		= 4,	// /
    EXPONENTIATION		= 5,	// ^
    PI					= 6,	// 圆周率
    EXP					= 7,	// e
};

/* 单项式 */
class Item {
public:
    QString mStrItem;
    enum MathSymbolType mType;//单项式类型

    /* 目前只实现一种赋值方法,有需要可以加实现方法 */
    Item();
    Item(QString& strItem, enum MathSymbolType type):mStrItem(strItem),mType(type){}
};

/* 单项式链表 */
class ItemList {
public:
    QList<Item*> mItemList;
    void addItem(Item* item);
    void delItem(Item* item);

};

#endif // ITEM_H
