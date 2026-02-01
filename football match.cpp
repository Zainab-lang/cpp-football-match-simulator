#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

struct team {
    string name;
    int attack;
    int defence;
};

struct league {
    string name;
    vector<team> teams;
};

// random number function
int random(int min, int max) {
    int x = min + (rand() % (max - min + 1));
    return x;
}

// creating leagues
vector<league> buildleague() {
    league primier;
    primier.name = "Primier League";
    primier.teams.push_back({ "Karachi kings", 77, 80 });
    primier.teams.push_back({ "Lahore lions", 72, 79 });
    primier.teams.push_back({ "Peshawar", 77, 73 });
    primier.teams.push_back({ "Multan", 80, 71 });

    league laliga;
    laliga.name = "laliga league";
    laliga.teams.push_back({ "Qalanders", 76, 74 });
    laliga.teams.push_back({ "Qalanders 1", 77, 73 });
    laliga.teams.push_back({ "Qalanders 2", 72, 78 });
    vector<league> leagues;
    leagues.push_back(primier);
    leagues.push_back(laliga);

    return leagues;
}
// show leagues
void showleagues(const vector<league>& leagues) {
    cout << "Select league" << endl;
    for (size_t i = 0; i < leagues.size(); i++) {
        cout << i + 1 << " " << leagues[i].name << endl;
    }
}
// show teams
void showteams(const vector<team>& teams) {
    for (size_t i = 0; i < teams.size(); i++) {
        cout << i + 1 << " " << teams[i].name << endl;
    }
}
// select league
league slectleagues(const vector<league>& leagues) {
    int leaguenum = leagues.size();
    while (true)
    {
        showleagues(leagues);
        int n;
        cin >> n;
        if (n >= 1 && n <= leaguenum)
        {
            return leagues[n - 1];
        }
        else {
            cout << "Invalid Sorry! try again choose between 1 to " << leaguenum << endl;
        }
    }
}
// select team
team slectteam(const league& selectedleague) {
    int teamnum = selectedleague.teams.size();
    while (true)
    {
        cout << "---Available Teams----" << endl;
        showteams(selectedleague.teams);
        int m;
        cin >> m;
        if (m >= 1 && m <= teamnum) {
            return selectedleague.teams[m - 1];
        }
        else {
            cout << "Invalid Sorry! try again choose between 1 to " << teamnum << endl;
        }
    }
}

// select opponent
team slectoponent(const league& selectedleague, int userindex) {
    int opponentindex;
    do {
        opponentindex = random(0, selectedleague.teams.size() - 1);
    } while (opponentindex == userindex);

    return selectedleague.teams[opponentindex];
}

// select difficulty
int slectdifficulty() {
    cout << "Select difficulty level" << endl;
    cout << "1. Easy" << endl;
    cout << "2. Normal" << endl;
    cout << "3. Difficulty" << endl;
    int diff;
    cin >> diff;
    return diff;
}
// match start
void matchstart(team user, team opponent, int difficulty) {
    int usergoals = 0;
    int oponentgoals = 0;
    int userpower = user.attack;
    int oponentpower = opponent.attack;
    if (difficulty == 1) {
        userpower += 10;
    }
    else if (difficulty == 3) {
        oponentpower += 10;
    }
    cout << "_______Match start!________  " << endl;
    cout << "   1. Kickoff Game begins" << endl;
    vector<string> players = { "player 1", "player 2", "player 3", "player 4", "player 5" };

    for (int min = 3; min <= 90; min += random(3, 8)) {
        bool userattack = random(0, 1);

        if (userattack) {
            cout << min << " - " << user.name << " attempts a shot";
            int chance = random(0, 100);

            if (chance < userpower - opponent.defence) {
                cout << " Goal (" << players[random(0, 4)] << ")" << endl;
                usergoals++;
            }
            else if (chance < 70) {
                cout << " Saved" << endl;
            }
            else {
                cout << " Missed" << endl;
            }
        }
        else {
            cout << min << " - " << opponent.name << " attacks";
            int chance = random(0, 100);
            if (chance < oponentpower - user.defence) {
                cout << "  Goal (" << players[random(0, 4)] << ")" << endl;
                oponentgoals++;
            }
            else if (chance < 70) {
                cout << "  Saved by the Goalkeeper!" << endl;
            }
            else {
                cout << "  Offside" << endl;
            }
        }
        if (min == 45) {
            cout << "45 - Half time whistle" << endl;
            cout << "Second half begins" << endl;
        }
    }
    cout << "Full time whistle" << endl;
    cout << "Final score = " << user.name << " " << usergoals
        << " - " << opponent.name << " " << oponentgoals << endl;
    cout << "Man of the match = " << players[random(0, 4)] << endl;
}
int main() {
    srand(time(0));
    cout << "=== WELCOME TO FOOTBALL SIMULATOR ===" << endl;
    vector<league> leagues = buildleague();

    league selectedleague = slectleagues(leagues);
    cout << "You selected = " << selectedleague.name << endl;

    team userteam = slectteam(selectedleague);
    int userindex = -1;

    for (size_t i = 0; i < selectedleague.teams.size(); i++) {
        if (selectedleague.teams[i].name == userteam.name) {
            userindex = i;
            break;
        }
    }
    if (userindex != -1) {
        // team found
    }
    else {
        // team not found
    }
    team oponentteam = slectoponent(selectedleague, userindex);

    cout << "Your team: " << userteam.name << endl;
    cout << "Opponent team: " << oponentteam.name << endl;

    int difficulty = slectdifficulty();
    matchstart(userteam, oponentteam, difficulty);

    return 0;
}
