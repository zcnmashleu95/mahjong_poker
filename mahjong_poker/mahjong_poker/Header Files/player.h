#pragma once


#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

#include "card.h"
#include "deck.h"


using namespace std;

class Player {
	private:
		string player_name = "0";
		int player_number = 0;

		vector<Card> hand;
		map <int, vector<int>> memo;
		bool is_human_player = false;
		bool is_playing = false;
	public:
		Player(string name, int number);
		map <int, vector<int>> _get_memo();
		void _set_name(string name);
		bool _player_is_playing();
		bool _player_is_human();
		void _set_player_to_human(bool value);
		void _set_player_to_playing(bool value);
		int _get_player_no();
		string _get_player_name();
		vector<Card> _access_hand();

		void _update_memo_with_card(Card a);
		void _update_player_hand_to_memo();
		Card _highest_card_in_memo_based_on_copies(int number_of_copies);
		void _top_two_counts_in_memo(int& highest_count, int& second_highest_count, int &highest_count_card_value, int& sec_highest_count_card_value);

		void _clear_hand();
		void _clear_memo();
		Card _access_card(int index);
		int _get_hand_size();

		void _print_hand();
		bool _check_hand_size();
		void _discard_card(int option, Deck& discard_pile);
		void _draw_card(int number_of_cards, Deck& main_deck);
		void _hand_sort(int flag);

		// used for testing
		void _add_card(Card a);
};
