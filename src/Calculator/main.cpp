#include "calculator.h"
#include <QApplication>
#include <merge.h>
#include <algorithm>
#include <qdebug.h>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator w;
    //w.show();
    int aa = -1;
    int b = -2;
    int i = 0,k,res = -1;
    ItemList testList("123-456+678+abc+111+aaa+222+333");

    bool flag = true;

    for(int j = 0;j < testList.mItemList.size();j++){

        std::list<Item*>::iterator itemlist_iter = testList.mItemList.begin();
        k = j;
        qDebug() << "k = " << k;
        while(k--){
            ++itemlist_iter;
        }
        qDebug() << "first str = " << (*itemlist_iter)->mStrItem.c_str();
        flag = true;

        for(std::list<Item*>::iterator nextList_iter = testList.mItemList.begin();
            nextList_iter!= testList.mItemList.end(); ++nextList_iter){
            if(flag){
                i = j+1;
                while(i--)
                    ++nextList_iter;
                if(nextList_iter == testList.mItemList.end())
                    break;
            }
           qDebug() << "next str = " << (*nextList_iter)->mStrItem.c_str();
           qDebug() << "first1 str = " << (*itemlist_iter)->mStrItem.c_str();
            res = judgeItems((*(*itemlist_iter)),(*(*nextList_iter)),&testList,nextList_iter);
            if(nextList_iter == testList.mItemList.end())
                --nextList_iter;

            flag = false;
            /*if(res == -1)
                continue;*/

        }
    }
    qDebug() << "for over";
    for(std::list<Item*>::iterator itemlist_iter = testList.mItemList.begin();
        itemlist_iter!= testList.mItemList.end(); ++itemlist_iter){
        qDebug() << "finaly str = " << (*itemlist_iter)->mStrItem.c_str();
    }



    //int res = judgeItems(origItem,newItem);

    int &cc = aa;
    cc = 10;

    qDebug() << aa;

    return a.exec();
}
