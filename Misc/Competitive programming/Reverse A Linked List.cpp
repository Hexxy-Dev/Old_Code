#include <iostream>
#include <algorithm>
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

void print_singly_linked_list(SinglyLinkedListNode* node, string sep, ofstream& fout) {
    while (node) {
        fout << node->data;

        node = node->next;

        if (node) {
            fout << sep;
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
SinglyLinkedListNode* insertNodeAtTail(SinglyLinkedListNode* head, int data) {
    SinglyLinkedListNode* current = head;
    while (current->next)
    {
        current = current->next;
    }

    current->next = new SinglyLinkedListNode(data);
    return head;
}

SinglyLinkedListNode* reverse(SinglyLinkedListNode* head) {
    if (!head->next)
    {
        SinglyLinkedListNode* newHead = head;
        return newHead;
    }
    SinglyLinkedListNode* newHead = reverse(head->next);
    newHead = insertNodeAtTail(newHead, head->data);
    delete head;
    return newHead;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS VERSION IS WAYY BETTER!!
SinglyLinkedListNode* reverse(SinglyLinkedListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    SinglyLinkedListNode* remaining = reverse(head->next);
    head->next->next = head;
    head->next = nullptr;
    return remaining;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//Node Reverse(Node head) {

    /* We have two conditions in this if statement.
      This first condition immediately returns null
      when the list is null. The second condition returns
      the final node in the list. That final node is sent
      into the "remaining" Node below.
    -----------------------------------------------------*/

//    if (head == null || head.next == null) {
//        return head;
//    }

    /* When the recursion creates the stack for A -> B -> C
       (RevA(RevB(RevC()))) it will stop at the last node and
       the recursion will end, beginning the unraveling of the
       nested functions from the inside, out.
    -----------------------------------------------------*/

//    Node remaining = Reverse(head.next);

    /* Now we have the "remaining" node returned and accessible
       to the node prior. This remaining node will be returned
       by each function as the recursive stack unravels.

       Assigning head to head.next.next where A is the head
       and B is after A, (A -> B), would set B's pointer to A,
       reversing their direction to be A <- B.
    -----------------------------------------------------*/

//    head.next.next = head;

    /* Now that those two elements are reversed, we need to set
    the pointer of the new tail-node to null.
    -----------------------------------------------------*/

//    head.next = null;

    /* Now we return remaining so that remaining is always
       reassigned to itself and is eventually returned by the
       first function call.
    -----------------------------------------------------*/

//    return remaining;
//}

/*

Take an example, 1 -> 2 -> 3 -> null
First Call to the function,

1 -> 2 -> 3 -> null
^
|
head

head is not null OR head.next is not null,
Jump to ELSE block,
Assigning Node remaining = Reverse(head.next);
//Statements after this to be executed later


Second Call to the function,

1 -> 2 -> 3 -> null
     ^
     |
     head

head is not null OR head.next is not null,
Jump to ELSE block,
Assigning Node remaining = Reverse(head.next);
//Statements after this to be executed later


Third Call to the function,

1 -> 2 -> 3 -> null
          ^
          |
          head

head is not null OR BUT head.next is null,
return head; //Now important thing is to remember what we are returning, (head, pointing to 3)



Attaboy! Time Machine time!

1 -> 2 -> 3 -> null
          ^
          |
          head

Resuming Second Call to the function,
Second call,
head here is equal to the reference to the node which has data = 2
1 -> 2 -> 3 -> null
     ^
     |
     head


Node remaining is equal to a reference to the node, which has 3 inside it.

head.next.next = head;
//head is reference to node having data as 2
head.next = null;

So the status is now,
1 -> 2 <- 3 -> null
     ^    ^
     |    |
     head remaining

We reach the last line of second function,

return remaining;




Resuming First Call to the function,
Second call to the function returned 'remaining' which is a reference to the node which has 3 as its data,
Whereas we know that, head in the first function instance is equal to the reference to the node which has data = 1
1 -> 2 -> 3 -> null
^
|
head


Node remaining is STILL equal to a reference to the node, which has 3 inside it.

head.next.next = head;
//head is reference to node having data as 1
head.next = null;

So the status is now,
null <-1 <- 2 <- 3 -> null
       ^         ^
       |         |
       head      remaining

We reach the last line of first copy of function

return remaining;

And the head of the reversed linked list is returned.

*/
int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int tests;
    cin >> tests;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int tests_itr = 0; tests_itr < tests; tests_itr++) {
        SinglyLinkedList* llist = new SinglyLinkedList();

        int llist_count;
        cin >> llist_count;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < llist_count; i++) {
            int llist_item;
            cin >> llist_item;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            llist->insert_node(llist_item);
        }

        SinglyLinkedListNode* llist1 = reverse(llist->head);

        print_singly_linked_list(llist1, " ", fout);
        fout << "\n";

        free_singly_linked_list(llist1);
    }

    fout.close();

    return 0;
}
