#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <string>
#include <cstdio>

int main() {
    for (int i = 1; i <= 100; ++i) {
        std::cout << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        // Check if the number is a multiple of 7
        if (i % 7 == 0) {
            std::string command = "python3 py_comm.py ";
            command += std::to_string(i);
            command += " " + std::to_string(i); // Pass the number back to Python script
            std::string result = "";
            FILE* pipe = popen(command.c_str(), "r");
            if (!pipe) {
                std::cerr << "Error: Couldn't open pipe." << std::endl;
                continue;
            }
            char buffer[128];
            while (!feof(pipe)) {
                if (fgets(buffer, 128, pipe) != NULL)
                    result += buffer;
            }
            pclose(pipe);
            if (result.find("bup") != std::string::npos) {
                std::cout << result;
            }
        }
    }
    return 0;
}
