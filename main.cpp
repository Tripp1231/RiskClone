#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include "Player.h"
using namespace std;
//REMEMBER TO FIX IF NEEDED


void printBoard(vector<vector <pair <Player *, int> > > & Board){
    // printing the col key:
    cout << " ";
    for (int i = 0; i < STAND_COL; i++){
        cout << "      " << "[" << i << "]" << "";
    }
    cout << endl;

    for (int i = 0; i < STAND_ROW; i++){
        cout << "[" << i << "]";
        for(int j = 0; j < STAND_COL; j++){
            cout << "   <" << Board[i][j].first->toInt() << "," << Board[i][j].second << "> ";
        }
        cout << endl;
    }
}

//Here begins the great change!!
int main(){

    vector<vector <pair <Player *, int> > > Board;

    Player * def_player = new Player(0,0);


    int total_provinces = STAND_ROW * STAND_COL;

    cout << "Generating Game Board..." << endl;
    for(int i=0; i< STAND_ROW; i++) {
        Board.push_back(vector<pair<Player *, int> >());
        for (int j = 0; j < STAND_COL; j++) {
            Board[i].push_back(make_pair(def_player, 0));
        }
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

    players_in_game[0].TakeTurn(Board);

    printBoard(Board);

    //Main Game Loop
//    while (true){
//        for (int i = 0; i < players_in_game.size(); i++){
//            players_in_game[i].TakeTurn(Board);
//        }
//    }


}