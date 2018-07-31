//
//  Employee.cpp
//  payroll
//
//  Created by Charles Adam on 2/28/15.
//  Copyright (c) 2015 Charles Adam. All rights reserved.
//

#include "Employee.h"

//----------- setters -------------
void Employee::setID(int i) {
    eID = i;
}
void Employee::setWeeklyRate(double rate) {
    weeklyRate = rate;
}
void Employee::setHourlyRate(double rate) {
    hourlyRate = rate;
}
void Employee::setLastPayDate(string date) {
    lastPayDate = date;
}
void Employee::setLastPayAmount(double amount) {
    lastPayAmount = amount;
}
//----------- End of setters -------------

// Add dependent to current employee dependents list
void Employee::addDependent(Dependent* d) {
    dependents.push_back(d);
}

// Dependent d is an employee or not?
// true, return the employee id
int Employee::isDependent(Dependent *d) {
    if (d->getFname() == this->getFname() && d->getLname() == this->getLname()
        && d->getSex() == this->getSex() && d->getAge() == this->getAge()) {
        return this->eID;
    }
    return -1;
}

// Set the dID of one dependent of current employee
void Employee::setDependentID(Employee *e, int dedi) {
    for (Dependent *&dep : dependents) {
        if (dep->getFname() == e->getFname() && dep->getLname() == e->getLname()
            && dep->getSex() == e->getSex() && dep->getAge() == e->getAge()) {
            dep->setID(dedi);
        }
    }
}

// calculate payroll for weekly and hourly employees
void Employee::calcPay(int n) {
    if (weeklyRate != -1) { // n stands for n weeks
        lastPayAmount = weeklyRate * n;
    }
    if (hourlyRate != -1) { // n stands for n hours/week
        lastPayAmount = hourlyRate * n;
    }
}

// Print weekly & hourly pay employee payroll info
void Employee::printPay() {
    cout << "[" << eID << "] " << getFname() << "-" << getLname() << " $" << lastPayAmount << " Date:" << lastPayDate << endl;
}

// Print weekly & hourly pay employee WITH dependents
void Employee::printWithDependents() {
    if ( !dependents.empty() ) { // if has dependents, print all info
        cout << endl;
        print();
        cout << "Dependents: \n";
        for (Dependent *d : dependents)
            d->print();
    }
}

// Destructor
Employee::~Employee() {
    for (Dependent* d : dependents) {
        d->~Dependent(); // Explicit call to destructor
    }
}


