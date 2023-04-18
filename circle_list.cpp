#include <iostream>
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

int main()
{
    List list;
    /*Node* p = list.InsertAfter(nullptr, 2);
    list.InsertAfter(p, 3);
    Node* p1 = list.InsertAfter(p, 10);
    list.InsertAfter(p1, 5);
    list.Print(p);
    cout << '\n';
    list.RemoveAfter(p);
    list.Print(p);
    cout << '\n';

    list.ReverseItr(p);
    list.Print(p);
    cout << '\n';

    list.ReverseRec(p);
    list.Print(p);
    cout << '\n';*/

    Node* p = nullptr;
    int n, k;
    cin >> n >> k;
    for (int i = 1; i < n + 1; i++)
    {
        Node* p1 = list.InsertAfter(p, i);
        p = p1;
    }

    while (p->next != p)
    {
        for (int i = 1; i < k; i++)
        {
            p = p->next;
        }
        list.RemoveAfter(p);
    }

    list.Print(p);

    return 0;
}