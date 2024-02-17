#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

class SinglyLinkedListNode {
public:
    int data;
    SinglyLinkedListNode* next;

    SinglyLinkedListNode(int node_data) {
        this->data = node_data;
        this->next = nullptr;
    }
};

class SinglyLinkedList {
public:
    SinglyLinkedListNode* head;
    SinglyLinkedListNode* tail;

    SinglyLinkedList() {
        this->head = nullptr;
        this->tail = nullptr;
    }

    void insert_node(int node_data) {
        SinglyLinkedListNode* node = new SinglyLinkedListNode(node_data);

        if (!this->head) {
            this->head = node;
        }
        else {
            this->tail->next = node;
        }

        this->tail = node;
    }
};

void print_singly_linked_list(SinglyLinkedListNode* node, string sep) {
    while (node) {
        cout << node->data;

        node = node->next;

        if (node) {
            cout << sep;
        }
    }
}

void free_singly_linked_list(SinglyLinkedListNode* node) {
    while (node) {
        SinglyLinkedListNode* temp = node;
        node = node->next;

        free(temp);
    }
}

// Complete the mergeLists function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
SinglyLinkedListNode* mergeLists(SinglyLinkedListNode*& head1, SinglyLinkedListNode*& head2) {

    SinglyLinkedListNode* result = new SinglyLinkedListNode(0);
    
    SinglyLinkedListNode* temp = result;
    while (head1 != nullptr && head2 != nullptr)
    {
        if (head1->data < head2->data)
        {
            temp->next = head1;
            head1 = head1->next;
            temp = temp->next;
        }
        else
        {
            temp->next = head2;
            head2 = head2->next;
            temp = temp->next;
        }
    }

    if (head1 != nullptr)
    {
        temp->next = head1;
    }
    else
    {
        temp->next = head2;
    }

    temp = result;
    result = result->next;
    delete temp;

    return result;
}

int main()
{
        SinglyLinkedList* llist1 = new SinglyLinkedList();

        llist1->insert_node(1);
        llist1->insert_node(3);
        llist1->insert_node(7);


        SinglyLinkedList* llist2 = new SinglyLinkedList();

        llist2->insert_node(3);
        llist2->insert_node(4);

        SinglyLinkedListNode* llist3 = mergeLists(llist1->head, llist2->head);

        print_singly_linked_list(llist3, " ");
        cout << "\n";

        free_singly_linked_list(llist3);

    return 0;
}
