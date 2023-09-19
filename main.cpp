#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include "Player.h"
#include <iomanip>
using namespace std;

void printBoard(vector<vector <pair <Player *, int>>> & Board){
        cout << setw(9) << "[" << 0 << "]";// Orig: 9
        int stand_num = 8; //orig: 8
        cout << setw(0);
        for(int i = 1; i < STAND_COL; i++){
            cout << setw(stand_num) << "[" << i << "]";
        }

    cout << endl;
    for(int i = 0; i < STAND_ROW; i++){
       cout<< setw(0) << "[" << i << "]";
        for(int j = 0; j <STAND_COL; j++){
            cout<< setw(4) << "{" << Board[i][j].first -> toInt() << " " << setw(3)<< Board[i][j].second << "}";//Orig1: 4
                                                                                                                      //Orig2: 3
        }
        cout << endl<<endl;
    }
}

int main(){

    vector<vector <pair <Player *, int>>> Board;

    Player * def_player = new Player(0,0);

    int total_provinces = STAND_ROW * STAND_COL;

    cout << "Generating Game Board..." << endl;
    for(int i=0; i< STAND_ROW; i++) {
        Board.push_back(vector<pair<Player *, int>>());
        for (int j = 0; j < STAND_COL; j++) {
            Board[i].push_back(make_pair(def_player, 0));
        }
    }

    printBoard(Board);

    //Temporary Comment out to test printboard
    cout << "How many players?: " << endl;
    int num_players;
    cin >> num_players;


    //Tests to make sure there are more than two players
    while (num_players > 6){
        cout << "Error: Cannot have more than 6 Players. Reenter." << endl;
        cin >> num_players;
    }

    vector<Player> players_in_game; // This will handle player turn order and how many players there are

    for(int i = 0; i < num_players; i++){
        Player new_player(i + 1, num_players);
        players_in_game.push_back(new_player);
    }


    //Initial Deployment of Troops
    while (total_provinces > 0) {//decrementer handled in GameStartDeploy()
        for (int i = 0; i < num_players; i++) {
            players_in_game[i].GameStartDeploy(total_provinces, Board);
            if (total_provinces == 0){
                break;
            }
        }
    }

    //Full Unloading of Troops
    for (int i =0; i < num_players; i++){
        players_in_game[i].DeployTroops(Board);
    }

    players_in_game[0].TakeTurn(Board);

    printBoard(Board);

    //Main Game Loop
//    while (true){
//        for (int i = 0; i < players_in_game.size(); i++){
//            players_in_game[i].TakeTurn(Board);
//        }
//    }


}