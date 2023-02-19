//
// Created by me on 11/30/2022.
//

#include <string>
#include <vector>
#include <ostream>

using namespace std;

#ifndef HOSPITAL_ADMINISTRATION_CONSOLE_APPLICATION_PATIENT_H
#define HOSPITAL_ADMINISTRATION_CONSOLE_APPLICATION_PATIENT_H


class Patient {
public:
    Patient();
    Patient(string firstName, string middleName, string lastName, string suffix, vector<string> ailment, string doctor, bool treated, int priority);

    bool operator<(const Patient &rhs) const;
    friend ostream &operator<<(ostream &os, const Patient &patient);
    string printAilments() const;

    //getters
    const string &getFirstName() const;
    const string &getMiddleName() const;
    const string &getLastName() const;
    const string &getSuffix() const;
    const vector<string> &getAilment() const;
    const string &getDoctor() const;
    bool getTreated() const;
    int getPriority() const;

    //setters
    void setFirstName(const string &firstName);
    void setMiddleName(const string &middleName);
    void setLastName(const string &lastName);
    void setSuffix(const string &suffix);
    void setAilment(const string &ailment);
    void setDoctor(const string &doctor);
    void setTreated(bool treated);
    void setPriority(int priority);



private:
    string firstName;
    string middleName;
    string lastName;
    string suffix;
    vector<string> ailment;
    string doctor;
    bool treated;
    int priority;
};

//functor name may be confusing but essentially this determines which is greater instead of less so the priority queue spits out the value with the least amount first
//may want to do operator> instead?
class LessThanValue{
public:
    bool  operator() (const Patient &lhs, const Patient &rhs) const{
        return lhs.getPriority() >= rhs.getPriority();
    }
};

#endif //HOSPITAL_ADMINISTRATION_CONSOLE_APPLICATION_PATIENT_H
