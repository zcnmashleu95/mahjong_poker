#pragma once

#include <vector>
#include "card.h"
#include <iostream>
#include "deck.h"
#include <algorithm>


using namespace std;

class Player {
	private:
		string player_name = "0";
		int player_number = 0;

		vector<Card> hand;
		map <int, int> memo;

		bool is_human_player = false;
		bool is_playing = false;

	public:
		Player (string name, int number){
			this->player_name = name;
			this->player_number = number;
		}

		void _set_player_to_human(bool value) {
			this->is_human_player = value;
		}

		int _get_player_no() {
			return this->player_number;
		}

		string _get_player_name() {
			return this->player_name;
		}

		vector<Card> _access_hand() {
			return this->hand;
		}

		Card _access_card(int index) {
			int size = this->hand.size();
			Card result;
			if (index >= 0 && index <= size - 1) {
				result = this->hand[index];
			}
			return result;
		}

		int _return_size() {
			return this->hand.size();
		}

		void _print_hand() {
			int option = 1;
			int size = this->hand.size();
			cout << "Player " << this->player_name << "'s hand: " << endl;
			for (int i = 0; i < size; i++) {
				cout << option << ": ";
				this->hand[i]._print_card();
				option = option + 1;
			}
		}

		bool _check_hand_size() {
			return (this->hand.size() <= 6);
		}

		void _discard_card(int option) {
			//option ranges from 1 to 6, hand[0] to hand[5], size = 6
			int size = this->hand.size();
			option = option - 1;
			if (option >= 0 && option < size) {
				cout << "Player" << this->player_name << "Discards: ";
				this->hand.at(option)._print_card();
				this->hand.erase(this->hand.begin() + option);
			}
		}


		void _draw_card(int number_of_cards, Deck &main_deck) {
			while (number_of_cards >= 1) {
				if (main_deck._empty_deck() == false) {
					this->hand.push_back(main_deck._top_of_deck());

					main_deck._pop_top_deck();
					
					number_of_cards = number_of_cards - 1;
				}
				else {
					break;
				}
				
			}
		}


		void _hand_sort(int flag) {
			
			switch (flag) {
				case 1:
					sort( this->hand.begin(), this->hand.end(), [](Card a, Card b) -> bool {return (a._get_value() < b._get_value());   });
					break;
				case 2:
					sort(this->hand.begin(), this->hand.end(), [](Card a, Card b) -> bool {return (a._get_suit() < b._get_suit()); });
					break;
				
				default:
					cout << "Error in sort Flag" << endl;
			}
		}


};