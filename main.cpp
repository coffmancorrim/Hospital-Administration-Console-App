#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include "HospitalAdministrationApp.h"

using namespace std;

bool numbersOnly(const string& input){
    string alphabet = "`-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>? ";
    for (int i = 0; i < alphabet.length(); ++i) {
        if(input.contains(alphabet[i])){
            return false;
        }
    }
    return true;
}

void interface(const string& input){
    cout << "\nHospital Administration Console Application Interface \nOptions are labeled with numbers 1 through 9. Please select an option by typing in a number from 1-9, then press enter" << endl;
    if(input == "badInput"){
        cout << "***BAD INPUT ENTER A NUMBER LIKE... 0 1 2 3 4 5 6 7 8 9 10 11, THEN PRESS ENTER***" << endl;
    }
    cout << "0: exit" << endl;
    if(input == "9")
        cout << "-- close the program" << endl;
    cout << "1: add a patient" << endl;
    if(input == "9")
        cout << "-- add a patient and their information to the system, type in all fields to add to the system" << endl;
    cout << "2: treat next patient in queue" << endl;
    if(input == "9")
        cout << "-- mark tha patient as treated, then move them into the treated container" << endl;
    cout << "3: print a patient report" << endl;
    if(input == "9")
        cout << "-- select a patient by entering in their first name, last name, and priority and print out a report" << endl;
    cout << "4: print a report for all treated patients" << endl;
    if(input == "9")
        cout << "-- print the information of all patients that have the treated status and are in the treated container to the console" << endl;
    cout << "5: print/view details of the next patient to be treated" << endl;
    if(input == "9")
        cout << "-- view the next patient in priority to be treated (prints their information)" << endl;
    cout << "6: print a report for all patients in the triage" << endl;
    if(input == "9")
        cout << "-- all information for patients yet to be treated will be printed to the console" << endl;
    cout << "7: treat all patients" << endl; //DID NOT CHANGE TREAT FROM 0 TO 1
    if(input == "9")
        cout << "-- all patients will be marked as treated and moved to the treated container" << endl;
    cout << "8: print out all patients information by doctor" << endl;
    if(input == "9")
        cout << "-- print out all patients information listed by doctor" << endl;
    cout << "9: (HELP) print out a guide on each command in the system" << endl;
    if(input == "9")
        cout << "-- print out a guide on each command in the system" << endl;
    cout << "10: add patients from a file" << endl;
    if(input == "9")
        cout << "-- specify a file name with the extension .txt (for example patients.txt) and add the patients information to the system" << endl;
    cout << "11: debug mode" << endl;
    if(input == "9"){
        cout << "-- see the return values of the system when you run the command" << endl;
    }
}

void run(){
    string input = "-1";
    HospitalAdministrationApp app;
    while(input != "0"){
        interface(input);
        cin >> input;
        if(input =="1") {
            string prompts[9]{
                    "enter the patients first name",
                    "enter the patients middle name (if none type in none)",
                    "enter the patients last name",
                    "enter the patients suffix (if none type in none)",
                    "how many ailments does the patient have (min: 1, numbers only)",
                    "enter the patients ailment",
                    "enter the patients doctor",
                    "is the patient already treated? (yes, no)",
                    "enter the patients priority (numbers only)",
            };
            Patient p;
            int ailments;
            for (int state = 0; state < 9; state++) {
                cout << prompts[state] << endl;
                cin >> input;
                if(state == 1 && input == "none" || state == 3 && input == "none"){
                    input = "";
                }
                if (state == 4 || state == 8) { //check for non-numerical values
                    if(!numbersOnly(input) || input == "0"){
                        cout << "Only numbers are allowed for this field, except for the number 0 please try again (ex. 1 2 3 4 5 6 7 8 9 10...)" << endl;
                        state--;
                        continue;
                    }
                }
                if (state == 7 && !(input == "yes" || input == "no")) {
                    cout << "you must answer with yes or no" << endl;
                    state--;
                    continue;
                }

                if (state == 0) {
                    p.setFirstName(input);
                } else if (state == 1) {
                    p.setMiddleName(input);
                } else if (state == 2) {
                    p.setLastName(input);
                } else if (state == 3) {
                    p.setSuffix(input);
                } else if (state == 4){
                    ailments = stoi(input);
                }else if (state == 5) {
                    p.setAilment(input);
                    for (int i = 0; i < ailments - 1; ++i) {
                        cout << prompts[state] + " " + to_string(i + 2) << endl;
                        cin >> input;
                        p.setAilment(input);
                    }
                } else if (state == 6) {
                    p.setDoctor(input);
                } else if (state == 7) {
                    if (input == "yes")
                        p.setTreated(1);
                    else {
                        p.setTreated(0);
                    }
                } else if (state == 8) {
                    p.setPriority(stoi(input));
                }

            }

            app.add(p);
            cout << "successfully added patient" << endl;
        }
        else if(input =="2"){
            try{
                string name = app.treatPatient();
                cout<< name + " has been treated" << endl;
            }
            catch (bool &a){
                cout << "there are no more patients to treat" << endl;
            }

        }
        else if(input =="3"){
            cout << "Please enter in the patients information as prompted" << endl;
            string prompts[5]{
                    "enter the patients first name",
                    "enter the patients last name",
                    "enter the patients doctor",
                    "is the patient already treated? (yes, no)",
                    "enter the patients priority (numbers only)",
            };
            string p; //patient
            bool t; //treated
            for (int state = 0; state < 5; state++) {
                cout << prompts[state] << endl;
                cin >> input;
                if (state == 4) { //check for non-numerical values
                    if(!numbersOnly(input) || input == "0"){
                        cout << "Only numbers are allowed for this field, except for the number 0 please try again (ex. 1 2 3 4 5 6 7 8 9 10...)" << endl;
                        state--;
                        continue;
                    }
                }
                if (state == 3 && !(input == "yes" || input == "no")) {
                    cout << "you must answer with yes or no" << endl;
                    state--;
                    continue;
                }
                if (state == 0) { //first name
                    p = input + " ";
                } else if (state == 1) { //last name
                    p += input + " ";
                } else if (state == 2) { //doctor
                    p += input + " ";
                } else if (state == 3) { //treated
                    if (input == "yes")
                        t = true;
                    else {
                       t = false;
                    }
                } else if (state == 4) {
                    p += input;
                }
            }
            app.patientReport(p, t);
        }
        else if(input =="4"){
            app.printTreated();
        }
        else if(input =="5"){
            app.treatedNext();
        }
        else if(input =="6"){
            app.printPatients();
        }
        else if(input =="7"){
            try{
                app.treatAll();
                cout<< "All patients have been successfully treated" <<endl;
            }
            catch (bool &a){
                cout << "there are no more patients to treat" << endl;
            }

        }
        else if(input =="8"){
            app.printByDoctor();
        }
        else if(input =="9"){
        }
        else if(input == "10"){
            cout << "enter the filename and the directory of the file you want to add (ex. patients.txt)" << endl;
            cin >> input;
            try{
                app.addFile(input);
                cout << "File successfully added" << endl;
            }
            catch(string &f){
                cout<<"FILE DOES NOT EXIST PLEASE TRY AGAIN" << endl;
            }
        }
        else if(input == "11"){
            if(app.isDebugMode()){
                app.setDebugMode(false);
                cout << "debug mode is off" << endl;
            }
            else{
                app.setDebugMode(true);
                cout << "debug mode is on" << endl;
            }

        }
        else if(input == "0"){
            cout << "system is shutting down" << endl;
        }

        else{
            input = "badInput";
        }

        if(input != "badInput" && input != "0" && input != "9"){
            cout << "Press Enter to continue";
            cin.ignore();
            cin.ignore();
        }

    }
}

void pqTesting(){
    //test priority queue
    priority_queue<Patient, vector<Patient>, LessThanValue> patientQueue;
    srand(time(NULL));
    char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i=0; i < 10; i++) {
        //random string generation
        int randomLength = 1 + (rand() % 10);
        string randomString = "";
        for (int j = 0; j<randomLength; j++)
            randomString += alphabet[1 + (rand() % 52)];

        //test randomstring generation print to console
        //cout<<"RANDOMSTRING: " + randomString << endl;
        vector<string> ailments {randomString};
        //add random data to Patient
        Patient p(randomString,randomString,randomString,randomString, ailments,randomString, 1 + (rand() % 20), 1 + (rand() % 20) );

        //push to queue
        patientQueue.push(p);
    }
    //print out elements see if correct
    while (!patientQueue.empty()) {
        cout << "\nname: "+ patientQueue.top().getFirstName()<<endl;
        cout << "priority: "+ to_string(patientQueue.top().getPriority()) +"\n" <<endl;
        patientQueue.pop();
    }
}

//1: add a patient
//10: bulk add patient's from file
void addPatientTest(){
    HospitalAdministrationApp app;
    app.addFile("patients.txt");
    vector<string> ailments {"sick"};
    Patient p ("johnny", "doeesy", "amengely", "S", ailments, "Juice", false, 1);
    app.add(p);
    app.printPatients();

}

//2: treat a patient
//
void treatPatientTest(){
    HospitalAdministrationApp app;
    app.addFile("patients.txt");
    string name = app.treatPatient();
    cout << name + "has been treated";
}

//3: print a patient report
void patientReportTest(){
    HospitalAdministrationApp app;
    app.addFile("patients.txt");
    app.treatPatient();
    app.patientReport("Amy Clark Pepper 1", true);
}

//4: print out a report of all treated patients
//5: view details of next patient to be treated
//7: treat all patients
void treatAllTest(){
    HospitalAdministrationApp app;
    app.addFile("patients.txt");
    app.treatedNext();
    app.treatAll();
    app.printTreated();
}

//6: print out a report of all the patients in triage(in priority order)
//8: print out of all patients by doctor
void printByDoctorTest(){
    HospitalAdministrationApp app;
    app.addFile("patients.txt");
    app.printPatients();
    app.printByDoctor();
}

//9: print out a guide on each command in the system

void logTest(){
    HospitalAdministrationApp app;
    app.addFile("patients.txt");
    cout << "File successfully added"<< endl;
    app.patientReport("John deoue Clark 52", false);
//    app.printByDoctor();
//    app.printPatients();
//    app.treatedNext();
//    app.treatAll();
//    cout<< "All patients have been successfully treated" <<endl;
//    app.printTreated();

}

void debugTest(){
    HospitalAdministrationApp app;
    app.setDebugMode(true);
    app.addFile("patients.txt");
    app.printByDoctor();
    app.printPatients();
    app.printTreated();
    app.treatedNext();
}

void numberOnlyTest(){
    string a = "1213 4";
    cout << a << endl;
    if(numbersOnly(a)){
        cout << "NO ERROR";
    }else{
        cout << "ERROR";
    }
}

int main() {
    run();

    //TESTING
//    pqTesting();
//    addPatientTest();
//    treatPatientTest();
//    patientReportTest();
//    treatAllTest();
//    printByDoctorTest();
//    logTest();
//    debugTest();
    return 0;
}

