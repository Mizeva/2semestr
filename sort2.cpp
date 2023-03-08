#include <iostream>
#include <random>
#include <chrono>

using namespace std;

void sortt(unsigned arr[], int step, unsigned begin_idx, unsigned end_idx)
{
    for (unsigned i = 0; i < end_idx - begin_idx - step; i += step)
    {
        for (unsigned j = 0; j < end_idx - begin_idx; j += step)
        {
            if (arr[j] > arr[j + step])
            {
                swap(arr[j], arr[j + step]);
            }
        } 
    }
    return;
}


int main()
{
    const int n = 1000;
    unsigned arr[n], arr1[n];

    unsigned seed = 1001;
    default_random_engine rng(seed);
    uniform_int_distribution<unsigned> dstr(1, 1500);
    for (int i = 0; i < n; i++)
    {
        arr[i] = dstr(rng);
    }


    for (unsigned i = 10; i < 1000; i += 10)
    {
        cout << i << " ";
        for (int i = 0; i < n; i++)
        {
            arr1[i] = arr[i];
        }

        auto begin = chrono::steady_clock::now();

        int step = 2;
        while (n / step > 0)
        {
            sortt(arr1, step, 0, n);
            step *= 2;
        }

        auto end = chrono::steady_clock::now();
        auto time_span = chrono::duration_cast<chrono::microseconds>(end - begin);

        cout << time_span.count() << '\n';
    }

    bool flag = 0;
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            flag = 1;
        }
    }

    return 0;
}

