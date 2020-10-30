#include "../lib/log_el.h"

using namespace var_C;

int main() {
    int n;
    char st;
    Clamp cl;
    int key1 = -1;
    while (1) {
        std::cout << "Choose an operation:" << std::endl;
        std::cout << "0. Quit;" << std::endl;
        std::cout << "1. Enter statements of all clamps;" << std::endl;
        std::cout << "2. Enter statement of a clamp by its number;" << std::endl;
        std::cout << "3. Get statement of a clamp by its number;" << std::endl;
        std::cout << "4. Increase number of ports of a clamp by one;" << std::endl;
        std::cout << "5. Decrease number of ports of a clamp by one;" << std::endl;
        std::cout << "6. Add clamp to a logic element." << std::endl;
        std::cout << "Enter operation code: --> ";
        if (!getNum(key1)) {
            std::cout << "Incorrect data!" << std::endl;
            return 0;
        }
        if (key1 == 0)
            break;
        try {
            switch (key1) {
                case 1: {
                    std::cout << "Enter number of clamps: -->";
                    if (!getNum(n)) {
                        std::cout << "Incorrect data!" << std::endl;
                        return 0;
                    }
                    LogElement le(n);
                    std::cout << le;
                    std::cout << "Enter values of signal statements: 0, 1 or X for undefined statement." << std::endl;
                    std::cin >> le;
                    std::cout << le;
                }
                break;
                case 2: {
                    std::cout << "Enter number of clamps: -->";
                    if (!getNum(n)) {
                        std::cout << "Incorrect data!" << std::endl;
                        return 0;
                    }
                    LogElement le(n);
                    std::cout << le;
                    std::cout << "Enter number of a clamp: --> ";
                    if (!getNum(n)) {
                        std::cout << "Incorrect data!" << std::endl;
                        return 0;
                    }
                    std::cout << "Enter signal statement: 0, 1 or X --> ";
                    std::cin >> st;
                    le(n, st);
                    std::cout << le;
                }
                break;
                case 3: {
                    std::cout << "Enter number of clamps: -->";
                    if (!getNum(n)) {
                        std::cout << "Incorrect data!" << std::endl;
                        return 0;
                    }
                    LogElement le(n);
                    std::cout << "Enter values of signal statements: 0, 1 or X for undefined statement." << std::endl;
                    std::cin >> le;
                    std::cout << le;
                    std::cout << "Enter number of a clamp: --> ";
                    if (!getNum(n)) {
                        std::cout << "Incorrect data!" << std::endl;
                        return 0;
                    }
                    std::cout << "Signal: " << le[n] << std::endl;
                }
                break;
                case 4: {
                    LogElement le;
                    std::cout << le;
                    std::cout << "Enter number of a clamp: --> ";
                    if (!getNum(n)) {
                        std::cout << "Incorrect data!" << std::endl;
                        return 0;
                    }
                    le.connect(n);
                    std::cout << le;
                }
                break;
                case 5: {
                    LogElement le;
                    le.connect(1);
                    std::cout << le;
                    std::cout << "Enter number of a clamp: --> ";
                    if (!getNum(n)) {
                        std::cout << "Incorrect data!" << std::endl;
                        return 0;
                    }
                    le.disconnect(n);
                    std::cout << le;
                }
                break;
                case 6: {
                    LogElement le;
                    std::cout << "Enter type of clamp: 0 for input, 1 for output --> ";
                    if (!getNum(cl.t)) {
                        std::cout << "Incorrect data!" << std::endl;
                        return 0;
                    }
                    std::cout << "Enter number of ports: not above 1 for input clamp and not above 3 for output clamp --> ";
                    if (!getNum(cl.ports)) {
                        std::cout << "Incorrect data!" << std::endl;
                        return 0;
                    }
                    if (cl.ports != 0) {
                        std::cout << "Enter signal statement: 0, 1 or X --> ";
                        std::cin >> cl.signal;
                    }
                    else
                        cl.signal = 'X';
                    le += cl;
                    std::cout << le;
                }
                break;
                default: {
                    std::cout << "Please, enter correct operation code!" << std::endl;
                }
                break;
            }
        }
        catch (std::exception &ex) {
            std::cout << ex.what() << std::endl;
            break;
        }
    }
    return 0;
}