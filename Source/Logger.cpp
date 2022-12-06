#ifndef KPLC_LOGGER_CPP
#define KPLC_LOGGER_CPP

#include "IO.cpp"

enum class LogSeverity {
    Verbose,
    Info,
    Warning,
    Error,
};

class Logger {
    IO io;

public:
    Void Log(LogSeverity severity, const Text8 *message);
};

#endif // KPLC_LOGGER_CPP
