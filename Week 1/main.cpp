#include <iostream>

void intentional_memory_leak() {
    int* leaked_array = new int[100];
    leaked_array[0] = 42;
    std::cout << "Leaked array created, first element: " << leaked_array[0] << std::endl;
    // Missing delete[] -> leaked_array
}

void intentional_out_of_bounds() {
    int arr[5] = {1, 2, 3, 4, 5};
    std::cout << "Out of bounds access: " << arr[5] << std::endl; // Accessing index 5 (6th element)
}

int main() {
    std::cout << "This program has intentional bugs to demonstrate AddressSanitizer and GDB!\n\n";
    
    // Uncomment these to test sanitizers
    // intentional_memory_leak();
    // intentional_out_of_bounds();
    
    std::cout << "Run the program with gdb or check the source code for commented-out bugs.\n";
    // Actually gdb is not useful here since we have used the sanitizer!
    return 0;
}
