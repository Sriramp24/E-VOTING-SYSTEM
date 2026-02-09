#include <iostream>
#include <string>
using namespace std;

// ------------------ Constants -------------------
const int MAX_VOTES = 100;

// ------------------ Vote Structure -------------------
struct Vote {
    string voterID;
    string vote;
    string hash;
};

// ------------------ Global Variables -------------------
Vote votes[MAX_VOTES];
int voteCount = 0;
string prevHash = "0";

// ------------------ Simple Hash Function -------------------
string simpleHash(const string &data) {
    long long hash = 0;
    for (char c : data) {
        hash = (hash * 31 + c) % 100000;
    }
    return to_string(hash);
}

// ------------------ Validation Functions -------------------
bool isValidVoterID(const string &id) {
    for (char c : id)
        if (!isdigit(c)) return false; // only digits allowed
    return true;
}

bool isValidPartyName(const string &name) {
    for (char c : name)
        if (!isalpha(c)) return false; // only letters allowed
    return true;
}

// ------------------ Functions -------------------
void castVote() {
    if (voteCount >= MAX_VOTES) {
        cout << "Vote limit reached!\n";
        return;
    }

    string voterID, voteName;

    // --- Voter ID input ---
    while (true) {
        cout << "Enter Voter ID (numbers only): ";
        cin >> voterID;
        if (isValidVoterID(voterID)) break;
        cout << "Invalid Voter ID! Use numbers only.\n";
    }

    // --- Party Name input ---
    while (true) {
        cout << "Vote (Party Name - letters only): ";
        cin >> voteName;
        if (isValidPartyName(voteName)) break;
        cout << "Invalid Vote! Use letters only.\n";
    }

    // --- Cast vote ---
    string hash = simpleHash(voterID + voteName + prevHash);
    votes[voteCount] = {voterID, voteName, hash};
    prevHash = hash;
    voteCount++;
    cout << "Vote casted successfully!\n";
}

void showVotes() {
    cout << "\n#\tVoterID\tVote\tHash\n";
    for (int i = 0; i < voteCount; i++) {
        cout << i + 1 << "\t" << votes[i].voterID << "\t" 
             << votes[i].vote << "\t" << votes[i].hash << "\n";
    }
}

void tamperVote() {
    if (voteCount >= 2) {
        votes[1].vote = "HackedVote"; // change 2nd vote
        cout << "Tampered 2nd vote to 'HackedVote'\n";
    } else {
        cout << "Need at least 2 votes to tamper.\n";
    }
}

void verifyVotes() {
    string hash = "0";
    bool valid = true;
    for (int i = 0; i < voteCount; i++) {
        string expected = simpleHash(votes[i].voterID + votes[i].vote + hash);
        if (expected != votes[i].hash) {
            valid = false;
            break;
        }
        hash = votes[i].hash;
    }
    if (valid) cout << "All votes are verified. No tampering detected.\n";
    else cout << "Verification failed! Tampering detected!\n";
}

// ------------------ Main Menu -------------------
int main() {
    int choice;
    while (true) {
        cout << "\n===== E-Voting System =====\n";
        cout << "1. Cast Vote\n2. Show Votes\n3. Verify Votes\n4. Tamper 2nd Vote\n5. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1: castVote(); break;
            case 2: showVotes(); break;
            case 3: verifyVotes(); break;
            case 4: tamperVote(); break;
            case 5: return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}
