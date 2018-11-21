#include <item.h>

/*
 *  单项式单元实现方法
*/
Item::Item(const std::string& strItem)
    :mStrItem(strItem)
{


    if(isSimpleNumber(strItem)) {
        mType = SIMPLENUMBER;
        goto done;
    }

    if(isSimpleAlpha(strItem)) {
        mType = SIMPLEALPHA;
        goto done;
    }

    if(isMix(strItem)) {
        mType = MIX;
        goto done;
    }


done:

    switch (mType) {
        case SIMPLEALPHA :
        case MIX:
        {
            parseItemToCell(mStrItem);
            break;
        }
        default:
        {
            break;
        }
    }
}


void Item::addCell(Cell* cell)
{
    mCellList.push_back(cell);
}

void Item::delCell(Cell* cell)
{
    mCellList.remove(cell);
    delete cell;
}

void Item::delAllCell()
{
    for(std::list<Cell*>::iterator celllist_iter = mCellList.begin(); celllist_iter!= mCellList.end(); ++celllist_iter) {
        delCell((*celllist_iter));
    }
}

bool Item::isSimpleNumber(std::string str)
{
    for(size_t i = 0;i < str.size(); i++) {
        if ((str.at(i) == '+') || str.at(i) == '-')
            continue;

        if (!isdigit(str.at(i))) {
            return false;
        }
    }
    return true;
}


bool Item::isSimpleAlpha(std::string str)
{
    for(size_t i = 0;i < str.size(); i++) {
        if ((str.at(i) == '+') || str.at(i) == '-')
            continue;

        if (!isalpha(str.at(i))) {
            return false;
        }
    }
    return true;
}


bool Item::isMix(std::string str)
{
    if (isSimpleNumber(str) || isSimpleAlpha(str))
        return false;

    return true;
}


/* strItem = +3*pi*exp*a*b[0]*c^2*pi[0]*exp[0]*exp[0]^2 */
void Item::parseItemToCell(std::string& strItem)
{
    int iPosStart = 0;
    int iPosEnd = 0;
    std::string tmpStr = strItem;

    if ((strItem.at(0) == '+') || strItem.at(0) == '-')
        tmpStr = strItem.substr(1);

    if (tmpStr.empty())
        return;

    while (1) {
        iPosEnd = tmpStr.find('*', iPosStart);
        if (iPosEnd < 0)
            break;

        std::string subStr = tmpStr.substr(iPosStart, iPosEnd - iPosStart);
        Cell *cell = new Cell(subStr);
        addCell(cell);

        iPosEnd++;
        iPosStart = iPosEnd;
    }

    std::string subStr = tmpStr.substr(iPosStart);
    Cell *cell = new Cell(subStr);
    addCell(cell);

    updateFromAllCell();
}


int Item::stringSplit(std::vector<std::string>& dst, const std::string& src, const std::string& separator)
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

void Item::parseCelltoItem()
{
    std::list<Cell*>::iterator temp_iter;
    mStrItem.erase(mStrItem.begin()+1,mStrItem.end());
    for(std::list<Cell*>::iterator celllist_iter = mCellList.begin(); celllist_iter!= mCellList.end(); ++celllist_iter) {
        temp_iter = celllist_iter;
        ++temp_iter;
        mStrItem.append((*celllist_iter)->mStrCell);
        if(temp_iter != mCellList.end())
            mStrItem.append("*");
    }
}

/* exp[0]^(12)*a^(12)*a^(1/2) */
void Item::exponentUnfold(void)
{

}

void Item::updateFromAllCell(void)
{
    std::string tmpStr;

    tmpStr = mStrItem.at(0);

    for(std::list<Cell*>::iterator celllist_iter = mCellList.begin(); celllist_iter!= mCellList.end(); ++celllist_iter) {
        tmpStr += (*celllist_iter)->mStrCell;
        tmpStr += "*";
    }
    tmpStr.pop_back();
    mStrItem = tmpStr;
}

void Item::printAllCell(void)
{
    for(std::list<Cell*>::iterator celllist_iter = mCellList.begin(); celllist_iter!= mCellList.end(); ++celllist_iter) {
        std::cout << (*celllist_iter)->mStrCell << ":" << (*celllist_iter)->mCellType << std::endl;
    }
}
