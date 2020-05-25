#pragma once

#include "../Header Files/during_match_funcs.h"

int _human_player_phase(Player* schedule[], Player& human_player, Deck& main_deck, Deck& discard_pile, int& cheats) {
    string input;

    switch (cheats) {
    case 2:
        _print_all_hands(schedule);
        break;

    case 3:
        main_deck._print_deck();
        break;

    case 4:
        _print_all_hands(schedule);
        main_deck._print_deck();
        break;

    }

    human_player._draw_card(1, main_deck);
    human_player._print_hand();
    cout << endl;
Player_Phase_Options:
    cout << PLAYER_OPTIONS  << endl;
    getline(cin, input);
    if (input.size() == 1 && _input_is_valid(input.at(0), "01234")) {

        switch (int(input.at(0) - '0')) {
        case 1:
        Discard_Phase:
            cout << "Which card will you discard? Please enter the number:" << endl;
            getline(cin, input);
            if (input.size() == 1 && _input_is_valid(input.at(0), "123456")) {
                human_player._discard_card(int(input.at(0) - '0'), discard_pile);
            }
            else {
                cout << INVALID_INPUT << endl;
                goto Discard_Phase;
            }

            break;

        case 2:
            cout << "Sorting Hand by Value" << endl;
            human_player._hand_sort(1);
            human_player._print_hand();
            goto Player_Phase_Options;

        case 3:
            cout << "Sorting Hand by Suit" << endl;
            human_player._hand_sort(2);
            human_player._print_hand();
            goto Player_Phase_Options;

        case 4:
            cout << "Printing Discard Pile:" << endl;
            discard_pile._print_deck();
            goto Player_Phase_Options;
        case 0:
            cout << "Player wants to resign from this match" << endl;
            return 1;
        }
    }
    else {
        cout << INVALID_INPUT << endl;
        goto Player_Phase_Options;
    }

    return 0;
}


void _print_all_hands(Player* schedule[]) {
    for (int i = 0; i < sizeof(schedule); i++) {
        if (schedule[i]->_player_is_playing() == true) {
            schedule[i]->_print_hand();
            
            cout << "Player " << schedule[i]->_get_player_name() << "'s hand type: " << _hand_type_in_string(_hand_type_evaluation(*(schedule[i])) ) << endl << endl;
        }
    }
}



void _end_of_game_evaluation(Player* players_turn_schedule[], int& no_of_players, int& winner_index, int& points, int& wager) {
    winner_index = _evaluate_winner(players_turn_schedule, no_of_players);

    cout << "Player " << players_turn_schedule[winner_index]->_get_player_name() << " won the match!" << endl << endl;

    if (players_turn_schedule[winner_index]->_player_is_human() == true) {
        points = points + wager;
    }
    else {
        points = points - wager;
    }
}

int _ready_to_quit(string& input, int& human_is_quitting, Player* players_turn_schedule[], Deck& main_deck,
    Deck& discard_pile, int& points, int& turn, int& round, int& difficulty, int& cheats) {
    human_is_quitting = 0;

    if (points < 0) { points = 0; }
    cout << "Total points at the end of the match: " << points << endl;

Determine_Goto_After_End:
    if (points > 0) {
        cout << CONTINUE_OR_QUIT << endl;
        getline(cin, input);
        if (input.size() == 1 && _input_is_valid(input.at(0), "019")) {
            switch (int(input.at(0) - '0')) {
            case 1:
                _ready_for_new_match(players_turn_schedule, main_deck, discard_pile, turn);
                return 1;
            case 9:
                _ready_for_new_game(players_turn_schedule, main_deck, discard_pile, turn, round, difficulty, cheats);
                return 2;
            case 0:
                return 0;
            }
        }
        else {
            cout << INVALID_INPUT << endl;
            goto Determine_Goto_After_End;
        }

    }
    else {
        cout << NEW_OR_QUIT << endl;
        getline(cin, input);
        if (input.size() == 1 && _input_is_valid(input.at(0), "01")) {
            switch (int(input.at(0) - '0')) {
            case 1:
                _ready_for_new_game(players_turn_schedule, main_deck, discard_pile, turn, round, difficulty, cheats);
                return 2;
            case 0:
                return 0;
            }
        }
        else {
            cout << INVALID_INPUT << endl;
            goto Determine_Goto_After_End;
        }
    }


    return 0;
}

void _ready_for_new_match(Player* schedule[], Deck& main_deck, Deck& discard_pile, int& turn) {
    //reset variables to get ready for new match 
    for (int i = 0; i < sizeof(schedule); i++) {
        schedule[i]->_clear_memo();
        schedule[i]->_clear_hand();
    }

    turn = 0;
    main_deck._clear_deck();
    main_deck._fill_up_deck();
    main_deck._shuffle_deck();
    discard_pile._clear_deck();

    for (int i = 0; i < sizeof(schedule); i++) {
        if (schedule[i]->_player_is_playing() == true) {
            schedule[i]->_draw_card(5, main_deck);
        }
        
    }

}

void _ready_for_new_game(Player* schedule[], Deck& main_deck, Deck& discard_pile, int& turn, int& round, int& difficulty, int& cheats) {
    for (int i = 0; i < sizeof(schedule); i++) {
        schedule[i]->_set_name(to_string(i + 1));
        schedule[i]->_clear_memo();
        schedule[i]->_clear_hand();
        schedule[i]->_set_player_to_human(false);
        schedule[i]->_set_player_to_playing(false);
    }

    turn = 0;
    round = 1;
    difficulty = 1;
    cheats = 1;

    main_deck._clear_deck();
    main_deck._fill_up_deck();
    main_deck._shuffle_deck();
    discard_pile._clear_deck();
}


