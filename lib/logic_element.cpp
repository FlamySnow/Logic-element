#include "logic_element.h"

namespace Program3 {
    LogElement::LogElement() :num(2){
        clmps[0].t = input;
        clmps[0].signal = 'X';
        clmps[0].ports = 1;
        clmps[1].t = output;
        clmps[1].signal = 'X';
        clmps[1].ports = 1;
    }
    LogElement::LogElement(int n, int m) :num(0){
        if ((n + m) > SZ)
            throw std::invalid_argument("Too many clamps!");
        num = n + m;
        for (int i = 0; i < n; i++){
            clmps[i].t = input;
            clmps[i].signal = 'X';
            clmps[i].ports = 0;
        }
        for (int i = n; i < m; i++){
            clmps[i].t = output;
            clmps[i].signal = 'X';
            clmps[i].ports = 0;
        }
    }
    LogElement::LogElement(int N) :num(0){
        if (N > SZ)
            throw std::invalid_argument("Too many clamps!");
        num = N;
        for (int i = 0; i < N/2; i++){
            clmps[i].t = input;
            clmps[i].signal = 'X';
            clmps[i].ports = 0;
        }
        for (int i = N/2; i < N; i++){
            clmps[i].t = output;
            clmps[i].signal = 'X';
            clmps[i].ports = 0;
        }
    }
}