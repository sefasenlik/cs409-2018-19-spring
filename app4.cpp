// almost always auto - AAA rule: move type to the right

// C: malloc/free, old C++: new/delete

// l-value, r-value
// l-value references, r-value references
// move-ctor, move-assignment

// operator overloading

// user-defined literals

// inheritance
// dynamic polymorphism, v-table

#include <iostream>
#include <vector>
#include <array>

struct Int
{
    int value;

    Int() : value{0} { }
    Int(int value) : value{value} { }
    Int(const Int& other) : value{other.value} { }

    operator int() { return value; }
    operator float() { return value*2; }

};

struct Huge
{
    Int x;
    Int y;
    std::vector<int> v;

    Huge() : x{10}, y{20}, v(100)
    {
        std::cout << "ctor" << std::endl;
    }

    Huge(const Huge& other) : x{other.x}, y{other.y}, v(other.v)
    {
        std::cout << "copy ctor" << std::endl;
    }

    Huge(Huge&& other) : x{std::move(other.x)}, y{std::move(other.y)}, v(std::move(other.v))
    {
        std::cout << "move ctor" << std::endl;
    }

    void operator=(const Huge& right)
    {
        x = right.x;
        y = right.y;
        v = right.v;

        std::cout << "copy assignment" << std::endl;
    }

    void operator=(Huge&& right)
    {
        x = std::move(right.x);
        y = std::move(right.y);
        v = std::move(right.v);

        std::cout << "move assignment" << std::endl;
    }

    ~Huge()
    {
        std::cout << "Siliyorum" << std::endl;
    }
};

int f1() { return 10; }
int f2() { return 20; }

struct Acceleration
{
    long double value;
    Acceleration(long double value) : value{value} { }
};


auto operator"" _acc(long double value) -> Acceleration
{
    return {value};
}

auto operator"" _acc(unsigned long long value) -> Acceleration
{
    return {(long double)value};
}


int main(int argc, char* argv[])
{
//    auto g = Acceleration{9.81};

    auto g1 = 9_acc;
    auto g2 = 9.81_acc;

    {
//        Int a(100);
        auto a = Int(100);
        int b = a;
    }

    {
//        auto h1 = Huge{};
//        Huge h2(h1); // copy ctor
        Huge h3(std::move(Huge{})); // move ctor
//        auto h4 = h3;
    }


//    // a pointer to memory. type is unknown.
//    void* p1 = malloc(250000 * sizeof(int));
//    free(p1);

//    // pointed type is int
//    int* p2 = (int*)malloc(250000 * sizeof(int));
//    free(p2);
//    int* p2_cpp = new int[250000];
//    //auto p2_cpp = new int[250000]; // left hand modern, right hand old school!
//    delete[] p2_cpp;

//    // pointed type is int. auto works only if right hand type is ptr to smt.
//    auto* p3 = (int*)malloc(250000 * sizeof(int));
//    free(p3);

//    // same thing with p3. no constraint.
//    auto p4 = (int*)malloc(250000 * sizeof(int));
//    free(p4);

//    Huge* p5 = new Huge(); // old C++
//    delete p5;

//    Huge* p6 = new Huge[1000]; // old C++
//    delete[] p6;

//    {
//        // v1, v2, v3 are l-values (memory addresses are available)
//        auto v1 = f1(); // returned value from f1() is r-value
//        auto v2 = f2(); // returned value from f2() is r-value
//        auto v3 = v1 + v2;

//        int* v1_ptr = &v1; // C and old C++
//        v1_ptr++;
//        ++v1_ptr;
//        v1_ptr += 10;

//        auto& v1_ref_cpp = v1; // both old C++ and modern C++

////        int& ir = 10; // error
//        const int& ir = 10; // okay
//        int&& irr = 10; // r-value ref, okay

//        int value = 100;
////        int&& irr2 = value; // not okay

//        // v4 is l-value
//        auto v4 = f1() + f2(); // returned value from f1() and f2() are r-values


//        {
//            int L[100];
//            L[0] = 1000;
//            L[100] = 2000; // out of bounds, UB
//        }
//        {
//            auto L = std::array<int, 100>();
//            L[0] = 1000;
//            L[100] = 2000; // out of bounds, UB, caught in run-time if debug mode compile
//        }



//        auto h = Huge{}; // h is in stack, h.x, h.y, h.v are all in stack

//        std::vector<Huge> v(1000); // Huge instances are allocated in Head memory

//        // h is destructed, v is destructed
//    }

////    int a = 10;
////    int const * const p = &a;
////    *p = 20;

    return 0;
}
