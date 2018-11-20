#ifndef MERGE_H
#define MERGE_H

#include <itemlist.h>
#include <item.h>
#include <cell.h>
#include <algorithm>

enum ItemFlag {
    NUMBERFLAG,         //纯数字
    ALPHAFLAG,          //字母
};

int mergeItem(ItemList* itemList);
int judgeItem(Item& origItem, Item& newItem);
int judgeItems(Item &origItem, Item &newItem,ItemList *itemList,std::list<Item*>::iterator &iter);
int extractItemcoef(Item &origItem,Item &nextItem);
//int judgeCells(Cell &Cell,Item &item,std::list<Cell*>::iterator &iter,int &coef);

#endif // MERGE_H
