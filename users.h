#include"SocialNetwork.h"
#pragma once
class User {
public:
    int id;
    string name;
    string familyName;
    int yearOfBirth;
    string university;
    string major;
    string jobPlace;
    vector<int> connections;

    User(int id, string name, string familyName, int yearOfBirth, string university, string major, string jobPlace)
        : id(id), name(name), familyName(familyName), yearOfBirth(yearOfBirth), university(university), major(major), jobPlace(jobPlace) {}

    void addConnection(int connectionId) {
        connections.push_back(connectionId);
    }

    User() : id(0), name(""), familyName(""), yearOfBirth(0), university(""), major(""), jobPlace("") {}

    void displayProfile() const {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Year of Birth: " << yearOfBirth << endl;
        cout << "University: " << university << endl;
        cout << "Major: " << major << endl;
        cout << "Job Place: " << jobPlace << endl;
        cout << "Connections: ";
        for (const auto& connection : connections) {
            cout << connection << " ";
        }
        cout << endl;
    }
};