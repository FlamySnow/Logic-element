#include "C:/Users/sweet/Desktop/projects/Logic-element/lib/logic_element.h"

using namespace Program3;

int main() {
    LogElement le;
    int n;
    char st;
    Clamp cl;
    std::cout << "Invertor:" << std::endl;
    std::cout << le;
    std::cout << "Please, enter signal statements for clamps (0 or 1, or X)" << std::endl;
    try {
        std::cin >> le;
    }
    catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
    }
    std::cout << "Enter number of clamp and statement of its signal: ";
    std::cin >> n >> st;
    try {
        le(n, st);
    }
    catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
    }
    std::cout << "Enter number of clamp: ";
    std::cin >> n;
    try {
        std::cout << "Signal statement: " << le[n] << std::endl;
    }
    catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
    }
    std::cout << "Enter number of clamp to increase its ports: ";
    std::cin >> n;
    try {
        le.connect(n);
    }
    catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
    }
    std::cout << "Enter number of clamp to decrease its ports: ";
    std::cin >> n;
    try {
        le.disconnect(n);
    }
    catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
    }
    std::cout << "Enter type of clamp (0 for input, 1 for output): ";
    std::cin >> n;
    if (n == 0)
        cl.t = input;
    else if (n == 1)
        cl.t = output;
    else
    {
        std::cout << "Incorrect type of clamp!";
        return 0;
    }
    std::cout << "Enter number of ports: (not above 1 for input, not above 3 for output): ";
    std::cin >> cl.ports;
    std::cout << "Enter statement of signal (0, 1 or X for undefined statement): ";
    std::cin >> cl.signal;
    if (cl.signal != '0' && cl.signal != '1' && cl.signal != 'X') {
        std::cout << "Incorrect statement of signal!";
        return 0;
    }
    le += cl;
    std::cout << "Your logic element:" << std::endl;
    std::cout << le;
    return 0;
}