#pragma once


#include "player.h"
#include "deck.h"
#include "card.h"

using namespace std;
//for easy phase, ai discards the lowest valued card every turn
//for normal phase, ai will not discard cards which it has copies every turn
//for hard phase, ai will do card counting 


void _computer_player_phase(Player* schedule[], Player &current_bot_player, Deck &main_deck,Deck &discard_pile,int &difficulty);