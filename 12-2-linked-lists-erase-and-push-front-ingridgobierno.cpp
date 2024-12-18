#include <iostream>
using namespace std;

class List {

private:
    struct Node {
        int value;
        Node* next;
        Node* prev;
        Node(int val) : value(val), next(nullptr), prev(nullptr) {}
    };

    Node* first = nullptr;
    Node* last = nullptr;
    unsigned int num_elems = 0;

public:
    List() {
        first = nullptr;
        last = nullptr;
        num_elems = 0;
    }
    ~List() {
        while (first != nullptr) {
            Node* temp = first;
            first = first->next;
            delete temp;
        }
    }

    void push_back(const int& value) {
        Node* newNode = new Node(value);
        if (last == nullptr) {
            first = last = newNode;
        }
        else {
            last->next = newNode;
            newNode->prev = last;
            last = newNode;
        }
        num_elems++;
    }

    void push_front(const int& value) {
        Node* newNode = new Node(value);
        if (first == nullptr) {
            first = last = newNode;
        }
        else {
            newNode->next = first;
            first->prev = newNode;
            first = newNode;
        }
        num_elems++;
    }


    void insert(unsigned int position, const int& value) {
        if (position == 0) {
            Node* newNode = new Node(value);
            if (first == nullptr) {
                first = last = newNode;
            }
            else {
                newNode->next = first;
                first->prev = newNode;
                first = newNode;
            }
            num_elems++;
        }
        else if (position >= num_elems) {
            push_back(value);
        }
        else {
            Node* current = first;
            unsigned int index = 0;
            while (index < position) {
                current = current->next;
                index++;
            }
            Node* newNode = new Node(value);
            newNode->next = current;
            newNode->prev = current->prev;
            if (current->prev != nullptr) {
                current->prev->next = newNode;
            }
            current->prev = newNode;
            num_elems++;
        }
    }

    void erase(unsigned int position) {
        if (position >= num_elems) {
            return; 
        }

        Node* current = first;
        unsigned int index = 0;

        while (index < position) {
            current = current->next;
            index++;
        }

        if (current == first) {
            first = current->next;
            if (first != nullptr) {
                first->prev = nullptr;
            }
            else {
                last = nullptr; 
            }
        }
        else if (current == last) {
            last = current->prev;
            if (last != nullptr) {
                last->next = nullptr;
            }
        }
        else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }

        delete current;
        num_elems--;
    }

    void print() const {
        Node* current = first;
        while (current != nullptr) {
            std::cout << current->value << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void recursivePrint(Node* current) const {
        if (current == nullptr) return;
        cout << current->value << " ";
        recursivePrint(current->next);
    }

    void recursivePrint() const {
        recursivePrint(first);
        cout << endl;
    }

};


int main() {
    List myList;
    myList.push_back(0);
    myList.print();
    myList.insert(1, 1);
    myList.print();
    myList.insert(2, 2);
    myList.print();
    myList.insert(3, 3);
    myList.print();
   
    cout << "After push_front:" << endl;
    myList.push_front(-1);
    myList.print();

    cout << "After erase:" << endl;
    myList.erase(0); 
    myList.print();
    myList.erase(0); 
    myList.print();
    myList.erase(0); 
    myList.print();
    myList.erase(0); 
    myList.print();

    cout << "Recursive print:" << endl;
    myList.recursivePrint();

    return 0;
}

