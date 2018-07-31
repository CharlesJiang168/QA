//
//  main.cpp
//  payroll
//
//  Created by Charles Adam on 2/27/15.
//  Copyright (c) 2015 Charles Adam. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <sstream>
#include "Person.h"
#include "EmployeeList.h"

// Get current date in day-month-year
string getCurrentDate() {
    time_t rawtime;
    struct tm *timeinfo;
    
    char buffer[80];
    time (&rawtime);
    
    timeinfo = localtime(&rawtime);
    strftime(buffer, 80, "%d-%m-%Y", timeinfo);
    
    string str(buffer);
    return str;
}
// Print program usage
void usage() {
    cout << "***************** Welcome to Payroll *****************\n";
    cout << "1. Display the salaried employees;\n";
    cout << "2. Display the hourly employees;\n";
    cout << "3. Display all employees who have dependents, with their dependents’ information.\n";
    cout << "4. Load the data file containing the list of members and family.\n";
    cout << "5. Save the employee/depending data in memory to the data file.\n";
    cout << "6. Add a new employee.\n";
    cout << "7. Add a new dependent to an employee.\n";
    cout << "8. Run payroll.\n";
    cout << "9. Exit.\n";
    cout << "Please select: ";
}

int main(int argc, const char * argv[]) {
    // Dynamic EmployeeList object
    EmployeeList *list = new EmployeeList();
    // Loading default data
//    string path;
//    path = "/Users/charlesadam/CS582AH1PRACTICALC++PROGRAMMING/CS582/finalexam/payroll/payroll/in.dat";
//    cout << "input: " << path << endl;
//    list->loadInfo(path);
    
    while (1) {
        usage();
        string line;
        getline(cin, line);
        stringstream ss(line);
        int option = 4; // default is loading data
        ss >> option;
    
        switch (option) {
            case 1: // Display salary employee
                list->printSalaryEmployees();
                break;
            case 2: // Display hourly employee
                list->printHourEmployees();
                break;
            case 3: // Display all employees with dependents
                list->printEmployeesWithDependents();
                break;
            case 4: // load data
            {
                string path;
                path = "/Users/charlesadam/CS582AH1PRACTICALC++PROGRAMMING/CS582/finalexam/payroll/payroll/in.dat";
                cout << "Please specify the database path: \n";
                getline (cin, path);
                cout << "input: " << path << endl;
                list->loadInfo(path);
            }
                break;
            case 5: // Save to file
            {   string path;
                path = "/Users/charlesadam/CS582AH1PRACTICALC++PROGRAMMING/CS582/finalexam/payroll/payroll/out.dat";
                cout << "Please specify the output file path: \n";
                getline (cin, path);
                cout << "input: " << path << endl;
                list->saveInfo(path);
            }
                break;
            case 6: // Add a new employee
            {    // W Charles Adam M 25 53000.00 Cathy Adam F 20
                cout << "H/W fname lname sex age payrate [depdent] fname lname sex age ...\n";
                cout << "Please provide above info: ";
                string line;
                getline(cin, line);
                list->addNewEmployee(line);
            }
                break;
            case 7: // Add a new dependent to an employee
            {   // 15 Monkey Adam M 1
                // 12 Jenny Wong F 11
                cout << "employeeID fname lname sex age ...\n";
                cout << "Please provide above info: ";
                string line;
                getline(cin, line);
                list->addDependent(line);
                //list->printEmployeesWithDependents();
            }
                break;
            case 8: // Run payroll for all employees
                list->runPayroll(getCurrentDate());
                break;
            case 9:
                return 0;
                break;
            default:
                break;
        }
        
    }
    
    return 0;
}
