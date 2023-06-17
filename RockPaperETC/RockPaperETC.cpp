#include <iostream>
#include <thread>
#include <string>
#include <map>
#include <mutex> 

using namespace std;

char games[100][2];
int gameCount = 100;
int player1_Wins, player2_Wins, ties;
mutex m; // Mutex for synchronization

void players(int round, int playerNum, int setup, char ranChar) {
    bool vaild = false; 

    if (setup == 1) {
        if (playerNum == 0) {
            games[round][playerNum] = 'P';
        }
        else {
            games[round][playerNum] = ranChar;
        }
    }
    else {
        while (!vaild) { // while loop to make sure user input is vaild
            m.lock(); // Locks to allow player a chance to enter value
            cout << "\nPlayer " << playerNum + 1
                << "\nS = Scissor\n"
                << "R = Rock\n"
                << "P = Paper\n"
                << "L = Lizard\n"
                << "K = Spock\n"
                << "Enter:";
            cin >> games[round][playerNum];

            games[round][playerNum] = toupper(games[round][playerNum]);

            if (games[round][playerNum] == 'S' || games[round][playerNum] == 'R' || games[round][playerNum] == 'P' || games[round][playerNum] == 'L' || games[round][playerNum] == 'K') {
                vaild = true;
                m.unlock(); // Unlocks once user input has been confirmed as a valid input
            }
            else {
                cout << "Invalid input" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discards remaining characters in input buffer
            }
        }
    }
}

void judge(int round) { // Determines the winner
    m.lock(); // Locks so it can safely change the ties, player1_Wins, player2_Wins variables

    if (games[round][0] == games[round][1]) {
        ties++;
    }
    else if (games[round][0] == 'S') {
        if (games[round][1] == 'P' || games[round][1] == 'L') {
            player1_Wins++;
        }
        else {
            player2_Wins++;
        }
    }
    else if (games[round][0] == 'R') {
        if (games[round][1] == 'S' || games[round][1] == 'L') {
            player1_Wins++;
        }
        else {
            player2_Wins++;
        }
    }
    else if (games[round][0] == 'P') {
        if (games[round][1] == 'R' || games[round][1] == 'K') {
            player1_Wins++;
        }
        else {
            player2_Wins++;
        }
    }
    else if (games[round][0] == 'L') {
        if (games[round][1] == 'K' || games[round][1] == 'P') {
            player1_Wins++;
        }
        else {
            player2_Wins++;
        }
    }
    else if (games[round][0] == 'K') {
        if (games[round][1] == 'S' || games[round][1] == 'R') {
            player1_Wins++;
        }
        else {
            player2_Wins++;
        }
    }

    m.unlock();
}

char randomChar() { // Randomly picks a letter
    int random = 1 + (rand() % 5);

    map<int, char> gameValues{
        {1, 'S'},
        {2, 'R'},
        {3, 'P'},
        {4, 'L'},
        {5, 'K'},
    };

    return gameValues[random];
}

int main() {
    int setupChoice;
    bool exit = false;
    int j = 1;

    while (!exit) {
        cout << "Select the setup (1 or 2) or enter 3 to exit: ";
        cin >> setupChoice;
        
        player1_Wins = 0;
        player2_Wins = 0;
        ties = 0;

        if (setupChoice == 1) {
            for (int i = 0; i < gameCount; i++) {
                thread player1(players, i, 0, setupChoice, randomChar());
                thread player2(players, i, 1, setupChoice, randomChar());

                player1.join();
                player2.join();

                if (j == 1) {
                    thread judge1(judge, i);
                    judge1.join();
                    j++;
                }
                else if (j == 2) {
                    thread judge2(judge, i);
                    judge2.join();
                    j++;
                }
                else {
                    thread judge3(judge, i);
                    judge3.join();
                    j = 1;
                }
            }
            cout << "\nPlayer 1 won = " << player1_Wins << endl;
            cout << "Player 2 won = " << player2_Wins << endl;
            cout << "Ties = " << ties << endl << endl;
        }
        else if (setupChoice == 2) {
            for (int i = 0; i < gameCount; i++) {
                thread player1(players, i, 0, setupChoice, 'P');
                thread player2(players, i, 1, setupChoice, 'P');

                player1.join();
                player2.join();

                if (j == 1) {
                    thread judge1(judge, i);
                    judge1.join();
                    j++;
                }
                else if (j == 2) {
                    thread judge2(judge, i);
                    judge2.join();
                    j++;
                }
                else {
                    thread judge3(judge, i);
                    judge3.join();
                    j = 1;
                }
            }
            cout << "\nPlayer 1 won = " << player1_Wins << endl;
            cout << "Player 2 won = " << player2_Wins << endl;
            cout << "Ties = " << ties << endl << endl;
        }
        else if (setupChoice == 3) {
            exit = true;
        }
        else {
            cout << "Invalid input" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discards remaining characters in input buffer
        }
    }
}
