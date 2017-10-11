#ifndef DECK_H
#define DECK_H

#include <array>
#include "card.h"

class Deck
{
private:
    std::array<Card, 52> m_deck;
    int m_cardIndex;
public:
    Deck();

    void printDeck() const;
    void shuffleDeck();

    static int getRandomNumber(int min, int max);

    static void swapCard(Card &a, Card &b);
    const Card& dealCard();
};

#endif // DECK_H
