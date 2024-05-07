#include <iostream>
#include <cstdio>
#include <string>

int main() {
    for (int i = 1; i <= 100; i++) {
        if (i % 7 == 0) {
            std::string command = "python py_comm.py " + std::to_string(i);
            FILE* pipe = popen(command.c_str(), "r");
            if (pipe) {
                char buffer[128];
                std::string result = "";
                while (fgets(buffer, 128, pipe) != NULL) {
                    result += buffer;
                }
                pclose(pipe);
                
                // Print "bup bup" followed by the received number
                std::cout << "bup bup " << result;
            }
        }
    }
    
    return 0;
}
