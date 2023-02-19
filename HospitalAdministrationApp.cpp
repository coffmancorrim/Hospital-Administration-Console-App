//
// Created by me on 11/30/2022.
//

#include <queue>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include "HospitalAdministrationApp.h"
#include <map>

HospitalAdministrationApp::HospitalAdministrationApp() {
LogFile.open("log.txt");
debugMode = false;
}

void HospitalAdministrationApp::add(Patient &patient){
    string message;
    if(!patient.getTreated()){
        patients.push(patient);
        message = "USER: accessed command 1: method add(), " + patient.getFirstName() + " " + patient.getLastName() + " added to TRIAGE container";
    }
    else{
        treated.push(patient);
        message = "USER: accessed command 1: method  add(), " + patient.getFirstName() + " " + patient.getLastName() + " added to TREATED container";
    }

    if(debugMode){
       logger.log(message);
    }else{
        systemLog(message);
    }
}

void HospitalAdministrationApp::systemLog(const string& log) {
    LogFile << log << endl;
}

void HospitalAdministrationApp::addFile(string file) {
    ifstream ReadPatientsFile(file); //ios::in
    if(!ReadPatientsFile){
        throw(file);
    }

    string input;
    while (getline(ReadPatientsFile, input)){  //read data from file
        Patient p; //read data into patient object
        for(int i = 0; i < 999999; i++){ //read file data into the correct fields of the patient object
            int j = input.find(':');
            string title = input.substr(0, j);
            string value = input.substr(j+1, input.length()-1); //data value
            if(title == "firstName")
                p.setFirstName(value);
            else if(title == "middleName")
                p.setMiddleName(value);
            else if(title == "lastName")
                p.setLastName(value);
            else if(title == "suffix")
                p.setSuffix(value);
            else if(title == "ailment")
                p.setAilment(value);
            else if(title == "doctor")
                p.setDoctor(value);
            else if(title == "treated")
                p.setTreated(stoi(value));
            else if(title == "priority")
                p.setPriority(stoi(value));

            getline(ReadPatientsFile, input); //get next line
            if(input.empty())//check if empty, if empty then it's the end of that patient's data, so we go on to the next
                break;
        }

        if(!p.getTreated()){
            patients.push(p);
        }
        else{
            treated.push(p);
        }
    }
    ReadPatientsFile.close();

    string message = "USER: accessed command 10: method addFile(), added patient data from " + file + " to the system";
    if(debugMode){
        logger.log(message);
    }else{
        systemLog(message);
    }

}

void HospitalAdministrationApp::printPatients() {

    priority_queue copy = patients;
    cout << "\nPATIENTS" << endl;
    if(patients.empty()){
        cout << "no patients in queue" << endl;
    }
    while (!copy.empty()) {
        cout << copy.top() << endl;
        copy.pop();
    }

    string message = "USER: accessed command 6: method printPatients()";
    if(debugMode){
        logger.log(message);
    }else{
        systemLog(message);
    }
}


const priority_queue<Patient, vector<Patient>, LessThanValue> &HospitalAdministrationApp::getPatients() const {
    return patients;
}

const queue<Patient> &HospitalAdministrationApp::getTreated() const {
    return treated;
}

string HospitalAdministrationApp::treatPatient() {
    if(patients.empty())
        throw (patients.empty());

    Patient p = patients.top();
    p.setTreated(true);
    treated.push(p);
    string name;
    name = patients.top().getFirstName() +" "+ patients.top().getLastName();
    patients.pop();
    sleep(1 + (rand() % 3));

    string message = "USER: accessed command 2: method treatPatient()";
    if(debugMode){
        logger.log(message);
    }else{
        systemLog(message);
    }
    return name;
}

void HospitalAdministrationApp::treatedNext() {
    if(!patients.empty()){
        cout << "\nNEXT PATIENT\n" << patients.top() << endl;
    }
    else{
        cout << "There are no patients in queue to be treated" << endl;
    }

    string message = "USER: accessed command 5: method treatedNext()";
    if(debugMode){
        logger.log(message);
    }else{
        systemLog(message);
    }
}

void HospitalAdministrationApp::printTreated() {
    queue copy = treated;
    cout << "\nTREATED\n";
    if(treated.empty()){
        cout << "there are no treated patients currently in the system" << endl;
    }
    while (!copy.empty()) {
        cout << copy.front() << "\n";
        copy.pop();
    }
    string message = "USER: accessed command 4: method printTreated()";
    if(debugMode){
        logger.log(message);
    }else{
        systemLog(message);
    }
}

void HospitalAdministrationApp::treatAll() {
    if(patients.empty())
        throw (patients.empty());

    Patient p = patients.top();
    p.setTreated(true);
    while (!patients.empty()) {
        treated.push(p);
        patients.pop();
        sleep(1 + (rand() % 3));
    }

    string message = "USER: accessed command 7: method treatAll(), all patients moved / marked as treated";
    if(debugMode){
        logger.log(message);
    }else{
        systemLog(message);
    }
}

void HospitalAdministrationApp::printByDoctor() {


    multimap<string, Patient> doctors;
    priority_queue<Patient, vector<Patient>, LessThanValue> copy1 = patients;
    queue copy2 = treated;
    while (!copy1.empty()) {
        doctors.insert(pair<string,Patient>(copy1.top().getDoctor(), copy1.top()));
        copy1.pop();
    }
    while (!copy2.empty()) {
        doctors.insert(pair<string,Patient>(copy2.front().getDoctor(), copy2.front()));
        copy2.pop();
    }

    multimap<string, Patient>::iterator i;
    string doctorCalled;
    cout <<"\nPATIENTS BY DOCTOR"<< endl;
    if(patients.empty() && treated.empty()){
        cout << "there are no patients in the system" << endl;
    }
    for(i = doctors.begin(); i != doctors.end(); i++){
        if(i == doctors.begin()){
            cout << "DOCTOR: " + i->first<< endl;
            doctorCalled = i->first;
        }else if(doctorCalled != i->first){
            cout << "\nDOCTOR: " + i->first<< endl;
            doctorCalled = i->first;
        }
        cout << i->second << endl;
    }

    string message = "USER: accessed command 8: method printByDoctor()";
    if(debugMode){
        logger.log(message);

    }else{
        systemLog(message);
    }
}

void HospitalAdministrationApp::patientReport(const string& name, bool isTreated) {
    if(patients.empty() && treated.empty()){
        cout << "no patients in system" << endl;
    }

    bool toReturn = false;
    if(!isTreated){
        priority_queue<Patient, vector<Patient>, LessThanValue> copy1 = patients;
        while (!copy1.empty()) {
            string name2 = copy1.top().getFirstName() + " " + copy1.top().getLastName() + " " + copy1.top().getDoctor() + " " + to_string(copy1.top().getPriority());

            if(name == name2){
                Patient p = copy1.top();
                cout << "\nPATIENT: " + p.getFirstName() + " " + p.getLastName() << endl;
                cout << p << endl;
                toReturn = true;
                break;
            }
            copy1.pop();
        }
    }
    else{
        queue copy2 = treated;
        while (!copy2.empty()) {
            string name2 = copy2.front().getFirstName() + " " + copy2.front().getLastName() + " " + copy2.front().getDoctor() + " " + to_string(copy2.front().getPriority());
            if(name == name2){
                Patient p = copy2.front();
                cout << "\nPATIENT: " + p.getFirstName() + " " + p.getLastName() << endl;
                cout << p << endl;
                toReturn = true;
                break;
            }
            copy2.pop();
        }
    }

    if(!toReturn){
        cout << "no patient found matching " + name << endl;
    }
    string message = "USER: accessed command 3: method patientReport()";
    if(debugMode){
        logger.log(message);
    }else{
        systemLog(message);
    }
}


void HospitalAdministrationApp::setDebugMode(bool debugValue) {
    HospitalAdministrationApp::debugMode = debugValue;

    string message = "USER: accessed command 11: method setDebugMode(), debugMode = " + to_string(debugMode);
    if(debugMode){
        logger.log(message);
    }else{
        systemLog(message);
    }
}

bool HospitalAdministrationApp::isDebugMode() const {
    return debugMode;
}

