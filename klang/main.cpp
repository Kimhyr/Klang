#include <iostream>

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdexcept>

char const* load_file(std::string_view file_path);

int main(int argc, char** argv)
{
        (void)argc, (void)argv;

        std::cout << "Hello, World!" << std::endl;       
        return 0;
}

char const* load_file(std::string_view file_path)
{
    // Open the file.
    int file_descriptor{open(file_path.cbegin(), O_RDWR)};
    if (file_descriptor == -1) [[unlikely]]
        throw std::invalid_argument{"open failed"};

    // Get the size of the file.
    struct stat file_stats;
    if (fstat(file_descriptor, &file_stats) == -1) [[unlikely]]
        throw std::invalid_argument{"fstat failed"};
    std::size_t file_size{static_cast<std::size_t>(file_stats.st_size)};

    // Memory map the file.
    char const* line{reinterpret_cast<char const*>(
        mmap(nullptr, file_size,
             PROT_READ | PROT_WRITE,
             MAP_PRIVATE, file_descriptor,
             0))};
    if (line == MAP_FAILED) [[unlikely]]
        throw std::invalid_argument{"map failed"};

    return line;
}
