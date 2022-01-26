#ifndef BIGNUM_H
#define BIGNUM_H

#include <QtWidgets>

class BigNum
{
    QVector<qint8> vec; // Массив для хранения цифр числа
public:
    BigNum(){};
    BigNum(QString);

    QString toString();
    BigNum operator +(BigNum);
    BigNum operator -(BigNum);
    bool operator <(BigNum);
};

#endif // BIGNUM_H
