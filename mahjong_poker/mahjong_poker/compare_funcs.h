#pragma once

// HELPER FUNCTIONS for Comparing between hands
// int for the correspponding hand, 10: royal flush, 9: straight flush, 8: 4 of a kind, 
//  7: full house, 6: flush, 5: straight, 4: 3 of a kind, 3: two pair, 2: pair, 1: high card

//TODO: _compare_same_hand_type for flushes and lower hand values 

#include <iostream>
#include <string>
#include "deck.h"
#include "player.h"
#include <algorithm>
#include <map>

using namespace std;

int _compare_same_hand_type(Player& a, Player& b, map<int, vector<int>>& memo_a, map<int, vector<int>>& memo_b, string hand_type);
int hand_combi_value(string hand_type);
string _hand_type_evaluation(Player a, map<int, vector<int>>& memo);
void _update_memo(Card a, map<int, vector<int>>& memo);
bool _is_royal_flush(Player a, int i);
bool _is_straight(Player a, int i, bool flush);
int _compare_cards(Card& a, Card& b);
int _compare_values(Card& a, Card& b);
int _compare_suits(Card& a, Card& b);
Card _highest_card_in_memo_based_on_copies(map<int, vector<int>>& memo, int value);
int _compare_hands(Player& a, Player& b);

//return player's number

int evaluate_winner(Player* schedule[], int number_of_players) {
    int winning_index = 0;

    for (int i = 1; i < number_of_players; i++) {
        winning_index = _compare_hands(*(schedule[winning_index]), *(schedule[i])) - 1;
    }

    return winning_index;
}






int _compare_hands(Player &a, Player &b) {
 
    string hand_a_type = _hand_type_evaluation(a, a._get_memo());
    string hand_b_type = _hand_type_evaluation(b, b._get_memo());

    int hand_a_type_value = hand_combi_value(hand_a_type);
    int hand_b_type_value = hand_combi_value(hand_b_type);

    if (hand_a_type_value > hand_b_type_value) {
        return a._get_player_no();
    }
    else if (hand_b_type_value > hand_a_type_value) {
        return b._get_player_no();
    }
    else {
        return _compare_same_hand_type(a, b, a._get_memo(), b._get_memo(), hand_a_type);
    }
    return 0;
}


//return int for the hand combinations based on the comments at top.
int hand_combi_value(string hand_type) {
    if (hand_type == "royal_flush") {
        return 10;
    }

    if (hand_type == "straight_flush") {
        return 9;
    }

    if (hand_type == "four_of_a_kind") {
        return 8;
    }

    if (hand_type == "full_house") {
        return 7;
    }

    if (hand_type == "flush") {
        return 6;
    }

    if (hand_type == "straight") {
        return 5;
    }

    if (hand_type == "three_of_a_kind") {
        return 4;
    }

    if (hand_type == "two_pair") {
        return 3;
    }

    if (hand_type == "pair") {
        return 2;
    }

    if (hand_type == "high_card") {
        return 1;
    }
    else {
        cerr << "Error in _hand_combi_value";
        return 0;
    }

}


// the int "hand_combination" that reaches a counter of 4 means that the hand has that combination 
//(eg. int royal_flush = 4, means the hand is a royal flush)
string _hand_type_evaluation(Player a, map<int, vector<int>>& memo) {
    a._hand_sort(1);
    int size = a._return_size();
    int royal_flush = 0;
    int straight_flush = 0;
    int straight = 0;

    int highest_count = 0;
    int second_highest_count = 0;

    map<int, vector<int>>::iterator iter;

    int i = 0;
    for (i = 0; i < size - 1; i++) {

        if (_is_royal_flush(a, i)) {
            royal_flush++;
        }

        if (_is_straight(a, i, true)) {
            straight_flush++;
        }

        if (_is_straight(a, i, false)) {
            straight++;
        }

        _update_memo(a._access_card(i), memo);
    }
    _update_memo(a._access_card(i + 1), memo);

    if (royal_flush == 4) {
        return "royal_flush";
    }
    else if (straight_flush == 4) {
        return "straight_flush";
    }
    else if (straight == 4) {
        return "straight";
    }

    for (iter = memo.begin(); iter != memo.end(); iter++) {
        if ( (int)iter->second.size() >= highest_count) {
            second_highest_count = highest_count;
            highest_count = iter->second.size();
        }
    }


    switch (highest_count) {
    case 4:
        return "four_of_a_kind";

    case 3:
        if (second_highest_count == 2) {
            return "full_house";
        }
        else {
            return "three_of_a_kind";
        }
    case 2:
        if (second_highest_count == 2) {
            return "two_pair";
        }
        else {
            return "pair";
        }

    default:
        return "high_card";
    }

}

//comparing hands that have the same type
int _compare_same_hand_type(Player& a, Player& b, map<int, vector<int>>& memo_a, map<int, vector<int>>& memo_b, string hand_type) {
    a._hand_sort(1);
    b._hand_sort(1);

    int result = 0;
    Card temp_a(0,0);
    Card temp_b(0,0);


    int index = 4;

    if (hand_type == "royal_flush" || hand_type == "flush" || hand_type == "straight" || hand_type == "high_card") {
        temp_a = a._access_card(index);
        temp_b = b._access_card(index);
    }
    else if (hand_type == "straight_flush") {

        //for exception if straight flush hand starts with ace
        if (a._access_card(4)._get_value() == 14 && index == 4) {
            temp_a = a._access_card(3);
        }
        else if (b._access_card(4)._get_value() == 14 && index == 4) {
            temp_b = a._access_card(3);   
        }
        
    }
    else if (hand_type == "four_of_a_kind") {
        temp_a = _highest_card_in_memo_based_on_copies(memo_a, 4);
        temp_b = _highest_card_in_memo_based_on_copies(memo_b, 4);
        
    }
    else if (hand_type == "full_house" || hand_type == "three_of_a_kind") {
        temp_a = _highest_card_in_memo_based_on_copies(memo_a, 3);
        temp_b = _highest_card_in_memo_based_on_copies(memo_b, 3);
        
    }
    else if (hand_type == "two_pair" || hand_type == "pair") {
        temp_a = _highest_card_in_memo_based_on_copies(memo_a, 2);
        temp_b = _highest_card_in_memo_based_on_copies(memo_b, 2);
    }
    
    result = _compare_cards(temp_a, temp_b);

    if (result == 1) {
        return a._get_player_no();
    }
    else {
        return b._get_player_no();
    }

    return 0;
}


Card _highest_card_in_memo_based_on_copies(map<int, vector<int>>& memo, int number_of_copies) {
    int highest_suit = 0;
    int highest_value = 0;
    map<int, vector<int>>::iterator iter;

    for(iter = memo.begin(); iter != memo.end(); iter++) {
        if ((int)iter->second.size() == number_of_copies && iter->first > highest_value) {
            highest_value = iter->first;
            highest_suit = *(max_element(iter->second.begin(), iter->second.end() ));
        }
    }

    return Card(highest_value, highest_suit);
}


//compare based on value first, then suits
int _compare_cards(Card& a, Card& b) {
    int result = 0;
    result = _compare_values(a, b);
    if (result == 0) {
        result = _compare_suits(a, b);
    }

    return result;

}


int _compare_suits(Card& a, Card& b) {
    if (a._get_suit() > b._get_suit()) {
        return 1;
    }
    else {
        return 0;
    }
}

int _compare_values(Card& a, Card& b) {
    if (a._get_suit() > b._get_suit()) {
        return 1;
    }
    else if (b._get_suit() > a._get_suit()) {
        return -1;
    }
    else {
        return 0;
    }
}




bool _is_royal_flush(Player a, int i) {
    return (a._access_card(i)._get_value() == a._access_card(i + 1)._get_value() - 1
        && a._access_card(i)._get_suit() == a._access_card(i + 1)._get_suit() && a._access_card(0)._get_value() == 10);
}

bool _is_straight(Player a, int i, bool flush) {
    if (flush) {
        switch (i) {
        case 0:
            return ((a._access_card(i)._get_value() == a._access_card(i + 1)._get_value() - 1
                || a._access_card(4)._get_value() - a._access_card(i)._get_value() == 12)
                && a._access_card(i)._get_suit() == a._access_card(i + 1)._get_suit());

        case 3:
            return ((a._access_card(i)._get_value() == a._access_card(i + 1)._get_value() - 1
                || a._access_card(4)._get_value() - a._access_card(0)._get_value() == 12)
                && a._access_card(i)._get_suit() == a._access_card(i + 1)._get_suit());

        default:
            return (a._access_card(i)._get_value() == a._access_card(i + 1)._get_value() - 1
                && a._access_card(i)._get_suit() == a._access_card(i + 1)._get_suit());
        }
    }
    else {
        switch (i) {
        case 0:
            return (a._access_card(i)._get_value() == a._access_card(i + 1)._get_value() - 1
                || a._access_card(4)._get_value() - a._access_card(i)._get_value() == 12);

        case 3:
            return (a._access_card(i)._get_value() == a._access_card(i + 1)._get_value() - 1
                || a._access_card(4)._get_value() - a._access_card(0)._get_value() == 12);

        default:
            return (a._access_card(i)._get_value() == a._access_card(i + 1)._get_value() - 1);

        }
    }

}

void _update_memo(Card a, map<int, vector<int>>& memo) {
    int card_value = a._get_value();
    if (memo.count(card_value) == 0) {
        memo.insert(pair <int, vector<int>>(card_value, vector<int>()));
    }

    memo.find(card_value)->second.push_back(a._get_suit());
}