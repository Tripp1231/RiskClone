#include <iostream>
#include <sstream>
#include <string>
#include "Player.h"

using namespace std;

#include <utility>

/*printBoard(int row, int col, pair<int, int> ** Board){...} is placed into Player.h*/
//void printBoard(int row, int col, pair<int, int> ** Board){
//    // printing the col key:
//    cout << " ";
//    for (int i = 0; i < col; i++){
//        cout << "   " << "[" << i << "]" << "";
//    }
//    cout << endl;
//
//    for (int i = 0; i < row; i++){
//        cout << "[" << i << "]";
//        for(int j = 0; j < col; j++){
//            cout << "  " << Board[i][j].first << "   ";
//        }
//        cout << endl;
//    }
//}


//Iteration 2: Simplify, make a 2D matrix that just contains pairs, the first containing which Player Occupies
//and the second contains the amount of troops,
int main(){
    pair <int, Player> ** Board_player;
    pair <int,int> ** Board;
    int total_provinces = STAND_ROW * STAND_COL;
////IDEAS: WORK OFF A COIN FLIPPING SYSTEM
////    IF ATTACKER HAS 16 TROOPS BUT DEFENDER HAS 8 WE FLIP 16 TIMES FOR ATTACKER TO WIN
////    IMPASSABLE TERRAIN
////    FOG OF WAR!?!?!?!!?
////TO DO: IMPLEMENT LOSING AND WINNING
////TO DO: IMPLEMENT THE CARD SYSTEM
////    FOR TRACKING WHICH PROVINCES YOU OWN:
////    SHOULD WE ACTUALLY MAKE IT THAT THE .first OF EACH PAIR IS THE OBJECT OF THE PLAYER?
////    COULD WORK OUT FINE WITH PRINTING. ALREADY HAVE A TO STRING METHOD FOR IT
////    IF THIS IS THE CASE, WE NEED TO CHANGE THE PRINT BOARD FUNCTION AND HOW THE .first IS CHANGED



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


    int player_in_row;
    int player_in_col;
    cout << "Force Check Troop Counts" << endl;
    cin >> player_in_row >> player_in_col;

    while(player_in_row != 20 && player_in_col != 20){
        cout << "Troops at [" << player_in_row << "] [" << player_in_col << "]: " << Board[player_in_row][player_in_col].second << endl;
        cin >> player_in_row >> player_in_col;

    }

    cout << "Thanks for playing!"<< endl;



}






//Iteration 1 of making the Gameboard an object, doesnt work too well
//int main() {
//    cout << "How many players?: ";
//    int num_players;
//    cin >> num_players;
//    vector<Player> players_in_game; // This will handle player turn order and how many players there are
//
//    for(int i = 0; i < num_players; i++){
//        Player new_player(i, num_players);
//        players_in_game.push_back(new_player);
//    }
//
//
//    GameBoard * game_rnr = new GameBoard(STAND_ROW, STAND_COL);
//    int none;
//
//
//    int total_provinces = STAND_COL * STAND_ROW;
//
//    while (total_provinces > 0){
//        for(int i = 0; i < players_in_game.size(); i++){
//            cout<< "Player #" << players_in_game[i].toString() << ", Place 1 Troop at Unoccupied Province" << endl;
//            //Need To redo this logic, GameStartDeploy is a bool operator, make sure
//            //players_in_game[i].GameStartDeploy( game_rnr, total_provinces, int row, int col); //PlaceTroop to be implemented later, needs to be inserted by reference
//        }
//        total_provinces -= 1; //Placeholder decrement, will be handled in GameStartDeploy() in actual implementation
//    }
//
//    for(int i =0; i < players_in_game.size(); i++){
//        cout << "Player #" << players_in_game[i].toString() << ", Place Remaining Troops at Owned Province";
//        //players_in_game[i].DeployTroops(); EmptyOUtTroop to be implemented later
//    }
//
//
//    // Main game loop:
//    while (players_in_game.size() > 1){
//        for(int i=0; i < players_in_game.size(); i++){
//            players_in_game[i].TakeTurn();
//            cout << "Wait";
//            cin >> none;
//        }
//        cout<<endl;
//        players_in_game.pop_back();
//    }
//
//
//
//
//}
