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

node* linkmerge(node* a, node *b)
{   node *result = NULL;
    if (a==NULL)
        return b;
    else if (b==NULL)
        return a;

    if (a->data<=b->data)
    {
        cout<<"kya hora";
        result =  a;
        result->next = linkmerge(a->next, b);
    }
    else
    {
        cout<<"kcuh ini";
        result = b;
        result->next = linkmerge(a, b->next);
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
    second->data = 7; // assign data to second node
    second->next = third;

    third->data = 14; // assign data to third node
    third->next = NULL;

    node* first2 = NULL;
    node* second2 = NULL;
    node* third2 = NULL;

    first2 = new node;
    second2 = new node;
    third2 = new node;

    first2->data = 4;
    first2->next = second2;
    second2->data = 6; // assign data to second node
    second2->next = third2;

    third2->data = 9; // assign data to third node
    third2->next = NULL;
    print(first2);
    print(first);
    node* a = NULL;
    a = linkmerge(first,first2);
    print(a);

    return 0;

}
