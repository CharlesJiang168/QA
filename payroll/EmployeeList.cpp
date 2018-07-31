//
//  EmployeeList.cpp
//  EmployeeList is the top class to hold all the employee and dependent information,
//  as well as provides functions to display, modify, output and calculate payroll.
//  payroll
//
//  Created by Charles Adam on 2/28/15.
//  Copyright (c) 2015 Charles Adam. All rights reserved.
//

#include "EmployeeList.h"
#include <sstream>

//----------- constructor -------------
EmployeeList::EmployeeList(){
    unid = 0;
}

//----------- load info from file -------------
// Deal duplicate cases, e.g. both wife and husband are employees.
// Therefore we only save employee records;
void EmployeeList::loadInfo(string path) {
    ifstream infile(path);
    string line;
    if (infile.is_open()) {
        // first clear any employee/dependent data already in memory
        sEmployees.clear();
        hEmployees.clear();
        dependents.clear();
        
        cout << "Erasing old database & Loading Payroll Info ... ...\n";
        string type, fname, lname, sex;
        int age = 0; double payrate = 0.0;
        
        string line;
        // Auto-generated id number for weekly, hourly employee and dependent
        while (getline(infile, line)) { // Get element count
            stringstream ss(line);
            ss >> type;
            ss >> fname; ss >> lname;
            ss >> sex;
            ss >> age;
            ss >> payrate;
            
            if (type == "W") {
                Employee *s = new Employee(fname, lname, sex, age);
                s->setWeeklyRate(payrate);
                s->setID(unid);
                int eid = unid;
                unid++;
                
                while (ss.peek() != -1) { // Has next dependent?
                    ss >> fname; ss >> lname;
                    ss >> sex;
                    ss >> age;
                    Dependent *d = new Dependent(fname, lname, sex, age);
                    d->belongsTo(eid);
                    d->setID(unid);
                    unid++;
                    if (dependentIsEmployee(d, s) == false) {
                        addDependent(d);    // Add dependent EmployeeList
                    }
                    
                    s->addDependent(d); // Add dependent to employee
                }
                addSalaryEmployee(s); // Add salary employee to list
            }
            else if (type == "H") {
                Employee *h = new Employee(fname, lname, sex, age);
                h->setHourlyRate(payrate);
                h->setID(unid);
                int eid = unid;
                unid++;
                while (ss.peek() != -1) { // Has next dependent?
                    ss >> fname; ss >> lname;
                    ss >> sex;
                    ss >> age;
                    Dependent *d = new Dependent(fname, lname, sex, age);
                    d->belongsTo(eid);
                    d->setID(unid);
                    unid++;
                    if (dependentIsEmployee(d, h) == false) {
                        addDependent(d);    // Add dependent EmployeeList
                    }
                    h->addDependent(d); // Add dependent to employee
                }
                addHourEmployee(h); // Add hourly employee to list
            }
        }
        
        cout << "Loading Completed!\n";
    }
    else {
        cout << "Unable to open the file: " << path << endl;
        cout << "------- BYE --------\n";
        exit(1);
    }
    
}

//----------- add employee to corresponding vector -------------
void EmployeeList::addSalaryEmployee(Employee *s) {
    sEmployees.push_back(s);
    
}
void EmployeeList::addHourEmployee(Employee *h) {
    hEmployees.push_back(h);
}
//----------- add new employee, dealing with duplicate case -------------
void EmployeeList::addNewEmployee(string line) {
    // W Charles Adam M 25 53000.00 Cathy Adam F 20
    string type, fname, lname, sex;
    int age = 0;
    double payrate = 0;
    // Auto-generated id number for weekly, hourly employee and dependent
    stringstream ss(line);
    ss >> type;
    ss >> fname; ss >> lname;
    ss >> sex;
    ss >> age;
    ss >> payrate;
    
    if (type == "W") {
        Employee *s = new Employee(fname, lname, sex, age);
        s->setWeeklyRate(payrate);
        s->setID(unid);
        int eid = unid;
        unid++;
        
        while (ss.peek() != -1) { // Has next dependent?
            ss >> fname; ss >> lname;
            ss >> sex;
            ss >> age;
            Dependent *d = new Dependent(fname, lname, sex, age);
            d->belongsTo(eid);
            d->setID(unid);
            unid++;
            if (dependentIsEmployee(d, s) == false) {
                addDependent(d);    // Add dependent EmployeeList
            }
            
            s->addDependent(d); // Add dependent to employee
        }
        addSalaryEmployee(s); // Add salary employee to list
    }
    else if (type == "H") {
        Employee *h = new Employee(fname, lname, sex, age);
        h->setHourlyRate(payrate);
        h->setID(unid);
        int eid = unid;
        unid++;
        while (ss.peek() != -1) { // Has next dependent?
            ss >> fname; ss >> lname;
            ss >> sex;
            ss >> age;
            Dependent *d = new Dependent(fname, lname, sex, age);
            d->belongsTo(eid);
            d->setID(unid);
            unid++;
            if (dependentIsEmployee(d, h) == false) {
                addDependent(d);    // Add dependent EmployeeList
            }
            h->addDependent(d); // Add dependent to employee
        }
        addHourEmployee(h); // Add hourly employee to list
    }

}

//----------- add dependent to dependents vector -------------
// Add a dependent to an employee
// if the employee doesn't exist, cerr and stop
void EmployeeList::addDependent(string line) {
    // 15 Monkey Adam M 1
    // 12 Jenny Wong F 11
    int eid = -1;
    string fname, lname, sex;
    int age = 0;
    // Auto-generated id number for weekly, hourly employee and dependent
    stringstream ss(line);
    
    while (ss.peek() != -1) { // Has next dependent?
        ss >> eid;
        ss >> fname; ss >> lname;
        ss >> sex;
        ss >> age;
        
        Dependent *d = new Dependent(fname, lname, sex, age);
        d->setID(unid);
        d->belongsTo(eid);
        unid++;
        for (Employee *s : sEmployees) {
            if (s->getID() == eid)
                s->addDependent(d);
        }
        for (Employee *h : hEmployees) {
            if (h->getID() == eid)
                h->addDependent(d);
        }
        addDependent(d); // Add dependent to list
    }
}

//----------- Deal with duplicate employee&dependent case -------------
// Dependent is one employee, return eID, else -1
bool EmployeeList::dependentIsEmployee(Dependent *d, Employee *se) {
    int dedi = d->getEID(); // current dependent belongs to employee id
    int eid = -1;
    // Traverse salary employees
    for (Employee *e : sEmployees) {
        eid = e->isDependent(d);
        if (eid != -1) { // eid = 0
            e->setDependentID(se, dedi); // set that depedent belongs to new employee id
            d->setID(eid); // set depedent id to existing employee id
            removeDependent(dedi); // remove previous stored dependent
            return true;
        }
    }
    // Traverse hourly employees
    for (Employee *e : hEmployees) {
        eid = e->isDependent(d);
        if (eid != -1) { // eid = 0
            e->setDependentID(se, dedi); // set that depedent belongs to new employee id
            d->setID(eid); // set depedent id to existing employee id
            removeDependent(dedi); // remove previous stored dependent
            return true;
        }
    }
    return false;
}

//----------- removeDependent -------------
void EmployeeList::removeDependent(int did) {
    for (int i=0; i<dependents.size(); i++) {
        if (dependents[i]->getDID() == did) {
            dependents.erase(dependents.begin()+i);
        }
    }
}
//----------- add dependent to dependents vector -------------
void EmployeeList::addDependent(Dependent *d) {
    dependents.push_back(d);
}

//----------- print details for weekly employee without dependents -------------
void EmployeeList::printSalaryEmployees() {
    cout << "------------ Salary Employees ---------------\n";
    if (sEmployees.empty()) cout << "null\n";
    for (Employee *e : sEmployees) {
        cout << endl;
        e->print();
    }
}

//----------- print details for hourly employee without dependents -------------
void EmployeeList::printHourEmployees() {
    cout << "------------ Hourly Employees ---------------\n";
    if (hEmployees.empty()) cout << "null\n";
    for (Employee *e : hEmployees) {
        cout << endl;
        e->print();
    }
}

//----------- print details for all dependents -------------
void EmployeeList::printDependents() {
    cout << "------------ Dependents ---------------\n";
    if (dependents.empty()) cout << "null\n";
    for (Dependent *d : dependents) {
        cout << endl;
        d->print();
    }
}

//----------- print details for all employees with dependents -------------
void EmployeeList::printEmployeesWithDependents() {
    cout << "------------ Employees with Dependents ---------------\n";
    for (Employee *e : sEmployees) {
        e->printWithDependents();
    }
    for (Employee *e : hEmployees) {
        e->printWithDependents();
    }
}

//----------- calculate payroll for all employees -------------
void EmployeeList::runPayroll(string date) {
    cout << "------------ Salary Employees Payroll ---------------\n";
    for (Employee *e : sEmployees) {
        e->setLastPayDate(date);
        e->calcPay(1); // calculate 1 week payroll
        e->printPay();
    }
    cout << "------------ Hourly Employees Payroll ---------------\n";
    for (Employee *e : hEmployees) {
        e->setLastPayDate(date);
        cout << e->getID() << ", please specify the # of hours: ";
        int n = 0;
        cin >> n;
        e->calcPay(n);
        e->printPay();
    }
}

//----------- output employees and dependents info to file -------------
void EmployeeList::saveInfo(string path) {
    cout << "Writing to the output file path: \n" << path << endl;
    fstream fs;
    fs.open(path, fstream::out);
    for (Employee *s : sEmployees) { // write out weekly employees info
        fs << "ID:" << s->getID() << ", FName:" << s->getFname() << ", LName:" << s->getLname()
        << ", Sex:" << s->getSex() << ", Age:" << s->getAge() << ", ";
        
        if (s->getWeeklyRate() != -1) fs << "Weekly Rate:" << s->getWeeklyRate();
        else if (s->getHourlyRate() != -1) fs << "Hourly Rate:" << s->getHourlyRate();
        fs << endl;
        for (Dependent *d : s->getDependents()) {
            fs << "[ID:" << d->getDID() << ", FName:" << d->getFname() << ", LName:" << d->getLname()
            << ", Sex:" << d->getSex() << ", Age:" << d->getAge() << ", belongs to:" << d->getEID() << "]\n";
        }
        fs << endl;
    }
    for (Employee *s : hEmployees) { // write out hourly employees info
        fs << "ID:" << s->getID() << ", FName:" << s->getFname() << ", LName:" << s->getLname()
        << ", Sex:" << s->getSex() << ", Age:" << s->getAge() << ", ";
        
        if (s->getWeeklyRate() != -1) fs << "Weekly Rate:" << s->getWeeklyRate();
        else if (s->getHourlyRate() != -1) fs << "Hourly Rate:" << s->getHourlyRate();
        fs << endl;
        for (Dependent *d : s->getDependents()) {
            fs << "[ID:" << d->getDID() << ", FName:" << d->getFname() << ", LName:" << d->getLname()
            << ", Sex:" << d->getSex() << ", Age:" << d->getAge() << ", belongs to:" << d->getEID() << "]\n";
        }
        fs << endl;
    }
    fs.close(); // close the file stream
}

//----------- destructor -------------
EmployeeList::~EmployeeList() {
    sEmployees.clear();
    hEmployees.clear();
    dependents.clear();
}