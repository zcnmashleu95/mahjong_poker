#pragma once

#include "../Header Files/during_match_funcs.h"

int _human_player_phase(Player* schedule[], Player& human_player, Deck& main_deck, Deck& discard_pile, int& cheats) {
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
    cout << "What would you want to do? Options 1 for discard, 2 for sort, 3 for sort, 4 for pritn discard pile, 0 for quit etc" << endl;
    getline(cin, input);
    if (input.size() == 1 && _input_is_valid(input.at(0), "01234")) {

        switch (int(input.at(0) - '0')) {
        case 1:
        Discard_Phase:
            cout << "Which card would you discard? Enter the Number:" << endl;
            getline(cin, input);
            if (input.size() == 1 && _input_is_valid(input.at(0), "123456")) {
                human_player._discard_card(int(input.at(0) - '0'), discard_pile);
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
            return 1;
        }
    }
    else {
        cout << "Invalid Input" << endl;
        goto Player_Phase_Options;
    }

    return 0;
}


void _print_all_computer_hands(Player* schedule[]) {
    for (int i = 0; i < sizeof(schedule); i++) {
        if (schedule[i]->_player_is_playing() == true && schedule[i]->_player_is_human() == false) {
            schedule[i]->_print_hand();
        }
    }
}



void _end_of_game_evaluation(Player* players_turn_schedule[], int& no_of_players, int& winner_index, int& points, int& wager) {
    winner_index = _evaluate_winner(players_turn_schedule, no_of_players);

    cout << "Player " << players_turn_schedule[winner_index]->_get_player_name() << "won!";

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
    cout << "Points: " << points << endl;

Determine_Goto_After_End:
    if (points > 0) {
        cout << "The match is over. Do you want to 1: Continue in a new match 9:New Game  0:Quit" << endl;
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
            cout << "Invalid Input" << endl;
            goto Determine_Goto_After_End;
        }

    }
    else {
        cout << "Game Over, your points = 0. Do you want to 1: New Game or 0: Quit" << endl;
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
            cout << "Invalid Input" << endl;
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

    turn = 1;

    main_deck._clear_deck();
    main_deck._fill_up_deck();
    discard_pile._clear_deck();

}

void _ready_for_new_game(Player* schedule[], Deck& main_deck, Deck& discard_pile, int& turn, int& round, int& difficulty, int& cheats) {
    for (int i = 0; i < sizeof(schedule); i++) {
        schedule[i]->_set_name(to_string(i + 1));
        schedule[i]->_clear_memo();
        schedule[i]->_clear_hand();
        schedule[i]->_set_player_to_human(false);
        schedule[i]->_set_player_to_playing(false);
    }

    turn = 1;
    round = 1;
    difficulty = 1;
    cheats = 1;

    main_deck._clear_deck();
    main_deck._fill_up_deck();
    discard_pile._clear_deck();
}


