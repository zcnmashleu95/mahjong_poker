#pragma once
#include <string>

using namespace std;

#define INVALID_INPUT "The input that you have entered is invalid. Please enter again"

#define WELCOME_MESSAGE "Welcome to Mahjong Poker \n\nThis is a turn based game whereby you try to construct your winning hand and pit it against other players."
#define GAME_INSTRUCTIONS "Instructions: \nEach player will start off with 5 cards in their hand. During each turn, the corresponding player will draw a card from the deck and choose a card to be discarded from their hand."
#define HOW_TO_WIN "How to WIN: When the deck runs out of cards, every player's hand will be evaluated. The player with the highest valued hand wins.\n"
#define HAND_ORDER "The hand types follow this order. Royal Flush is the most valued hand type. Royal Flush > Straight Flush > 4 of a kind > Full House > Flush > /nStraight > 3 of a kind > Two Pair > Pair > High Card"
#define HAND_EVALUATION "In the event that 2 similar hand types are compared, the hands will be compared based on the highest valued cards that forms the respective hands. First by Card Value, then the Card Suit.\n Eg. Hand 1: Highcard (8, Spade)		Hand 2: Highcard (8, Club)\n Hand 1 is the winner."


#define INPUT_NAME "Please type in the name for your player:"
#define INPUT_POINTS "Please input the amount of points you wish to have for the game. From 1 to 100."
#define INPUT_WAGER "Please input the wager amount that you wish to wager every match. The wager amount should not be more than the points set earlier."
#define INPUT_COM "Please input the number of Computer Players that you wish to compete against. Min: 1 Max: 3"
#define INPUT_HUMAN "Please input which player you want to be. This will determine the turn order. (eg. If you input 2, you will be the 2nd player)"
#define INPUT_DIFFICULTY "Please input the difficulty level of the Computer Player. As the level increases, the computer player is less likely to discard cards beneficial to his hand.\n1: Easy  2: Normal  3: Difficult"
#define INPUT_CHEATS "Do you wish to enable cheats?\n1: Default(no cheats)  2: Print opponents' hands during your turn  3: Print the deck during your turn  4: Combination of 2 and 3"

#define PLAYER_OPTIONS "What do you want to do? Input the number for the following options. \n1: Continue to the Discard Phase  2: Sort your hand by Card value  3: Sort your hand by Card suit  4: Print the Discard Pile  0: Resign "
#define CONTINUE_OR_QUIT "The match is over. Do you want to \n1: Continue to a new match  9: New Game  0:Quit"
#define NEW_OR_QUIT "Game Over. Do you want to \n1: Continue to a new match  9: New Game  0:Quit"

