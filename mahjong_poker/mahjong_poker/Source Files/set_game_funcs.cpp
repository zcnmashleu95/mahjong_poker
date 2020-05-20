#pragma once

#include "../Header Files/set_game_funcs.h"

void _set_number_of_points(string& input, int points) {
Set_Points:
    cout << "How many points" << endl;
    getline(cin, input);
    if (input.size() >= 1 || input.size() <= 3 && stoi(input) >= 1 && stoi(input) <= 100) {
        points = stoi(input);
    }
    else {
        cerr << "Input Error" << endl;
        goto Set_Points;
    }
}

void _set_wager(string& input, int& wager, int& points) {
Set_Wager:
    cout << "How much points per wager (must be <= points)" << endl;
    getline(cin, input);
    if (stoi(input) >= 1 && stoi(input) <= points) {
        wager = stoi(input);
    }
    else {
        cerr << "Input Error" << endl;
        goto Set_Wager;
    }
}

void _set_number_of_com_players(string& input, int& no_of_players) {
Number_Of_Computer_Players_Phase:
    cout << "How many Computer Players?" << endl;
    getline(cin, input);

    if (input.size() == 1 && _input_is_valid(input.at(0), "123") == true) {
        no_of_players = int(input.at(0) - '0') + 1;
        cout << "Number of Players: " << no_of_players << endl;
    }
    else {
        cerr << "Input Error" << endl;
        goto Number_Of_Computer_Players_Phase;
    }
}

void _set_cheats(string& input, int& cheats) {
Enable_Cheats:
    cout << "Do you want to enable cheats? 1: Default(no cheats) 2: Print Opponents' Hands during your turn 3:Print Deck during your turn 4:Combination of 2 and 3" << endl;

    getline(cin, input);
    if (input.size() == 1 && _input_is_valid(input.at(0), "1234")) {
        cheats = int(input.at(0) - '0');
    }
    else {
        cerr << "Invalid Input" << endl;
        goto Enable_Cheats;
    }
}

void _set_human_player_index(string& input, int& human_player_no, int& no_of_players) {
Select_Human_Player:
    cout << "Which Player do you want to be? This will last till the entire game is over" << endl;
    getline(cin, input);
    if (input.size() == 1 && (int(input.at(0) - '0') >= 1) && (int(input.at(0) - '0') <= no_of_players)) {
        human_player_no = int(input.at(0) - '0');
    }
    else {
        cerr << "Invalid Input" << endl;
        goto Select_Human_Player;
    }
}



void _set_human_player_in_schedule(Player* schedule[], int number_of_players, int human_no, Deck& main_deck) {
    for (int i = 0; i < number_of_players; i++) {
        schedule[i]->_set_player_to_playing(true);
        schedule[i]->_draw_card(5, main_deck);
        if (i == human_no - 1) {
            schedule[i]->_set_player_to_human(true);
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