//
//  Employee.h
//  Employee is derived from Person
//  (more info: employee id, dependents, weeklyRate, hourlyRate, lastPayAmount, lastPayDate)
//  payroll
//
//  Created by Charles Adam on 2/28/15.
//  Copyright (c) 2015 Charles Adam. All rights reserved.
//

#ifndef __payroll__Employee__
#define __payroll__Employee__

#include <stdio.h>
#include <vector>
#include "Person.h"
#include "Dependent.h"

class Employee : public Person {
private:
    int eID;    // Unique id
    vector<Dependent *> dependents;
    double weeklyRate;
    double hourlyRate;
    
    double lastPayAmount;
    string lastPayDate;
    
public:
    //----------- constructor -------------
    Employee(string fn, string ln, string s, int a):Person(fn, ln, s, a),
    weeklyRate(-1), hourlyRate(-1), lastPayAmount(0){};
    
    //----------- setters -------------
    void setID(int i);
    void setWeeklyRate(double rate);
    void setHourlyRate(double rate);
    
    void setLastPayDate(string date);
    void setLastPayAmount(double amount);
    
    void addDependent(Dependent* d);
    // Dependent d is an employee or not?
    // true, return the employee id
    int isDependent(Dependent *d);
    
    // Set the dID of one dependent of current employee
    void setDependentID(Employee *d, int dedi);
    
    //----------- getters -------------
    int getID() { return eID; }
    vector<Dependent *> getDependents() { return dependents; }
    double getWeeklyRate() { return weeklyRate; }
    double getHourlyRate() { return hourlyRate; }
    double getLastPayAmount() { return lastPayAmount; }
    string getLastPayDate() { return lastPayDate; }
    
    // calculate payroll for weekly and hourly employees
    void calcPay(int n);
    
    // Print weekly & hourly pay employee payroll info
    void printPay();
    
    // Print weekly & hourly pay employee WITHOUT dependents
    virtual void print() {
        cout << "ID:" << eID << ", FName:" << getFname() << ", LName:" << getLname()
        << ", Sex:" << getSex() << ", Age:" << getAge() << ", ";
        
        if (weeklyRate != -1) cout << "Weekly Rate:" << weeklyRate;
        else if (hourlyRate != -1) cout << "Hourly Rate:" << hourlyRate;
        cout << endl;
    }
    
    // Print weekly & hourly pay employee WITH dependents
    void printWithDependents();
    
    // Destructor
    ~Employee();
};

#endif /* defined(__payroll__Employee__) */
