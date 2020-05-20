#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <map>

#include "player.h"
#include "compare_hands_funcs.h"

using namespace std;

void _set_number_of_points(string& input, int points);
void _set_wager(string& input, int& wager, int& points);
void _set_number_of_com_players(string& input, int& no_of_players);
void _set_cheats(string& input, int& cheats);
void _set_human_player_index(string& input, int& human_player_no, int& no_of_players);
void _set_human_player_in_schedule(Player* schedule[], int number_of_players, int human_no, Deck& main_deck);

bool _input_is_valid(char c, string range);