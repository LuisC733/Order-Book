#ifndef ITCH_PROCESSOR_READER_H
#define ITCH_PROCESSOR_READER_H
#include <fstream>
#include <stdexcept>
#include <vector>

inline std::vector<std::uint8_t> readFile(const char* path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file) {throw std::runtime_error("Datei konnte nicht geöffnet werden");}

    const auto size = file.tellg();
    if (size < 0) {throw std::runtime_error("Dateigröße konnte nicht gelesen werden");}

    std::vector<std::uint8_t> data(static_cast<std::size_t>(size));

    if (!file.seekg(0, std::ios::beg)) {
        throw std::runtime_error("Leseposition konnte nicht gesetzt werden");
    }
    if (!data.empty() && !file.read(
        reinterpret_cast<char*>(data.data()),
        static_cast<std::streamsize>(data.size())))
    {
        throw std::runtime_error("Datei konnte nicht vollständig gelesen werden");
    }
    return data;
};

#endif //ITCH_PROCESSOR_READER_H
