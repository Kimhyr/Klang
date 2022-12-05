#include <iostream>

#include "Utilities/Dynar.cpp"
#include "Definitions.cpp"

Int32 main() {
    U::Dynar<Text8> string;
    string.Put('H');
    string.Put('i');
    string.Put('!');
    string.Put('\n');
    string.Put('\0');
    std::cout << string.Flush();
    return 0;
}
