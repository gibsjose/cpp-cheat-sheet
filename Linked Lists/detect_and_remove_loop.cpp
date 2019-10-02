#include <bits/stdc++.h>
using namespace std;

struct Node {
	int data;
	struct Node* next;
};

void push(struct Node** head_ref, int new_data)
{

	struct Node* new_node = new Node;


	new_node->data = new_data;


	new_node->next = (*head_ref);


	(*head_ref) = new_node;
}


void loopremover(Node* head)
{

    unordered_map<Node*, int> node_map;

    Node* last = NULL;
    while (head != NULL) {

        if (node_map.find(head) == node_map.end()) {
            node_map[head]++;
            last = head;
            head = head->next;
        }

        else {
            last->next = NULL;
            break;
        }
    }
}
void printList(Node* head)
{
	while (head != NULL) {
		cout << head->data << " ";
		head = head->next;
	}
	cout << endl;
}


int main()
{

	struct Node* head = NULL;

	push(&head, 7);
	push(&head, 4);
	push(&head, 5);
	push(&head, 10);

	head->next->next->next->next = head;
    //printList(head);
	loopremover(head);

    printf("Linked List after removing loop \n");
    printList(head);

    return 0;
}

