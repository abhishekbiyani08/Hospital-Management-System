#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <limits>
#include <bits/stdc++.h>

using namespace std;

// Define a structure for patient information
struct Patient
{
    string name;
    int age;
    char gender;
    float bill;
};

// Function to add a new patient to the system
void addPatient(vector<Patient> &patients)
{
    Patient newPatient;
    cout << "Enter patient's name: ";
    getline(cin, newPatient.name); // To store the entire line as input (spaces too)

    // Input age with error handling
    while(true)
    {
        cout << "Enter patient's age: ";
        if(!(cin >> newPatient.age))
        {
            cout << "Invalid input! Please enter a valid age.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        } 
        else
            break;
    }

    // Input gender with error handling
    while(true)
    {
        cout << "Enter patient's gender (M/F/Other): ";
        cin >> newPatient.gender;
        if(newPatient.gender == 'M' || newPatient.gender == 'F' || newPatient.gender == 'Other')
        {
            break;
        }
        else
        {
            cout << "Invalid input! Please enter 'M' for Male, 'F' for Female, or 'O' for Other.\n";
        }
    }

    cout << "Enter patient's bill: INR ";
    cin >> newPatient.bill;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clears remaining input in buffer
    
    // Add the new patient to the vector
    patients.push_back(newPatient);
    cout << "Patient added successfully!" << endl;
}

// Function to delete a patient from the system
void deletePatient(vector<Patient> &patients)
{
    string name;
    cout << "Enter the name of the patient to delete: ";
    getline(cin, name);
    
    // Iterate through the vector to find the patient by name
    for(auto it = patients.begin(); it != patients.end(); it++)
    {
        if(it->name == name)
        {
            patients.erase(it); // Remove the patient
            cout << "Patient deleted successfully!" << endl;
            return;
        }
    }
    cout << "Patient not found!" << endl;
}

// Function to call an ambulance
void callAmbulance()
{
    static random_device rd;  // Ensures that it is initialized only once, even after multiple function calls
    static mt19937 generator(rd()); // Declares a instance of the Mersenne Twister random number generator
    uniform_int_distribution<long long int> distribution(6000000000LL, 9999999999LL);
    long long int randomNumber = distribution(generator);
    
    cout << "Ambulance called! Please wait for assistance." << endl;
    cout << "Contact the ambulance driver with the following number: " << randomNumber << endl;
}

// Function to display all patients in the system
void displayPatients(const vector<Patient> &patients)
{
    cout << "\nPatients in the system:\n";
    for (const auto &patient : patients)
    {
        cout << "Name: " << patient.name << ", Age: " << patient.age << ", Gender: " << patient.gender << ", Bill: INR " << patient.bill << endl;
    }
}

// Function to find a patient by name
void findPatientByName(const vector<Patient> &patients)
{
    string name;
    cout << "Enter the name of the patient to search: ";
    getline(cin, name);
    
    // Iterate through the vector to find the patient by name
    for(const auto &patient : patients)
    {
        if(patient.name == name)
        {
            cout << "Patient found:\n";
            cout << "Name: " << patient.name << ", Age: " << patient.age << ", Gender: " << patient.gender << ", Bill: INR " << patient.bill << endl;
            return;
        }
    }
    cout << "Patient not found!" << endl;
}

// Function to display pending bills
void displayPendingBills(const vector<Patient> &patients)
{
    cout << "\nPending Bills:\n";
    for(const auto &patient : patients)
    {
        if(patient.bill > 0)
            cout << "Name: " << patient.name << ", Bill: INR " << patient.bill << endl;
    }
}

// Function to display settled bills
void displaySettledBills(const vector<Patient> &patients)
{
    cout << "\nSettled Bills:\n";
    for(const auto &patient : patients)
    {
        if(patient.bill == 0)
            cout << "Name: " << patient.name << ", Bill: INR " << patient.bill << endl;
    }
}

// Function to update patient's bill
void updateBill(vector<Patient> &patients)
{
    string name;
    float newBill;
    cout << "Enter the name of the patient to update bill: ";
    getline(cin, name);

    cout << "Enter the new bill amount: INR ";
    cin >> newBill;

    // Clear input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Iterate through the vector to find the patient by name
    for (auto &patient : patients)
    {
        if (patient.name == name)
        {
            patient.bill = newBill;
            cout << "Bill updated successfully!" << endl;
            return;
        }
    }
    cout << "Patient not found!" << endl;
}

// Function to load patients' details from file
void loadPatientsFromFile(vector<Patient> &patients)
{
    ifstream file("details.txt");
    if(file.is_open())
    {
        Patient patient;
        while(file >> patient.name >> patient.age >> patient.gender >> patient.bill)
        {
            patients.push_back(patient);
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file!" << endl;
    }
}

// Function to save patients' details to file
void savePatientsToFile(const vector<Patient> &patients)
{
    ofstream file("details.txt");
    if(file.is_open())
    {
        for(const auto &patient : patients)
        {
            file << patient.name << " " << patient.age << " " << patient.gender << " " << patient.bill << endl;
        }
        file.close();
        cout << "Patients' details saved to file." << endl;
    }
    else
    {
        cout << "Unable to open file!" << endl;
    }
}

int main()
{
    vector<Patient> patients;
    loadPatientsFromFile(patients); // Load patients' details from file
    
    int choice;
    do
    {
        cout << "\nHospital Management System\n";
        cout << "1. Add Patient\n";
        cout << "2. Delete Patient\n";
        cout << "3. Call Ambulance\n";
        cout << "4. Display Patients\n";
        cout << "5. Find Patient by Name\n";
        cout << "6. Display Pending Bills\n";
        cout << "7. Display Settled Bills\n";
        cout << "8. Update Patient's Bill\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch(choice)
        {
            case 1:
                addPatient(patients);
                break;
            case 2:
                deletePatient(patients);
                break;
            case 3:
                callAmbulance();
                break;
            case 4:
                displayPatients(patients);
                break;
            case 5:
                findPatientByName(patients);
                break;
            case 6:
                displayPendingBills(patients);
                break;
            case 7:
                displaySettledBills(patients);
                break;
            case 8:
                updateBill(patients);
                break;
            case 9:
                savePatientsToFile(patients); // Save patients' details to file before exit
                cout << "Exiting... Thank you!\n" << endl << endl;
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
    while(choice != 9);
    return 0;
}