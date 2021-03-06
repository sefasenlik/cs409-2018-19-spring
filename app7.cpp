// know-it: always shared_ptr + deferred d-tor as garbage col. <---> Java's way

// in compiled machine code there is only executable code and non-executable data
// consider executable code as one big function.
// we emulate our so-called "functions" by loading/saving from/to stack
//   and jumping to different locations of machine language executable
// so "functions" are only our abstractions. they are portions of exe. code.
// you cannot create a new function at run-time. (there are exceptions)
// all functions are created at compile-time.

// function pointers: printWithStyleA, printWithStyleB
// function objects: PrintWithStyleA, PrintWithStyleB
// how to pass any one of PrintWithStyleA or PrintWithStyleB?
//  bad solution: inheritance and virtual functions.
//  (resolved at run-time but we know details about it at compile-time)
//  better solution: std::function. works with any callable. still run-time resolved
//  probably best solution: templates + lambdas

// new way of defining functions: lambdas: in-line function object instantiation

// following lectures:
// lambdas in detail
// template parameters binding with runtime parameter types
// template-template types, template auto, type constructors
// curiously recurring template pattern (CRTP)

#include <iostream>
#include <functional>
#include <stdint.h>

#include "Matrix.h"

using namespace std;

//void printColorWithStyleA(const Color& col)
//{
//    cout << (int)col.r << "," << (int)col.g << "," << (int)col.b;
//}

//void printColorWithStyleB(const Color& col)
//{
//    cout << (int)col.r << ":" << (int)col.g << ":" << (int)col.b;
//}


struct PrintColorWithStyleA
{
    auto operator()(const Color& col) const
    {
        cout << (int)col.r << "," << (int)col.g << "," << (int)col.b;
    }
};

//struct PrintColorWithStyleB
//{
//    void operator()(const Color& col) const
//    {
//        cout << (int)col.r << ":" << (int)col.g << ":" << (int)col.b;
//    }
//};

auto printImage = [](const Image& img, auto printStyler)
{
    using FUNC = decltype(printStyler);

    for(int i=0; i<img.nRows; ++i)
    {
        for(int j=0; j<img.nCols; ++j)
        {
            printStyler(img(i, j));
            if(j != img.nCols-1)
                cout << "|";
        }
        cout << endl;
    }
};

// ----------------------
int main(int argc, char* argv[])
{
    auto img = Image{10, 10};
    img(5, 5) = 100;
//    printImage(img, printColorWithStyleA);
//    cout << "------" << endl;
//    printImage(img, printColorWithStyleB);
//    cout << "++++++" << endl;
//    printImage(img, PrintColorWithStyleA{});
//    cout << "------" << endl;
//    printImage(img, PrintColorWithStyleB{});
//    cout << "++++++" << endl;

    char separator = '_';

    auto printStyler = [=](const Color& col) {
        cout << (int)col.r << separator << (int)col.g << separator << (int)col.b;
    };
    printImage(img, printStyler);

    printImage(img, [=](const Color& col) {
        cout << (int)col.r << "/" << (int)col.g << "/" << (int)col.b;
    });

    return 0;
}
