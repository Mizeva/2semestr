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

    /*void removeFirst()
    {
        //if (IsEmpty()) return;

        Node* p = first;
        first = p->next;
        delete p;
    }

    void removeLast()
    {
        if (first == last)
        {
            last = nullptr;
            removeFirst();
            return;
        }
        Node* p = first;
        while (p->next != last)
        {
            p = p->next;
        }
        p->next = nullptr;
        delete last;
        last = p;
    }*/

public:

    List() : first(nullptr), last(nullptr) {}

    bool IsEmpty()
    {
        if (first == nullptr)
            return 1;
        else
            return 0;
    }

    /*void PushBack(int v)
    {
        Node* p = new Node(v);
        if (IsEmpty())
        {
            first = p;
            last = p;
            return;
        }
        last->next = p;
        last = p;
    }*/

    void Print()
    {
        if (!IsEmpty())
        {
            Node* p = first;
            while (p)
            {
                cout << p->val << ' ';
                p = p->next;
            }
        }
    }

    /*Node* Find(int v)
    {
        Node* p = first;
        while (p && v != p->val)
        {
            p = p->next;
        }
        return p;
    }

    void Remove(int v)
    {
        if (IsEmpty()) return;
        if (first->val == v)
        {
            removeFirst();
            return;
        }
        if (last->val == v)
        {
            removeLast();
            return;
        }
    }

    Node* operator[] (const int index)
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
        if (current == nullptr)
        {
            Node* p1 = new Node(v);
            first = p1;
            return p1;
        }
        Node* p = first;
        while (p != current)
        {
            p = p->next;
        }
        Node* p1 = new Node(v);
        p1->next = current->next;
        current->next = p1;
        return p1;
    }

    Node* RemoveAfter(Node* const current)
    {
        if (current == nullptr)
        {
            return nullptr;
        }
        Node* p = current->next;
        current->next = p->next;
        delete p;
        return current->next;
    }

    void Erase(Node* const head)
    {
        Node* p = head;
        while (p)
        {
            p = RemoveAfter(head);
        }
        delete head;
        return;
    }

    Node* ReverseRec(Node* const head)
    {
        if (head->next != nullptr)
        {
            Node* p = ReverseRec(head->next);
            p->next = head;
        }
        else
        {
            first = head;
            return head;
        }
        head->next = nullptr;
        return head;
    }

    Node* ReverseItr(Node* const head)
    {
        Node* h = head;
        Node* p = head->next;
        Node* p1 = p->next;
        head->next = nullptr;
        while (p1 != nullptr)
        {
            p->next = h;
            h = p;
            p = p1;
            p1 = p->next;
        }
        p->next = h;
        first = p;
        return p;
    }

};

int main()
{
    List list;
    Node* p = list.InsertAfter(nullptr, 2);
    list.InsertAfter(p, 3);
    Node* p1 = list.InsertAfter(p, 10);
    list.InsertAfter(p1, 5);
    list.Print();
    cout << '\n';
    list.RemoveAfter(p);
    list.Print();
    cout << '\n';
    Node* p2 = list.ReverseItr(p);
    list.Print();
    cout << '\n';
    list.ReverseRec(p2);
    list.Print();
    cout << '\n';

    list.Erase(p);
}