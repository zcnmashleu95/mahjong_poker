#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <map>

#include "../Header Files/define_string_messages.h"

#include "../Header Files/deck.h"
#include "../Header Files/card.h"
#include "../Header Files/player.h"
#include "../Header Files/compare_hands_funcs.h"
#include "../Header Files/set_game_funcs.h"
#include "../Header Files/during_match_funcs.h"
#include "../Header Files/computer_player_ai.h"
// not sure how to organise the files into tests and what not. will organise this more in the future



void _test_hand_types() {
    Player a("test", 1);

    //For royale flush
    a._add_card(Card(4, 14));
    a._add_card(Card(4, 13));
    a._add_card(Card(4, 12));
    a._add_card(Card(4, 11));
    a._add_card(Card(4, 10));

    a._print_hand();
    cout << "Royal flush: " << _hand_type_evaluation(a) << endl << endl;
    a._clear_hand();
    a._clear_memo();
    //straight flush

    a._add_card(Card(1, 9));
    a._add_card(Card(1, 13));
    a._add_card(Card(1, 12));
    a._add_card(Card(1, 11));
    a._add_card(Card(1, 10));

    a._print_hand();
    cout << "Straight flush: " << _hand_type_evaluation(a) << endl << endl;
    a._clear_hand();
    a._clear_memo();
    //Four of a kind

    a._add_card(Card(1, 9));
    a._add_card(Card(2, 9));
    a._add_card(Card(3, 9));
    a._add_card(Card(4, 9));
    a._add_card(Card(2, 10));

    a._print_hand();
    cout << "Four of a kind: " << _hand_type_evaluation(a) << endl << endl;
    a._clear_hand();
    a._clear_memo();
    //Full house

    a._add_card(Card(1, 9));
    a._add_card(Card(2, 9));
    a._add_card(Card(3, 9));
    a._add_card(Card(4, 10));
    a._add_card(Card(2, 10));

    a._print_hand();
    cout << "Full House: " << _hand_type_evaluation(a) << endl << endl;
    a._clear_hand();
    a._clear_memo();
    //Flush
    a._add_card(Card(1, 9));
    a._add_card(Card(1, 2));
    a._add_card(Card(1, 14));
    a._add_card(Card(1, 10));
    a._add_card(Card(1, 5));

    a._print_hand();
    cout << "Flush: " << _hand_type_evaluation(a) << endl << endl;
    a._clear_hand();
    a._clear_memo();
    //straight
    a._add_card(Card(1, 9));
    a._add_card(Card(2, 13));
    a._add_card(Card(3, 12));
    a._add_card(Card(1, 11));
    a._add_card(Card(2, 10));

    a._print_hand();
    cout << "Straight: " << _hand_type_evaluation(a) << endl << endl;
    a._clear_hand();
    a._clear_memo();
    //three of a kind
    a._add_card(Card(1, 9));
    a._add_card(Card(2, 9));
    a._add_card(Card(3, 9));
    a._add_card(Card(1, 2));
    a._add_card(Card(2, 4));

    a._print_hand();
    cout << "Three of a kind: " << _hand_type_evaluation(a) << endl << endl;
    a._clear_hand();
    a._clear_memo();
    //two pair
    a._add_card(Card(1, 9));
    a._add_card(Card(2, 9));
    a._add_card(Card(3, 8));
    a._add_card(Card(1, 4));
    a._add_card(Card(2, 4));

    a._print_hand();
    cout << "Two Pair: " << _hand_type_evaluation(a) << endl << endl;
    a._clear_hand();
    a._clear_memo();
    //Pair
    a._add_card(Card(1, 2));
    a._add_card(Card(2, 5));
    a._add_card(Card(3, 8));
    a._add_card(Card(1, 4));
    a._add_card(Card(2, 4));

    a._print_hand();
    cout << "Pair: " << _hand_type_evaluation(a) << endl << endl;
    a._clear_hand();
    a._clear_memo();
    //High Card
    a._add_card(Card(1, 2));
    a._add_card(Card(2, 5 ));
    a._add_card(Card(3, 8));
    a._add_card(Card(1, 10));
    a._add_card(Card(2, 13));

    a._print_hand();
    cout << "High Card: " << _hand_type_evaluation(a) << endl << endl;
    a._clear_hand();
    a._clear_memo();
}