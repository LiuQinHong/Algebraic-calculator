#include "calculator.h"
#include <QApplication>
#include <merge.h>
#include <algorithm>
#include <qdebug.h>
#include <iostream>
#include <separation.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator w;
    //w.show();
    QString den;
    QString mole;
    ItemList *denItemList;
    ItemList *moleItemList;

    Separation("a/b + c/d + (exp[0]^2 + 2)/(pi[0]^4 +  exp[0])", den, mole);

    qDebug() << den;
    qDebug() << mole;

    denItemList = new ItemList(den.toStdString());

    qDebug() << "denItemList = " << denItemList->mExpressionStr.c_str();
    denItemList->allExponentUnFold();
    qDebug() << "denItemList = " << denItemList->mExpressionStr.c_str();

    moleItemList = new ItemList(mole.toStdString());

    Merge denMerge(denItemList);
    denMerge.mergeItem();

    Merge moleMerge(moleItemList);
    moleMerge.mergeItem();

    qDebug() << moleItemList->mExpressionStr.c_str();
    qDebug() << denItemList->mExpressionStr.c_str();


    return 0;
}
