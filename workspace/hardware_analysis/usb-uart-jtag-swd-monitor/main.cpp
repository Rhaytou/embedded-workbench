// x86_64 Linux
/* */
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}


// Arm bare metal
/*
extern "C" void _start(void) {
    extern int main(void);
    main();
    while (1) {}
}

int main(void) {
    while (1) {}
}
*/


// Arm 32 Linux


// Arm 64 Linux


// Risc V Linux

















