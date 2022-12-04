#include <iostream>

#include "Utility/Collections/Dynar.hpp"

#include "Definitions.hpp"

Int32 main() {
    Utility::Collections::Dynar<Text8> string;
    string.Put('H');
    string.Put('i');
    string.Put('!');
    string.Put('\n');
    string.Put('\0');
    std::cout << string.Flush();
    return 0;
}
