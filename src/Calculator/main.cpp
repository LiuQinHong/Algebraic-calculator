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

    ItemList testList("111+a*b*y-a*y*2*b+b*2*a*y-a*b*y+111-a*b*y");
    mergeItem(&testList);
    return a.exec();
}
