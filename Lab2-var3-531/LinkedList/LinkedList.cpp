#pragma once
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <random>
#include <cstdlib>

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
        head = nullptr;
        Node<T>* otherCurrent = other.head;

        while (otherCurrent != nullptr) {
            push_tail(otherCurrent->data);
            otherCurrent = otherCurrent->next;
            if (otherCurrent->next == other.head) {
                break;
            }
        }
    }

    LinkedList(int size) {
        head = nullptr;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<T> distribution(0, 99);

        for (int i = 0; i < size; ++i) {
            push_tail(distribution(gen));
        }
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            Node<T>* otherCurrent = other.head;

            while (otherCurrent != nullptr) {
                push_tail(otherCurrent->data);
                otherCurrent = otherCurrent->next;
                if (otherCurrent->next == other.head) {
                    break;
                }
            }
        }

        return *this;
    }

    void push_tail(const T& value) {
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

    void push_tail(const LinkedList& otherList) {
        if (otherList.head == nullptr) {
            return;
        }

        Node<T>* otherCurrent = otherList.head;

        do {
            push_tail(otherCurrent->data);
            otherCurrent = otherCurrent->next;
        } while (otherCurrent != otherList.head);
    }

    void push_head(const T& value) {
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
            newNode->next = head;
            head = newNode;
            current->next = head;
        }
    }

    void push_head(const LinkedList& otherList) {
        if (otherList.head == nullptr) {
            return;
        }

        Node<T>* otherCurrent = otherList.head;
        Node<T>* lastAdded = nullptr;

        do {
            Node<T>* newNode = new Node<T>(otherCurrent->data);
            newNode->next = lastAdded;
            lastAdded = newNode;

            otherCurrent = otherCurrent->next;
        } while (otherCurrent != otherList.head);

        Node<T>* current = lastAdded;
        do {
            push_head(current->data);
            current = current->next;
        } while (current != nullptr);
    }

    void printList() const {
        if (head == nullptr) {
            std::cout << "List is empty" << std::endl;
        }
        else {
            Node<T>* current = head;
            do {
                std::cout << current->data << " ";
                current = current->next;
            } while (current != head);
            std::cout << std::endl;
        }
    }

    void clear() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        head = nullptr;
    }
};

int main() {
    try {
        LinkedList<int> list1;
        list1.push_tail(1);
        list1.push_tail(2);
        list1.push_tail(3);

        std::cout << "List 1:" << std::endl;
        list1.printList();

        LinkedList<int> list2;
        list2.push_tail(4);
        list2.push_tail(5);

        std::cout << "List 2:" << std::endl;
        list2.printList();

        list1.push_tail(list2);

        std::cout << "List 1 after push_tail list2:" << std::endl;
        list1.printList();

        list1.push_head(0);  
        std::cout << "List 1 after push_head 0:" << std::endl;
        list1.printList();

        list1.push_head(list2);  
        std::cout << "List 1 after push_head with list2:" << std::endl;
        list1.printList();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}