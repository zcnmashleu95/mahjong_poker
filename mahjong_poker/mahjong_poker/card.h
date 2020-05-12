
#include <iostream>

using namespace std;

class Card {
	private:
		int suit;
		int value;
	public:
		Card (int suit, int value) {
			this->suit = suit;
			this->value = value;
		};

		int get_suit(){
			return this->suit;
		};

		int get_value(){
			return this->value;
		};

		void print_card(Card card){
			int suit = card.get_suit();
			int value = card.get_value();

			cout << "(";

			switch(value){
				case 1:
					cout << "Ace";
					break;
				case 11:
					cout << "Jack";
					break;
				case 12:
					cout << "Queen";
					break;
				case 13:
					cout << "King";
					break;
				default:
					if(value >=1 && value <= 13){
						cout << value;
					}else{
						cout << "Error in card's value";
					}

			};
			
			cout << ", ";

			switch(suit){
				case 1:
					cout << "Spade";
					break;
				
				case 2:
					cout << "Heart";
					break;

				case 3:
					cout << "Club";
					break;

				case 4:
					cout << "Diamond";
					break;
				
				default:
					cout << "ERROR in Suits";
			};

			cout << ")";
		}
};



