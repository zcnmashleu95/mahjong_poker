#pragma once

// HELPER FUNCTIONS for Comparing between hands
// int values for the correspponding hand, 10: royal flush, 9: straight flush, 8: 4 of a kind, 
//  7: full house, 6: flush, 5: straight, 4: 3 of a kind, 3: two pair, 2: pair, 1: high card

//TODO: Everythings works but lots to be improved upon/streamlined

#include "../Header Files/compare_hands_funcs.h"


//return player's number
// winning index i < number of players 4, 3
int _evaluate_winner(Player* schedule[], int number_of_players) {
    int winning_index = 0;

    for (int i = 1; i < number_of_players; i++) {
        //cout << "Compare :" << winning_index << " " << i << endl;
        winning_index = _compare_hands(*(schedule[winning_index]), *(schedule[i]));
        //cout << "Winner is  " << winning_index << endl;
    }

    return winning_index;
}


//returns the index in the schedule
int _compare_hands(Player &a, Player &b) {
 
    
    int hand_a_type_value = _hand_type_evaluation(a);
    int hand_b_type_value = _hand_type_evaluation(b);

    string hand_a_type = _hand_type_in_string(hand_a_type_value);
    string hand_b_type = _hand_type_in_string(hand_b_type_value);

    if (hand_a_type_value > hand_b_type_value) {
        return a._get_player_no() - 1;
    }
    else if (hand_b_type_value > hand_a_type_value) {
        return b._get_player_no() - 1;
    }
    else {
        return _compare_same_hand_type(a, b, hand_a_type_value) - 1;
    }
    return 0;
}


//return an int for the hand combinations based on the comments at top.
string _hand_type_in_string(int hand_type) {
    switch (hand_type) {
        case 10:
            return "Royal Flush";
        case 9:
            return "Straight Flush";
        case 8:
            return "Four of a kind";
        case 7:
            return "Full House";
        case 6:
            return "Flush";
        case 5:
            return "Straight";
        case 4:
            return "Three of a kind";
        case 3:
            return "Two Pair";
        case 2:
            return "Pair";
        case 1:
            return "High Card";

        default:
            cerr << "Error in Hand type evaluation";
            return "Error";
    }

}


// the int "hand_combination" that reaches a counter of 4 means that the hand has that combination 
//(eg. int royal_flush = 4, means the hand is a royal flush)

int _hand_type_evaluation(Player &a) {

    a._hand_sort(1);
    int size = a._get_hand_size();
    int royal_flush = 0;
    int straight_flush = 0;
    int straight = 0;
    int flush = 0;

    int highest_count = 0;
    int sec_highest_count = 0;
    int highest_count_card_value = 0;
    int sec_highest_count_card_value = 0;

    map<int, vector<int>>::iterator iter;

    int index = 0;
    // [0] to [2], [3] will compare with [4]. size = 5.
    // this entire section can be further improved,
    for (index = 0; index <= size - 1; index++) {

        if (_is_royal_flush(a, index)) {
            royal_flush++;
        }

        if (_is_straight(a, index, true)) {
            straight_flush++;
        }

        if (_is_straight(a, index, false)) {
            straight++;
        }

        if (_is_flush(a, index)) {
            flush++;
        }
    }


    if (royal_flush == 4) {
        return 10;
    }
    else if (straight_flush == 4) {
        return 9;
    }
    else if (flush == 4) {
        return 6;
    }
    else if (straight == 4) {
        return 5;
    }


    a._clear_memo();

    a._update_player_hand_to_memo();
    a._top_two_counts_in_memo(highest_count, sec_highest_count, highest_count_card_value, sec_highest_count_card_value);

    //cout << "Highest count: " << highest_count << " Value: " << highest_count_card_value << endl;
    //cout << "Sec highest: " << sec_highest_count << " Value: "<< sec_highest_count_card_value << endl;


    switch (highest_count) {
    case 4:
        return 8;

    case 3:
        if (sec_highest_count == 2) {
            return 7;
        }
        else {
            return 4;
        }
    case 2:
        if (sec_highest_count == 2) {
            return 3;
        }
        else {
            return 2;
        }

    default:
        return 1;
    }

}

//comparing hands that have the same type, will return the winning PLAYER NUMBER
int _compare_same_hand_type(Player& a, Player& b, int hand_type) {
    a._hand_sort(1);
    b._hand_sort(1);

    int result = 0;
    Card temp_a(0,0);
    Card temp_b(0,0);


    int index = 4;

    //royal flush, flush, straight, high_card,
    if (hand_type == 10 || hand_type == 6 || hand_type == 5 || hand_type == 1) {
        temp_a = a._access_card(index);
        temp_b = b._access_card(index);
    }
    else if (hand_type == 9) {
        //for exception if straight flush hand starts with ace
        if (a._access_card(4)._get_value() == 14 && index == 4) {   
            temp_a = a._access_card(3); 
        }
        else {
            temp_a = a._access_card(index);
        }


        if (b._access_card(4)._get_value() == 14 && index == 4) { 
            temp_b = b._access_card(3); 
        }
        else {
            temp_b = b._access_card(index);
        }
        
    }
    else if (hand_type == 8) {
        //four of a kind
        temp_a = a._highest_card_in_memo_based_on_copies(4);
        temp_b = b._highest_card_in_memo_based_on_copies(4);
        
    }
    else if (hand_type == 7 || hand_type == 4) {
        //full house, 3 of a kind
        temp_a = a._highest_card_in_memo_based_on_copies(3);
        temp_b = b._highest_card_in_memo_based_on_copies(3);
        
    }
    else if (hand_type == 3 || hand_type == 2) {
        //two_pair and pair
        temp_a = a._highest_card_in_memo_based_on_copies(2);
        temp_b = b._highest_card_in_memo_based_on_copies(2);
    }
    

    //cout << a._get_player_no() - 1 << ": ";
    //temp_a._print_card();
    //cout << endl;
    //cout << b._get_player_no() - 1 << ": ";
    //temp_b._print_card();
    //cout << endl;

    result = _compare_cards(temp_a, temp_b);

    if (result == 1) {
        return a._get_player_no();
    }
    else if (result == -1){
        return b._get_player_no();
    }

    return 0;
}


//
//compare based on value first, then suits
int _compare_cards(Card& a, Card& b) {
    int result = 0;
    result = _compare_values(a, b);
    if (result == 0) {
        result = _compare_suits(a, b);
    }

    return result;

}


int _compare_values(Card& a, Card& b) {
    if (a._get_value() > b._get_value()) {
        return 1;
    }
    else if (b._get_value() > a._get_value()) {
        return -1;
    }
    else {
        return 0;
    }
}


int _compare_suits(Card& a, Card& b) {
    if (a._get_suit() > b._get_suit()) {
        return 1;
    }
    else {
        return -1;
    }
}






bool _is_royal_flush(Player &a, int index) {
    return (a._access_card(index)._get_value() == a._access_card(index + 1)._get_value() - 1
        && a._access_card(index)._get_suit() == a._access_card(index + 1)._get_suit() && a._access_card(0)._get_value() == 10);
}

// Ace = 14, Ace - 2 = 12
bool _is_straight(Player &a, int index, bool flush) {
    if (flush) {
        switch (index) {
        case 0:
            return ((a._access_card(index)._get_value() == a._access_card(index + 1)._get_value() - 1
                || a._access_card(4)._get_value() - a._access_card(index)._get_value() == 12)
                && a._access_card(index)._get_suit() == a._access_card(index + 1)._get_suit());

        case 3:
            return ((a._access_card(index)._get_value() == a._access_card(index + 1)._get_value() - 1
                || a._access_card(4)._get_value() - a._access_card(0)._get_value() == 12)
                && a._access_card(index)._get_suit() == a._access_card(index + 1)._get_suit());

        default:
            return (a._access_card(index)._get_value() == a._access_card(index + 1)._get_value() - 1
                && a._access_card(index)._get_suit() == a._access_card(index + 1)._get_suit());
        }
    }
    else {
        switch (index) {
        case 0:
            return (a._access_card(index)._get_value() == a._access_card(index + 1)._get_value() - 1
                || a._access_card(4)._get_value() - a._access_card(index)._get_value() == 12);

        case 3:
            return (a._access_card(index)._get_value() == a._access_card(index + 1)._get_value() - 1
                || a._access_card(4)._get_value() - a._access_card(0)._get_value() == 12);

        default:
            return (a._access_card(index)._get_value() == a._access_card(index + 1)._get_value() - 1);

        }
    }

}


bool _is_flush(Player &a, int index) {
    return (a._access_card(index)._get_suit() == a._access_card(index + 1)._get_suit());
}
