//============================================================================
// Name        : Topic4Assignment.cpp
// Author      : Dylan Forbord
// Version     :
// Copyright   : Your copyright notice
// Description : Topic 4 Assignment
//============================================================================

#include <iostream>
#include <string>
using namespace std;


class Person {
public:
    string id;
    string name;

    Person(string id, string name) {
        this->id = id;
        this->name = name;
    }

    virtual ~Person() {}
    virtual void printAbout() = 0;
};


class Student : public Person {
public:
    char avgGrade;
    string major;

    Student(string id, string name, char avgGrade, string major)
        : Person(id, name) {
        this->avgGrade = avgGrade;
        this->major = major;
    }

    void printAbout() override {
        cout << "Name: " << name << " ; Id: " << id
             << " ; Major: " << major << " ; Average Grade: " << avgGrade << endl;
    }
};


class Teacher : public Person {
public:
    string title;
    string department;

    Teacher(string id, string name, string title, string department)
        : Person(id, name) {
        this->title = title;
        this->department = department;
    }

    void printAbout() override {
        cout << "Name: " << name << " ; Id: " << id
             << " ; Title: " << title << " ; Department: " << department << endl;
    }
};

// Nodes for linked list
struct Node {
    Person* person;
    Node* next;

    Node(Person* p) {
        person = p;
        next = nullptr;
    }
};


class RecordList {
private:
    Node* head;
public:
    RecordList() { head = nullptr; }

    ~RecordList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp->person;
            delete temp;
        }
    }

    bool idExists(string id) {
        Node* temp = head;
        while (temp) {
            if (temp->person->id == id) return true;
            temp = temp->next;
        }
        return false;
    }

    void addStudent() {
        string id, name, major;
        char avgGrade;

        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Id number: ";
        cin >> id;

        if (idExists(id)) {
            cout << "This Id number already exists." << endl;
            return;
        }

        cout << "Enter average grade of Student: ";
        cin >> avgGrade;
        cin.ignore();

        cout << "Enter major of Student: ";
        getline(cin, major);

        Node* newNode = new Node(new Student(id, name, avgGrade, major));
        newNode->next = head;
        head = newNode;
    }

    void addTeacher() {
        string id, name, department, title;
        int choice;

        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Id number: ";
        cin >> id;

        if (idExists(id)) {
            cout << "This Id number already exists." << endl;
            return;
        }

        cout << "Enter title of Teacher: 1 if Lecturer ; 2 if Assistant Professor ; 3 if Associate Professor: ";
        cin >> choice;

        if (choice == 1) title = "Lecturer";
        else if (choice == 2) title = "Assistant Professor";
        else if (choice == 3) title = "Associate Professor";
        else {
            cout << "Invalid title option. Returning to menu." << endl;
            return;
        }

        cin.ignore();
        cout << "Enter teacher department: ";
        getline(cin, department);

        Node* newNode = new Node(new Teacher(id, name, title, department));
        newNode->next = head;
        head = newNode;
    }

    void displayRecords() {
        if (!head) {
            cout << "No records available." << endl;
            return;
        }
        Node* temp = head;
        while (temp) {
            temp->person->printAbout();
            temp = temp->next;
        }
    }
};

int main() {
    RecordList records;
    int choice;

    do {
        cout << "\n\t\tWelcome to RU Record Management System\n";
        cout << "\tPress\n";
        cout << "\t1 to create a new Student Record\n";
        cout << "\t2 to create a new Teacher record\n";
        cout << "\t3 to view all records\n";
        cout << "\t4 to Exit\n";
        cout << "Enter your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                records.addStudent();
                break;
            case 2:
                records.addTeacher();
                break;
            case 3:
                records.displayRecords();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
