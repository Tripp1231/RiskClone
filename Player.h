//
// Created by Tripp Peterson on 5/22/23.
//

#ifndef RISKCLONE_PLAYER_H
#define RISKCLONE_PLAYER_H

using namespace std;
#include <stdlib.h>
#include <vector>
#include <set>
#include <unordered_set>
const int STAND_ROW = 4;
const int STAND_COL = 4;


class Player{

private:

    void printBoard(vector<vector <pair <Player *, int> > > & Board) const{
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

    void CollectTroops(){
        if (my_pairs.size() / 3 > BASE_TROOP_INCOME ){
            troop_deploy += (my_pairs.size() /3);
        }
        else {
            troop_deploy += BASE_TROOP_INCOME;
        }
    }

    bool CheckIfTargetIsUnoccupied(int check_row, int check_col, vector<vector <pair <Player *, int> > > & Board) const {
        if(Board[check_row][check_col].first->toInt() == 0){
            return true;
        }
        return false;
    }

    bool CheckIfSingleAllied(int player_row, int player_col, vector<vector <pair <Player *, int> > > & Board) const {
        if(Board[player_row][player_col].first == this){
            return true;
        }
        return false;
    }

    bool CheckAdjacency(int row_1, int col_1, int row_2, int col_2) const{
        //North Movement
        if(   (((row_1 - 1)== row_2) && (col_1 == col_2))
              //South Movement
              || (((row_1 + 1) == row_2) && (col_1 == col_2))
              //East Movement
              || ((row_1 == row_2) && ((col_1 + 1) == col_2))
              //West Movement
              || ((row_1 == row_2) && ((col_1 - 1) == col_2)))
        {
            return true;
        }
        return false;
    }

    bool CheckIfBothOwner(int player_row, int player_col, int check_row, int check_col, vector<vector <pair <Player *, int> > > & Board) const {
        //you can use this to both check if it's an "allied" province or if it's an enemy province
        //Useful for Phase 3 of fortifying
        if(Board[player_row][player_col].first == Board[check_row][check_col].first){
            return true;
        }
        return false;
    }

    bool CheckEnoughTroops(int attacker_troop, int defender_troop) const {
        if (attacker_troop > 2 && (attacker_troop - defender_troop > 2)){
            return true;
        }
        cerr << "There are not enough troops to attack." << endl;
        return false;
    }
//THIS IS BUGGED HOLY
    bool CheckIfExistingPath(int first_row, int first_col, int second_row, int second_col, vector<vector <pair <Player *, int> > > & Board){
        //Cant reinforce to the same exact province
        //check CheckIfBothOwner()
        //Make more efficient just by checking to see if theyre directly adjacent first


        if(!CheckIfValid(first_row, first_col, second_row, second_col)){
            cout << "Some of the coordinates may be invalid." << endl;
            return false;
        }

        if (!CheckIfBothOwner(first_row, first_col, second_row, second_col, Board)){
            cout << "You cannot fortify to an enemy province." << endl;
            return false;
        }
        if (first_row == second_row && first_col == second_col){
            cout << "You cannot fortify to the same province." << endl;
            return false;
        }
        if (CheckAdjacency(first_row, first_col, second_row, second_col)){
            return true;
            //Allows for a very quick initial check to see if its even necessary to recurse
        }
        else {
            bool flag = false;
            return CheckPathHelper(first_row, first_col, second_row, second_col, flag, Board);
        }
    }

//THESE ARE BUGGED
//WE GOTTA DECONSTRUCT THE BOARD AT THE END!!!!!
    bool CheckPathHelper(int cur_row, int cur_col,  int second_row, int second_col, bool & flag, vector<vector <pair <Player *, int> > > Board){

        if (flag){
            cout << "flag case hit!" << endl;
            return true;
        }

        //Preliminary Check to make sure that coords are even valid
        if(!CheckIfValid(cur_row, cur_col)){ //||Board[cur_row][cur_col].second == TEMP){
            return false;
        }

        if (Board[cur_row][cur_col].second == TEMP || Board[cur_row][cur_col].second == PATH){
            return false;
        }

        //Makes sure that we aren't recursing off of enemy provinces
        if(!CheckIfSingleAllied(cur_row, cur_col, Board)){
            return false;
        }

        //This condition is reached if we have found a route!
        if(cur_row == second_row && cur_col == second_col){
            flag = true;
            return true;
        }

        //need to pass in the board because we dont want to call this on provinces that aren't owned

        Board[cur_row][cur_col].second = PATH;
        if(CheckPathHelper(cur_row - 1, cur_col, second_row, second_col, flag, Board)
           || CheckPathHelper(cur_row + 1, cur_col, second_row, second_col, flag, Board)
           || CheckPathHelper(cur_row, cur_col - 1, second_row, second_col, flag, Board)
           || CheckPathHelper(cur_row, cur_col + 1, second_row, second_col, flag, Board)){
            Board[cur_row][cur_col].second = PATH;
            return true;
        }
        else{
            Board[cur_row][cur_col].second = TEMP;
            return false;
        }
    }

    bool ValidTroopMove(int row_1, int col_1, int amount, vector<vector <pair <Player *, int> > > Board) const{
        if (amount > (Board[row_1][col_1].second - 1)){
            return false;
        }
        return true;
    }

    //Gotta redo at least the overloaded CheckIfValid
    //Ahhh we have a discrepency between how the check if valids actually work...standardize
    bool CheckIfValid(int row, int col){
        if ( (row < STAND_ROW && row >= 0 ) && (col < STAND_COL && col >= 0) ){
            return true;
        }
        return false;
    }

    bool CheckIfValid(int row, int col, int e_row, int e_col){
        if (  (row < STAND_ROW && row >= 0 ) && (col < STAND_COL && col >= 0)
              && (e_row < STAND_ROW && e_row >= 0) && (e_col < STAND_COL && e_col >= 0)  ){
            return true;
        }
        return false;

    }


    int const BASE_TROOP_INCOME = 3;

public:
    int player_num = 0;
    int troop_deploy = 35;
    unordered_set<pair <Player, int> *> my_pairs;
    const int PATH = -10;
    const int TEMP = -20;


    Player(int player_slot=0, int player_count=0){//int faction
        player_num = player_slot;
        //faction_choice = faction;
        for (int i = 3; i < player_count; i++){
            troop_deploy -= 5;
        }
        if (player_count == 0){
            troop_deploy = 0;
        }
    }

    ~Player(){}

    bool operator==(Player &rhs){
        if (this == &rhs){
            return true;
        }
        return false;
    }


    int toInt() const {
        return player_num;
    }

    string toString() const{
        stringstream ss;
        ss << "Player #" << player_num;// << ", Faction Choice: " << faction_choice;
        return ss.str();
    }

    void GameStartDeploy(int & total_provinces, vector<vector <pair <Player *, int> > > & Board){
        bool deployment = true;
        int player_row;
        int player_col;
        while (deployment) {

            cout << "Player #" << player_num << " place 1 troop." << endl;
            cout << "Input the coordinates in Row Column form Ex: 1 2 " << endl;
            cin >> player_row >> player_col;

            if (CheckIfValid(player_row, player_col) && CheckIfTargetIsUnoccupied(player_row, player_col, Board)) {
                //If the Province targeted is unoccupied
                Board[player_row][player_col].first = this;
                Board[player_row][player_col].second += 1;
                troop_deploy--;
                total_provinces--;
                deployment = false;
            } else {
                cout << "Error: The Targeted Province is already occupied. Reselect your Coordinates" << endl;
                cin >> player_row >> player_col;
            }
        }
        printBoard(Board);
    }

    void TakeTurn(vector<vector <pair <Player *, int> > > & Board){
        CollectTroops();

        //Deploying Troops
        DeployTroops(Board);

        //Attacking Enemy Provinces
        PlayerAttack(Board);

        //Fortifying Allied Provinces
        PlayerFortify(Board);

        printBoard(Board);

        cout<< "End of Player #" << player_num <<"'s turn." << endl;
    }

    void DeployTroops(vector<vector <pair <Player *, int> > > & Board){
        int player_in_row;
        int player_in_col;
        int player_in_troops;
        while (troop_deploy > 0){

            cout << "Player #"<< player_num << ", Place the rest of your troops." << endl;
            cout << "Place them by listing coordinates and then troop count. Ex: 1 2 6."<< endl;
            cout <<"Remaining troops: " <<  troop_deploy << endl;
            cin >> player_in_row >> player_in_col >> player_in_troops;

            while (player_in_troops <= 0) {
                cout << "Please enter a valid number of troops Ex: 3" << endl;
                cin >> player_in_troops;
            }


            if(CheckIfValid(player_in_row, player_in_col) &&
               CheckIfSingleAllied(player_in_row, player_in_col, Board)){

                if (player_in_troops > troop_deploy){//Case to make sure not negative
                    Board[player_in_row][player_in_col].second += troop_deploy;
                    troop_deploy = 0;
                    return;
                }
                else {
                    troop_deploy -= player_in_troops;
                    Board[player_in_row][player_in_col].second += player_in_troops;
                }

            }

                //case if player did not choose an allied province
            else{
                cout << "Error: Enter the correct coordinates of a province you own. Ex: 1 2 6."<< endl;
            }

        }

        //printBoard(Board);

    }

    void PlayerAttack(vector<vector <pair <Player *, int> > > & Board){
        int player_choice;
        int player_row;
        int player_col;
        int enemy_row;
        int enemy_col;

        cout << "Player #"<< player_num << ", Attack [1] or End Attack Phase [3]" << endl;
        cin >> player_choice;
        while (player_choice == 1) {
            cout << "Attack by selecting your province first. Ex: 1 2." << endl;
            cin >> player_row >> player_col;
            cout << "Now select an adjacent enemy province. Ex: 1 3" << endl;
            cin >> enemy_row >> enemy_col;
            //Check these if statements
            if(CheckIfValid(player_row, player_col, enemy_row, enemy_col)
               && !CheckIfBothOwner(player_row, player_col, enemy_row, enemy_col, Board)
               && CheckAdjacency(player_row, player_col, enemy_row, enemy_col)
               && CheckEnoughTroops(Board[player_row][player_col].second, Board[enemy_row][enemy_col].second)){

                int left_over_troop = Board[player_row][player_col].second - Board[enemy_row][enemy_col].second;

                Board[player_row][player_col].second = 1;

                Board[enemy_row][enemy_col].second = left_over_troop - 1;

                Board[enemy_row][enemy_col].first = this;

                cout << "Player #" << player_num << " has taken over [" << enemy_row << "] [" << enemy_col << "]!" << endl;
                //printBoard(Board);


            }
            else {
                cout << "Please select new provinces." << endl;
            }

            cout << "Player #"<< player_num << ", Attack [1] or End Turn [3]" << endl;
            cin >> player_choice;

        }


        //Figure out how to clear the terminal
        //"End of Player player_num turn"
        //clear()
        printBoard(Board);


    }

    void PlayerFortify(vector<vector <pair <Player *, int> > > & Board){
//// ACTUALLY IMPLEMENT THIS
        int row_1;
        int col_1;
        int row_2;
        int col_2;
        int amount;
        int player_choice;

        cout << "Player #"<< player_num << ", Fortify [1] or End Fortify Phase [3]" << endl;
        cin >> player_choice;

        while(player_choice == 1) {
            cout << "Please select two provinces that you own and are connected to fortify. Ex. 1 1 3 1"<< endl;
            cin >> row_1 >> col_1 >> row_2 >> col_2;

            if (CheckIfExistingPath(row_1, col_1, row_2, col_2, Board)) {
                cout << "Choose the amount of troops you want to move." << endl;
                cout << "(You must leave 1 troop at the first province.)" << endl;
                cin >> amount;

                if (ValidTroopMove(row_1, col_1, amount, Board)){
                    Board[row_2][col_2].second += amount;
                    Board[row_1][col_1].second -= amount;
                }
                else{
                    Board[row_2][col_2].second += (Board[row_1][col_1].second - 1);
                    Board[row_1][col_1].second = 1;
                }
                player_choice = -1;
            }
            else {
                cout << "There does not exist a path between those provinces or another error occurred." << endl;
            }
        }
    }

};





#endif RISKCLONE_PLAYER_H