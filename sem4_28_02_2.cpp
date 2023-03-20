#include <iostream>
#include <chrono>
#include <random>
#include <fstream>

using namespace std;

int strat_a(int k, int n, int* numbers)
{
    for (int i = 0; i < n; i++)
    {
        if (numbers[i] == k)
        {
            if (i != 0)
            {
                swap(numbers[0], numbers[i]);
                return 0;
            }
            else
            {
                return i;
            }
        }
    }
    return -1;
}


int strat_b(int k, int n, int* numbers)
{
    for (int i = 0; i < n; i++)
    {
        if (numbers[i] == k)
        {
            if (i != 0)
            {
                swap(numbers[i - 1], numbers[i]);
                return i - 1;
            }
            else
            {
                return i;
            }
        }
    }
    return -1;
}


int strat_c(int k, int n, int* numbers, int* cnt)
{
    for (int i = 0; i < n; i++)
    {
        if (numbers[i] == k)
        {
            cnt[k]++;
            if ((i != 0) && (cnt[k] >= cnt[numbers[i - 1]]))
            {
                swap(numbers[i - 1], numbers[i]);
                return i - 1;
            }
            else
            {
                return i;
            }
        }
    }
    return -1;
}


int main()
{
    const int n = 1000;
    int numbers[n];
    int cnt[n];
    for (int i = 0; i < n; i++)
    {
        numbers[i] = i;
        cnt[i] = 0;
    }

    cout << "iter = [";
    for (int i = 10; i < 1000; i += 10)
    {
        cout << i << ", ";
    }

    cout << "]" << '\n' << '\n' << "A = [";
    const long iter = 100;

    unsigned seed = 1001;
    default_random_engine rng(seed);
    uniform_int_distribution<unsigned> dstr(1, 1500);
    int values[iter];
    for (int i = 0; i < 20; i++)
    {
        values[i] = numbers[dstr(rng)];
    }

    for (int i = 20; i < iter; i++)
    {
        values[i] = values[i - 20];
    }


    for (unsigned i = 10; i < 1000; i += 10)
    {
        auto begin = chrono::steady_clock::now();
        for (unsigned c = 0; c < 100; c++)
        {
            strat_a(values[c], i, numbers);
        }
        auto end = chrono::steady_clock::now();
        auto time_span = chrono::duration_cast<chrono::microseconds>(end - begin);
        cout << time_span.count() << ", ";
    }


    cout << "]" << '\n' << '\n' << "B = [";
    for (unsigned i = 10; i < 1000; i += 10)
    {
        auto begin = chrono::steady_clock::now();
        for (unsigned c = 0; c < 100; c++)
        {
            strat_b(values[c], i, numbers);
        }
        auto end = chrono::steady_clock::now();
        auto time_span = chrono::duration_cast<chrono::microseconds>(end - begin);
        cout << time_span.count() << ", ";
    }


    cout << "]" << '\n' << '\n' << "C = [";
    for (unsigned i = 10; i < 1000; i += 10)
    {
        auto begin = chrono::steady_clock::now();
        for (unsigned c = 0; c < 100; c++)
        {
            strat_c(values[c], i, numbers, cnt);
        }
        auto end = chrono::steady_clock::now();
        auto time_span = chrono::duration_cast<chrono::microseconds>(end - begin);
        cout << time_span.count() << ", ";
    }

    cout << "]";

    return 0;
}

