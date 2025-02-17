#pragma once
#include <iostream>
#include <string>
#include "deck.h"
#include "player.h"
#include <algorithm>
#include <map>

using namespace std;

int _compare_same_hand_type(Player& a, Player& b, int hand_type);
string _hand_type_in_string(int hand_type);

int _hand_type_evaluation(Player& a);

bool _is_royal_flush(Player &a, int index);
bool _is_straight(Player &a, int index, bool flush);
bool _is_flush(Player& a, int index);

int _compare_cards(Card& a, Card& b);
int _compare_values(Card& a, Card& b);
int _compare_suits(Card& a, Card& b);
int _compare_hands(Player& a, Player& b);
int _evaluate_winner(Player* schedule[], int number_of_players);