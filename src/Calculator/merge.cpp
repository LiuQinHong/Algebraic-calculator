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
    int res = -1,k = 0;
    bool flag = true;

    // 两次遍历链表,去比较
    for(int i = 0;i < itemListTemp_i->mItemList.size();i++){
        std::list<Item*>::iterator itemlist_iter = itemListTemp_i->mItemList.begin();
        int j = i;
        while(j--){
            ++itemlist_iter;//由于每一次循环itemlist_iter都会指向表头,已经合并过的不需要再去匹配,直接移动到第i个
        }
        flag = true;

        for(std::list<Item*>::iterator nextList_iter = itemListTemp_i->mItemList.begin();
            nextList_iter!= itemListTemp_i->mItemList.end(); ++nextList_iter){
            // flag 标记 i 下一次循环开始
            if(flag){
                k = i+1;
                while(k--)
                    ++nextList_iter;//把nextList_iter移动到需要比较单项式
                if(nextList_iter == itemListTemp_i->mItemList.end())
                    break;
            }
            //匹配单项式是否相同并合并
            res = judgeItems((*(*itemlist_iter)),(*(*nextList_iter)),itemListTemp_i,nextList_iter);
            if(nextList_iter == itemListTemp_i->mItemList.end())//防止溢出
                --nextList_iter;

            flag = false;
        }
    }

    makeItem(itemListTemp_i);

    qDebug() << "for over";
    for(std::list<Item*>::iterator itemlist_iter = itemListTemp_i->mItemList.begin();
        itemlist_iter!= itemListTemp_i->mItemList.end(); ++itemlist_iter){
        qDebug() << "finaly str = " << (*itemlist_iter)->mStrItem.c_str();
    }

}

/********************************************
 * Funtion   : 递归匹配单项式是否相同,并处理
 * @origItem : 所要判断的单项式
 * @newItem  : 所要判断的单项式
*********************************************/
int judgeItems(Item& origItem, Item& newItem,ItemList* itemList,std::list<Item*>::iterator& iter)
{
    int res = -1;
    int itemp = 0,jtemp = 0;
    std::stringstream ss;
    qDebug() << "origItem0 = " << origItem.mStrItem.c_str();
    qDebug() << "newItem0 = " << newItem.mStrItem.c_str();
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
        //递归判断下一项是否和origItem相同,处理接连3项或者以上为同一类型情况
        if(iter != itemList->mItemList.end())
            judgeItems(origItem,(*(*iter)),itemList,iter);

        return NUMBERFLAG;
    }else if(res == ALPHAFLAG){

        int cof = 0;
        std::string cofStr;

        //qDebug() << "origItem = " << origItem.mStrItem.c_str();
        //qDebug() << "newItem = " << newItem.mStrItem.c_str();

        cof = extractItemcoef(origItem,newItem);

        ss.clear();
        ss << cof;
        ss >> cofStr;
        qDebug() << "cofStr = " << cofStr.c_str();
        restoreCellLsist(origItem,cofStr);

        qDebug() << "iter = " << *iter;

        if(*iter)
            itemList->mItemList.erase(iter++);

        qDebug() << "iter after erase = " << *iter;

        if(iter != itemList->mItemList.end()){
            qDebug() << "enter judgeItems ";
            judgeItems(origItem,(*(*iter)),itemList,iter);
        }

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
int judgeItem(Item& origItem, Item& newItem)
{
    Item origitemTemp = origItem;
    Item newtemTemp = newItem;
    qDebug() << "origitemTemp = " << origitemTemp.mStrItem.c_str();
    qDebug() << "newtemTemp = " << newtemTemp.mStrItem.c_str();


    if(origItem.mType == newItem.mType){
        if(origItem.mType == SIMPLENUMBER){
            return NUMBERFLAG;
        }else {
            extractItemcoeff(origitemTemp,newtemTemp);//排序前去掉系数,否则会影响判断
            origitemTemp.mStrItem.erase(0,1);//去掉符号,否则会影响排序结果,临时Item,不会对原Item修改
            newtemTemp.mStrItem.erase(0,1);
            qDebug() << "origitemTemp1 = " << origitemTemp.mStrItem.c_str();
            qDebug() << "newtemTemp1 = " << newtemTemp.mStrItem.c_str();
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
    int origCoef = 0,nextCoef = 0;
    bool oneCoefFlag = false;

    //遍历Cell链表提取系数
    for(std::list<Cell*>::iterator origList_iter = origItem.mCellList.begin();
        origList_iter!= origItem.mCellList.end(); ++origList_iter){
        if((*origList_iter)->mCellType == NUMBER){
            origCoef += atoi((*origList_iter)->mStrCell.c_str());
            if(*origList_iter)
                origItem.mCellList.erase(origList_iter++);
            oneCoefFlag = true;
        }
    }
    origItem.parseCelltoItem();
    qDebug() << "after parseCelltoItem and delcoef origItem = " << origItem.mStrItem.c_str();
    if(!oneCoefFlag)
        origCoef = 1;
    if(origItem.mStrItem.at(0) == '-')
        origCoef = -origCoef;
    oneCoefFlag = false;

    for(std::list<Cell*>::iterator nextList_iter = nextItem.mCellList.begin();
        nextList_iter!= nextItem.mCellList.end(); ++nextList_iter){
        if((*nextList_iter)->mCellType == NUMBER){
            nextCoef += atoi((*nextList_iter)->mStrCell.c_str());
            if(*nextList_iter)
                nextItem.mCellList.erase(nextList_iter++);
            oneCoefFlag = true;
        }
    }
    nextItem.parseCelltoItem();
    qDebug() << "after parseCelltoItem and delcoef nextItem = " << nextItem.mStrItem.c_str();

    if(!oneCoefFlag)
        nextCoef = 1;
    if(nextItem.mStrItem.at(0) == '-')
        nextCoef = -nextCoef;

    return (origCoef)+(nextCoef);
}

/********************************************
 * Funtion   : 剔除系数为1的单项式系数
 * @itemList : 单项式链表
*********************************************/
void makeItem(ItemList *itemList)
{
    delItemZero(itemList);
}

/********************************************
 * Funtion   : 处理系数并恢复cell链表
 * @origItem : 单项式
 * @cofStr   : 系数
*********************************************/
void restoreCellLsist(Item &origItem, std::__cxx11::string &cofStr)
{
    std::string cofStrTemp = cofStr;
    cofStrTemp.erase(0,1);
    //Cell cofCell(cofStrTemp);
    cofStr.append("*");
    if(cofStr.at(0) == '-'){
        origItem.mStrItem.erase(0,1);
        origItem.mStrItem.insert(0,cofStr);
    }
    else{
        origItem.mStrItem.replace(0,1,"+");
        origItem.mStrItem.insert(1,cofStr);
    }
    //origItem.mCellList.push_front(&cofCell);
    origItem.delAllCell();
    origItem.parseItemToCell(origItem.mStrItem);
    for(std::list<Cell*>::iterator celllist_iter = origItem.mCellList.begin(); celllist_iter!= origItem.mCellList.end(); ++celllist_iter) {
        qDebug() << (*celllist_iter)->mStrCell.c_str() << ":" << (*celllist_iter)->mCellType;
    }
}

int extractItemcoeff(Item &origItem, Item &nextItem)
{
    int origCof = 0,nextCof;
    qDebug() << "enter coeff";
    for(std::list<Cell*>::iterator origList_iter = origItem.mCellList.begin();
        origList_iter!= origItem.mCellList.end(); ++origList_iter){
        if((*origList_iter)->mCellType == NUMBER){
            origCof += atoi((*origList_iter)->mStrCell.c_str());
            if(*origList_iter)
                origItem.mCellList.erase(origList_iter++);
        }
    }
    origItem.parseCelltoItem();

    for(std::list<Cell*>::iterator nextList_iter = nextItem.mCellList.begin();
        nextList_iter!= nextItem.mCellList.end(); ++nextList_iter){
        if((*nextList_iter)->mCellType == NUMBER){
            nextCof += atoi((*nextList_iter)->mStrCell.c_str());
            if(*nextList_iter)
                nextItem.mCellList.erase(nextList_iter++);
        }
    }
    nextItem.parseCelltoItem();
    qDebug() << "exit coeff";
}

void delItemZero(ItemList *itemList)
{
    for(std::list<Item*>::iterator itemList_iter = itemList->mItemList.begin();
        itemList_iter!= itemList->mItemList.end(); ++itemList_iter){

        if((*itemList_iter)->mStrItem.at(1) == '0'){
            qDebug() << "at(1) == " << (*itemList_iter)->mStrItem.c_str();
            itemList->mItemList.erase(itemList_iter++);
        }
        eraseItemOne((*(*itemList_iter)));
    }
}

void eraseItemOne(Item &item)
{
    bool flag = false;
    for(std::list<Cell*>::iterator celllist_iter = item.mCellList.begin(); celllist_iter!= item.mCellList.end(); ++celllist_iter) {
        if(((*celllist_iter)->mStrCell == "1") && (item.mType != SIMPLENUMBER)){
            item.mCellList.erase(celllist_iter++);
            flag = true;
        }
    }
    if(flag)
        item.parseCelltoItem();

}
