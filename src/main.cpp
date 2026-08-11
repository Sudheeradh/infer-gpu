#include <iostream>
#include <fstream>
#include <filesystem>
#include "json.hpp"

using json = nlohmann::json;

std::string MODEL_PATH = "...";

int main() {
     std::cout << "model path: " << MODEL_PATH << '\n';
     std::ifstream safetensor_file(MODEL_PATH, std::ios_base::binary);
     uint64_t header_size;
     safetensor_file.read(reinterpret_cast <char *> (&header_size), 8);
     
     std::string header = std::string(header_size, '\0');
     safetensor_file.read(&header[0], header_size);

     std::cout << header << '\n';
}