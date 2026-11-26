#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <limits>
using namespace std;

// Abstract Base Class
class Person {
protected:
    string name;
    int age;

public:
    Person() : name("Unknown"), age(0) {}

    Person(const string& n, int a) : name(n), age(a) {}

    string getName() const { return name; }
    int getAge() const { return age; }

    virtual void display() const = 0;

    virtual ~Person() {}
};

// Student Class
class Student : public Person {
private:
    int rollNo;
    float marks;

public:
    // Default Constructor
    Student() : Person(), rollNo(0), marks(0.0f) {}

    // Parameterized Constructor
    Student(const string& n, int a, int r, float m)
        : Person(n, a), rollNo(r), marks(m) {}

    // Function Overloading
    void setDetails(const string& n, int a, int r) {
        name = n;
        age = a;
        rollNo = r;
    }

    void setDetails(const string& n, int a, int r, float m) {
        name = n;
        age = a;
        rollNo = r;
        marks = m;
    }

    int getRollNo() const {
        return rollNo;
    }

    float getMarks() const {
        return marks;
    }

    // Operator Overloading
    bool operator>(const Student& s) const {
        return marks > s.marks;
    }

    // Runtime Polymorphism
    void display() const override {
        cout << left << setw(15) << name
             << setw(10) << age
             << setw(12) << rollNo
             << setw(10) << fixed << setprecision(2) << marks << endl;
    }

    string getGrade() const {
        if (marks >= 90) return "A+";
        if (marks >= 80) return "A";
        if (marks >= 70) return "B";
        if (marks >= 60) return "C";
        if (marks >= 40) return "D";
        return "F";
    }
};

// Function Template
template <typename T>
T findMaximum(T a, T b) {
    return (a > b) ? a : b;
}

// Student Management Class
class StudentManagement {
private:
    vector<Student> students;

public:
    // Add Student
    void addStudent() {
        string name;
        int age = 0, rollNo = 0;
        float marks = 0.0f;

        cout << "\nEnter Name: ";
        getline(cin >> ws, name);

        cout << "Enter Age: ";
        if (!(cin >> age)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("Please enter valid numeric values!");
        }

        cout << "Enter Roll Number: ";
        if (!(cin >> rollNo)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("Please enter valid numeric values!");
        }

        cout << "Enter Marks: ";
        if (!(cin >> marks)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("Please enter valid numeric values!");
        }

        if (age <= 0 || rollNo <= 0 || marks < 0 || marks > 100) {
            throw invalid_argument("Invalid student details!");
        }

        for (const auto& s : students) {
            if (s.getRollNo() == rollNo) {
                throw runtime_error("Roll number already exists!");
            }
        }

        students.emplace_back(name, age, rollNo, marks);
        cout << "\nStudent added successfully!\n";
    }

    // Display Students
    void displayStudents() const {
        if (students.empty()) {
            cout << "\nNo student records found.\n";
            return;
        }

        cout << "\n";
        cout << left << setw(15) << "Name"
             << setw(10) << "Age"
             << setw(12) << "Roll No"
             << setw(10) << "Marks" << endl;

        cout << string(47, '-') << endl;

        for (const auto& s : students) {
            s.display();
        }
    }

    // Search Student
    void searchStudent() const {
        int rollNo = 0;

        cout << "\nEnter Roll Number to Search: ";
        if (!(cin >> rollNo)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid roll number!\n";
            return;
        }

        auto it = find_if(
            students.begin(),
            students.end(),
            [rollNo](const Student& s) {
                return s.getRollNo() == rollNo;
            }
        );

        if (it != students.end()) {
            cout << "\nStudent Found:\n";
            it->display();
            cout << "Grade: " << it->getGrade() << endl;
        } else {
            cout << "\nStudent not found!\n";
        }
    }

    // Sort Students
    void sortStudents() {
        sort(
            students.begin(),
            students.end(),
            [](const Student& a, const Student& b) {
                return a.getMarks() > b.getMarks();
            }
        );

        cout << "\nStudents sorted by marks!\n";
    }

    // Display Topper
    void displayTopper() const {
        if (students.empty()) {
            cout << "\nNo student records available.\n";
            return;
        }

        auto topper = max_element(
            students.begin(),
            students.end(),
            [](const Student& a, const Student& b) {
                return a.getMarks() < b.getMarks();
            }
        );

        cout << "\nTopper Details:\n";
        topper->display();
    }

    // Save Records to File
    void saveToFile() const {
        ofstream file("students.txt");

        if (!file) {
            throw runtime_error("Unable to open file!");
        }

        file << "Name,Age,RollNo,Marks\n";

        for (const auto& s : students) {
            file << s.getName() << ","
                 << s.getAge() << ","
                 << s.getRollNo() << ","
                 << s.getMarks() << "\n";
        }

        file.close();

        cout << "\nRecords saved successfully!\n";
    }

    // Total Students
    void totalStudents() const {
        cout << "\nTotal Students: "
             << students.size() << endl;
    }
};

// Main Function
int main() {
    StudentManagement manager;
    int choice = -1;

    do {
        cout << "STUDENT MANAGEMENT SYSTEM\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Sort Students by Marks\n";
        cout << "5. Display Topper\n";
        cout << "6. Total Students\n";
        cout << "7. Save Records to File\n";
        cout << "0. Exit\n";

        cout << "\nEnter Your Choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nPlease enter a valid menu choice!\n";
            continue;
        }

        try {
            switch (choice) {
                case 1:
                    manager.addStudent();
                    break;
                case 2:
                    manager.displayStudents();
                    break;
                case 3:
                    manager.searchStudent();
                    break;
                case 4:
                    manager.sortStudents();
                    break;
                case 5:
                    manager.displayTopper();
                    break;
                case 6:
                    manager.totalStudents();
                    break;
                case 7:
                    manager.saveToFile();
                    break;
                case 0:
                    cout << "\nThank you for using the system!\n";
                    break;
                default:
                    cout << "\nInvalid choice! Try again.\n";
            }
        }
        catch (const exception& e) {
            cout << "\nError: " << e.what() << endl;
        }

    } while (choice != 0);

    return 0;
}