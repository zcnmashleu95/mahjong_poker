#pragma once


using namespace std;

class Card {
	private:
		int suit;
		int value;
	public:
		Card new_card(int suit, int value);
		void print_card();
};

Card new_card(int suit, int value) {
	suit = suit;
	value = value;
}

void print_card() {

}