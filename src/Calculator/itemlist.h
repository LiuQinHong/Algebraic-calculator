#ifndef ITEMLIST_H
#define ITEMLIST_H

#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <item.h>

/* 单项式链表 */
class ItemList {
public:
    std::list<Item*> mItemList;
    std::string mExpressionStr;

    ItemList(){}
    ItemList(const std::string &str);

    void addItem(Item* item);
    void delItem(Item* item);
    void delAllItem(void);

    void deleteAllMark(std::string &s, const std::string &mark);
    int stringSplit(std::vector<std::string>& dst, const std::string src, const std::string& separator);
    void strReplace(std::string& str, const std::string& strsrc, const std::string& strdst);
    void exponentUnfold(void);
    std::string getExponent(std::string str);
    void printAllItem(void);
};

#endif // ITEMLIST_H
