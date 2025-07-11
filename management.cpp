#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

struct Patient {
    int id;
    string name;
    int age;
    string gender;
    string diagnosis;
};

void addPatient();
void viewPatients();
void deletePatient();

int main() {
    int choice;
    do {
        cout << "\n=== Hospital Management System ===\n";
        cout << "1. Add Patient\n";
        cout << "2. View Patients\n";
        cout << "3. Delete Patient\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: deletePatient(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
void addPatient() {
    Patient p;
    cout << "\nEnter Patient ID: ";
    cin >> p.id;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, p.name);
    cout << "Enter Age: ";
    cin >> p.age;
    cin.ignore();
    cout << "Enter Gender: ";
    getline(cin, p.gender);
    cout << "Enter Diagnosis: ";
    getline(cin, p.diagnosis);

    ofstream file("patients.dat", ios::binary | ios::app);
    file.write(reinterpret_cast<char*>(&p), sizeof(Patient));
    file.close();

    cout << "Patient added successfully.\n";
}
void viewPatients() {
    Patient p;
    ifstream file("patients.dat", ios::binary);
    if (!file) {
        cout << "No records found.\n";
        return;
    }

    cout << "\n--- Patient Records ---\n";
    while (file.read(reinterpret_cast<char*>(&p), sizeof(Patient))) {
        cout << "ID: " << p.id << "\n";
        cout << "Name: " << p.name << "\n";
        cout << "Age: " << p.age << "\n";
        cout << "Gender: " << p.gender << "\n";
        cout << "Diagnosis: " << p.diagnosis << "\n";
        cout << "-----------------------\n";
    }
    file.close();
}
void deletePatient() {
    int id;
    cout << "\nEnter Patient ID to delete: ";
    cin >> id;

    ifstream inFile("patients.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);

    Patient p;
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&p), sizeof(Patient))) {
        if (p.id != id) {
            outFile.write(reinterpret_cast<char*>(&p), sizeof(Patient));
        } else {
            found = true;
        }
    }

    inFile.close();
    outFile.close();

    remove("patients.dat");
    rename("temp.dat", "patients.dat");

    if (found)
        cout << "Patient record deleted.\n";
    else
        cout << "Patient ID not found.\n";
}




