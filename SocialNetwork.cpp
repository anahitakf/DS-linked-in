// SocialNetwork.cpp

#include "SocialNetwork.h"

void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void sug(SocialNetwork& network) {
    int targetUserId;
    system("cls");
    SetColor(14);
    cout << "\n\x1b[1m\x1b[36m\x1b[5m  SUGGESTIONS\n";
    cout << "-----------\n\x1b[0m";
    cout << "\x1b[36mID: \x1b[0m";
    cin >> targetUserId;

    vector<int> bestConnections = network.getTopConnections(targetUserId);

    cout << "Best Connections for User " << targetUserId << ":" << endl;
    for (int userId : bestConnections) {
        network.displayUser(userId);
        cout << endl;
    }
}


void SocialNetwork::registerUser(int id, const string& name, const string& familyName, int yearOfBirth,
    const string& university, const string& major, const string& jobPlace) {
    users[id] = User(id, name, familyName, yearOfBirth, university, major, jobPlace);
}

void SocialNetwork::addConnection(int userId, int connectionId) {
    if (users.find(userId) != users.end() && users.find(connectionId) != users.end()) {
        const User& user1 = users[userId];
        const User& user2 = users[connectionId];

        int ageUser1 = 2024 - user1.yearOfBirth;
        int ageUser2 = 2024 - user2.yearOfBirth;

        if ((ageUser1 < 18 && ageUser2 > 18) || (ageUser1 > 18 && ageUser2 < 18)) {
            cerr << "Error: Users have age mismatch. Connection not allowed." << endl;
        }
        else {
            users[userId].addConnection(connectionId);
        }
    }
    else {
        cerr << "Error: User ID " << userId << " or connection ID " << connectionId << " not found." << endl;
    }
}

void SocialNetwork::readFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.find("ID: ") == 0) {
            int id = stoi(line.substr(4));

            getline(file, line);
            string fullName = line.substr(6);
            size_t spacePos = fullName.find_last_of(' ');
            string name = fullName.substr(0, spacePos);
            string familyName = fullName.substr(spacePos + 1);

            getline(file, line);
            int yearOfBirth = stoi(line.substr(15));

            getline(file, line);
            string university = line.substr(12);

            getline(file, line);
            string major = line.substr(7);

            getline(file, line);
            string jobPlace = line.substr(10);

            registerUser(id, name, familyName, yearOfBirth, university, major, jobPlace);

            getline(file, line);
            if (line.find("Connections: ") == 0) {
                string connections = line.substr(13);
                istringstream ss(connections);
                string connection;
                while (getline(ss, connection, ',')) {
                    addConnection(id, stoi(connection));
                }
            }
        }
    }

    file.close();
}

void SocialNetwork::displayUser(int userId) const {
    auto it = users.find(userId);
    if (it != users.end()) {
        const User& user = it->second;
        cout << "ID: " << user.id << endl;
        cout << "Name: " << user.name << endl;
        cout << "Year of Birth: " << user.yearOfBirth << endl;
        cout << "University: " << user.university << endl;
        cout << "Major: " << user.major << endl;
        cout << "Job Place: " << user.jobPlace << endl;
        cout << "Connections: ";
        for (int conn : user.connections) {
            cout << conn << " ";
        }
        cout << endl;
    }
    else {
        cerr << "User with ID " << userId << " not found." << endl;
    }
}

int SocialNetwork::bfsShortestPathLength(int startUserId, int goalUserId) {
    queue<int> q;
    unordered_set<int> visited;
    unordered_map<int, int> distance;

    q.push(startUserId);
    visited.insert(startUserId);
    distance[startUserId] = 0;

    while (!q.empty()) {
        int currentUserId = q.front();
        q.pop();

        if (currentUserId == goalUserId) {
            return distance[currentUserId];
        }

        for (int neighborId : users[currentUserId].connections) {
            if (visited.find(neighborId) == visited.end()) {
                visited.insert(neighborId);
                q.push(neighborId);
                distance[neighborId] = distance[currentUserId] + 1;
            }
        }
    }

    return -1;
}




vector<int> SocialNetwork::getTopConnections(int startUserId) {
    const int universityWeight = 3;
    const int majorWeight = 4;
    const int jobPlaceWeight = 2;
    const int degreeOfConnectionWeight = 1;

    vector<pair<int, int>> userPriorities;
    unordered_set<string> engineeringMajors = { "Mechanical Engineer", "Electrical Engineer", "Computer Engineer" };
    unordered_set<string> medicineMajors = { "Medicine", "Biology", "Chemistry" };

    for (auto& entry : users) {
        int userId = entry.first;
        const User& user = entry.second;

        int priority = 0;
        if (user.university == users[startUserId].university) {
            priority += universityWeight;
        }
        if (user.major == users[startUserId].major) {
            priority += majorWeight;
        }
        else if (engineeringMajors.count(user.major) > 0 && engineeringMajors.count(users[startUserId].major) > 0) {
            priority += 2;
        }
        else if (medicineMajors.count(user.major) > 0 && medicineMajors.count(users[startUserId].major) > 0) {
            priority += 2;
        }

        if (user.jobPlace == users[startUserId].jobPlace) {
            priority += jobPlaceWeight;
        }
        int degreeOfConnection = bfsShortestPathLength(startUserId, userId);
        if (degreeOfConnection != -1) {
            priority += degreeOfConnectionWeight * (3 - degreeOfConnection);  // Inverse weighting for shorter paths
        }

        userPriorities.emplace_back(userId, priority);
    }

    sort(userPriorities.begin(), userPriorities.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
        });

    vector<int> topConnections;
    for (const auto& pair : userPriorities) {

    }
}