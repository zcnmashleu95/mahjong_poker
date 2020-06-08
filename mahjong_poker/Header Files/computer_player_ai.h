#pragma once


#include "player.h"
#include "deck.h"
#include "card.h"
#include "compare_hands_funcs.h"

using namespace std;
//for easy phase, ai discards the lowest valued card every turn
//for normal phase, ai will not discard cards which it has copies every turn
//for hard phase, ai will do card counting 


void _computer_player_phase(Player* schedule[], Player &current_bot_player, Deck &main_deck,Deck &discard_pile,int &difficulty);
void _com_player_normal_ai(Player& current_bot_player, Deck& main_deck, Deck& discard_pile);
void _com_player_difficult_ai(Player& current_bot_player, Deck& main_deck, Deck& discard_pile);
void _discard_not_max_count(Player& current_bot_player, int& highest_count_card_value, Deck& discard_pile);
void _discard_not_max_count_and_sec(Player& current_bot_player, int& highest_count_card_value, int& sec_highest_count_card_value, Deck& discard_pile);
void _discard_not_max_suit(Player& current_bot_player, int& max_suit_value, Deck& discard_pile);