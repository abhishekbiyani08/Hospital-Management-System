#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <limits>
#include <map>

using namespace std;

// Patient class to hold patient information
class Patient
{
public:
    string name;
    int age;
    char gender;
    float bill;

    // Constructor to initialize patient details
    Patient(string n, int a, char g, float b) : name(n), age(a), gender(g), bill(b) {}
};

// HospitalManagement class to manage all hospital-related operations
class HospitalManagement
{
private:
    vector<Patient> patients;
    map<string, int> patientIndexMap; // Map to store patient names and their indices

    // Helper function to update the patient index map
    void updatePatientIndexMap()
    {
        patientIndexMap.clear();
        for (size_t i = 0; i < patients.size(); ++i)
        {
            patientIndexMap[patients[i].name] = i;
        }
    }

public:
    // Function to add a new patient
    void addPatient()
    {
        string name;
        int age;
        char gender;
        float bill;

        cout << "Enter patient's name: ";
        getline(cin, name);

        // Age input with error handling
        while (true)
        {
            cout << "Enter patient's age: ";
            if (!(cin >> age))
            {
                cout << "Invalid input! Please enter a valid age.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else
                break;
        }

        // Gender input with error handling
        while (true)
        {
            cout << "Enter patient's gender (M/F/O): ";
            cin >> gender;
            if (gender == 'M' || gender == 'F' || gender == 'O')
            {
                break;
            }
            else
            {
                cout << "Invalid input! Please enter 'M' for Male, 'F' for Female, or 'O' for Other.\n";
            }
        }

        // Bill input with error handling
        while (true)
        {
            cout << "Enter patient's bill: INR ";
            if (!(cin >> bill) || bill < 0)
            {
                cout << "Invalid input! Please enter a positive bill amount.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else
                break;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        patients.push_back(Patient(name, age, gender, bill));
        updatePatientIndexMap(); // Update the map with the new patient
        cout << "Patient added successfully!" << endl;
    }

    // Function to delete a patient
    void deletePatient()
    {
        string name;
        cout << "Enter the name of the patient to delete: ";
        getline(cin, name);

        auto it = patientIndexMap.find(name);
        if (it != patientIndexMap.end())
        {
            int index = it->second;
            patients.erase(patients.begin() + index);
            updatePatientIndexMap(); // Update the map after deletion
            cout << "Patient deleted successfully!" << endl;
        }
        else
        {
            cout << "Patient not found!" << endl;
        }
    }

    // Function to call an ambulance
    void callAmbulance()
    {
        static random_device rd;
        static mt19937 generator(rd());
        uniform_int_distribution<long long int> distribution(6000000000LL, 9999999999LL);
        long long int randomNumber = distribution(generator);

        cout << "Ambulance called! Please wait for assistance." << endl;
        cout << "Contact the ambulance driver with the following number: " << randomNumber << endl;
    }

    // Function to display all patients
    void displayPatients() const
    {
        cout << "\nPatients in the system:\n";
        for (const auto &patient : patients)
        {
            cout << "Name: " << patient.name << ", Age: " << patient.age << ", Gender: " << patient.gender << ", Bill: INR " << patient.bill << endl;
        }
    }

    // Function to find a patient by name
    void findPatientByName() const
    {
        string name;
        cout << "Enter the name of the patient to search: ";
        getline(cin, name);

        auto it = patientIndexMap.find(name);
        if (it != patientIndexMap.end())
        {
            const Patient &patient = patients[it->second];
            cout << "Patient found:\n";
            cout << "Name: " << patient.name << ", Age: " << patient.age << ", Gender: " << patient.gender << ", Bill: INR " << patient.bill << endl;
        }
        else
            cout << "Patient not found!" << endl;
    }

    // Function to display pending bills
    void displayPendingBills() const
    {
        cout << "\nPending Bills:\n";
        for (const auto &patient : patients)
        {
            if (patient.bill > 0)
                cout << "Name: " << patient.name << ", Bill: INR " << patient.bill << endl;
        }
    }

    // Function to display settled bills
    void displaySettledBills() const
    {
        cout << "\nSettled Bills:\n";
        for (const auto &patient : patients)
        {
            if (patient.bill == 0)
                cout << "Name: " << patient.name << ", Bill: INR " << patient.bill << endl;
        }
    }

    // Function to update patient's bill
    void updateBill()
    {
        string name;
        float newBill;
        cout << "Enter the name of the patient to update bill: ";
        getline(cin, name);

        // Bill input with error handling
        while (true)
        {
            cout << "Enter the new bill amount: INR ";
            if (!(cin >> newBill) || newBill < 0)
            {
                cout << "Invalid input! Please enter a positive bill amount.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else
                break;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        auto it = patientIndexMap.find(name);
        if (it != patientIndexMap.end())
        {
            int index = it->second;
            patients[index].bill = newBill;
            cout << "Bill updated successfully!" << endl;
        }
        else
            cout << "Patient not found!" << endl;
    }

    // Function to load patients' details from file
    void loadPatientsFromFile()
    {
        ifstream file("details.txt");
        if (file.is_open())
        {
            string name;
            int age;
            char gender;
            float bill;
            while (file >> name >> age >> gender >> bill)
            {
                patients.push_back(Patient(name, age, gender, bill));
            }
            file.close();
            updatePatientIndexMap(); // Update the map after loading data
        }
        else
            cout << "Unable to open file!" << endl;
    }

    // Function to save patients' details to file
    void savePatientsToFile() const
    {
        ofstream file("details.txt");
        if (file.is_open())
        {
            for (const auto &patient : patients)
            {
                file << patient.name << " " << patient.age << " " << patient.gender << " " << patient.bill << endl;
            }
            file.close();
            cout << "Patients' details saved to file." << endl;
        }
        else
            cout << "Unable to open file!" << endl;
    }
};

int main()
{
    HospitalManagement hm;
    hm.loadPatientsFromFile(); // Load patients' details from file

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
        if (!(cin >> choice))
        {
            cout << "Invalid input! Please enter a valid choice.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            hm.addPatient();
            break;
        case 2:
            hm.deletePatient();
            break;
        case 3:
            hm.callAmbulance();
            break;
        case 4:
            hm.displayPatients();
            break;
        case 5:
            hm.findPatientByName();
            break;
        case 6:
            hm.displayPendingBills();
            break;
        case 7:
            hm.displaySettledBills();
            break;
        case 8:
            hm.updateBill();
            break;
        case 9:
            hm.savePatientsToFile(); // Save patients' details to file before exit
            cout << "Exiting... Thank you!\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 9);

    return 0;
}
