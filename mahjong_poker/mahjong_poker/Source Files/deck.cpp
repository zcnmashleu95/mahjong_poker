
#pragma once

#include "../Header Files/deck.h"

using namespace std;

Deck::Deck(bool is_full) {
	if (is_full == true) {
		this->_fill_up_deck();
	}

};

void Deck::_add_to_deck(Card a) {
	this->deck.push_back(a);
};

void Deck::_shuffle_deck() {
	unsigned seed = unsigned (time(NULL));
	shuffle(this->deck.begin(), this->deck.end(), default_random_engine(seed));
};

bool Deck::_is_deck_empty() {
	return this->deck.empty();
};

Card Deck::_top_of_deck() {
	return this->deck.back();
};

void Deck::_pop_top_deck() {
	this->deck.pop_back();
};

void Deck::_print_deck() {
	int size = this->deck.size();
	cout << "\nSize: " << size << endl;

	for (int i = 0; i <= size - 1; i++) {
		cout << (i + 1) << " ";
		this->deck[i]._print_card();
	}

};

void Deck::_clear_deck() {
	this->deck.clear();
};

void Deck::_fill_up_deck() {
	int suit = 0;
	int value = 0;
	for (int suit = 1; suit <= 4; suit++) {
		for (value = 2; value <= 14; value++) {

			this->deck.push_back(Card(suit, value));
		}
	}
};