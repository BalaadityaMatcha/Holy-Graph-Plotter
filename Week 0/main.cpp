#include <iostream>
#include <memory>
#include <string>
#include <vector>

// 1. References
void increment_by_reference(int& val) {
    val++;
}

// 2. RAII (Resource Acquisition Is Initialization)
class FileHandler {
public:
    FileHandler(const std::string& filename) {
        std::cout << "Opening file: " << filename << "\n";
    }
    ~FileHandler() {
        std::cout << "Closing file(RAII)\n";
    }
};

void badfunction(){
    FileHandler file("data.txt");
    
    // Simulating an error.
    std::cout << "Handling\n";
    throw std::runtime_error("Something went wrong!");
    // Without RAII, the file wouldn't have been closed.
}

// 3. Smart Pointers
class Entity {
public:
    Entity() { std::cout << "Entity Created\n"; }
    ~Entity() { std::cout << "Entity Destroyed\n"; }
    void do_something() { std::cout << "Entity doing something\n"; }
};

// 4. Operator Overloading
struct Vector2 {
    float x, y;
    Vector2(float x, float y) : x(x), y(y) {}
    
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }
};
std::ostream& operator<<(std::ostream& stream, const Vector2& other) {
    stream << "(" << other.x << ", " << other.y << ")";
    return stream;
}

// 5. Function Overloading
void print(int val) { std::cout << "Int: " << val << "\n"; }
void print(float val) { std::cout << "Float: " << val << "\n"; }
void print(const std::string& val) { std::cout << "String: " << val << "\n"; }

// 6. Templates
template<typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    std::cout << "1. References\n";
    int a = 5;
    increment_by_reference(a);
    std::cout << "a after increment: " << a << "\n\n";

    std::cout << "2. RAII\n";
    try{
        badfunction();
        // FileHandler destructor called here automatically
    }
    catch(...){
        std::cout << "Caught the exception.\n";
    }
    std::cout << "\n";

    std::cout << "3. Smart Pointers\n";
    {
        std::unique_ptr<Entity> ptr1 = std::make_unique<Entity>();
        ptr1->do_something();
        std::unique_ptr<Entity> ptr2 = std::move(ptr1);
        // Moving the ownership from ptr1 to ptr2(ptr1 = null)
    } // entity destroyed automatically
    std::cout << "\n";

    std::cout << "4. Operator Overloading\n";
    Vector2 v1(1.0f, 2.0f);
    Vector2 v2(3.0f, 4.0f);
    Vector2 v3 = v1 + v2;
    std::cout << "v1 + v2 = " << v3 << "\n\n";

    std::cout << "5. Function Overloading\n";
    print(10);
    print(10.5f);
    print(std::string("Hello"));
    std::cout << "\n";

    std::cout << "6. Templates\n";
    std::cout << "add(1, 2) = " << add(1, 2) << "\n";
    std::cout << "add(1.5, 2.5) = " << add(1.5, 2.5) << "\n";

    return 0;
}
