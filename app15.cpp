// std::reference_wrapper
// threads --> std::thread: func*, functor, lambda
// tasks --> std::async: future, promise

// structured bindings: pair, map examples

#include <iostream>
#include <vector>
#include <thread>
#include <future>

using namespace std;

//template<typename T>
//struct ReferenceWrapper
//{
//    T& ref;
//    ReferenceWrapper(T& ref) : ref{ref} { }

//    operator T() const { return ref; }
//};

void accumulate(const vector<int>& v, int& sum, int left, int right)
{
    sum = 0;
    for(int i=left; i<right; ++i)
    {
        cout << i << endl;
        sum += v[i];
    }
}

struct Accumulate
{
    int sum;

    void operator() (const vector<int>& v, int left, int right)
    {
        sum = 0;
        for(int i=left; i<right; ++i)
        {
            cout << i << endl;
            sum += v[i];
        }
    }
};


// ----------------------
int main(int argc, char* argv[])
{
//    int k = 10, m = 20;
//    auto k_ref = ref(k);
//    auto V = vector{ref(k), ref(m)}; // using std::reference_wrapper<int> automatically

    auto v = vector{1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6};
//    {
//        auto sum1 = 0, sum2 = 0;
//        auto t1 = thread{accumulate, ref(v), ref(sum1), 0, v.size()/2};
//        auto t2 = thread{accumulate, ref(v), ref(sum2), v.size()/2, v.size()};
//        t1.join();
//        t2.join();
//        cout << "sum1=" << sum1 << ", sum2=" << sum2 << ", total=" << (sum1+sum2) << endl;
//    }

//    {
//        auto a1 = Accumulate{};
//        auto a2 = Accumulate{};
//        auto t1 = thread{ref(a1), ref(v), 0, v.size()/2};
//        auto t2 = thread{ref(a2), ref(v), v.size()/2, v.size()};
//        t1.join();
//        t2.join();
//        cout << "sum1=" << a1.sum << ", sum2=" << a2.sum << ", total=" << (a1.sum+a2.sum) << endl;
//    }

//    {
//        auto sum1 = 0, sum2 = 0;
//        auto t1 = thread{[&] {
//            auto sz = v.size()/2;
//            for(int i=0; i<sz; ++i)
//            {
//                cout << i << endl;
//                sum1 += v[i];
//            }
//        }};
//        auto t2 = thread{[&] {
//            auto right = v.size();
//            auto left = right/2;
//            for(int i=left; i<right; ++i)
//            {
//                cout << i << endl;
//                sum2 += v[i];
//            }
//        }};
//        t1.join();
//        t2.join();
//        cout << "sum1=" << sum1 << ", sum2=" << sum2 << ", total=" << (sum1+sum2) << endl;
//    }


    {
        auto f = [](const vector<int>& v, int left, int right)
        {
            auto sum = 0;
            for(int i=left; i<right; ++i)
            {
                cout << i << endl;
                sum += v[i];
            }
            return sum;
        };

        auto t1 = async(launch::async, f, ref(v), 0, v.size()/2);
        auto t2 = async(launch::async, f, ref(v), v.size()/2, v.size());
        auto sum1 = t1.get();
        auto sum2 = t2.get();
        cout << "sum1=" << sum1 << ", sum2=" << sum2 << ", total=" << (sum1+sum2) << endl;
    }

    return 0;
}
