#include <cell.h>

/* cell类实现方法 */

/* 判断单元类型 */
Cell::Cell(const std::string& strCell)
    :mStrCell(strCell)
{
    if (isNumber(strCell))
        mCellType = NUMBER;
    else if (isAlpha(strCell))
        mCellType = ALPHA;
    else if (isExp(strCell))
        mCellType = EXP;
    else if (isPI(strCell))
        mCellType = PI;
    else if (isNumberMixAlphaSubscript(strCell))
        mCellType = NUMBERMIXALPHASUBSCRIPT;
    else if (isNumberMixEXPSubscript(strCell))
        mCellType = NUMBERMIXEXPSUBSCRIPT;
    else if (isNumberMixPISubscript(strCell))
        mCellType = NUMBERMIXPISUBSCRIPT;
    else if (isAlphaWithExponent(strCell))
        mCellType = ALPHAWITHEXPONENT;
    else if (isExpWithExponent(strCell))
        mCellType = EXPWITHEXPONENT;
    else if (isPIwithExponent(strCell))
        mCellType = PIWITHEXPONENT;
    else if (isNumberMixAlphaSubscriptWithExponent(strCell))
        mCellType = NUMBERMIXALPHASUBSCRIPTWITHEXPONENT;
    else if (isNumberMixEXPSubscriptWithExponent(strCell))
        mCellType = NUMBERMIXEXPSUBSCRIPTWITHEXPONENT;
    else if (isNumberMixPISubscriptWithExponent(strCell))
        mCellType = NUMBERMIXPISUBSCRIPTWITHEXPONENT;
    else
        mCellType = RESERVE;
}


/* 1 */
bool Cell::isNumber(std::string str)
{
    for(int i = 0;i < str.size(); i++) {
        if (!isdigit(str.at(i))) {
            return false;
        }
    }
    return true;
}

/* a */
bool Cell::isAlpha(std::string str)
{
    if (str.size() != 1)
        return false;

    for(int i = 0;i < str.size(); i++) {
        if (!isalpha(str.at(i))) {
            return false;
        }
    }
    return true;
}

/* exp */
bool Cell::isExp(std::string str)
{
    if (str == "exp")
        return true;

    return false;
}

/* 圆周率 pi */
bool Cell::isPI(std::string str)
{
    if (str == "pi")
        return true;

    return false;
}

/* a[0] */
bool Cell::isNumberMixAlphaSubscript(std::string str)
{
    int iPos;

    iPos = str.find('^', 0);
    if (iPos >= 0)
        return false;

    iPos = str.find('[', 0);
    if (iPos < 0)
        return false;

    /* 这种情况下'['一定在pos = 1 处*/
    if (iPos != 1)
        return false;

    iPos = str.find(']', 0);
    if (iPos < 0)
        return false;


    return true;
}

/* exp[0] */
bool Cell::isNumberMixEXPSubscript(std::string str)
{
    int iPos;

    iPos = str.find('^', 0);
    if (iPos >= 0)
        return false;


    iPos = str.find('[', 0);
    if (iPos < 0)
        return false;

    /* 这种情况下'['一定在pos = 3 处*/
    if (iPos != 3)
        return false;

    /* 得到exp */
    std::string expStr = str.substr(0, iPos);
    if (expStr != "exp")
        return false;


    iPos = str.find(']', 0);
    if (iPos < 0)
        return false;


    return true;

}

/* pi[0] */
bool Cell::isNumberMixPISubscript(std::string str)
{
    int iPos;

    iPos = str.find('^', 0);
    if (iPos >= 0)
        return false;


    iPos = str.find('[', 0);
    if (iPos < 0)
        return false;

    /* 这种情况下'['一定在pos = 2 处*/
    if (iPos != 2)
        return false;

    /* 得到 pi */
    std::string expStr = str.substr(0, iPos);
    if (expStr != "pi")
        return false;


    iPos = str.find(']', 0);
    if (iPos < 0)
        return false;


    return true;
}


/* a^2 */
bool Cell::isAlphaWithExponent(std::string str)
{
    int iPos;

    if (!isalpha(str.at(0)))
        return false;

    iPos = str.find('^', 0);
    if (iPos < 0)
        return false;

    /* 这种情况下'^'一定在pos = 1 处*/
    if (iPos != 1)
        return false;

    /* 得到指数 */
    std::string numStr = str.substr(iPos+1);

    if (!isNumber(numStr))
        return false;


    return true;
}

/* exp^2 */
bool Cell::isExpWithExponent(std::string str)
{
    int iPos;

    iPos = str.find('^', 0);
    if (iPos < 0)
        return false;

    /* 这种情况下'^'一定在pos = 3 处*/
    if (iPos != 3)
        return false;

    /* 得到exp */
    std::string expStr = str.substr(0, 3);
    if (expStr != "exp")
        return false;

    /* 得到指数 */
    std::string numStr = str.substr(iPos+1);

    if (!isNumber(numStr))
        return false;

    return true;
}

/* pi^2 */
bool Cell::isPIwithExponent(std::string str)
{
    int iPos;

    iPos = str.find('^', 0);
    if (iPos < 0)
        return false;

    /* 这种情况下'^'一定在pos = 2 处*/
    if (iPos != 2)
        return false;

    /* 得到pi */
    std::string expStr = str.substr(0, 2);
    if (expStr != "pi")
        return false;

    /* 得到指数 */
    std::string numStr = str.substr(iPos+1);

    if (!isNumber(numStr))
        return false;

    return true;
}

/* a[0]^2 */
bool Cell::isNumberMixAlphaSubscriptWithExponent(std::string str)
{
    int iPos;

    iPos = str.find('^', 0);
    if (iPos < 0)
        return false;

    /* 得到指数 */
    std::string numStr = str.substr(iPos+1);

    if (!isNumber(numStr))
        return false;

    /* 得到a[0] */
    std::string numberMixAlphaSubscriptStr = str.substr(0, iPos);
    if (!isNumberMixAlphaSubscript(numberMixAlphaSubscriptStr))
        return false;

    return true;
}


/* exp[0]^2 */
bool Cell::isNumberMixEXPSubscriptWithExponent(std::string str)
{
    int iPos;

    iPos = str.find('^', 0);
    if (iPos < 0)
        return false;

    /* 得到指数 */
    std::string numStr = str.substr(iPos+1);

    if (!isNumber(numStr))
        return false;

    /* 得到exp[0] */
    std::string numberMixEXPSubscriptStr = str.substr(0, iPos);
    if (!isNumberMixEXPSubscript(numberMixEXPSubscriptStr))
        return false;

    return true;
}



/* pi[0]^2 */
bool Cell::isNumberMixPISubscriptWithExponent(std::string str)
{
    int iPos;

    iPos = str.find('^', 0);
    if (iPos < 0)
        return false;

    /* 得到指数 */
    std::string numStr = str.substr(iPos+1);

    if (!isNumber(numStr))
        return false;

    /* 得到pi[0] */
    std::string numberMixPISubscriptStr = str.substr(0, iPos);
    if (!isNumberMixPISubscript(numberMixPISubscriptStr))
        return false;

    return true;
}
