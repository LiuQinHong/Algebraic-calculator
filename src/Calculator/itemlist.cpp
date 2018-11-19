#include <itemlist.h>

/* a*b*c + a[0]*b[0]^2 + exp^2*exp[0] - a^(12)*exp[12]^(12) */
ItemList::ItemList(const std::string &str)
    :mExpressionStr(str)
{
    int iCount = 0;
    std::vector<std::string> dst;
    char acBuf[1024] = {0};
    int iPos = 0;

    /* 去掉空格 */
    deleteAllMark(mExpressionStr, " ");

    /* 统一格式: a^2 --->a^(2) */
    iCount = stringSplit(dst, mExpressionStr, "+-");
    for (int i = 0; i < iCount; i++) {
        std::string tmpStr1;
        std::string tmpStr2;
        int iPos = dst[i].find('^', 0);
        if ((iPos < 0) || dst[i].at(iPos+1) == '(')
            continue;

        tmpStr1 = "^(" + getExponent(dst[i]) + ")";
        tmpStr2 = dst[i];
        strReplace(tmpStr2, "^" + getExponent(dst[i]), tmpStr1);

        strReplace(mExpressionStr, dst[i], tmpStr2);
    }



    std::cout << "mExpressionStr = " << mExpressionStr << std::endl;

    acBuf[iPos] = '+';
    iPos++;
    for (int i = 0; i < mExpressionStr.size(); i++) {
        if ((mExpressionStr.at(i) == '+') || mExpressionStr.at(i) == '-') {
            acBuf[iPos] = mExpressionStr.at(i);
            iPos++;
        }
    }
    std::cout << "mExpressionStr = " << mExpressionStr << std::endl;
    iCount = stringSplit(dst, mExpressionStr, "+-");

    for (int i = 0; i < iCount; i++) {
        dst[i] = acBuf[i] + dst[i];
        std::cout << " dst[i] = " <<  dst[i] << std::endl;
        Item *item = new Item(dst[i]);
        addItem(item);
    }
    std::cout << "mExpressionStr = " << mExpressionStr << std::endl;

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
        delItem((*itemlist_iter));
    }
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

/* a^12 or a^(12) or a^(1/2) */
std::string ItemList::getExponent(std::string str)
{
    std::string strRet;
    int iPosStart = 0;
    int iPosEnd = 0;

    int iPos = str.find('^', 0);
    if (iPos < 0)
        return strRet;

    iPosStart = str.find('(', 0);
    iPosEnd = str.find(')', 0);
    if ((iPosStart >= 0) && (iPosEnd >= 0)) {
        iPosStart++;
        strRet = str.substr(iPosStart, iPosEnd - iPosStart);
    }
    else {
        iPosStart = iPos + 1;
        strRet = str.substr(iPosStart);
    }

    return strRet;
}



/* a^2+b^2*a^12-a^(12)*a^(1/2) */
void ItemList::exponentUnfold(void)
{
    std::string strTmp = mExpressionStr;
    int iExponent;
    int iIndex = 0;
    std::vector<std::string> dst;
    int iCount = 0;


    while (1) {
        iIndex = strTmp.find('^', iIndex);
        if (iIndex < 0) {
            break;
        }

        /* 得到指数的大小 */
        iExponent = atoi(&strTmp[iIndex + 1]);

        switch (strTmp[iIndex - 1]) {
            case ']' :
            {
                int iPos = strTmp.rfind('[', iIndex);
                int iTmp = iPos;

                if ((strTmp.at(--iTmp) == 'p') && (strTmp.at(--iTmp) == 'x') && (strTmp.at(--iTmp) == 'e'))
                    goto done;
                else
                    iTmp = iPos;

                if ((strTmp.at(--iTmp) == 'i') && (strTmp.at(--iTmp) == 'p'))
                    goto done;
                else
                    iTmp = iPos;

            done:
                std::string strSrc = strTmp.substr(iTmp, iIndex - iTmp + 2);
                std::string strDst = strTmp.substr(iTmp, iIndex - iTmp);
                std::string term = strDst;

                for (int i = 0; i < iExponent - 1; i++) {
                    strDst += '*';
                    strDst += term;
                }
                strReplace(strTmp, strSrc, strDst);
                break;

            }
            case ')' :
            {
                int slip = 0;
                int tmp = iIndex - 1;	//指向')'

                while (1) {
                    tmp--;

                    if (strTmp[tmp] == ')')
                        slip++;

                    if (strTmp[tmp] == '(') {
                        if (slip > 0) {
                            slip--;
                        }
                        else if (slip == 0) {
                            break;
                        }
                    }
                }

                std::string strSrc = strTmp.substr(tmp, iIndex - tmp + 2);
                std::string strDst = strTmp.substr(tmp, iIndex - tmp);
                std::string term = strDst;

                for (int i = 0; i < iExponent - 1; i++) {
                    strDst += '*';
                    strDst += term;
                }
                strReplace(strTmp, strSrc, strDst);

                break;
            }
            /* 数字或则是字母 */
            default :
            {
                int iTmp = iIndex - 1;

                /* exp^2 */
                if ((strTmp.at(iTmp--) == 'p') && (strTmp.at(iTmp--) == 'x') && (strTmp.at(iTmp) == 'e'))
                    goto done2;
                else
                    iTmp = iIndex - 1;

                /* pi^2 */
                if ((strTmp.at(iTmp--) == 'i') && (strTmp.at(iTmp) == 'p'))
                    goto done2;
                else
                    iTmp = iIndex - 1;

                done2:

                std::string strSrc = strTmp.substr(iTmp, iIndex - iTmp + 2);
                std::string strDst = strTmp.substr(iTmp, iIndex - iTmp);
                std::string term = strDst;


                for (int i = 0; i < iExponent - 1; i++) {
                    strDst += '*';
                    strDst += term;
                }
                strReplace(strTmp, strSrc, strDst);
                break;
            }
        }

    }


    mExpressionStr = strTmp;

}


void ItemList::printAllItem(void)
{
    for(std::list<Item*>::iterator itemlist_iter = mItemList.begin(); itemlist_iter!= mItemList.end(); ++itemlist_iter) {
        std::cout << (*itemlist_iter)->mStrItem << std::endl;
        (*itemlist_iter)->printAllCell();
    }
}
