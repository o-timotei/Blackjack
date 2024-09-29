#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

#ifndef SUITS_HPP // Folosim pentru a nu include de doua ori acelasi fisier in compilare
#define SUITS_HPP 

enum class Suits // Enumeratie pentru suita cartilor
{
    CLUBS,
    HEARTS,
    DIAMONDS,
    SPADES
};



enum class CardNames // Enumeratie pentru numele cartilor
{
    ACE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
};

class Card
{
public:
    CardNames name;
    Suits suit;
    int value;

    void PrintCard()
    {
        this->PrintValue(this->name);

        std::cout << " of ";

        this->PrintSuit(this->suit);

        std::cout << std::endl;
    }


    void PrintValue(CardNames name)
    {
        if (name == CardNames::JACK)
        {
            std::cout << " - Jack";
        }
        else if (name == CardNames::QUEEN)
        {
            std::cout << " - Queen";
        }
        else if (name == CardNames::KING)
        {
            std::cout << " - King";
        }
        else if (name == CardNames::ACE)
        {
            std::cout << " - Ace";
        }
        else
        {
            std::cout << " - " << static_cast<int>(name);
        }
    }

    void PrintSuit(Suits suit)
    {
        if (suit == Suits::CLUBS)
        {
            std::cout << "Clubs -";
        }
        else if (suit == Suits::DIAMONDS)
        {
            std::cout << "Diamonds -";
        }
        else if (suit == Suits::SPADES)
        {
            std::cout << "Spades -";
        }
        else if (suit == Suits::HEARTS)
        {
            std::cout << "Hearts -";
        }
    }

    CardNames GetValue()
    {
        if (name == CardNames::JACK)
        {
            return CardNames::JACK;
        }
        else if (name == CardNames::QUEEN)
        {
            return CardNames::QUEEN;
        }
        else if (name == CardNames::KING)
        {
            return CardNames::KING;
        }
        else if (name == CardNames::ACE)
        {
            return CardNames::ACE;
        }
        else
        {
            return name;
        }
    }

    Suits GetSuit()
    {
        if (suit == Suits::CLUBS)
        {
            return Suits::CLUBS;
        }
        else if (suit == Suits::DIAMONDS)
        {
            return Suits::DIAMONDS;
        }
        else if (suit == Suits::SPADES)
        {
            return Suits::SPADES;
        }
        else if (suit == Suits::HEARTS)
        {
            return Suits::HEARTS;
        }
    }
};

class Deck
{
public:
    std::vector<Card> arrCards;

    void PrintAll()
    {
        for (int col = (int)Suits::CLUBS; col <= (int)Suits::SPADES; col++)
        {
            for (int row = (int)CardNames::ACE; row <= (int)CardNames::KING; row++)
            {
                int index = (13 * col) + row - 1;
                arrCards[index].PrintCard();
            }
            std::cout << std::endl;
        }
    }

    void SetupCards()
    {
        arrCards.resize(52); // Facem resize la vector sa contina doar 52 de elemente

        for (int col = (int)Suits::CLUBS; col <= (int)Suits::SPADES; col++)
        {
            for (int row = (int)CardNames::ACE; row <= (int)CardNames::KING; row++) // Iteram prin fiecare carte si setam numele, suita si valoarea ei
            {
                Card c;
                c.name = (CardNames)row;
                c.suit = (Suits)col;

                if (c.name == CardNames::JACK || c.name == CardNames::KING || c.name == CardNames::QUEEN) // Daca cartea este J/Q/K, valoarea ei este 10
                {
                    c.value = 10;
                }
                else if (c.name == CardNames::ACE) // Daca cartea este As, valoarea ei este 11
                {
					c.value = 11;
				}
                else
                {
                    c.value = (int)c.name; // Castam numele cartii la int pentru a obtine valoarea ei
                }

                int index = (13 * col) + row - 1; // Calculam indexul cartii in vector
                arrCards[index] = c; // Adaugam cartea in vector
            }
        }
    }

    void Shuffle()
    {
        srand(time(0)); // Cream seed-ul pentru functia rand()

        for (int i = 0; i < 52; i++)
        {
            int randomIndex = rand() % 52; // Generam un index random

            // Schimbam cartea de pe pozitia i cu cartea de pe pozitia randomIndex
            Card temp = arrCards[i];
            arrCards[i] = arrCards[randomIndex];
            arrCards[randomIndex] = temp;
        }
    }

    Card DrawCard()
    {
        Card drawnCard = arrCards.back(); 
        arrCards.pop_back(); // Scoatem cartea din vector
        return drawnCard;
    }
};
#endif
