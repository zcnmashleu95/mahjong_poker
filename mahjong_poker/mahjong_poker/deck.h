
#include <vector>
#include "card.h"
#include <algorithm>
#include <random>
#include <iostream>

using namespace std;

//shuffle deck -  seed to be changed in future

class Deck {
	private:
		vector<Card> deck;
	public:
		Deck () {
			int suit = 0;
			int value = 0;
			for(int suit =  1; suit <= 4; suit ++){
				for(value = 1; value <= 13; value++){

					this->deck.push_back( Card (suit, value));
				}
			}

		};

		void shuffle_deck(){
			unsigned seed = 1;
			shuffle(this->deck.begin(), this->deck.end(), default_random_engine(seed) );
		};

		Card peek_deck(int index){
			return this->deck[index];
		};


		void print_deck(){
			int size = this->deck.size();
			cout << "\nSize: " << size ;

			for(int i = 0; i <= size - 1; i++){
				cout << "\n" << i << " ";
				this->deck[i].print_card(this->deck[i]);
			}

		};
		
};

