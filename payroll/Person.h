//
//  Person.h
//  Person is the abtract base class (fname, lname, sex, age)
//
//  payroll
//
//  Created by Charles Adam on 2/28/15.
//  Copyright (c) 2015 Charles Adam. All rights reserved.
//

#ifndef payroll_Person_h
#define payroll_Person_h

#include <iostream>
using namespace std;

class Person {
private:
    string fname; // first name
    string lname; // last name
    string sex;
    int age;
public:
    //--------- constructor ---------
    Person(string fn, string ln, string s, int a):
        fname(fn), lname(ln), sex(s), age(a){}
    
    //--------- getters ---------
    string getFname() { return fname; }
    string getLname() { return lname; }
    string getSex() { return sex; }
    int getAge() { return age; }
    
protected:
    //--------- destructor ---------
    ~Person() {}
    //--------- print person info ---------
    virtual void print()=0; // pure virtual => abstract class
};

#endif
