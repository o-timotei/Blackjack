#include<vector>
#include<iostream>
#include<string>
#include<fstream>
#include "Deck.hpp"

using namespace std;

int CalculateHandTotal(vector<Card>& hand) // Functie care calculeaza totalul mainii
{
    int total = 0;
    int numAces = 0;

    for (auto& card : hand)
    {
        if (card.GetValue() == CardNames::ACE)
        {
            total += 11;
            numAces++;
        }
        else if (card.GetValue() == CardNames::TWO)
        {
            total += 2;
        }
        else if (card.GetValue() == CardNames::THREE)
        {
            total += 3;
        }
        else if (card.GetValue() == CardNames::FOUR)
        {
            total += 4;
        }
        else if (card.GetValue() == CardNames::FIVE)
        {
            total += 5;
        }
        else if (card.GetValue() == CardNames::SIX)
        {
            total += 6;
        }
        else if (card.GetValue() == CardNames::SEVEN)
        {
            total += 7;
        }
        else if (card.GetValue() == CardNames::EIGHT)
        {
            total += 8;
        }
        else if (card.GetValue() == CardNames::NINE)
        {
            total += 9;
        }
        else if (card.GetValue() == CardNames::TEN || card.GetValue() == CardNames::JACK || card.GetValue() == CardNames::QUEEN || card.GetValue() == CardNames::KING)
        {
            total += 10;
        }
    }

    // Ajustam valoarea asurilor daca totalul mainii este mai mare de 21
    while (total > 21 && numAces > 0)
    {
        total -= 10;
        numAces--;
    }

    return total;
}

// functie pentru actualizarea balantei jucatorului in fisierul Money.txt
void UpdatePlayerBalance(const string& username, int balance)
{
    ifstream inputFile("Money.txt");
    ofstream outputFile("temp.txt");

    string line;
    while (getline(inputFile, line))
    {
        int pos = line.find(",");
        string existingUsername = line.substr(0, pos);

        if (existingUsername == username)
        {
            outputFile << username << "," << balance << endl;
        }
        else
        {
            outputFile << line << endl;
        }
    }

    inputFile.close();
    outputFile.close();

    remove("Money.txt");
    rename("temp.txt", "Money.txt");
}