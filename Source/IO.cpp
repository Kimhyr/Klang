#ifndef KPLC_IO_CPP
#define KPLC_IO_CPP

#include "Definitions.cpp"

class IO {
    const Text8 *path;

public:
    Void Write(const Text8 *text);

    const Text8 *Read();

public:

};

#endif // KPLC_IO_CPP
