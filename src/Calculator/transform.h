#ifndef TRANSFORM_H
#define TRANSFORM_H

/*
 * QString 转换 Html
 *
*/
#include <QObject>
#include <QString>

class Transform : public QObject
{
    Q_OBJECT

public:
    bool transform(QString &original,QString *outHtml);

private:

};

#endif // TRANSFORM_H
