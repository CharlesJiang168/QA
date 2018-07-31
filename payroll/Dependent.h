//
//  Dependent.h
//  Dependent is derived from Person
//  (more info: dependent id, employee id which it belongs to)
//  payroll
//
//  Created by Charles Adam on 2/28/15.
//  Copyright (c) 2015 Charles Adam. All rights reserved.
//

#ifndef __payroll__Dependent__
#define __payroll__Dependent__

#include <stdio.h>
#include "Person.h"

class Dependent : public Person {
private:
    int dID; // dependent unique id
    int eID; // employee unique id which current dependent belongs to
public:
    //------------- constructor -----------------
    Dependent(string fn, string ln, string s, int a):Person(fn, ln, s, a){};
    
    //------------- setters -----------------
    void setID(int i) { dID = i; };      // set dependent id
    void belongsTo(int i) { eID = i; };  // set employee id which it belongs to
    
    //------------- getters -----------------
    int getDID() { return dID; }
    int getEID() { return eID; }
    
    //------------- print dependent info -----------------
    virtual void print() {
        cout << "[ID:" << dID << ", FName:" << getFname() << ", LName:" << getLname()
        << ", Sex:" << getSex() << ", Age:" << getAge() << ", belongs to:" << eID << "]\n";
    }
    
    //------------- desctructor -----------------
    ~Dependent() {};
};


#endif /* defined(__payroll__Dependent__) */
