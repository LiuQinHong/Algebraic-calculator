#include <itemlist.h>
#include <qdebug.h>

ItemList::ItemList(const std::string &str)
    :mExpressionStr(str)
{
    int iCount = 0;
    std::vector<std::string> dst;
    char acBuf[1024] = {0};
    int iPos = 0;

    if (str.empty())
        return;

    /* 去掉空格 */
    deleteAllMark(mExpressionStr, " ");
    deleteAllMark(mExpressionStr, "\t");
    deleteAllMark(mExpressionStr, "\r");
    deleteAllMark(mExpressionStr, "\n");

    if ((mExpressionStr.at(0) != '+') &&  mExpressionStr.at(0) != '-') {
        acBuf[iPos] = '+';
        iPos++;
    }

    for (size_t i = 0; i < mExpressionStr.size(); i++) {
        if ((mExpressionStr.at(i) == '+') || mExpressionStr.at(i) == '-') {
            acBuf[iPos] = mExpressionStr.at(i);
            iPos++;
        }
    }

    iCount = stringSplit(dst, mExpressionStr, "+-");

    for (int i = 0; i < iCount; i++) {
        dst[i] = acBuf[i] + dst[i];
        Item *item = new Item(dst[i]);
        addItem(item);
    }

    updateFromAllItem();
    //digitalMergeAllItem();

}


/* 添加一个item到链表末尾 */
void ItemList::addItem(Item *item)
{
    mItemList.push_back(item);
}

/* 从链表中删除一个item */
void ItemList::delItem(Item *item)
{
    mItemList.remove(item);
    delete item;
}

void ItemList::delAllItem(void)
{
    for(std::list<Item*>::iterator itemlist_iter = mItemList.begin(); itemlist_iter!= mItemList.end(); ++itemlist_iter) {
        delete (*itemlist_iter);
    }
    mItemList.clear();
}


void ItemList::deleteAllMark(std::string &s, const std::string &mark)
{
    size_t nSize = mark.size();
    while(1) {
        size_t pos = s.find(mark);

        if(pos == std::string::npos)	{
            return;
        }

        s.erase(pos, nSize);
    }
}


int ItemList::stringSplit(std::vector<std::string>& dst, const std::string src, const std::string& separator)
{
    if (src.empty() || separator.empty())
        return 0;

    int iCount = 0;
    char *p = NULL;
    std::string tmpStr;

    p = strtok((char *)src.c_str(), separator.c_str());
    tmpStr = p;

    while(p) {
            tmpStr = p;
            dst.push_back(tmpStr);
            iCount++;
            p = strtok(NULL, separator.c_str());
    }

    return iCount;
}


/* 原字符串，要替换的字符串，替换为什么字符串  */
void ItemList::strReplace(std::string& str, const std::string& strsrc, const std::string& strdst)
{
    std::string::size_type pos = 0;//位置
    std::string::size_type srclen = strsrc.size();//要替换的字符串大小
    std::string::size_type dstlen = strdst.size();//目标字符串大小
    while((pos = str.find(strsrc,pos)) != std::string::npos) {
        str.replace(pos,srclen,strdst);
        pos += dstlen;
    }
}

void ItemList::digitalMergeAllItem(void)
{
    for(std::list<Item*>::iterator itemlist_iter = mItemList.begin(); itemlist_iter!= mItemList.end(); ++itemlist_iter) {
        (*itemlist_iter)->digitalMerge();
    }
    updateFromAllItem();
}

void ItemList::printAllItem(void)
{
    std::cout << "==========printAllItem start==========" << std::endl;
    for(std::list<Item*>::iterator itemlist_iter = mItemList.begin(); itemlist_iter!= mItemList.end(); ++itemlist_iter) {
        std::cout << (*itemlist_iter)->mStrItem << std::endl;
        (*itemlist_iter)->printAllCell();
    }
    std::cout << "==========printAllItem end==========" << std::endl;
}


void ItemList::updateFromAllItem(void)
{
    std::string tmpStr;

    for(std::list<Item*>::iterator itemlist_iter = mItemList.begin(); itemlist_iter!= mItemList.end(); ++itemlist_iter) {
        (*itemlist_iter)->updateFromAllCell();
        tmpStr += (*itemlist_iter)->mStrItem;
    }

    mExpressionStr = tmpStr;
}

void ItemList::allExponentUnFold(void)
{
    for(std::list<Item*>::iterator itemlist_iter = mItemList.begin(); itemlist_iter!= mItemList.end(); ++itemlist_iter) {
        (*itemlist_iter)->exponentUnfold();
    }

    updateFromAllItem();
}

void ItemList::allExponentFold(void)
{

}


