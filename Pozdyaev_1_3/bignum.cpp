//3.	Создать приложение, которое находит произведе-ние двух больших целых чисел , используя контейнеры и итераторы.

#include "bignum.h"
#include <QDebug>
BigNum::BigNum(QString str) // основной конструктор
{
     /* поскольку операции сложения и вычитания выполняются справа налево, запишем числа, соответствующие цифрам в массив в обратном порядке: */
    for (int i = str.length()-1; i>=0; --i)
    {
        qint8 item = str[i].unicode() - '0';
         // число, соответствующее цифре
        vec.push_back(item);  // добавляем число в конец массива
    }
}
 // преобразование массива в строку:
QString BigNum::toString()
{
    QString tmp;
    // Итератор в стиле STL:
    QVector<qint8>::iterator it = vec.end(); // идем от конца вектора
    while (it != vec.begin()) // к началу
    {
        qint8 item = *--it; // один элемент массива
        tmp += QChar(item+'0'); // создаем цифру из числа и добавляем к строке
    }
    return tmp;
}
 // Операторная функция сложения:
BigNum BigNum::operator +(BigNum b)
{
  BigNum sum;
  // Итераторы в стиле Java:
  QVectorIterator<qint8> it1(vec); // итератор для левого операнда
  QVectorIterator<qint8> it2(b.vec); // для правого операнда
  qint8 digit = 0; // число в текущем разряде результата
  qint8 carry = 0; // перенос в следующий разряд
  while (it1.hasNext()|| it2.hasNext())
    // пока хотя бы одно из чисел не закончено
  {
       qint8 a = it1.hasNext()? it1.next() : 0; // если число закончилось, то складывается ноль
       qint8 b = it2.hasNext()? it2.next() : 0;
       digit = a + b + carry ;  // сложение в текущем разряде
       carry = digit / 10; // перенос в следующий разряд
       digit %= 10; // цифра в текущем разряде
       sum.vec.push_back(digit); // добавляем цифру к сумме
    }
  if (carry) sum.vec.push_back(carry);
  return sum;
}

// Операторная функция умножения:
BigNum BigNum::operator*(BigNum b)
{
    BigNum result("0"), buffer;

    // Итераторы в стиле Java:
    QVector<qint8> vec_buf;
    QVector<qint8>::iterator iter_b = b.vec.begin(), iter_a;

    qint8 digit, carry;
    int i = 0;

    while(iter_b != b.vec.end())
    {
        carry = 0;
        iter_a = vec.begin();
        vec_buf.clear();

        while(iter_a != vec.end())
        {
            digit = *iter_a * *iter_b + carry;
            vec_buf.append(digit%10);
            carry = digit/10;
            iter_a++;
        }

        if (carry != 0)
            vec_buf.append(carry);

        for (int counter = 0; counter < i; counter++)
            vec_buf.push_front(0);

        buffer.vec = vec_buf;
        result = result + buffer;
        iter_b++;
        i++;
    }
    return result;
}

