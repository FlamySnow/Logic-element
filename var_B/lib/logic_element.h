#ifndef _LOGIC_ELEMENT_H
#define _LOGIC_ELEMENT_H
#include <iostream>

namespace Program3 {
    enum Type {input, output};//два типа клемм

    struct Clamp {
        int t;//тип - входная или выходная
        //количество соединений, для входной - не больше 1, для выходной - не больше 3
        //по умолчанию - 0
        short int ports;
        char signal;//состояние сигнала: 0, 1, X (неопределённое состояние)
    };

    class LogElement {
    private:
        static const int SZ = 10;//максимальное количество клемм
        int num;//количество клемм
        Clamp clmps[SZ];//массив описателей клемм
        void corrSignal ();//проверка состояний сигналов на корректность
        void corrNumber (int n);//проверка введённого номера клеммы
        void initInput (int b, int e);//инициализация входных клемм
        void initOutput (int b, int e);//инициализация выходных клемм
    public:
        LogElement();//пустой конструктор, лог. эл. - инвертор
        LogElement(int n, int m);//инициализация кол-вом входных и выходных клемм
        LogElement(int N);//инициализация массивом клемм заданной длины
        friend std::istream & operator >> (std::istream &, LogElement &);//ввод состояний сигналов всех клемм
        friend std::ostream & operator << (std::ostream &, const LogElement &);//вывод логического элемента в виде псевдографического рисунка
        void operator() (int n, char st);//ввод состояния сигнала клеммы по заданному номеру
        char operator[] (int n);//получение состояния сигнала клеммы по заданному номеру
        int connect (int n);//увеличение соединений клеммы
        int disconnect (int n);//уменьшение соединений клеммы
        LogElement & operator += (const Clamp &c);//добавление клеммы к логическому элементу
    };

    template <class T>
    int getNum (T &a) {
        std::cin >> a;
        if (!std::cin.good()){
            return 0;
        }
        return 1;
    }
}

#endif //_LOGIC_ELEMENT_H