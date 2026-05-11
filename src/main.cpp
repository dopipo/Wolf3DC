#include "ide_interface.h"
#include <iostream>

int main(int argc, char* argv[]) {
    IDEInterface ide;
    
    if (!ide.initialize()) {
        std::cerr << "Fatal: Failed to initialize IDE. Check compiler installation." << std::endl;
        return 1;
    }
    
    ide.run();
    ide.shutdown();
    
    return 0;
}
