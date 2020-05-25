
#include "../Test Header Files/test_cases.h"

void _test_cases_consolidated() {
    //_test_hand_types();
    _test_compare_card();

}

void _test_compare_card() {
    int result = 0;
    Card a(3, 8);
    Card b(4, 7);
    result = _compare_cards(a, b);

    if (result == 1) {
        cout << "A" << endl;
    }
    else {
        cout << "B" << endl;
    }
}


void _test_hand_types() {
    Player a("test", 1);

    //For royale flush
    _load_royal_flush(a, 4);

    a._print_hand();
    cout << "Royal flush: " << _hand_type_in_string(_hand_type_evaluation(a)) << endl << endl;
    a._print_memo();
    a._clear_hand();
    a._clear_memo();

    //straight flush

    _load_straight_flush(a, 3, 5);

    a._print_hand();
    cout << "Straight flush: " << _hand_type_in_string(_hand_type_evaluation(a)) << endl << endl;
    a._print_memo();
    a._clear_hand();
    a._clear_memo();

    //Four of a kind

    a._add_card(Card(1, 9));
    a._add_card(Card(2, 9));
    a._add_card(Card(3, 9));
    a._add_card(Card(4, 9));
    a._add_card(Card(2, 10));

    a._print_hand();
    cout << "Four of a kind: " << _hand_type_in_string(_hand_type_evaluation(a)) << endl << endl;
    a._print_memo();
    a._clear_hand();
    a._clear_memo();

    //Full house

    a._add_card(Card(1, 9));
    a._add_card(Card(2, 9));
    a._add_card(Card(3, 9));
    a._add_card(Card(4, 10));
    a._add_card(Card(2, 10));

    a._print_hand();
    cout << "Full House: " << _hand_type_in_string(_hand_type_evaluation(a)) << endl << endl;
    a._print_memo();
    a._clear_hand();
    a._clear_memo();

    //Flush
    a._add_card(Card(1, 9));
    a._add_card(Card(1, 2));
    a._add_card(Card(1, 14));
    a._add_card(Card(1, 10));
    a._add_card(Card(1, 5));

    a._print_hand();
    cout << "Flush: " << _hand_type_in_string(_hand_type_evaluation(a)) << endl << endl;
    a._print_memo();
    a._clear_hand();
    a._clear_memo();

    //straight
    a._add_card(Card(1, 9));
    a._add_card(Card(2, 13));
    a._add_card(Card(3, 12));
    a._add_card(Card(1, 11));
    a._add_card(Card(2, 10));

    a._print_hand();
    cout << "Straight: " << _hand_type_in_string(_hand_type_evaluation(a)) << endl << endl;
    a._print_memo();
    a._clear_hand();
    a._clear_memo();

    //three of a kind
    a._add_card(Card(1, 9));
    a._add_card(Card(2, 9));
    a._add_card(Card(3, 9));
    a._add_card(Card(1, 2));
    a._add_card(Card(2, 4));

    a._print_hand();
    cout << "Three of a kind: " << _hand_type_in_string(_hand_type_evaluation(a)) << endl << endl;
    a._print_memo();
    a._clear_hand();
    a._clear_memo();

    //two pair
    a._add_card(Card(1, 9));
    a._add_card(Card(2, 9));
    a._add_card(Card(3, 8));
    a._add_card(Card(1, 4));
    a._add_card(Card(2, 4));

    a._print_hand();
    cout << "Two Pair: " << _hand_type_in_string(_hand_type_evaluation(a)) << endl << endl;
    a._print_memo();
    a._clear_hand();
    a._clear_memo();

    //Pair
    a._add_card(Card(1, 2));
    a._add_card(Card(2, 5));
    a._add_card(Card(3, 8));
    a._add_card(Card(1, 4));
    a._add_card(Card(2, 4));

    a._print_hand();
    cout << "Pair: " << _hand_type_in_string(_hand_type_evaluation(a)) << endl << endl;
    a._print_memo();
    a._clear_hand();
    a._clear_memo();
    //High Card
    a._add_card(Card(1, 2));
    a._add_card(Card(2, 5));
    a._add_card(Card(3, 8));
    a._add_card(Card(1, 10));
    a._add_card(Card(2, 13));

    a._print_hand();
    cout << "High Card: " << _hand_type_in_string( _hand_type_evaluation(a)) << endl << endl;
    a._print_memo();
    a._clear_hand();
    a._clear_memo();
}

void _load_royal_flush(Player& a, int suits) {
    a._add_card(Card(suits, 14));
    a._add_card(Card(suits, 13));
    a._add_card(Card(suits, 12));
    a._add_card(Card(suits, 11));
    a._add_card(Card(suits, 10));
}

void _load_straight_flush(Player& a, int suits, int start) {
    a._add_card(Card(suits, start));
    a._add_card(Card(suits, start + 1));
    a._add_card(Card(suits, start + 2));
    a._add_card(Card(suits, start + 3));
    a._add_card(Card(suits, start + 4));

}

void _load_four_kind(Player& a, int copy) {
    a._add_card(Card(1, copy));
    a._add_card(Card(2, copy));
    a._add_card(Card(3, copy));
    a._add_card(Card(4, copy));
    a._add_card(Card(4, 10));
}
//void _load