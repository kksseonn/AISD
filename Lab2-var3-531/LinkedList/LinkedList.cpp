#pragma once
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <random>


template <typename T>
struct Node {
    T coefficient;
    int exponent;
    Node* next;

    Node(const T& coeff, int exp = 0) : coefficient(coeff), exponent(exp), next(nullptr) {}
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
            push_tail(otherCurrent->coefficient, otherCurrent->exponent);

            if (otherCurrent->next == other.head) {
                break;
            }

            otherCurrent = otherCurrent->next;
        }
    }

    LinkedList(int size) {
        head = nullptr;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<T> distribution(0, 20);

        for (int i = 0; i < size; ++i) {
            push_tail(distribution(gen), distribution(gen));
        }
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();

            Node<T>* otherCurrent = other.head;

            while (otherCurrent != nullptr) {
                push_tail(otherCurrent->coefficient, otherCurrent->exponent);
                otherCurrent = otherCurrent->next;

                if (otherCurrent == other.head) {
                    break;
                }
            }
        }

        return *this;
    }

    void push_tail(const T& coefficient, int exponent) {
        Node<T>* newNode = new Node<T>(coefficient, exponent);

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
            throw std::out_of_range("push_tail: List is empty");
        }

        Node<T>* otherCurrent = otherList.head;

        do {
            push_tail(otherCurrent->coefficient, otherCurrent->exponent);
            otherCurrent = otherCurrent->next;
        } while (otherCurrent != otherList.head);
    }

    void push_head(const T& coefficient, int exponent) {
        Node<T>* newNode = new Node<T>(coefficient, exponent);

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
            throw std::out_of_range("push_head: List is empty");
        }

        Node<T>* otherCurrent = otherList.head;
        Node<T>* lastAdded = nullptr;

        do {
            Node<T>* newNode = new Node<T>(otherCurrent->coefficient, otherCurrent->exponent);
            newNode->next = lastAdded;
            lastAdded = newNode;

            otherCurrent = otherCurrent->next;
        } while (otherCurrent != otherList.head);

        Node<T>* current = lastAdded;
        do {
            push_head(current->coefficient, current->exponent);
            current = current->next;
        } while (current != nullptr);
    }

    void pop_head() {
        if (head == nullptr) {
            throw std::out_of_range("pop_head: List is empty");
        }

        Node<T>* temp = head;
        Node<T>* current = head;

        while (current->next != head) {
            current = current->next;
        }

        if (head->next == head) {
            delete head;
            head = nullptr;
        }
        else {
            head = head->next;
            current->next = head;
            delete temp;
        }
    }

    void pop_tail() {
        if (head == nullptr) {
            throw std::out_of_range("pop_tail: List is empty");
        }

        Node<T>* current = head;
        Node<T>* previous = nullptr;

        while (current->next != head) {
            previous = current;
            current = current->next;
        }

        if (previous == nullptr) {
            delete head;
            head = nullptr;
        }
        else {
            previous->next = head;
            delete current;
        }
    }

    void delete_node(const T& value, int exponent) {
        if (head == nullptr) {
            return;
        }

        Node<T>* current = head;
        Node<T>* previous = nullptr;

        while (current != nullptr) {
            if (current->coefficient == value && current->exponent == exponent) {
                if (previous == nullptr) {
                    Node<T>* temp = current;
                    current = current->next;
                    head = current;
                    delete temp;
                }
                else {
                    previous->next = current->next;
                    Node<T>* temp = current;
                    current = current->next;
                    delete temp;
                }
            }
            else {
                previous = current;
                current = current->next;
            }

            if (current == head) {
                break;
            }
        }
    }

    const Node<T>& operator[](int index) const {
        if (head == nullptr || index < 0) {
            throw std::out_of_range("Index out of range");
        }

        Node<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
            if (current == head) {
                throw std::out_of_range("Index out of range");
            }
        }

        return *current;
    }

    Node<T>& operator[](int index) {
        if (head == nullptr || index < 0) {
            throw std::out_of_range("Index out of range");
        }

        Node<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
            if (current == head) {
                throw std::out_of_range("Index out of range");
            }
        }

        return *current;
    }

    void printList() const {
        if (head == nullptr) {
            std::cout << "Polynomial is empty" << std::endl;
        }
        else {
            Node<T>* current = head;
            do {
                std::cout << current->coefficient << "x^" << current->exponent;

                if (current->next != head) {
                    std::cout << " + ";
                }

                current = current->next;
            } while (current != head);

            std::cout << " = f" << std::endl << std::endl;
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

    const Node<T>* getHead() const {
        return head;
    }

    bool empty() const {
        return head == nullptr;
    }
};

template <typename T>
T evaluate(const LinkedList<T>& list, T x) {
    if (list.empty()) {
        throw std::out_of_range("evaluate: Polynomial is empty");
    }

    double result = 0;
    const Node<T>* current = list.getHead();

    do {
        result += current->coefficient * std::pow(x, current->exponent);
        current = current->next;
    } while (current != list.getHead());

    return static_cast<T>(result);
}


int main() {
    try {
        LinkedList<int> randomList(5);
        std::cout << "List with random values:" << std::endl;
        randomList.printList();

        LinkedList<int> assignedList;
        assignedList = randomList;
        std::cout << "List assigned from randomList:" << std::endl;
        assignedList.printList();

        LinkedList<int> list1;
        list1.push_tail(2, 3); 
        list1.push_tail(5, 2);  
        list1.push_tail(1, 0); 
        std::cout << "List 1:" << std::endl;
        list1.printList();

        LinkedList<int> list2;
        list2.push_tail(4, 3);
        list2.push_tail(2, 2);
        std::cout << "List 2:" << std::endl;
        list2.printList();

        list1.push_tail(list2);
        std::cout << "List 1 after push_tail list2:" << std::endl;
        list1.printList();

        list1.push_head(1, 1);
        std::cout << "List 1 after push_head:" << std::endl;
        list1.printList();

        list1.push_head(list2);
        std::cout << "List 1 after push_head with list2:" << std::endl;
        list1.printList();

        std::cout << "List 1 after pop_head:" << std::endl;
        list1.pop_head();
        list1.printList();

        std::cout << "List 1 after pop_tail:" << std::endl;
        list1.pop_tail();
        list1.printList();

        std::cout << "List 1 after deleting node with 2x^3:" << std::endl;
        list1.delete_node(2, 3);
        list1.printList();

        std::cout << "Polynom at index 0 in List 1: " << std::endl;
        const Node<int>& term = list1[0];
        std::cout << term.coefficient << "x^" << term.exponent << std::endl << std::endl;

        
        std::cout << "List 1 after modifying term at index 1:" << std::endl;
        list1[1].coefficient = 6;
        list1[1].exponent = 6;
        list1.printList();

        std::cout << "Evaluating the polynomial at x = 2: f = " << evaluate(list1, 2) << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}