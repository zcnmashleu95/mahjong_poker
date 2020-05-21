#pragma once

#include "define_string_messages.h"
#include <iostream>

class Card {
	private:
		int suit = 0;
		int value = 0;
	public:
		Card (int suit, int value);

		int _get_suit();
		int _get_value();
		void _print_card();
};
