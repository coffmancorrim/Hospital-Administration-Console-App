//
// Created by me on 11/30/2022.
//

#ifndef HOSPITAL_ADMINISTRATION_CONSOLE_APPLICATION_HOSPITALADMINISTRATIONAPP_H
#define HOSPITAL_ADMINISTRATION_CONSOLE_APPLICATION_HOSPITALADMINISTRATIONAPP_H
#include <string>
#include <ostream>
#include "Logger.h"
#include "Patient.h"
using namespace std;

class HospitalAdministrationApp {
public:
    HospitalAdministrationApp();
    void add(Patient &patient);
    string treatPatient();
    void addFile(string file);

    void printPatients();

    const priority_queue<Patient, vector<Patient>, LessThanValue> &getPatients() const;

    const queue<Patient> &getTreated() const;

    void treatedNext();

    void printTreated();

    void treatAll();

    void printByDoctor();

    void patientReport(const string& name, bool treated);

    void setDebugMode(bool debugMode);

    bool isDebugMode() const;

private:
    priority_queue<Patient, vector<Patient>, LessThanValue> patients;
    queue<Patient> treated;
    Logger &logger = Logger::getLog();
    bool debugMode;
    ofstream LogFile;
    void systemLog(const string& log);
};


#endif //HOSPITAL_ADMINISTRATION_CONSOLE_APPLICATION_HOSPITALADMINISTRATIONAPP_H
