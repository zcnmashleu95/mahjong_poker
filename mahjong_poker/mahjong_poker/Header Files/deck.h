
#pragma once

#include "define_string_messages.h"

#include <algorithm>
#include <random>
#include <iostream>
#include <vector>
#include "card.h"
#include<ctime>


using namespace std;

class Deck {
	private:
		vector<Card> deck;
	public:
		Deck(bool is_full);
		void _add_to_deck(Card a);
		void _shuffle_deck();
		bool _is_deck_empty();
		Card _top_of_deck();
		void _pop_top_deck();
		void _print_deck();
		void _clear_deck();
		void _fill_up_deck();
};

