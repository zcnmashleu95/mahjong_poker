#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <map>

#include "../Header Files/define_string_messages.h"

#include "../Header Files/deck.h"
#include "../Header Files/card.h"
#include "../Header Files/player.h"
#include "../Header Files/compare_hands_funcs.h"
#include "../Header Files/set_game_funcs.h"
#include "../Header Files/during_match_funcs.h"
#include "../Header Files/computer_player_ai.h"

//For testing//
#include "../Test_Cases/Test Header Files/test_cases.h"
 
// TODO: Level 3 Difficulty AI *, try to use more data structures
// TODO: Define string messages


using namespace std;

int main() { 
    //_test_cases_consolidated();
    string input;

    Deck main_deck(true);
    Deck discard_pile(false);

    Player player_1("1", 1);
    Player player_2("2", 2);
    Player player_3("3", 3);
    Player player_4("4", 4);
    
    
    int turn = 0;
    int round = 1;

    string name;
    int no_of_players = 0;
    int human_player_no = 0;
    int difficulty = 1;
    int cheats = 1;
    int human_is_quitting = 0;

    Player* current_player_ptr = NULL;
    int winner_index = 0;
    int points = 0;
    int wager = 0;

    int after_quit_goto = 0;


    Player* players_turn_schedule[4] = {&player_1, &player_2, &player_3, &player_4};

    main_deck._shuffle_deck();
	
Start_Of_Game:
    cout << WELCOME_MESSAGE <<endl << endl;
    cout << GAME_INSTRUCTIONS << endl << endl;
    cout << HOW_TO_WIN << endl << endl;
    cout << HAND_EVALUATION << endl << endl;

    _set_name(input, name);

    _set_number_of_points(input, points);

    _set_wager(input, wager, points);

    _set_number_of_com_players(input, no_of_players);

    _set_human_player_index(input, human_player_no, no_of_players);

    players_turn_schedule[human_player_no - 1]->_set_name(name);

    _set_difficulty(input, difficulty);

    _set_cheats(input, cheats);

    _set_human_player_in_schedule(players_turn_schedule, no_of_players, human_player_no, main_deck);

Game_Match_Phase:
   
    system("cls");

    cout << "Match Round: " << (round + 1) << endl << endl;

    while (main_deck._is_deck_empty() == false) {

        current_player_ptr = players_turn_schedule[turn % no_of_players];

        cout << "Turn " << (turn + 1) << ": " << "Player " << current_player_ptr->_get_player_name() << "'s turn" << endl;

        if (current_player_ptr->_player_is_playing() == true) {
            if (current_player_ptr->_player_is_human() == true) {
                human_is_quitting = _human_player_phase(players_turn_schedule, *(current_player_ptr), main_deck, discard_pile, cheats);
            }
            else {
                _computer_player_phase(players_turn_schedule, *(current_player_ptr), main_deck, discard_pile, difficulty);
            }
            
        }
        else {
            cerr << "Error in Player schedule and phase";
        }
        
        if (human_is_quitting == 1) {
            points = points - wager;
            goto Quit_Phase;
        }

        turn = turn + 1;
    }

    _print_all_hands(players_turn_schedule);

    cout << "Starting Evaluation" << endl;
    _end_of_game_evaluation(players_turn_schedule, no_of_players, winner_index, points, wager);
    
    

Quit_Phase:

    after_quit_goto = _ready_to_quit(input, human_is_quitting, players_turn_schedule, 
                        main_deck, discard_pile, points, turn, round, difficulty, cheats);

    if (after_quit_goto == 1) {
        goto Game_Match_Phase;
    }
    else if (after_quit_goto == 2) {
        system("cls");
        goto Start_Of_Game;
    }
    else {
        return 0;
    }

}


int main_1() {
    _test_cases_consolidated();
    return 0;
}