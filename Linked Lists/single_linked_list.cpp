#include <bits/stdc++.h>

using namespace std;

class node
{
public:
    int data;
    node* next;
};

void print(node* head)
{
    while(head != NULL)
    {
        cout<<head->data;
        head = head->next;
    }
}

int main()
{
    node* first = NULL;
    node* second = NULL;
    node* third = NULL;

    first = new node;
    second = new node;
    third = new node;

    first->data = 1;
    first->next = second;
    second->data = 2; // assign data to second node
    second->next = third;

    third->data = 3; // assign data to third node
    third->next = NULL;

    print(first);

    return 0;

}
