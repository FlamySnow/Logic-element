#include "log_el.h"

namespace var_C {

    LogElement::LogElement() :num(2){//инвертор имеет две клеммы: входную и выходную в неопределённом состоянии
        try {
            clmps = new Clamp[2];
        }
        catch (std::bad_alloc &ba) {
            throw ba;
        }
        clmps[0].t = input;
        clmps[0].signal = 'X';
        clmps[0].ports = 0;
        clmps[1].t = output;
        clmps[1].signal = 'X';
        clmps[1].ports = 0;
    }

    LogElement::LogElement(int n, int m) :num(0){
        if (n <= 0 || m <= 0)
            throw std::invalid_argument("Incorrect number of clamps!");
        num = n + m;
        try {
            clmps = new Clamp[num];
        }
        catch (std::bad_alloc &ba) {
            throw ba;
        }
        initInput(0, n);
        initOutput(n, m);
    }

    LogElement::LogElement(int N) :num(0){
        if (N < 1)
            throw std::invalid_argument("Incorrect number of clamps!");
        num = N;
        try {
            clmps = new Clamp[num];
        }
        catch (std::bad_alloc &ba) {
            throw ba;
        }
        initInput(0, N/2);
        initOutput(N/2, N);
    }

    LogElement::LogElement(const LogElement &le) : num(le.num), clmps(new Clamp[le.num]){
        for (int i = 0; i < le.num; i++) {
            clmps[i] = le.clmps[i];
        }
    }

    LogElement::~LogElement() {
        delete[] clmps;
    }

    LogElement& LogElement::operator = (const LogElement & le) {
        if (this != &le) {
            delete[] clmps;
            num = le.num;
            clmps = new Clamp[num];
            for (int i = 0; i < num; i++) {
                clmps[i] = le.clmps[i];
            }
        }
        return *this;
    }

    void LogElement::corrSignal(){
        for (int i = 0; i < num; i++) {
            if (clmps[i].signal != '0' && clmps[i].signal != '1' && clmps[i].signal != 'X')
                throw std::invalid_argument("Incorrect state of signal!");
        }
    }

    void LogElement::corrNumber (int n) {
        if (n < 1 || n > num)
            throw std::invalid_argument("Incorrect number");
    }

    void LogElement::initInput (int b, int e) {
        for (int i = b; i < e; i++){
            clmps[i].t = input;
            clmps[i].signal = 'X';
            clmps[i].ports = 0;
        }
    }

    void LogElement::initOutput (int b, int e) {
        for (int i = b; i < e; i++){
            clmps[i].t = output;
            clmps[i].signal = 'X';
            clmps[i].ports = 0;
        }
    }

    std::istream & operator >> (std::istream &s, LogElement &le){
        for (int i = 0; i < le.num; i++){
            s >> le.clmps[i].signal;
        }
        if (s.good()){
            le.corrSignal();
        }
        else {
            s.setstate(std::ios::failbit);
        }
        return s;
    }

    std::ostream & operator << (std::ostream &s, const LogElement &le){
        s << "  *********  " << std::endl;
        s << "  *       *  " << std::endl;
        for (int i = 0; i < le.num; i++) {
            if (le.clmps[i].t == input)
                s << le.clmps[i].signal << " " << le.clmps[i].ports << "       *  " << std::endl;
            if (le.clmps[i].t == output)
                s << "  *       " << le.clmps[i].ports << " " << le.clmps[i].signal << std::endl;
        }
        s << "  *       *  " << std::endl;
        s << "  *********  " << std::endl;
        return s;
    }

    void LogElement::operator() (int n, char st){
        corrNumber(n);
        if (st != '0' && st != '1' && st != 'X')
            throw std::invalid_argument("Incorrect statement");
        clmps[n - 1].signal = st;
    }

    char LogElement::operator[] (int n) {
        corrNumber(n);
        return clmps[n - 1].signal;
    }

    int LogElement::connect (int n) {
        corrNumber(n);
        if ((clmps[n - 1].t == input && clmps[n - 1].ports == 1) || (clmps[n - 1].t == output && clmps[n - 1].ports == 3))
            throw std::invalid_argument("Impossible to connect port!");
        return ++clmps[n - 1].ports;
    }

    int LogElement::disconnect (int n) {
        corrNumber(n);
        if (clmps[n - 1].ports < 1)
            throw std::invalid_argument("Impossible to disconnect port!");
        if (clmps[n - 1].ports == 1)
            clmps[n - 1].signal = 'X';
        return --clmps[n - 1].ports;
    }

    LogElement & LogElement::operator += (const Clamp &c) {
        if (c.t != input && c.t != output)
            throw std::invalid_argument("Incorrect type!");
        if (c.signal != '0' && c.signal != '1' && c.signal != 'X')
            throw std::invalid_argument("Incorrect statement!");
        if (c.t == input && c.ports > 1)
            throw std::invalid_argument("Too many ports for input clamp!");
        if (c.t == output && c.ports > 3)
            throw std::invalid_argument("Too many ports for output clamp!");
        if (c.ports < 0)
            throw std::invalid_argument("Incorrect number of ports!");
        resize(num + 1);
        clmps[num] = c;
        num++;
        return *this;
    }

    void LogElement::resize (const int & n) {
        Clamp* tmp = nullptr;
        try {
            tmp = new Clamp[n];
        }
        catch (std::bad_alloc &ba) {
            throw ba;
        }
        for (int i = 0; i < num; i++) {
            tmp[i] = clmps[i];
        }
        delete[] clmps;
        clmps = tmp;
    }
}