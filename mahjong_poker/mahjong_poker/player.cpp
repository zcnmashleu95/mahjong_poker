#pragma once

#include "player.h"

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

int Player::_return_size() {
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
		sort(this->hand.begin(), this->hand.end(), [](Card a, Card b) -> bool {return (a._get_value() < b._get_value());   });
		break;
	case 2:
		sort(this->hand.begin(), this->hand.end(), [](Card a, Card b) -> bool {return (a._get_suit() < b._get_suit()); });
		break;

	default:
		cout << "Error in sort Flag" << endl;
	}
}

