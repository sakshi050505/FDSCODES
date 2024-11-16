/*
Name : SAKSHI SANDEEP CHAVAN
Roll No : 68
PRN No : F23112081
Class : SE-II(R-Batch)

/*Problem Statement
Second year Computer Engineering class, set A of students like Vanilla ice-cream and
set B of students like Butterscotch ice-cream. Write C++ program to store two sets using Linked List.
Compute and display-
i. Set of students who like both vanilla and butterscotch
ii. Set of students who like either vanilla or butterscotch or not both
iii. Number of students who like neither vanilla nor butterscotch 
*/

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

class LinkedList {
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void insert(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = head;
        head = newNode;
    }

    void display() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    bool contains(int value) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data == value) 
                return true;
            temp = temp->next;
        }
        return false;
    }

    LinkedList intersection(LinkedList& other) {
        LinkedList result;
        Node* temp = head;
        while (temp != nullptr) {
            if (other.contains(temp->data)) {
                result.insert(temp->data);
            }
            temp = temp->next;
        }
        return result;
    }

    LinkedList uni(LinkedList& other) {
        LinkedList result;
        Node* temp = head;
        while (temp != nullptr) {
            result.insert(temp->data);
            temp = temp->next;
        }
        temp = other.head;
        while (temp != nullptr) {
            if (!contains(temp->data)) {
                result.insert(temp->data);
            }
            temp = temp->next;
        }
        return result;
    }

    LinkedList difference(LinkedList& other) {
        LinkedList result;
        Node* temp = head;
        while (temp != nullptr) {
            if (!other.contains(temp->data)) {
                result.insert(temp->data);
            }
            temp = temp->next;
        }
        temp = other.head;
        while (temp != nullptr) {
            if (!contains(temp->data)) {
                result.insert(temp->data);
            }
            temp = temp->next;
        }
        return result;
    }

    int count() {
        int count = 0;
        Node* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }
};

int main() {
    LinkedList vanillaSet, butterscotchSet;
    int totalStudents, choice, studentID;

    cout << "Enter total number of students in the class: ";
    cin >> totalStudents;

    cout << "Enter the number of students who like Vanilla: ";
    int n;
    cin >> n;
    cout << "Enter the IDs of students who like Vanilla:\n";
    for (int i = 0; i < n; i++) {
        cin >> studentID;
        vanillaSet.insert(studentID);
    }

    cout << "Enter the number of students who like Butterscotch: ";
    int m;
    cin >> m;
    cout << "Enter the IDs of students who like Butterscotch:\n";
    for (int i = 0; i < m; i++) {
        cin >> studentID;
        butterscotchSet.insert(studentID);
    }

    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Students who like both Vanilla and Butterscotch\n";
        cout << "2. Students who like either Vanilla or Butterscotch but not both\n";
        cout << "3. Number of students who like neither Vanilla nor Butterscotch\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                LinkedList both = vanillaSet.intersection(butterscotchSet);
                cout << "Students who like both Vanilla and Butterscotch: ";
                both.display();
                break;
            }
            case 2: {
                LinkedList eitherOr = vanillaSet.difference(butterscotchSet);
                cout << "Students who like either Vanilla or Butterscotch but not both: ";
                eitherOr.display();
                break;
            }
            case 3: {
                LinkedList uniSet = vanillaSet.uni(butterscotchSet);
                int neither = totalStudents - uniSet.count();
                cout << "Number of students who like neither Vanilla nor Butterscotch: " << neither << endl;
                break;
            }
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 4);

    return 0;
}
