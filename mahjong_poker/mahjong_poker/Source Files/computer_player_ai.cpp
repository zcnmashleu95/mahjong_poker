#pragma once

#include "../Header Files/computer_player_ai.h"

void _computer_player_phase(Player* schedule[], Player& current_bot_player, Deck& main_deck, Deck& discard_pile, int& difficulty) {
	Card temp(0,0);
	
	int hand_size = current_bot_player._get_hand_size();

	int highest_count = 0;
	int sec_highest_count = 0;
	int highest_count_card_value = 0;
	int sec_highest_count_card_value = 0;
	int i = 0;

	int current_card_value = 0;

	current_bot_player._draw_card(1, main_deck);


	switch (difficulty) {
		case 1:
			current_bot_player._hand_sort(1);
			current_bot_player._discard_card(1, discard_pile);
			break;
		case 2:
			current_bot_player._hand_sort(1);
			current_bot_player._update_player_hand_to_memo();
			current_bot_player._top_two_counts_in_memo(highest_count, sec_highest_count, highest_count_card_value,
				sec_highest_count_card_value);

			if (highest_count == 4) {
				for (i = 0; i < hand_size; i++) {
					current_card_value = current_bot_player._access_card(i)._get_value();
					if (current_card_value != highest_count_card_value) {
						current_bot_player._discard_card((i + 1), discard_pile);
						current_bot_player._clear_memo();
						break;
					}
				}
			}
			else if (highest_count == 3) {
				if (sec_highest_count == 3) {
					current_bot_player._discard_card(1, discard_pile);
					current_bot_player._clear_memo();
				}
				else if(sec_highest_count == 2) {
					for (i = 0; i < hand_size; i++) {
						current_card_value = current_bot_player._access_card(i)._get_value();
						if (current_card_value != highest_count_card_value && current_card_value != sec_highest_count_card_value) {
							current_bot_player._discard_card((i + 1), discard_pile);
							current_bot_player._clear_memo();
							break;
						}
					}
				}
				else {
					current_bot_player._clear_memo();
					current_bot_player._discard_card(1, discard_pile);
				}

			}
			else if (highest_count == 2) {
				for (i = 0; i < hand_size; i++) {
					current_card_value = current_bot_player._access_card(i)._get_value();
					if (current_card_value != highest_count_card_value && current_card_value != sec_highest_count_card_value) {
						current_bot_player._discard_card((i + 1), discard_pile);
						current_bot_player._clear_memo();
						break;
					}
				}
			}
			else {
				current_bot_player._discard_card(1, discard_pile);
				current_bot_player._clear_memo();
			}

			break;

		case 3:
			current_bot_player._discard_card(1, discard_pile);
			//current_bot_player._update_player_hand_to_memo();

	}


}