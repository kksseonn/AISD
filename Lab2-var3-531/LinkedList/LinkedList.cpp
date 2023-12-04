#pragma once
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <random>


template <typename T>
struct Term {
    T coefficient;
    int exponent;

    Term(const T& coeff, int exp = 0) : coefficient(coeff), exponent(exp) {}
};

template <typename T>
struct Node {
    Term<T> data;
    Node* next;

    Node(const T& coeff, int exp = 0) : data(coeff, exp), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;

public:
    LinkedList() : head(nullptr) {}

    LinkedList(const LinkedList& other) : head(nullptr) {
        Node<T>* current = other.head;

        while (current != nullptr) {
            push_tail(current->data.coefficient, current->data.exponent);

            if (current->next == other.head) {
                break;
            }

            current = current->next;
        }
    }

    LinkedList(int size) : head(nullptr) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<T> distribution(0, 20);

        for (int i = 0; i < size; ++i) {
            push_tail(distribution(gen), distribution(gen));
        }
    }

    ~LinkedList() {
        if (head != nullptr) {
            Node<T>* current = head->next;
            while (current != head) {
                Node<T>* temp = current;
                current = current->next;
                delete temp;
            }
            delete head; 
        }
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {

            Node<T>* otherCurrent = other.head;

            while (otherCurrent != nullptr) {
                push_tail(otherCurrent->data.coefficient, otherCurrent->data.exponent);

                if (otherCurrent->next == other.head) {
                    break;
                }

                otherCurrent = otherCurrent->next;
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
            push_tail(otherCurrent->data.coefficient, otherCurrent->data.exponent);
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
            Node<T>* newNode = new Node<T>(otherCurrent->data.coefficient, otherCurrent->data.exponent);
            newNode->next = lastAdded;
            lastAdded = newNode;

            otherCurrent = otherCurrent->next;
        } while (otherCurrent != otherList.head);

        Node<T>* current = lastAdded;
        do {
            push_head(current->data.coefficient, current->data.exponent);
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
            throw std::out_of_range("delete_node: List is empty");
        }

        Node<T>* current = head;
        Node<T>* previous = nullptr;

        do {
            if (current->data.exponent == exponent && current->data.coefficient == value) {
                if (previous == nullptr) {
                    pop_head();
                    return;
                }
                else {
                    previous->next = current->next;
                    delete current;
                    return;
                }
            }

            previous = current;
            current = current->next;
        } while (current != head);

        throw std::out_of_range("delete_node: Node not found");
    }

    const Term<T>& operator[](int index) const {
        if (index < 0) {
            throw std::out_of_range("operator[]: Index must be non-negative");
        }

        if (head == nullptr) {
            throw std::out_of_range("operator[]: List is empty");
        }

        const Node<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
            if (current == head) {
                throw std::out_of_range("operator[]: Index out of range");
            }
        }

        return current->data;
    }

    Term<T>& operator[](int index) {
        if (index < 0) {
            throw std::out_of_range("operator[]: Index must be non-negative");
        }

        if (head == nullptr) {
            throw std::out_of_range("operator[]: List is empty");
        }

        Node<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
            if (current == head) {
                throw std::out_of_range("operator[]: Index out of range");
            }
        }

        return current->data;
    }

    void printList() const {
        if (head == nullptr) {
            std::cout << "Polynomial is empty" << std::endl;
        }
        else {
            const Node<T>* current = head;
            do {
                std::cout << current->data.coefficient << "x^" << current->data.exponent;

                if (current->next != head) {
                    std::cout << " + ";
                }

                current = current->next;
            } while (current != head);

            std::cout << " = f" << std::endl << std::endl;
        }
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
        result += current->data.coefficient * std::pow(x, current->data.exponent);
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
        const auto& term = list1[0];
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