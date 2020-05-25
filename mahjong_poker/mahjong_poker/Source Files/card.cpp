
#pragma once


#include "../Header Files/card.h"

using namespace std;

Card::Card(int suit, int value) {
	this->suit = suit;
	this->value = value;
};

int Card::_get_suit() {
	return this->suit;
};

int Card::_get_value() {
	return this->value;
};

void Card::_print_card() {
	int suit = this->suit;
	int value = this->value;

	cout << "(";

	switch (value) {
	case 11:
		cout << "Jack";
		break;
	case 12:
		cout << "Queen";
		break;
	case 13:
		cout << "King";
		break;
	case 14:
		cout << "Ace";
		break;
	default:
		if (value > 1 && value < 11) {
			cout << value;
		}
		else {
			cerr << "Error in card's Suit";
		}

	}

	cout << ", ";

	switch (suit) {
	case 1:
		cout << "Diamond";
		break;

	case 2:
		cout << "Club";
		break;

	case 3:
		cout << "Heart";
		break;

	case 4:
		cout << "Spade";
		break;

	default:
		cerr << "ERROR in Card's Value";
	};

	cout << ")" << endl;
};
