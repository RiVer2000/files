#include <iostream>
#include <cstdio>

int main() {
    for (int i = 1; i <= 100; i++) {
        if (i % 7 == 0) {
            // Call the Python script using popen
            FILE* pipe = popen("python py_comm.py", "w");
            if (pipe) {
                char buffer[128];
                std::string result = "";
                while (!feof(pipe)) {
                    if (fgets(buffer, 128, pipe) != NULL)
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