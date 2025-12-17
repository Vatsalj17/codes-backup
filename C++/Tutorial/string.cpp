#include <iostream>

int main(void) {
    std::string str = "hello";
    if (str[str.size()] == '\0')
        std::cout << str[str.size() - 1] << std::endl;
    else {
        std::cout << "Not expected\n";
    }
}
