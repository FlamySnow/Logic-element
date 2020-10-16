#ifndef _LOGIC_ELEMENT_H
#define _LOGIC_ELEMENT_H
#include <iostream>

enum Type {input, output};

namespace Program3 {
    struct Clamp {
        Type t;//тип - входная или выходная
        //количество соединений, для входной - не больше 1, для выходной - не больше 3
        //по умолчанию - 0
        short int ports;
        char signal;//состояние сигнала: 0, 1, X (неопределённое состояние)
    };

    class LogElement {
    private:
        static const int SZ = 10;//максимальное количество клемм
        int num;//количество клемм
        Clamp clmps[SZ];
    public:
        LogElement();//пустой конструктор, лог. эл. - инвертор
        LogElement(int n, int m);//инициализация кол-вом выходных и входных клемм
        LogElement(int N);//инициализация массивом клемм заданной длины
    };
}

#endif //_LOGIC_ELEMENT_H