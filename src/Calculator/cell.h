#ifndef CELL_H
#define CELL_H

#include <string>

// 1 a e pi b[0] 1^2 a^2 e^2 pi^2 b[0]^2
enum CellType {
    NUMBER,								// 数字 : 1
    ALPHA,								// 字母 : a
    EXP,								// exp
    PI,									// 圆周率 pi

    NUMBERMIXALPHASUBSCRIPT,			// 带下标的字母 : a[0]
    NUMBERMIXEXPSUBSCRIPT,				// exp[0]
    NUMBERMIXPISUBSCRIPT,				// pi[0]

    ALPHAWITHEXPONENT,					// 字母带幂 : a^2
    EXPWITHEXPONENT,					// exp带幂 : exp^2
    PIWITHEXPONENT,						// 圆周率带幂 ：pi^2

    NUMBERMIXALPHASUBSCRIPTWITHEXPONENT,// 带下标的字母	: a[0]^2
    NUMBERMIXEXPSUBSCRIPTWITHEXPONENT,	// 带下标的字母	: exp[0]^2
    NUMBERMIXPISUBSCRIPTWITHEXPONENT,	// 带下标的字母	: pi[0]^2

    RESERVE,							// 保留
};


class Cell {
public:
    std::string mStrCell;
    enum CellType mCellType;//单元类型
    Cell(){};
    Cell(const std::string& strCell);
    Cell(const std::string& strCell, enum CellType type):mStrCell(strCell),mCellType(type){}

    bool isNumber(std::string str);
    bool isAlpha(std::string str);
    bool isExp(std::string str);
    bool isPI(std::string str);

    bool isNumberMixAlphaSubscript(std::string str);
    bool isNumberMixEXPSubscript(std::string str);
    bool isNumberMixPISubscript(std::string str);

    bool isAlphaWithExponent(std::string str);
    bool isExpWithExponent(std::string str);
    bool isPIwithExponent(std::string str);

    bool isNumberMixAlphaSubscriptWithExponent(std::string str);
    bool isNumberMixEXPSubscriptWithExponent(std::string str);
    bool isNumberMixPISubscriptWithExponent(std::string str);
};

#endif // CELL_H