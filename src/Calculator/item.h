#ifndef ITEM_H
#define ITEM_H

#include <QList>
#include <QVector>
#include <QString>


class Item;

enum MathSymbolType {
    PI,                     // 圆周率
    EXP,                    // e
    ALPHA,                  // 字母包含系数 不包含带下标的字母
    NUMBER,                 // 纯number
    EXPONENTIATION,         // 带下标的没有幂的字母 ^
    EXPONENTIATIONSUBSCRIPT,// 带下标的有幂的字母 ^
    NUMBERMIXALPHASUBSCRIPT,// 带下标的字母
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
