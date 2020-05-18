#pragma once
#include <vector>
#include "card.h"
#include <algorithm>
#include <random>
#include <iostream>

using namespace std;

//shuffle_deck function -  seed to be changed in future

class Deck {
	private:
		vector<Card> deck;
	public:
		Deck (bool is_full) {
			if (is_full == true) {
				this->_fill_up_deck();
			}
			
		}

		void _shuffle_deck(){
			unsigned seed = 1;
			shuffle(this->deck.begin(), this->deck.end(), default_random_engine(seed) );
		}

		bool _is_deck_empty(){
			return this->deck.empty();
		}

		Card _top_of_deck() {
			return this->deck.back();
		}

		void _pop_top_deck() {
			this->deck.pop_back();
		}

		void _print_deck(){
			int size = this->deck.size();
			cout << "\nSize: " << size << endl;

			for(int i = 0; i <= size - 1; i++){
				cout << (i + 1) << " ";
				this->deck[i]._print_card();
			}

		}
		
		void _clear_deck() {
			this->deck.clear();
		}

		void _fill_up_deck() {
			int suit = 0;
			int value = 0;
			for (int suit = 1; suit <= 4; suit++) {
				for (value = 2; value <= 14; value++) {

					this->deck.push_back(Card(suit, value));
				}
			}
		}
};

