//
//  EmployeeList.h
//  payroll
//
//  Created by Charles Adam on 2/28/15.
//  Copyright (c) 2015 Charles Adam. All rights reserved.
//

#ifndef __payroll__EmployeeList__
#define __payroll__EmployeeList__

#include <stdio.h>
#include <fstream>
#include "Person.h"
#include "Employee.h"
#include "Dependent.h"

class EmployeeList {
private:
    vector<Employee *> sEmployees;  // Salary Employees with dependents
    vector<Employee *> hEmployees;  // Hourly Employees with dependents
    vector<Dependent *> dependents; // All dependents
    
    int unid;
    
public:
    //----------- constructor -------------
    EmployeeList();
    
    //----------- load info from file -------------
    void loadInfo(string fpath);
    
    //----------- add employee to corresponding vector -------------
    void addSalaryEmployee(Employee *s);
    void addHourEmployee(Employee *h);
    
    //----------- Deal with duplicate employee&dependent case -------------
    // true, dependent is one employee
    // s has dependent d, check through the employee list
    bool dependentIsEmployee(Dependent *d, Employee *s);
    
    //----------- Remove dependent did from current employee dependent list -------------
    void removeDependent(int did);
    
    //----------- add dependent to dependents vector -------------
    void addDependent(Dependent *d);
    
    //----------- add new employee, dealing with duplicate case -------------
    void addNewEmployee(string line);
    
    //----------- addDependent -------------
    // Add a dependent to an employee
    // if the employee doesn't exist, cerr and stop
    void addDependent(string line);
    
    //----------- print details for weekly employee without dependents -------------
    void printSalaryEmployees();
    
    //----------- print details for hourly employee without dependents -------------
    void printHourEmployees();
    
    //----------- print details for all dependents -------------
    void printDependents();
    
    //----------- print details for all employees with dependents -------------
    void printEmployeesWithDependents();
    
    //----------- calculate payroll for all employees -------------
    void runPayroll(string date);
    
    //----------- output employees and dependents info to file -------------
    void saveInfo(string fpath);
    
    //----------- destructor -------------
    ~EmployeeList();
};

#endif /* defined(__payroll__EmployeeList__) */
