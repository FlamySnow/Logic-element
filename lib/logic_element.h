#ifndef _LOGIC_ELEMENT_H
#define _LOGIC_ELEMENT_H
#include <iostream>

namespace Program3 {
    enum Type {input, output};

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
        void corrSignal ();
        void corrNumber (int n);
    public:
        LogElement();//пустой конструктор, лог. эл. - инвертор
        LogElement(int n, int m);//инициализация кол-вом входных и выходных клемм
        LogElement(int N);//инициализация массивом клемм заданной длины
        ~LogElement() {};
        friend std::istream & operator >> (std::istream &, LogElement &);
        friend std::ostream & operator << (std::ostream &, const LogElement &);
        void operator() (int n, char st);
        char operator[] (int n);
        int connect (int n);
        int disconnect (int n);
        LogElement & operator += (const Clamp &c);
    };
}

#endif //_LOGIC_ELEMENT_H