#pragma once


#include <iostream>

#include <string>
#include "deck.h"
#include "player.h"
#include "compare_funcs.h"
#include <algorithm>
#include <map>


// TODO: deck -> shuffle_deck seed, Need to work on the cin input, looks like it was all wrong.
bool _input_is_valid(char c, string range);
void _setting_human_player_in_schedule(Player* schedule[], int number_of_players, int human_no);
int _human_player_phase(Player* schedule[], Player &human_player, Deck &main_deck, Deck &discard_pile, int &cheats);
void _print_all_computer_hands(Player* schedule[]);


void _ready_for_new_match(Player* schedule[], Deck& main_deck, Deck& discard_pile, int &turn);
void _ready_for_new_game(Player* schedule[], Deck& main_deck, Deck& discard_pile, int& turn, int& round, int& difficulty, int& cheats);

//using namespace std;

int main() {
    string welcome_speech = "Welcome to the game \n";    
    
    string input_error = "Invalid Input, Please Input again";

    string input;

    Deck main_deck(true);
    Deck discard_pile(false);

    Player player_1("1", 1);
    Player player_2("2", 2);
    Player player_3("3", 3);
    Player player_4("4", 4);
    
    
    int turn = 0;
    int round = 1;

    int no_of_players = 0;
    int human_player_no = 0;
    int difficulty = 1;
    int cheats = 1;
    int human_is_quitting = 0;
    Player* current_player_ptr = NULL;
    int winner_index = 0;
    int points = 0;
    int wager = 0;


    Player* players_turn_schedule[4] = {&player_1, &player_2, &player_3, &player_4};

    main_deck._shuffle_deck();
    //main_deck._print_deck();
	
Start_Of_Game:
    cout << welcome_speech;



Number_Of_Computer_Players_Phase:
    cout << "How many Computer Players?" << endl;
    cin >> input;
    if (input.size() == 2 && _input_is_valid(input.at(0), "123") == true ) {
        cerr << input_error << endl;
        goto Number_Of_Computer_Players_Phase;
    }
    

    no_of_players = int(input.at(0) - '0') + 1;
    cout << no_of_players << endl;

Select_Human_Player:
    cout << "Which Player do you want to be? This will last till the entire game is over" << endl;
    cin >> input;
    if (input.size() == 2 && (int(input.at(0) - '0') >= 1) && (int(input.at(0) - '0') <= no_of_players)  ) {
        human_player_no = int(input.at(0) - '0');
    }
    else {
        cerr << "Invalid Input" << endl;
        goto Select_Human_Player;
    }

Enable_Cheats:
    cout << "Do you want to enable cheats? 1: Default(no cheats) 2: Print Opponents' Hands during your turn 3:Print Deck during your turn 4:Combination of 2 and 3" << endl;

    getline(cin, input);
    if (input.size() == 2 && _input_is_valid(input.at(0), "1234") ) {
        cheats = int(input.at(0) - '0');
    }
    else {
        cerr << "Invalid Input" << endl;
        goto Enable_Cheats;
    }

    _setting_human_player_in_schedule(players_turn_schedule, no_of_players, human_player_no);

    //loop to be made while deck not empty
    //new_deck._is_deck_empty() == false
Game_Match_Phase:
    while (false) {
        cout << "Turn " << turn << ": ";
        current_player_ptr = players_turn_schedule[turn % no_of_players];
        if (current_player_ptr->_player_is_playing() == true) {
            if (current_player_ptr->_player_is_human() == true) {
                human_is_quitting = _human_player_phase(players_turn_schedule, *(current_player_ptr), main_deck, discard_pile, cheats);
            }
            else {
                //_computer_player_phase(players_turn_schedule, *(current_player_ptr), main_deck, discard_pile, difficulty);
            }
            
        }
        else {
            cerr << "Error in Player schedule and phase";
        }
        


        if (human_is_quitting == 0) {
            points = points - wager;
            goto Quit_Phase;
        }



        turn = turn + 1;
    }

    //Evaluation_phase

    winner_index = evaluate_winner(players_turn_schedule, no_of_players);

    cout << "Player " << players_turn_schedule[winner_index]->_get_player_name() << "won!";

    if (players_turn_schedule[winner_index]->_player_is_human() == true ) {
        points = points + wager;
    }
    else{
        points = points - wager;
    }

Quit_Phase:
    human_is_quitting = 0;
    cout << "Points: " << points << endl;

    if (points > 0) {
        cout << "The match is over. Do you want to 1: Continue in a new match 9:New Game  0:Quit" << endl;
        getline(cin, input);
        if (input.size() == 2 && _input_is_valid(input.at(0), "019")) {
            switch (int(input.at(0))) {
                case 1:
                    _ready_for_new_match(players_turn_schedule, main_deck, discard_pile, turn);
                    goto Game_Match_Phase;
                case 9:
                    _ready_for_new_game(players_turn_schedule, main_deck, discard_pile, turn, round, difficulty, cheats);
                    goto Start_Of_Game;
                case 0:
                    return 0;
            }
        }
        else {
            cout << "Invalid Input" << endl;
            goto Quit_Phase;
        }
        
    }
    else {
        cout << "Game Over, your points = 0. Do you want to 1: New Game or 0: Quit" << endl;
        getline(cin, input);
        if (input.size() == 2 && _input_is_valid(input.at(0), "01" )) {
            switch (int(input.at(0))) {
            case 1:
                _ready_for_new_game(players_turn_schedule, main_deck, discard_pile, turn, round, difficulty, cheats);
                goto Start_Of_Game;
            case 0:
                return 0;

            default:
                cout << "Error in Quit Phase" << endl;
                    goto Quit_Phase;

            }
        }
        else {
            cout << "Invalid Input" << endl;
            goto Quit_Phase;
        }
    }


    return 0;
}


void _ready_for_new_match(Player* schedule[], Deck &main_deck, Deck &discard_pile, int &turn) {
    //reset variables to get ready for new match 
    for (int i = 0; i < sizeof(schedule); i++) {
        schedule[i]->_access_hand().clear();
        schedule[i]->_get_memo().clear();
    }

    turn = 0;

    main_deck._clear_deck();
    main_deck._fill_up_deck();
    discard_pile._clear_deck();

}

void _ready_for_new_game(Player* schedule[], Deck &main_deck, Deck &discard_pile, int &turn, int &round, int &difficulty, int &cheats) {
    for (int i = 0; i < sizeof(schedule); i++) {
        schedule[i]->_set_name( to_string(i + 1) );
        schedule[i]->_access_hand().clear();
        schedule[i]->_get_memo().clear();
        schedule[i]->_set_player_to_human(false);
        schedule[i]->_set_player_to_playing(false);
    }

    turn = 0;
    round = 1;
    difficulty = 1;
    cheats = 1;

    main_deck._clear_deck();
    main_deck._fill_up_deck();
    discard_pile._clear_deck();
}


int _human_player_phase(Player* schedule[], Player &human_player, Deck &main_deck, Deck &discard_pile, int &cheats) {
    string input;

    switch (cheats) {
        case 2:
            _print_all_computer_hands(schedule);

        case 3:
            main_deck._print_deck();

        case 4:
            _print_all_computer_hands(schedule);
            main_deck._print_deck();
            
    }

    human_player._draw_card(1, main_deck);
    human_player._print_hand();

Player_Phase_Options:
    cout << "What would you want to do? Options etc" << endl;
    getline(cin, input);
    if (input.size() == 2 && _input_is_valid(input.at(0), "01234") ) {
        
        switch (int(input.at(0))) {
            case 1:

            Discard_Phase:
                cout << "Which card would you discard? Enter the Number:" << endl;
                getline(cin, input);
                if (input.size() == 2 && _input_is_valid(input.at(0), "123456")) {
                    human_player._discard_card(int(input.at(0) - '0'));
                }
                else {
                    cout << "Incorrect Input, Please try again" << endl;
                    goto Discard_Phase;
                }

                break;
                
            case 2:
                cout << "Sorting Hand by Value:" << endl;
                human_player._hand_sort(1);
                human_player._print_hand();
                goto Player_Phase_Options;
                
            case 3:
                cout << "Sorting Hand by Suits:" << endl;
                human_player._hand_sort(2);
                human_player._print_hand();
                goto Player_Phase_Options;

            case 4:
                cout << "Printing Discard Pile:" << endl;
                discard_pile._print_deck();
                goto Player_Phase_Options;
            case 0:
                cout << "Player wants to resign from this match" << endl;
                return 0;
        }
    }
    else {
        goto Player_Phase_Options;
    }
  
    return 1;
}


void _print_all_computer_hands(Player* schedule[]) {
    for (int i = 0; i < sizeof(schedule); i++) {
        if (schedule[i]->_player_is_playing() == true && schedule[i]->_player_is_human() == false) {
            schedule[i]->_print_hand();
        }
    }
}

bool _input_is_valid(char c, string range) {
    int size = range.size();
    for (int i = 0; i < size; i++) {
        if (range[i] == c) {
            return true;
        }
    }

    return false;
}


void _setting_human_player_in_schedule(Player* schedule[], int number_of_players, int human_no) {
    for (int i = 0; i < number_of_players; i++) {
        schedule[i]->_set_player_to_playing(true);

        if (i == human_no - 1) {
            schedule[i]->_set_player_to_human(true);
        }
    }
}