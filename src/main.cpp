#include <iostream>
#include <fstream>
#include <filesystem>
#include "json.hpp"

#include <cuda_runtime.h>
#include <cuda_bf16.h>
#include <cublas_v2.h>

using json = nlohmann::json;

constexpr int B_TO_MB = 1024 * 1024;
constexpr int B_TO_GB = 1024 * 1024 * 1024;

std::string MODEL_PATH = "/home/h4x/infer-gpu/model.safetensors";

int checkGPUStatus() {
    int device_count = 0;
    cudaGetDeviceCount(&device_count);
    if (device_count == 0){
         std::cerr << "No CUDA devices found\n";
         return 1;
    }
    if (device_count == 1){
         std::cout << "There are " << device_count << " GPUs available on this machine\n";
    }

    cudaDeviceProp prop;
    cudaGetDeviceProperties(&prop, 0);
    std::cout << "Device: " << prop.name << "\n";
    std::cout << "Compute capability: " << prop.major << "." << prop.minor << "\n";
    std::cout << "Global memory: " << prop.totalGlobalMem / B_TO_GB << " GB\n";
    std::cout << "SM count: " << prop.multiProcessorCount << "\n";
    std::cout << "Max threads per block: " << prop.maxThreadsPerBlock << std::endl;

    size_t free_mem;
    size_t total_mem;
    cudaMemGetInfo(&free_mem, &total_mem);
    std::cout << "Free memory: " << free_mem / B_TO_GB << "GB, total memory: " << total_mem / B_TO_GB << "GB\n";
    return 0;
}

int main() {
     std::cout << "model path: " << MODEL_PATH << '\n';
     std::ifstream safetensor_file(MODEL_PATH, std::ios_base::binary);
     uint64_t header_size;
     safetensor_file.read(reinterpret_cast <char *> (&header_size), 8);
     
     std::string header = std::string(header_size, '\0');
     safetensor_file.read(&header[0], header_size);

     checkGPUStatus();
}