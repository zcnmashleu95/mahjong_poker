#pragma once

#include "../Header Files/player.h"

Player::Player(string name, int number) {
	this->player_name = name;
	this->player_number = number;
}

map <int, vector<int>> Player::_get_memo() {
	return this->memo;
}

void Player::_set_name(string name) {
	this->player_name = name;
}


bool Player::_player_is_playing() {
	return this->is_playing;
}

bool Player::_player_is_human() {
	return this->is_human_player;
}

void Player::_set_player_to_human(bool value) {
	this->is_human_player = value;
}

void Player::_set_player_to_playing(bool value) {
	this->is_playing = value;
}


int Player::_get_player_no() {
	return this->player_number;
}

string Player::_get_player_name() {
	return this->player_name;
}

vector<Card> Player::_access_hand() {
	return this->hand;
}

void Player::_clear_hand() {
	this->hand.clear();
}

void Player::_clear_memo() {
	this->memo.clear();
}

Card Player::_access_card(int index) {
	int size = this->hand.size();
	Card result(0, 0);
	if (index >= 0 && index <= size - 1) {
		result = this->hand[index];
	}
	return result;
}

int Player::_get_hand_size() {
	return this->hand.size();
}

void Player::_print_hand() {
	int option = 1;
	int size = this->hand.size();
	cout << "Player " << this->player_name << "'s hand: " << endl;
	for (int i = 0; i < size; i++) {
		cout << option << ": ";
		this->hand[i]._print_card();
		option = option + 1;
	}
}

bool Player::_check_hand_size() {
	return (this->hand.size() <= 6);
}

void Player::_discard_card(int option, Deck& discard_pile) {
	//option ranges from 1 to 6, hand[0] to hand[5], size = 6
	int size = this->hand.size();
	option = option - 1;
	if (option >= 0 && option < size) {
		cout << "Player " << this->player_name << " Discards: ";
		this->hand.at(option)._print_card();

		discard_pile._add_to_deck(this->hand.at(option));

		this->hand.erase(this->hand.begin() + option);
	}
}


void Player::_draw_card(int number_of_cards, Deck& main_deck) {
	while (number_of_cards >= 1) {
		if (main_deck._is_deck_empty() == false) {
			this->hand.push_back(main_deck._top_of_deck());

			main_deck._pop_top_deck();

			number_of_cards = number_of_cards - 1;
		}
		else {
			break;
		}

	}
}


void Player::_hand_sort(int flag) {

	switch (flag) {
	case 1:
		sort(this->hand.begin(), this->hand.end(), [](Card &a, Card &b) -> bool {return (a._get_value() < b._get_value());   });
		break;
	case 2:
		sort(this->hand.begin(), this->hand.end(), [](Card &a, Card &b) -> bool {return (a._get_suit() < b._get_suit()); });
		break;

	default:
		cout << "Error in sort Flag" << endl;
	}
}


void Player::_update_memo_with_card(Card a) {
	int card_value = a._get_value();
	if (this->memo.count(card_value) == 0) {
		this->memo.insert(pair <int, vector<int>> (card_value, vector<int>()));
	}
	this->memo.find(card_value)->second.push_back(a._get_suit());
}

void Player::_update_player_hand_to_memo() {

	int hand_size = this->_check_hand_size();
	
	for (int i = 0; i < hand_size; i++) {
		this->_update_memo_with_card(this->_access_card(i));
	}

}

Card Player::_highest_card_in_memo_based_on_copies(int number_of_copies) {
	int highest_suit = 0;
	int highest_value = 0;
	map<int, vector<int>>::iterator iter;

	for (iter = this->memo.begin(); iter != this->memo.end(); iter++) {
		if ((int)iter->second.size() == number_of_copies && iter->first > highest_value) {
			highest_value = iter->first;
			highest_suit = *(max_element(iter->second.begin(), iter->second.end()));
		}
	}

	if (highest_value == 0) {
		cerr << "Error in highest card in memo";
	}

	return Card(highest_value, highest_suit);
}

void Player::_top_two_counts_in_memo(int& highest_count, int &sec_highest_count, int &highest_count_card_value, int &sec_highest_count_card_value) {
	map<int, vector<int>>::iterator iter;;

	for (iter = this->memo.begin(); iter != this->memo.end(); iter++) {
		if ((int)iter->second.size() >= highest_count) {
			sec_highest_count = highest_count;
			sec_highest_count_card_value = highest_count_card_value;

			highest_count = iter->second.size();
			highest_count_card_value = iter->first;

		}
	}
}

void Player::_add_card(Card a) {
	this->hand.push_back(a);
}