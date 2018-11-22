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
    //+1*a*exp*pi*a[0]*exp[0]*pi[0]*1^a*a^2*exp^2*pi^2*a[0]^2*exp[0]^2*pi[0]^2
    ItemList testList("111+111+111+a*b*y-a*y*2*b+b*2*a*y-a*b*y+111-a*b*y+a[0]*b[0]*c[0]*2-a[0]*b[0]*c[0]*2+a*exp*pi"
                      "+a[0]*exp[0]*pi[0]-2*a*pi*exp-222");
    ItemList testList1("111+222");
    testList1.printAllItem();
    Merge merge(&testList1);
    merge.mergeItem();
    qDebug() << "mExpressionStr" << testList1.mExpressionStr.c_str();
    return 0;
}
