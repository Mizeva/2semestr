#include <iostream>
#include <chrono>
using namespace std;

struct Node
{
    int val;
    Node* next;

    Node(int v)
        : val(v), next(nullptr) {}

};

struct List
{
private:
    Node* first;
    Node* last;


public:

    List() : first(nullptr), last(nullptr) {}

    bool IsEmpty()
    {
        if (first == nullptr)
            return 1;
        else
            return 0;
    }

    void Print(Node* link)
    {
        cout << link->val << ' ';
        Node* p = link->next;
        while (p != link)
        {
            cout << p->val << ' ';
            p = p->next;
        }
    }

    /*Node* operator[] (const int index)
    {
        if (IsEmpty()) return nullptr;

        Node* p = first;

        for (int i = 0; i < index; i++)
        {
            p = p->next;
            if (!p) return nullptr;
        }
        return p;
    }*/

    Node* InsertAfter(Node* const current, int v)
    {
        Node* p = current;
        Node* p1 = new Node(v);
        if (current == nullptr)
        {
            p1->next = p1;
            return p1;
        }
        p1->next = p->next;
        p->next = p1;
        return p1;
    }

    Node* RemoveAfter(Node* const current)
    {
        Node* p1 = current;
        if (current == nullptr)
        {
            return nullptr;
        }
        Node* p = current->next->next;
        delete p1->next;
        p1->next = p;
        return p;
    }

    void Erase(Node* const head)
    {
        Node* p = head;
        while (p)
        {
            p = RemoveAfter(head);
        }
        delete p;
        return;
    }

    void ReverseRec(Node* const head)
    {
        Node* h = head;
        Node* p = h->next;
        h->next = nullptr;
        if (p->next != nullptr)
        {
            ReverseRec(p);
        }
        p->next = h;
        return;
    }

    void ReverseItr(Node* const head)
    {
        Node* h = head;
        Node* p = head->next;
        Node* p1 = head->next->next;
        while (p != head)
        {
            p->next = h;
            h = p;
            p = p1;
            p1 = p->next;
        }
        p->next = h;
        return;
    }
};


int array_flav(int total, int step) 
{
    int* arr = new int[total];
    for (int i = 0; i != total; i++) 
    {
        arr[i] = i;
    }
    int k = step;
    for (int i = 0; i != total - 1; i++) 
    {
        while (arr[k % total] == -1) 
        {
            k++;
        }
        arr[k % total] = -1;
        /*for (int j = 0; j != total; j++)
        {
            cout << arr[j] << " ";
        }*/
        k += step;
        //cout << "\n";
    }
    int t = 0;
    while (arr[t] == -1) 
    {
        t++;
    }
    int temp = arr[t];
    delete[] arr;
    return temp;
}

int main()
{
    
    int k = 3;
    for (int n = 10; n < 1000; n = n + 10)
    {
        List list;
        Node* p = nullptr;
        for (int j = 1; j < n + 1; j++)
        {
            Node* p1 = list.InsertAfter(p, j);
            p = p1;
        }
        auto begin = chrono::steady_clock::now();
        while (p->next != p)
        {
            for (int i = 1; i < k; i++)
            {
                p = p->next;
            }
            list.RemoveAfter(p);
        }
        auto end = chrono::steady_clock::now();
        auto time_span = chrono::duration_cast<chrono::microseconds>(end - begin);

        cout << time_span.count() << '\n';
    }

    
    //list.Print(p);
    //cout << '\n';

    cout << "array";
    for (int n = 10; n < 1000; n = n + 10)
    {
        int men[1000];
        int current = 0;
        for (int i = 0; i < n; i++)
        {
            men[i] = i + 1;
        }
        auto  begin = chrono::steady_clock::now();

        array_flav(n, k);

        auto end = chrono::steady_clock::now();
        auto time_span = chrono::duration_cast<chrono::microseconds>(end - begin);

        cout << time_span.count() << '\n';
    }

    return 0;
}