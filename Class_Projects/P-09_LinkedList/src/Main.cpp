#include <iostream>
#include <conio.h>

template<typename T>
struct LinkedList {
	LinkedList(const T& val)
		: val(val), next(NULL)
	{}
	LinkedList(const T& val, LinkedList* node)
		: val(val), next(node)
	{}
	T val;
	LinkedList* next;

	void Push_back(const T& val)
	{
		LinkedList* ptr = Get_Last_Node();
		ptr->next = new LinkedList(val);
	}

	T Pop_back()
	{
		if (Size() == 1)
			throw "Cannot pop root node";
		LinkedList* ptr = Get_Node_At_index(Size() - 2);
		T val = ptr->next->val;
		delete ptr->next;
		ptr->next = nullptr;
		return val;
	}

	void Delete(const size_t& index)
	{
		if (!index) {
			LinkedList* ptr = this->next;
			LinkedList* nxt = nullptr;
			if (ptr) {
				nxt = ptr->next;
				this->val = ptr->val;
				delete ptr;
			}
			this->next = nxt;
			return;
		}
		LinkedList* prev = Get_Node_At_index(index - 1);
		LinkedList* nxt = prev->next->next;
		delete prev->next;
		prev->next = nxt;
	}

	T Pop(const size_t& index)
	{
		LinkedList* ptr = Get_Node_At_index(index);
		T value = ptr->val;
		Delete(index);
		return value;
	}

	void Insert(const size_t& index, const T& value)
	{
		if (!index) {
			LinkedList* ptr = new LinkedList(this->val, this->next);
			this->val = value;
			this->next = ptr;
			return;
		}
		LinkedList* ptr = Get_Node_At_index(index - 1);
		LinkedList* nxt = ptr->next;
		ptr->next = new LinkedList(value);
		ptr->next->next = nxt;
	}


	size_t Size()
	{
		size_t size = 0;
		LinkedList* ptr = this;
		while (ptr->next) {
			ptr = ptr->next;
			size++;
		}
		return size + 1;
	}

	void display()
	{
		for (size_t i = 0; i < Size(); i++)
			std::cout << (*this)[i] << ' ';
		std::cout << '\n';
	}

	T operator[](const size_t& index) { return Get_Node_At_index(index)->val; }

	LinkedList* Get_Last_Node()
	{
		LinkedList* ptr = this;
		while (ptr->next)
			ptr = ptr->next;
		return ptr;
	}

	LinkedList* Get_Node_At_index(size_t index)
	{
		LinkedList* ptr = this;
		for (size_t i = 0; i < index; i++) {
			if (!ptr->next)
				throw "INVALID INDEX";
			ptr = ptr->next;
		}
		return ptr;
	}
};

void Test()
{
	LinkedList<int>* llist = new LinkedList(4);
	llist->Push_back(10);
	llist->Push_back(3);
	llist->Push_back(6);
	llist->Push_back(7);
	llist->Push_back(19);
	llist->Push_back(5);

	llist->display();

	std::cout << llist->Pop_back() << '\n';

	llist->display();

	llist->Insert(0, 2);
	llist->Insert(1, 5);

	llist->display();

	llist->Delete(0);
	llist->Delete(2);

	llist->display();

	std::cout << llist->Pop(3) << '\n';

	llist->display();
}

template<typename T>
void UserInput()
{
	puts("Enter the root node value");
	T val = 0;
	size_t index;
	std::cin >> val;
	LinkedList<T>* llist = new LinkedList(val);

	while (true) {
		puts("Select operation:"
			"\n\t1 - insert"
			"\n\t2 - delete"
			"\n\t3 - push back"
			"\n\t4 - pop"
			"\n\t5 - pop back"
			"\n\t6 - display"
			"\n\t* - exit\n");
		switch (getch()) {
			case '1': {
					puts("Enter node value and index");
					std::cin >> val;
					std::cin >> index;
					llist->Insert(index,val);
				} break;
			case '2': {
					puts("Enter index to delete");
					std::cin >> index;
					llist->Delete(index);
				} break;
			case '3': {
					puts("Enter new node value");
					std::cin >> val;
					llist->Push_back(val);
				} break;
			case '4': {
					puts("Enter index to pop");
					std::cin >> index;
					std::cout << "\n\n Value: " << llist->Pop(index);
				} break;
			case '5': std::cout << "\n\n Value: " << llist->Pop_back(); break;
			case '6': llist->display(); break;
			default: return;
		}
		puts("\n\n");
	}
}

int main()
{
	UserInput<int>();
}