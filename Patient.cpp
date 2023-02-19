//
// Created by me on 11/30/2022.
//

#include "Patient.h"


Patient::Patient() {}

Patient::Patient(string firstName, string middleName, string lastName, string suffix, vector<string> ailment, string doctor, bool treated, int priority) : firstName(firstName), middleName(middleName), lastName(lastName), suffix(suffix), ailment(ailment), doctor(doctor), treated(treated), priority(priority){}

//**
bool Patient::operator<(const Patient &rhs) const {
    return this->getPriority() >= rhs.getPriority();
    //returns true if more than or equal, false if not. Its done this way so that the priority queue puts the priority with the least amount first instead of the priority with the biggest amount first
}

const string &Patient::getFirstName() const {
    return firstName;
}

const string &Patient::getMiddleName() const {
    return middleName;
}

const string &Patient::getLastName() const {
    return lastName;
}

const string &Patient::getSuffix() const {
    return suffix;
}

const vector<string> &Patient::getAilment() const {
    return ailment;
}

const string &Patient::getDoctor() const {
    return doctor;
}

bool Patient::getTreated() const {
    return treated;
}

int Patient::getPriority() const {
    return priority;
}

void Patient::setTreated(bool treated) {
    Patient::treated = treated;
}

void Patient::setFirstName(const string &firstName) {
    Patient::firstName = firstName;
}

void Patient::setMiddleName(const string &middleName) {
    Patient::middleName = middleName;
}

void Patient::setLastName(const string &lastName) {
    Patient::lastName = lastName;
}

void Patient::setSuffix(const string &suffix) {
    Patient::suffix = suffix;
}

void Patient::setAilment(const string &ailment) {
    Patient::ailment.push_back(ailment);
}

void Patient::setDoctor(const string &doctor) {
    Patient::doctor = doctor;
}

void Patient::setPriority(int priority) {
    Patient::priority = priority;
}

ostream &operator<<(ostream &os, const Patient &patient) {
    os << "firstName: " << patient.firstName << ", middleName: " << patient.middleName << ", lastName: "
       << patient.lastName << ", suffix: " << patient.suffix << ", ailment: " << patient.printAilments() << ", doctor: "
       << patient.doctor << ", treated: " << patient.treated << ", priority: " << patient.priority;
    return os;
}

string Patient::printAilments() const {
    string a;
    for(string i:this->getAilment())
        a += i + " ";
    a.pop_back();
    return a;
}




