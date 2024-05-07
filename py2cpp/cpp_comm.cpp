#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib> // For system() function

int main() {
    for (int i = 1; i <= 100; ++i) {
        std::cout << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        // Check if the number is a multiple of 7
        if (i % 7 == 0) {
            std::string command = "python3 script.py ";
            command += std::to_string(i);
            system(command.c_str()); // Call Python script with the number as argument
        }
    }
    return 0;
}
