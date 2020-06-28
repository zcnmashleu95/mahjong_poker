#pragma once

#include "../Header Files/computer_player_ai.h"

//Should play test a few more times.

void _computer_player_phase(Player* schedule[], Player& current_bot_player, Deck& main_deck, Deck& discard_pile, int& difficulty) {

	switch (difficulty) {
		case 1:

			current_bot_player._draw_card(1, main_deck);
			current_bot_player._hand_sort(1);
			current_bot_player._discard_card(1, discard_pile);
			break;
		case 2:
			_com_player_normal_ai(current_bot_player, main_deck, discard_pile);
			break;

		case 3:
			_com_player_difficult_ai(current_bot_player, main_deck, discard_pile);
			break;
		
		default:
			cerr << "Error during com player phase" << endl;
			break;
	}

	current_bot_player._clear_memo();
}

void _com_player_normal_ai(Player &current_bot_player, Deck & main_deck, Deck &discard_pile ){
	int max_suit_count = 0;
	int max_suit_value = 0;

	int highest_count = 0;
	int sec_highest_count = 0;
	int highest_count_card_value = 0;
	int sec_highest_count_card_value = 0;
	int current_card_value = 0;
	

	int hand_size = current_bot_player._get_hand_size();

	current_bot_player._draw_card(1, main_deck);
	current_bot_player._hand_sort(1);
	current_bot_player._update_player_hand_to_memo();
	current_bot_player._top_two_counts_in_memo(highest_count, sec_highest_count, highest_count_card_value,
		sec_highest_count_card_value);

	switch (highest_count) {
	case 4:
		_discard_not_max_count(current_bot_player, highest_count_card_value, discard_pile);
		break;

	case 3:
		if (sec_highest_count == 3) {
			current_bot_player._discard_card(1, discard_pile);
		}
		else if (sec_highest_count == 2) {
			_discard_not_max_count_and_sec(current_bot_player, highest_count_card_value, sec_highest_count_card_value, discard_pile);
		}
		else {
			current_bot_player._discard_card(1, discard_pile);
		}

		break;

	case 2:
		if (sec_highest_count == 2) {
			_discard_not_max_count_and_sec(current_bot_player, highest_count_card_value, sec_highest_count_card_value, discard_pile);
		}
		else {
			_discard_not_max_count(current_bot_player, highest_count_card_value, discard_pile);
		}
		break;

	default:
		current_bot_player._discard_card(1, discard_pile);
		break;

	}
}




void _com_player_difficult_ai(Player& current_bot_player, Deck& main_deck, Deck& discard_pile){
	int hand_value = 0;
	int max_suit_count = 0;
	int max_suit_value = 0;

	int highest_count = 0;
	int sec_highest_count = 0;
	int highest_count_card_value = 0;
	int sec_highest_count_card_value = 0;
	int current_card_value = 0;

	hand_value = _hand_type_evaluation(current_bot_player);
	current_bot_player._draw_card(1, main_deck);

	if (hand_value >= 5) {
		current_bot_player._discard_card(6, discard_pile);
	}
	else {
		current_bot_player._hand_sort(1);
		max_suit_count = current_bot_player._max_suit_count(max_suit_value);
		current_bot_player._update_player_hand_to_memo();
		current_bot_player._top_two_counts_in_memo(highest_count, sec_highest_count, highest_count_card_value,
													sec_highest_count_card_value);


		if (max_suit_count == 4) {
			_discard_not_max_suit(current_bot_player, max_suit_value, discard_pile);
		}
		else {
			switch (highest_count) {
			case 4:
				_discard_not_max_count(current_bot_player, highest_count_card_value, discard_pile);
				break;
			case 3:
				if (sec_highest_count == 3) {
					current_bot_player._discard_card(1, discard_pile);
				}
				else if (sec_highest_count == 2) {
					_discard_not_max_count_and_sec(current_bot_player, highest_count_card_value, sec_highest_count_card_value, discard_pile);
				}
				else {
					_discard_not_max_count(current_bot_player, highest_count_card_value, discard_pile);
				}

				break;

			case 2:
				if (sec_highest_count == 2) {
					_discard_not_max_count_and_sec(current_bot_player, highest_count_card_value, sec_highest_count_card_value, discard_pile);
				}
				else {
					_discard_not_max_count(current_bot_player, highest_count_card_value, discard_pile);
				}

				break;
			default:
				current_bot_player._discard_card(1, discard_pile);
				break;

			}
		}
	}
}


void _discard_not_max_count(Player &current_bot_player, int &highest_count_card_value, Deck &discard_pile) {
	int current_card_value = 0;
	int hand_size = current_bot_player._get_hand_size();
	int i = 0;

	for (i = 0; i < hand_size; i++) {
		current_card_value = current_bot_player._access_card(i)._get_value();
		if (current_card_value != highest_count_card_value) {
			current_bot_player._discard_card((i + 1), discard_pile);
			break;
		}
	}
}


void _discard_not_max_count_and_sec(Player& current_bot_player, int& highest_count_card_value, int& sec_highest_count_card_value, Deck& discard_pile) {
	int current_card_value = 0;
	int hand_size = current_bot_player._get_hand_size();
	int i = 0;
	
	for (i = 0; i < hand_size; i++) {
		current_card_value = current_bot_player._access_card(i)._get_value();
		if (current_card_value != highest_count_card_value && current_card_value != sec_highest_count_card_value) {
			current_bot_player._discard_card((i + 1), discard_pile);
			break;
		}
	}
}

void _discard_not_max_suit(Player &current_bot_player, int &max_suit_value, Deck& discard_pile) {

	int current_card_suit = 0;
	int i = 0;
	int hand_size = current_bot_player._get_hand_size();
	for (i = 0; i < hand_size; i++) {
		current_card_suit = current_bot_player._access_card(i)._get_suit();
		if (current_card_suit != max_suit_value) {
			current_bot_player._discard_card((i + 1), discard_pile);
			break;
		}
	}
}