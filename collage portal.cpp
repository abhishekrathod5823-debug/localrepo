#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

// --- Screen Clear Function ---
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// --- Pause Function ---
void pressEnterToContinue() {
    cout << "\nOperation completed. Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get(); 
    clearScreen();
}

struct Student {
    string name;
    int enrollNo;
    string phone;
    string department;
    int marks = 0; 
};

struct Faculty {
    string name;
    int id;
    string phone;
    string department;
    string password;
};

vector<Student> students;
vector<Faculty> faculties;

int findStudentIndex(int enroll) {
    for (int i = 0; i < (int)students.size(); i++) {
        if (students[i].enrollNo == enroll) return i;
    }
    return -1;
}

// --- FACULTY LOGIN & MARKS ENTRY ---
void loginFaculty() {
    int id;
    string pass;
    clearScreen();
    cout << "--- Faculty Login ---\n";
    cout << "Enter ID: "; cin >> id;
    cout << "Enter Password: "; cin >> pass;

    bool loginSuccess = false;
    for (auto &f : faculties) {
        if (f.id == id && f.password == pass) {
            loginSuccess = true;
            clearScreen();
            cout << "Welcome, Prof. " << f.name << "!\n";
            cout << "1. Enter Student Marks\n2. Logout\nChoice: ";
            int subChoice; cin >> subChoice;

            if (subChoice == 1) {
                int sEnroll, sMark;
                cout << "Enter Student Enroll No: "; cin >> sEnroll;
                int idx = findStudentIndex(sEnroll);
                if (idx != -1) {
                    cout << "Enter Marks for " << students[idx].name << ": "; cin >> sMark;
                    students[idx].marks = sMark;
                    cout << "Marks updated successfully!\n";
                } else cout << "Student not found!\n";
            }
            break; 
        }
    }
    if (!loginSuccess) cout << "Invalid ID or Password!\n";
    pressEnterToContinue();
}

// --- TEACHER MENU ---
void teacherMenu() {
    int choice;
    while (true) {
        clearScreen();
        cout << "--- Teacher/Admin Portal ---\n";
        cout << "1. Add New Student\n2. Add New Faculty (Create Account)\n3. Login Faculty (Enter Marks)\n4. Show All Students\n5. Back to Main Menu\nEnter Choice: ";
        cin >> choice;

        if (choice == 1) {
            Student s;
            cout << "Name: "; cin.ignore(); getline(cin, s.name);
            cout << "Enroll No: "; cin >> s.enrollNo;
            cout << "Phone: "; cin >> s.phone;
            cout << "Dept: "; cin >> s.department;
            students.push_back(s);
            pressEnterToContinue();
        } 
        else if (choice == 2) {
            Faculty f;
            cout << "Faculty Name: "; cin.ignore(); getline(cin, f.name);
            cout << "Faculty ID (Numeric): "; cin >> f.id;
            cout << "Phone: "; cin >> f.phone;
            cout << "Department: "; cin >> f.department;
            cout << "Set Password: "; cin >> f.password;
            faculties.push_back(f);
            cout << "Faculty Account Created Successfully!\n";
            pressEnterToContinue();
        }
        else if (choice == 3) {
            loginFaculty();
        }
        else if (choice == 4) {
            clearScreen();
            cout << left << setw(10) << "Enroll" << setw(20) << "Name" << setw(15) << "Dept" << "Marks" << endl;
            cout << "------------------------------------------------------------\n";
            for (const auto &s : students) 
                cout << left << setw(10) << s.enrollNo << setw(20) << s.name << setw(15) << s.department << s.marks << endl;
            pressEnterToContinue();
        }
        else break;
    }
}

// --- STUDENT MENU ---
void studentMenu() {
    int id;
    clearScreen();
    cout << "--- Student Access ---\nEnter Enroll No: "; cin >> id;
    int idx = findStudentIndex(id);
    
    if (idx == -1) {
        cout << "Enrollment number not registered.\n";
        pressEnterToContinue();
        return;
    }

    int choice;
    while (true) {
        clearScreen();
        cout << "Welcome " << students[idx].name << "\n1. View Subjects\n2. View My Marks\n3. Logout\nChoice: ";
        cin >> choice;
        
        if (choice == 1) {
            clearScreen();
            cout << "--- All Subjects Detail ---\n\n";
            cout << left << setw(7) << "Sr No" << setw(15) << "Course Code" << setw(45) << "Course Name" << "Practical Batch" << endl;
            cout << "------------------------------------------------------------------------------------------\n";
            cout << left << setw(7) << "1" << setw(15) << "102000216" << setw(45) << "Linear Algebra Vector Calculus and ODE" << "1A11" << endl;
            cout << left << setw(7) << "2" << setw(15) << "102001216" << setw(45) << "Quantum Mechanics and Semiconductors" << "1A11" << endl;
            cout << left << setw(7) << "3" << setw(15) << "102001218" << setw(45) << "Engineering Visualization" << "1A11" << endl;
            cout << left << setw(7) << "4" << setw(15) << "102001220" << setw(45) << "Indian Constitution" << "1A11" << endl;
            cout << left << setw(7) << "5" << setw(15) << "102001221" << setw(45) << "Introduction to Physical Education" << "1A11" << endl;
            cout << left << setw(7) << "6" << setw(15) << "102001226" << setw(45) << "Object Oriented Programming with C++" << "1A11" << endl;
            cout << left << setw(7) << "7" << setw(15) << "102040201" << setw(45) << "Basics of Web Designing" << "1A11" << endl;
            pressEnterToContinue();
        } else if (choice == 2) {
            cout << "\nStudent Name: " << students[idx].name << endl;
            cout << "Current Marks: " << students[idx].marks << endl;
            pressEnterToContinue();
        } else break;
    }
}

int main() {
    int mainChoice;
    string adminPass;

    while (true) {
        clearScreen();
        cout << "====================================\n";
        cout << "   SMART PORTAL FOR A.R. COLLEGE\n";
        cout << "====================================\n";
        cout << "1. Teacher/Admin Login\n2. Student Login\n3. Exit\nSelection: ";
        cin >> mainChoice;
        
        if (mainChoice == 1) {
            cout << "Enter Admin Password: ";
            cin >> adminPass;
            if (adminPass == "admin123") {
                teacherMenu();
            } else {
                cout << "Incorrect Password! Access Denied.\n";
                pressEnterToContinue();
            }
        }
        else if (mainChoice == 2) studentMenu();
        else if (mainChoice == 3) break;
    }
    return 0;
}