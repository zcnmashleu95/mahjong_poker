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

// TODO: deck -> figure out how to best include the constant string messages, try to set up/get ready for coding the computer player ai




using namespace std;

int main() {  
    string input_error = "Invalid Input, Please Input again";

    string input;

    Deck main_deck(true);
    Deck discard_pile(false);

    Player player_1("1", 1);
    Player player_2("2", 2);
    Player player_3("3", 3);
    Player player_4("4", 4);
    
    
    int turn = 1;
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

    int after_quit_goto = 0;


    Player* players_turn_schedule[4] = {&player_1, &player_2, &player_3, &player_4};

    main_deck._shuffle_deck();
	
Start_Of_Game:
    cout << WELCOME_MESSAGE <<endl;
    cout << GAME_INSTRUCTIONS << endl;

    _set_number_of_points(input, points);

    _set_wager(input, wager, points);

    _set_number_of_com_players(input, no_of_players);

    _set_human_player_index(input, human_player_no, no_of_players);

    _set_cheats(input, cheats);

    _set_human_player_in_schedule(players_turn_schedule, no_of_players, human_player_no, main_deck);

Game_Match_Phase:
    while (main_deck._is_deck_empty() == false) {
        current_player_ptr = players_turn_schedule[turn % no_of_players];

        cout << "Turn " << turn << ": " << "Player " << current_player_ptr->_get_player_name() << "'s turn" << endl;

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
        
        if (human_is_quitting == 1) {
            points = points - wager;
            goto Quit_Phase;
        }

        turn = turn + 1;
    }

    //Evaluation_phase
    _end_of_game_evaluation(players_turn_schedule, no_of_players, winner_index, points, wager);
    

Quit_Phase:

    after_quit_goto = _ready_to_quit(input, human_is_quitting, players_turn_schedule, 
                        main_deck, discard_pile, points, turn, round, difficulty, cheats);

    if (after_quit_goto == 1) {
        goto Game_Match_Phase;
    }
    else if (after_quit_goto == 2) {
        goto Start_Of_Game;
    }
    else {
        return 0;
    }

}