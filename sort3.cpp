#include <iostream>
#include <random>
#include <chrono>
#include <fstream>

using namespace std;

void sort_half(unsigned arr[], unsigned begin_idx, unsigned end_idx)
{
    int step = end_idx - begin_idx / 2;
    while (step > 0)
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
        step /= 2;
    }
    
    return;
}

void sort_hibb(unsigned arr[], unsigned begin_idx, unsigned end_idx)
{
    int i = 0;
    while (pow(2, i) - 1 < end_idx - begin_idx)
    {
        i++;
    }
    int step = pow(2, i - 1) - 1;
    while (step >= 1)
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
        step = (step + 1) / 2 - 1;
    }
    return;
}

int fibon(unsigned arr[], unsigned n)
{
    arr[0] = 1;
    arr[1] = 1;
    int i = 1;
    while (arr[i] < n)
    {
        arr[i + 1] = arr[i] + arr[i - 1];
        i++;
    }
    return i;
}

void sort_fib(unsigned arr[], unsigned fib[], unsigned begin_idx, unsigned end_idx, int idx_f)
{
    int step = fib[idx_f];
    while (idx_f >= 1)
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
        idx_f--;
        step = fib[idx_f];
    }
    return;
}


int main()
{
    ofstream fout;
    fout.open("output.txt");


    const int n = 1000;
    unsigned arr[n], arr1[n];

    unsigned seed = 1001;
    default_random_engine rng(seed);
    uniform_int_distribution<unsigned> dstr(1, 1500);
    for (int i = 0; i < n; i++)
    {
        arr[i] = dstr(rng);
    }
    
    unsigned fib[n / 2];
    int idx = fibon(fib, n);

    fout << "iter = [";
    for (unsigned i = 10; i < 1000; i += 10)
    {
        if (i == 10)
        {
            fout << i;
        }
        else
        {
            fout << ", " << i;
        }
    }
    fout << "]" << '\n';

    fout << "half = [";
    for (unsigned i = 10; i < 1000; i += 10)
    {
        for (int j = 0; j < i; j++)
        {
            arr1[i] = arr[i];
        }
        auto begin = chrono::steady_clock::now();

        sort_half(arr1, 0, i);

        auto end = chrono::steady_clock::now();
        auto time_span = chrono::duration_cast<chrono::microseconds>(end - begin);

        if (i == 10)
        {
            fout << time_span.count();
        }
        else
        {
            fout << ", " << time_span.count();
        }
    }
    fout << "]" << '\n';

    fout << "hibb = [";
    for (unsigned i = 10; i < 1000; i += 10)
    {
        for (int j = 0; j < i; j++)
        {
            arr1[i] = arr[i];
        }
        auto begin = chrono::steady_clock::now();

        sort_hibb(arr1, 0, i);

        auto end = chrono::steady_clock::now();
        auto time_span = chrono::duration_cast<chrono::microseconds>(end - begin);

        if (i == 10)
        {
            fout << time_span.count();
        }
        else
        {
            fout << ", " << time_span.count();
        }
    }
    fout << "]" << '\n';

    fout << "fib = [";
    for (unsigned i = 10; i < 1000; i += 10)
    {
        for (int j = 0; j < i; j++)
        {
            arr1[i] = arr[i];
        }
        int idx = fibon(fib, i);
        idx--;
        auto begin = chrono::steady_clock::now();

        sort_fib(arr1, fib, 0, i, idx);

        auto end = chrono::steady_clock::now();
        auto time_span = chrono::duration_cast<chrono::microseconds>(end - begin);

        if (i == 10)
        {
            fout << time_span.count();
        }
        else
        {
            fout << ", " << time_span.count();
        }
    }
    fout << "]" << '\n';

    fout.close();
    return 0;
}

