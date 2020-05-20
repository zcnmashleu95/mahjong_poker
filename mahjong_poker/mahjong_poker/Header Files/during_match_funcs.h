#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <map>

#include "player.h"
#include "deck.h"
#include "compare_hands_funcs.h" //For _evaluate_winner
#include "set_game_funcs.h" // For _input_is_valid

int _human_player_phase(Player* schedule[], Player& human_player, Deck& main_deck, Deck& discard_pile, int& cheats);
void _print_all_computer_hands(Player* schedule[]);
void _ready_for_new_match(Player* schedule[], Deck& main_deck, Deck& discard_pile, int& turn);
void _ready_for_new_game(Player* schedule[], Deck& main_deck, Deck& discard_pile, int& turn, int& round, int& difficulty, int& cheats);
int _ready_to_quit(string& input, int& human_is_quitting, Player* players_turn_schedule[], Deck& main_deck,
    Deck& discard_pile, int& points, int& turn, int& round, int& difficulty, int& cheats);
void _end_of_game_evaluation(Player* players_turn_schedule[], int& no_of_players, int& winner_index, int& points, int& wager);