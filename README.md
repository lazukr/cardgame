# Card Game

This is a simple text game that I made partly from boredom and partly from wanting to explore what writing in C is like.

## Gameplay

The game is played using the standard playing cards. Each player gets half the deck corresponding to the color (all the red cards for one player, all the black for the other).
Each player's deck will be shuffled and 14 cards will be drawn faced down onto a pile known as the `field`. 

During each turn, the player does the following steps:

1. Flip two cards on the opponent's field
    * if the cards are a matching pair of numbers, it is removed from the game and the player scores a point. The opponent's field is then replished from drawing two more cards from their deck. If their deck is empty, then they do not draw.
    * if the cards do not match, they are placed face down again.

Players will continue to go back and forth until one player's field and deck is empty.

## Things to add in the future
* AI that can play with you
    * Multiple difficulties
* Optional move to remove card from your deck to make it harder for your opponent to keep track of all your cards
* Multiplayer, perhaps?

