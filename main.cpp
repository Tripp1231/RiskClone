#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include "Player.h"
using namespace std;


int main(){
    //Do we need this to by dynamically allocated or can this just be handled by vectors?
    pair <int, Player> ** Board_player;
    pair <int,int> ** Board;
    int total_provinces = STAND_ROW * STAND_COL;

    cout << "Generating Game Board..." << endl;
    Board = new pair<int, int> * [STAND_ROW];
    for(int i = 0; i < STAND_ROW; i++){
        Board[i] = new pair<int, int> [STAND_COL];
    }

    printBoard(Board);

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

    //Main Game Loop
    while (true){//This is gonna change, much more concrete game ending cons
        for (int i = 0; i < players_in_game.size(); i++){
            players_in_game[i].TakeTurn(Board);
        }

    }


}