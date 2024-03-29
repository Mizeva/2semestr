﻿#include <iostream>
#include <random>
#include <chrono>

using namespace std;

void forward_step(unsigned arr[], unsigned const begin_idx, unsigned const end_idx)
{
    for (unsigned j = 0; j < end_idx - begin_idx; ++j)
    {
        if (arr[j] > arr[j + 1])
        {
            swap(arr[j], arr[j + 1]);
        }
    }
    return;
}



void backward_step(unsigned arr[], unsigned const begin_idx, unsigned const end_idx)
{
    for (unsigned j = end_idx - begin_idx; j < 0; --j)
    {
        if (arr[j] > arr[j - 1])
        {
            swap(arr[j], arr[j - 1]);
        }
    }
    return;
}

void shaker_sort(unsigned arr[], unsigned const begin_idx, unsigned const end_idx)
{
    for (unsigned i = 0; i < end_idx - begin_idx; i++)
    {
        forward_step(arr, begin_idx, end_idx);
        backward_step(arr, begin_idx, end_idx);
    }
    return;
}

int main()
{
    const int n = 1000;
    unsigned arr1[n], arr2[n], arr3[n];

    unsigned seed = 1001;
    default_random_engine rng(seed);
    uniform_int_distribution<unsigned> dstr(1, 1500);
    for (int i = 0; i < n; i++)
    {
        arr1[i] = dstr(rng);
        arr2[i] = dstr(rng);
        arr3[i] = dstr(rng);
        //cout << arr1[i] << '\n';
    }

    for (unsigned i = 0; i < n; i++)
    {
        forward_step(arr1, 0, n);
    }

    for (unsigned i = 0; i < n; i++)
    {
        backward_step(arr2, 0, n);
    }

    shaker_sort(arr3, 0, n);

    bool flag1 = 0, flag2 = 0, flag3 = 0;
    for (int i = 0; i < n - 1; i++)
    {
        if (arr1[i] > arr1[i + 1])
        {
            flag1 = 1;
        }
        if (arr2[i] > arr2[i + 1])
        {
            flag2 = 1;
        }
        if (arr3[i] > arr3[i + 1])
        {
            flag3 = 1;
        }
    }

    if (flag1)
    {
        cout << "forward_step failed" << '\n';
    }
    else
    {
        cout << "forward_step works" << '\n';
    }

    if (flag1)
    {
        cout << "backward_step failed" << '\n';
    }
    else
    {
        cout << "backward_step works" << '\n';
    }

    if (flag1)
    {
        cout << "shaker_sort failed" << '\n';
    }
    else
    {
        cout << "shaker_sort works" << '\n';
    }

    return 0;
}