#include "bignum.h"
#include <QDebug>

// Конструктор для создания большого числа из строки:
BigNum::BigNum(QString str)
{
    //Записываем цифры в обратном порядке:

    for (int i = str.length()-1; i>=0; --i)
    {
        qint8 item = str[i].toLatin1() - '0';
        vec << item;
    }
}

QString BigNum::toString()
{
    QString tmp;
    // Итератор в стиле STL:
    QVector<qint8>::iterator  it = vec.end();
// переписываем цифры в обратном порядке:
    while (it != vec.begin())
    {
        qint8 item = *--it;
        tmp += QChar(item+'0');
    }
    return tmp;
}

BigNum BigNum::operator +(BigNum b)
{
  BigNum sum;
  // Итераторы в стиле Java:
  QVectorIterator<qint8> it1(vec);
  QVectorIterator<qint8> it2(b.vec);
  qint8 digit = 0; // цифра в текущем разряде
  qint8 carry = 0; // перенос

  while (it1.hasNext() || it2.hasNext())
    {
          qint8 a = it1.hasNext() ? it1.next() : 0;
          qint8 b = it2.hasNext() ? it2.next() : 0;
          digit = a + b+ carry ;
          carry = digit / 10;
          digit %= 10;
          // qDebug() << carry << " " << digit;
          sum.vec.push_back(digit);
      }
    if (carry) sum.vec.push_back(carry);
    return sum;
}

bool BigNum::operator <(BigNum b)
{
    if (vec.size()<b.vec.size()) // первое число короче второго
        return true; // значит первое меньше
    else if (vec.size() == b.vec.size()) // одинаковое количество цифр
    {
        for (int i = vec.size()-1; i >=0; i--)
 // проходим массивы с конца, поскольку цифры записаны в обратном порядке
        {
            if (vec[i] == b.vec[i]) continue;
        // если цифры равны, переходим к следующему разряду
            if (vec[i]<b.vec[i]) return true; // 123 и 130
            else return false; // 234 и 145
        }
        return false;
    }
    else
        return false;
}

BigNum BigNum::operator -(BigNum b)
{
  BigNum difference; // разность
  // Итераторы в стиле Java:
  QVectorIterator<qint8> it1(vec);
  QVectorIterator<qint8> it2(b.vec);
  bool sign = false;
  if ( *this < b) // применяется операторная функция
  {
      it1 = QVectorIterator<qint8>(b.vec);
      it2 = QVectorIterator<qint8>(vec);
 // поменяли местами итераторы, чтобы вычитать из большего числа
      sign = true; // нужно будет добавит минус к результату
  }
  qint8 digit = 0; // цифра в текущем разряде
  qint8 borrow = 0; // заем из следующего разряда

  while (it1.hasNext()|| it2.hasNext())
   {
         qint8 a = it1.hasNext()? it1.next() : 0;
      //  qDebug() << " a = " << a;
         if (borrow) a--;
 // Если занимали, то число в текущем разряде уменьшаем
         qint8 b = it2.hasNext()? it2.next() : 0;
     //  qDebug() << " b = " << b;
         borrow = (b > a || a < 0) ? 10 : 0; // Когда нужно занимать?
         a += borrow; // если произвели заем, добавляем в текущем разряде 10
         digit = a - b ;
         difference.vec.push_back(digit);
     }
  // Итератор в стиле STL:
   QVector<qint8>::iterator it = difference.vec.end();
 //  qDebug() <<"difference:";
  //  Удаляем нули, стоящие в начале числа: 1000 - 999 = 0001
   while (*--it == 0 && difference.vec.size()>1)
   {
       difference.vec.pop_back();
   }
   if (sign) difference.vec << '-' - '0';
 // ‘0’ потом будем прибавлять
   return difference;
}

