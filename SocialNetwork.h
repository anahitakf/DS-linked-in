#pragma once

#ifndef SOCIALNETWORK_H
#define SOCIALNETWORK_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <windows.h> 
#include "users.h"

using namespace std;



void sug(SocialNetwork& network);

class SocialNetwork {
private:
    unordered_map<int, User> users;

public:
    void registerUser(int id, const string& name, const string& familyName, int yearOfBirth,
        const string& university, const string& major, const string& jobPlace);

    void addConnection(int userId, int connectionId);

    void readFromFile(const string& filename);

    void displayUser(int userId) const;

    int bfsShortestPathLength(int startUserId, int goalUserId);

    vector<int> getTopConnections(int startUserId);
};

#endif // SOCIALNETWORK_H
