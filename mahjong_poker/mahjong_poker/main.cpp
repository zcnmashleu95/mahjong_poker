#pragma once
#include "deck.h"
#include <iostream>



using namespace std;

int main() {
    string welcome_speech = "Welcome to the game \n";    
    cout << welcome_speech;


    Deck new_deck;
    new_deck.print_deck();
    new_deck.shuffle_deck();
    new_deck.print_deck();


}