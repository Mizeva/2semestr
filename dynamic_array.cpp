#include <iostream>
using namespace std;

struct DynamicArray
{
    int* elements = nullptr;
    unsigned capacity = 0;
    unsigned size = 0;

    DynamicArray new_array(unsigned _size, int init_val = 0)
    {
        DynamicArray da;
        da.size = _size;
        da.capacity = _size;
        da.elements = new int[capacity];
        for (int i = 0; i < _size; i++)
        {
            elements[i] = init_val;
        }
        return da;
    }

    void erase()
    {
        if (elements)
        {
            size = 0;
            capacity = 0;
            delete[] elements;
            elements = nullptr;
        }
        return;
    }

    DynamicArray& reserve(DynamicArray& da, unsigned cap)
    {
        DynamicArray new_da;
        if (cap > capacity)
        {
            new_da.new_array(cap);
            new_da.elements = da.elements;
        }
        da.erase();
        return new_da;
    }

    DynamicArray clone(DynamicArray& da)
    {
        DynamicArray new_da;
        new_da.new_array(da.size);
        new_da.elements = da.elements;
        return new_da;
    }

    DynamicArray& assign(DynamicArray const& src, DynamicArray& dst)
    {
        if (dst.capacity < src.size)
        {
            dst.reserve(dst, src.size);
        }
        delete[] dst.elements;
        dst.size = src.size;
        dst.elements = src.elements;
        return dst;
    }

    DynamicArray& push_back1(DynamicArray& da, int val)
    {
        if (da.size + 1 > da.capacity)
        {
            unsigned cap = da.capacity + 1;
            da.reserve(da, cap);
        }
        size++;
        elements[size + 1] = val;
    }

    DynamicArray& push_back2(DynamicArray& da, int val)
    {
        if (da.size + 1 > da.capacity)
        {
            unsigned cap = da.capacity + 5;
            da.reserve(da, cap);
        }
        size++;
        elements[size + 1] = val;
    }

    DynamicArray& push_back3(DynamicArray& da, int val)
    {
        if (da.size + 1 > da.capacity)
        {
            unsigned cap = da.capacity * 2;
            da.reserve(da, cap);
        }
        size++;
        elements[size + 1] = val;
    }

    int& operator [] (int i)
    {
        return elements[i];
    }
};

int main()
{


    return 0;
}
