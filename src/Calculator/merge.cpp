#include <merge.h>
#include <qdebug.h>
#include <sstream>

/* list举例: a*b*c + a[0]*b[0]^2 + exp^2*exp[0] - a^(12)*exp[12]^(12) */
/********************************************
 * Funtion   : 合并同类项
 * @itemList : 传入要合并的代数式
*********************************************/
int mergeItem(ItemList *itemList)
{
    ItemList *itemListTemp_i = itemList;
    ItemList itemListTemp_j = *itemList;
    Item *itemTemp;
    Cell *cellTemp;

    int res = -1,i = 0;


    /* 两次遍历链表,去比较 */
    for(std::list<Item*>::iterator itemlist_iter = itemListTemp_i->mItemList.begin();
        itemlist_iter!= itemListTemp_i->mItemList.end(); ++itemlist_iter) {

        i++;
        itemListTemp_j.mItemList.pop_front();
        std::list<Item*>::iterator itemlist_jter = itemListTemp_j.mItemList.begin();

        for(itemlist_jter; itemlist_jter!= itemListTemp_j.mItemList.end(); ++itemlist_jter){

            /* 判断两个单项式是否相同 */

        }

    }

}

/********************************************
 * Funtion   : 递归匹配单项式是否相同,并处理
 * @origItem : 所要判断的单项式
 * @newItem  : 所要判断的单项式
*********************************************/
int judgeItems(Item &origItem, Item &newItem,ItemList *itemList,std::list<Item*>::iterator &iter)
{
    int res = -1;
    int itemp = 0,jtemp = 0;
    std::stringstream ss;

    res = judgeItem(origItem,newItem);
    if(res == NUMBERFLAG){/* 如果相同且为整数 */
        std::string istr = origItem.mStrItem;
        std::string jstr = newItem.mStrItem;
        if(istr.at(0) == '-'){
            istr.erase(0,1);
            itemp = -atoi(istr.c_str());
        }
        else {
            istr.erase(0,1);
            itemp = atoi(istr.c_str());
        }

        if(jstr.at(0) == '-'){
            jstr.erase(0,1);
            jtemp = -atoi(jstr.c_str());
        }
        else {
            jstr.erase(0,1);
            jtemp = atoi(jstr.c_str());
        }

        //合并求值并送到origItem,也就是每一次循环的首项,直接覆盖
        int sumtemp = (itemp)+(jtemp);
        ss << sumtemp;
        ss >> istr;
        if(sumtemp > 0){
            istr.insert(0,"+");
        }

        origItem.mStrItem = istr;
        if(*iter)
            itemList->mItemList.erase(iter++);

        if(iter != itemList->mItemList.end())
            judgeItems(origItem,(*(*iter)),itemList,iter);

        return NUMBERFLAG;
    }else if(res == ALPHAFLAG){

        /*int cof = 0;
        std::string cofStr;
        cof = extractItemcoef(origItem,newItem);

        ss.clear();
        ss << cof;
        ss >> cofStr;

        origItem.mStrItem.insert(1,cofStr);

        if(*iter)
            itemList->mItemList.erase(iter++);
        if(iter != itemList->mItemList.end())
            judgeItems(origItem,(*(*iter)),itemList,iter);*/

        return ALPHAFLAG;
    }else {
        return res;
    }
}

/********************************************
 * Funtion   : 判断单项式是否相同
 * @origItem : 所要判断的单项式
 * @newItem  : 所要判断的单项式
*********************************************/
int judgeItem(Item &origItem, Item &newItem)
{
    Item origitemTemp = origItem;
    Item newtemTemp = newItem;
    //qDebug() << " judge origitemTemp.mStrItem = " << origitemTemp.mStrItem.c_str();
    origitemTemp.mStrItem.erase(0,1);
    newItem.mStrItem.erase(0,1);

    if(origItem.mType == newItem.mType){
        if(origItem.mType == SIMPLENUMBER){
            return NUMBERFLAG;
        }else {
            //extractItemcoef(origitemTemp,newtemTemp);
            sort(origitemTemp.mStrItem.begin(),origitemTemp.mStrItem.end());
            sort(newtemTemp.mStrItem.begin(),newtemTemp.mStrItem.end());
            if(origitemTemp.mStrItem.compare(newtemTemp.mStrItem) == 0)
                return ALPHAFLAG;
            else
                return -1;
        }
    }
    else
        return -1;
}

/********************************************
 * Funtion    : 提取单项式系数
 * @origItem  : 单项式
 * @nextItem  : 单项式
 * return     : 系数
*********************************************/
int extractItemcoef(Item &origItem,Item &nextItem)
{
    int origCof = 0,nextCof;

    //遍历Cell链表提取系数
    for(std::list<Cell*>::iterator origList_iter = origItem.mCellList.begin();
        origList_iter!= origItem.mCellList.end(); ++origList_iter){
        if((*origList_iter)->mCellType == NUMBER){
            origCof += atoi((*origList_iter)->mStrCell.c_str());
            if(*origList_iter)
                origItem.mCellList.erase(origList_iter++);
        }
    }
    origItem.parseCelltoItem();

    if(origCof == 0)
        origCof = 1;
    if(origItem.mStrItem.at(0) == '-')
        origCof = -origCof;

    for(std::list<Cell*>::iterator nextList_iter = nextItem.mCellList.begin();
        nextList_iter!= nextItem.mCellList.end(); ++nextList_iter){
        if((*nextList_iter)->mCellType == NUMBER){
            nextCof += atoi((*nextList_iter)->mStrCell.c_str());
            if(*nextList_iter)
                nextItem.mCellList.erase(nextList_iter++);
        }
    }
    nextItem.parseCelltoItem();

    if(nextCof == 0)
        nextCof = 1;
    if(nextItem.mStrItem.at(0) == '-')
        nextCof = -nextCof;

    return (origCof)+(nextCof);
}

/********************************************
 * Funtion   : 判断单元类型
 * @origCell : 所要判断的单元
 * @newCell  : 所要判断的单元
*********************************************/
int judgeCells(Cell &cell,Item &item,std::list<Cell*>::iterator &iter,int &coef)
{

}
