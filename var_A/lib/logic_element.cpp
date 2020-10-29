#include "logic_element.h"

namespace var_A {
    LogElement::LogElement() :num(2){//инвертор имеет две клеммы: входную и выходную в неопределённом состоянии
        clmps[0].t = input;
        clmps[0].signal = 'X';
        clmps[0].ports = 0;
        clmps[1].t = output;
        clmps[1].signal = 'X';
        clmps[1].ports = 0;
    }

    LogElement::LogElement(int n, int m) :num(0){
        if ((n + m) > SZ || n < 0 || m < 0 || (n == 0 && m == 0))
            throw std::invalid_argument("Incorrect numbers of clamps!");
        num = n + m;
        initInput(0, n);
        initOutput(n, m);
    }

    LogElement::LogElement(int N) :num(0){
        if (N > SZ || N < 1)
            throw std::invalid_argument("Incorrect number of clamps!");
        num = N;
        initInput(0, N/2);
        initOutput(N/2, N);
    }

    void LogElement::corrSignal(){
        for (int i = 0; i < num; i++) {
            if (clmps[i].signal != '0' && clmps[i].signal != '1' && clmps[i].signal && 'X')
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

    int LogElement::enterSttmnts () {
        for (int i = 0; i < num; i++){
            std::cin >> clmps[i].signal;
        }
        if (std::cin.good()){
            corrSignal();
        }
        else {
            return 0;
        }
        return 1;
    }

    void LogElement::showLE () {
        if (num == 0) {
            throw std::invalid_argument("There are no clamps in your logic element!");
        }
        std::cout << "  *********  " << std::endl;
        std::cout << "  *       *  " << std::endl;
        for (int i = 0; i < num; i++) {
            if (clmps[i].t == input)
                std::cout << clmps[i].signal << " " << clmps[i].ports << "       *  " << std::endl;
            if (clmps[i].t == output)
                std::cout << "  *       " << clmps[i].ports << " " << clmps[i].signal << std::endl;
        }
        std::cout << "  *       *  " << std::endl;
        std::cout << "  *********  " << std::endl;
    }

    void LogElement::enterSgnl (int n, char st) {
        corrNumber(n);
        if (st != '0' && st != '1' && st != 'X')
            throw std::invalid_argument("Incorrect statement");
        clmps[n - 1].signal = st;
    }

    char LogElement::getSgnl (int n) {
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

    LogElement & LogElement::addClamp (const Clamp &c) {
        if (num == SZ)
            throw std::invalid_argument("Impossible to add clamp!");
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
        clmps[num] = c;
        num++;
        return *this;
    }
}