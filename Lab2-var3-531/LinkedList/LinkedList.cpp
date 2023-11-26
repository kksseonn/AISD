#pragma once
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <random>
#include <cstdlib>

using namespace std;

template <typename T>
struct Node {
    T data;
    Node* next;

    Node(const T& newData) : data(newData), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;

public:
    LinkedList() : head(nullptr) {}

    LinkedList(const LinkedList& other) {
        if (other.head == nullptr) {
            head = nullptr;
        }
        else {
            head = new Node<T>(other.head->data);
            if (head == nullptr) {
                throw bad_alloc(); 
            }

            Node<T>* current = head;
            Node<T>* otherCurrent = other.head->next;

            while (otherCurrent != nullptr) {
                current->next = new Node<T>(otherCurrent->data);
                if (current->next == nullptr) {
                    clear();
                    throw bad_alloc();
                }
                current = current->next;
                otherCurrent = otherCurrent->next;
            }
        }
    }

    LinkedList(int size) {
        head = nullptr;
        for (int i = 0; i < size; ++i) {
            pushBack(rand() % 100);
        }
    }

    ~LinkedList() {
        clear();
    }

    void pushBack(const T& value) {
        Node<T>* newNode = new Node<T>(value);

        if (head == nullptr) {
            head = newNode;
            newNode->next = head;
        }
        else {
            Node<T>* current = head;
            while (current->next != head) {
                current = current->next;
            }
            current->next = newNode;
            newNode->next = head;
        }
    }

    void printList() const {
        if (head == nullptr) {
            cout << "List is empty" << endl;
        }
        else {
            Node<T>* current = head;
            do {
                cout << current->data << " ";
                current = current->next;
            } while (current != head);
            cout << endl;
        }
    }

    void clear() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    try {
        LinkedList<int> list1;
        list1.pushBack(1);
        list1.pushBack(2);
        list1.pushBack(3);

        cout << "List 1: "<< endl;
        list1.printList();

        LinkedList<int> list2(list1);
        cout << "List 2 (copy List 1): " << endl;
        list2.printList();

        LinkedList<int> list3(5);
        cout << "List 3 (random value): " << endl;
        list3.printList();
    }
    catch (const std::exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}