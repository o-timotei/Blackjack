

#include <iostream>
#include <fstream>
#include <string>
#include<vector>

#include "Deck.hpp"
#include "LoginRegister.hpp"
#include "MiscFunctions.hpp"    

using namespace std;

string moneyBalance;

// functie pentru jocul de Blackjack
void playBlackjack()
{
    Deck deck;
    int choice;
    string username, password;
    int playerBalance;



    deck.SetupCards();
    deck.Shuffle();
    cout << "=========================================================" << endl;
    cout << endl;
    cout << "       Welcome to the Blackjack game!" << endl;
    cout << endl;
    cout << "=========================================================" << endl;

    while (true) {
        cout << endl;
        cout << "=========================================================" << endl;
        cout << " 1. Login" << endl;
        cout << " 2. Register" << endl;
        cout << " 3. Exit" << endl;
        cout << "=========================================================" << endl;
        cout << endl;
        cout << " Enter your choice: ";
        cin >> choice;
        cout << endl;

        if (choice == 1) // Login
        {
            cout << "=========================================================" << endl;
            cout << endl;
            cout << " Enter your username: ";
            cin >> username;
            cout << " Enter your password: ";
            cin >> password;
            cout << endl;
            cout << "=========================================================" << endl;

            system("cls");

            if (loginUser(username, password))
            {
                cout << "=========================================================" << endl;
                cout << endl;
                cout << "              Login successful!" << endl;
                cout << endl;
                cout << "=========================================================" << endl;


                // Dam display la username si balanta $
                ifstream moneyFile("Money.txt"); // Deschidem fisierul Money.txt
                string line; // Variabila in care salvam fiecare linie din fisierul text    

                while (getline(moneyFile, line)) // Citim fiecare linie din fisierul text si o salvam in variabila line 
                {
                    int pos = line.find(","); // Salvam pozitia virgulei intr-o variabila   
                    string existingUsername = line.substr(0, pos); // Salvam username-ul din fisierul text in variabila existingUsername incepand cu pozitia 0 pana la virgula  

                    if (existingUsername == username) // Verificam daca username-ul din fisierul text este acelasi cu cel introdus de la tastatura  
                    {
                        moneyBalance = line.substr(pos + 1); // Salvam balanta din fisierul text in variabila moneyBalance incepand cu pozitia virgulei + 1 
                        cout << endl;
                        cout << "=========================================================" << endl;
                        cout << " Username: " << username << endl;
                        cout << " Balance: $" << moneyBalance << endl; // Afisam balanta user-ului folosind variabila moneyBalance   
                        break;
                    }
                }

                moneyFile.close(); // Inchidem fisierul Money.txt   

                // Optiuni meniu
                while (true)
                {
                    cout << endl;
                    cout << " 1. Play" << endl;
                    cout << " 2. Exit" << endl;
                    cout << "=========================================================" << endl;
                    cout << endl;
                    cout << " Enter your choice: ";
                    cin >> choice;
                    cout << endl;
                    cout << "=========================================================" << endl;

                    if (choice == 1) // Play  
                    {
                        int playerBalance = stoi(moneyBalance); // Transformam string in integer
                        int betAmount;
                        cout << endl;
                        cout << " Enter the amount you want to bet: ";
                        cin >> betAmount;
                        cout << endl;
                        cout << "=========================================================" << endl;

                        system("cls");

                        if (betAmount > playerBalance) // Verificam daca suma introdusa este mai mare decat balanta user-ului
                        {
                            cout << "=========================================================" << endl;
                            cout << endl;
                            cout << " Insufficient balance. Please enter a valid bet amount." << endl;
                            cout << endl;
                            cout << "=========================================================" << endl;
                            continue;
                        }

                        // Impartim cartile initiale
                        vector<Card> playerHand;
                        vector<Card> dealerHand;

                        playerHand.push_back(deck.DrawCard());
                        dealerHand.push_back(deck.DrawCard());
                        playerHand.push_back(deck.DrawCard());
                        dealerHand.push_back(deck.DrawCard());

                        // Vedem cartile noastre
                        cout << "=========================================================" << endl;
                        cout << endl;
                        cout << " Player's Hand: " << endl;
                        cout << endl;
                        for (auto& card : playerHand)
                        {
                            card.PrintCard();
                        }
                        cout << endl;
                        cout << " Total: " << CalculateHandTotal(playerHand) << endl;
                        cout << endl;
                        cout << "=========================================================" << endl;
                        // Vedem prima carte a dealer-ului
                        cout << " Dealer's Hand: " << endl;
                        cout << endl;
                        dealerHand[0].PrintCard();
                        cout << endl;
                        cout << " Total: " << dealerHand[0].value << endl;
                        cout << endl;
                        cout << "=========================================================" << endl;

                        if (CalculateHandTotal(playerHand) == 21) // Verificam daca avem Blackjack
						{
							cout << "=========================================================" << endl;
							cout << endl;
							cout << " Blackjack! You win." << endl;
                            cout << " Previous balance: $" << playerBalance << endl; // Afisam balanta player-ului inainte de a castiga
                            cout << " Your bet: $" << betAmount << endl; // Afisam suma pariata
                            cout << " New balance: $" << playerBalance + betAmount<< endl; // Afisam balanta player-ului dupa ce a castigat
							cout << endl;
							cout << "=========================================================" << endl;
							playerBalance += betAmount * 1.5; // Adaugam suma pariata la variabila cu balanta player-ului
							UpdatePlayerBalance(username, playerBalance); // Dam update la banii player-ului in fisierul txt folosind functia UpdatePlayerBalance
							break;
						}

                        // Tura player-ului
                        bool playerBusted = false; // Variabila care ne spune daca player-ul a depasit 21
                        int playerTotal = 0;
                        while (true)
                        {
                            cout << " 1. Hit" << endl;
                            cout << " 2. Stand" << endl;
                            cout << "=========================================================" << endl;
                            cout << " Enter your choice: ";
                            cin >> choice;

                            if (choice == 1) // Hit
                            {
                                system("cls");
                                playerHand.push_back(deck.DrawCard()); // Tragem o carte 
                                cout << "=========================================================";
                                cout << endl;
                                cout << "The player drew a card." << endl;
                                cout << endl;

                                // Afisam cartile noastre
                                cout << "=========================================================" << endl;
                                cout << " Player's Hand: " << endl;
                                cout << endl;
                                for (auto& card : playerHand)
                                {
                                    card.PrintCard();
                                }
                                cout << endl;
                                cout << " Total: " << CalculateHandTotal(playerHand) << endl;
                                cout << "=========================================================" << endl;
                                cout << endl;

                                // Verificam daca noi avem peste 21
                                int playerTotal = CalculateHandTotal(playerHand);
                                if (playerTotal > 21)
                                {
                                    cout << "=========================================================" << endl;
                                    cout << endl;
                                    cout << " Player busted! You lose." << endl;
                                    cout << " Previous balance: $" << playerBalance << endl; // Afisam balanta player-ului inainte de a castiga
                                    cout << " Your bet: $" << betAmount << endl; // Afisam suma pariata
                                    cout << " New balance: $" << playerBalance - betAmount << endl; // Afisam balanta player-ului dupa ce a pierdut
                                    cout << endl;
                                    cout << "=========================================================" << endl;
                                    playerBusted = true;
                                    cout << endl;
                                    cout << " Dealer's Hand: " << endl;
                                    cout << endl;
                                    for (auto& card : dealerHand)
                                    {
                                        card.PrintCard();
                                    }
                                    cout << endl;
                                    cout << " Total: " << CalculateHandTotal(dealerHand) << endl;
                                    cout << endl;
                                    cout << "=========================================================" << endl;
                                    UpdatePlayerBalance(username, playerBalance); // Dam update la banii player-ului in fisierul txt folosind functia UpdatePlayerBalance
                                    break;

                                }
                                else if (CalculateHandTotal(playerHand) == 21) // Verificam daca avem Blackjack
                                {
                                    cout << "=========================================================" << endl;
                                    cout << endl;
                                    cout << " Blackjack! You win." << endl;
                                    cout << " Previous balance: $" << playerBalance << endl; // Afisam balanta player-ului inainte de a castiga
                                    cout << " Your bet: $" << betAmount << endl; // Afisam suma pariata
                                    cout << " New balance: $" << playerBalance + betAmount<< endl; // Afisam balanta player-ului dupa ce a castigat
                                    cout << endl;
                                    cout << "=========================================================" << endl;
                                    playerBalance += betAmount * 1.5; // Adaugam suma pariata la variabila cu balanta player-ului
                                    UpdatePlayerBalance(username, playerBalance); // Dam update la banii player-ului in fisierul txt folosind functia UpdatePlayerBalance
                                    break;
                                }
                                else if (CalculateHandTotal(dealerHand) == 21) // Verificam daca dealer-ul are Blackjack
                                {
                                    cout << "=========================================================" << endl;
                                    cout << " Dealer's Hand: " << endl;
                                    cout << endl;
                                    for (auto& card : dealerHand)
                                    {
                                        card.PrintCard();
                                    }
                                    cout << " Total: " << CalculateHandTotal(dealerHand) << endl;
                                    cout << endl;
                                    cout << "=========================================================" << endl;
                                    cout << endl;
                                    cout << " Dealer has Blackjack! You lose." << endl;
                                    cout << " Previous balance: $" << playerBalance << endl; // Afisam balanta player-ului inainte de a castiga
                                    cout << " Your bet: $" << betAmount << endl; // Afisam suma pariata
                                    cout << " New balance: $" << playerBalance - betAmount << endl; // Afisam balanta player-ului dupa ce a pierdut
                                    cout << endl;
                                    cout << "=========================================================" << endl;
                                    playerBalance -= betAmount; // Scadem suma pariata din variabila cu balanta player-ului
                                    UpdatePlayerBalance(username, playerBalance); // Dam update la banii player-ului in fisierul txt folosind functia UpdatePlayerBalance
                                    break;
                                }

                                cout << "=========================================================" << endl;
                                cout << " Dealer's Hand: " << endl;
                                cout << endl;
                                for (auto& card : dealerHand)
                                {
                                    card.PrintCard();
                                }
                                cout << endl;
                                cout << " Total: " << CalculateHandTotal(dealerHand) << endl;
                                cout << endl;
                                cout << "=========================================================" << endl;

                            }

							else if (choice == 2) // Stand  
							{
								if (CalculateHandTotal(dealerHand) == 21) // Verificam daca dealer-ul are Blackjack
								{
                                    // Afisam cartile noastre
                                    cout << "=========================================================" << endl;
                                    cout << " Player's Hand: " << endl;
                                    cout << endl;
                                    for (auto& card : playerHand)
                                    {
                                        card.PrintCard();
                                    }
                                    cout << endl;
                                    cout << " Total: " << CalculateHandTotal(playerHand) << endl;
                                    cout << "=========================================================" << endl;
                                    cout << endl;
									cout << " Dealer's Hand: " << endl;
									cout << endl;
									for (auto& card : dealerHand)
									{
										card.PrintCard();
									}
									cout << " Total: " << CalculateHandTotal(dealerHand) << endl;
									cout << endl;
									cout << "=========================================================" << endl;
									cout << endl;
									cout << " Dealer has Blackjack! You lose." << endl;
                                    cout << " Previous balance: $" << playerBalance << endl; // Afisam balanta player-ului inainte de a castiga
                                    cout << " Your bet: $" << betAmount << endl; // Afisam suma pariata
                                    cout << " New balance: $" << playerBalance - betAmount << endl; // Afisam balanta player-ului dupa ce a pierdut
									cout << endl;
									cout << "=========================================================" << endl;
									playerBalance -= betAmount; // Scadem suma pariata din variabila cu balanta player-ului
									UpdatePlayerBalance(username, playerBalance); // Dam update la banii player-ului in fisierul txt folosind functia UpdatePlayerBalance
                                    break;
								}
                                break;
							}
                            else
                            {
                                cout << "=========================================================" << endl;
                                cout << endl;
                                cout << " Invalid choice. Please try again." << endl;
                                cout << endl;
                                cout << "=========================================================" << endl;
                            }
                        }

                        // Turna dealer-ului
                        if (!playerBusted)
                        {
                            system("cls");
                            int num = 0; // Variabila care ne spune cate carti a tras dealer-ul

                            // Dealer-ul trage o carte pana are 17 sau mai mult
                            while (CalculateHandTotal(dealerHand) < 17)
                            {
                                dealerHand.push_back(deck.DrawCard());
                                num++;
                            }
                            cout << "=========================================================" << endl;
                            cout << endl;
                            if (num > 0)
                            {
                                cout << " The dealer drew " << num << " cards." << endl;
                            }
                            else
                            {
								cout << " The dealer stands." << endl;
							}
                            cout << endl;
                            cout << " Dealer's Hand: " << endl;
                            cout << endl;
                            for (auto& card : dealerHand)
                            {
                                card.PrintCard();
                            }
                            cout << endl;
                            cout << " Total: " << CalculateHandTotal(dealerHand) << endl;
                            cout << endl;

                            if (CalculateHandTotal(dealerHand) == 21) // Verificam daca dealer-ul are Blackjack
                            {
                                // Afisam cartile noastre
                                cout << "=========================================================" << endl;
                                cout << " Player's Hand: " << endl;
                                cout << endl;
                                for (auto& card : playerHand)
                                {
                                    card.PrintCard();
                                }
                                cout << endl;
                                cout << " Total: " << CalculateHandTotal(playerHand) << endl;
                                cout << "=========================================================" << endl;
                                cout << endl;
                                cout << " Dealer has Blackjack! You lose." << endl;
                                cout << " Previous balance: $" << playerBalance << endl; // Afisam balanta player-ului inainte de a castiga
                                cout << " Your bet: $" << betAmount << endl; // Afisam suma pariata
                                cout << " New balance: $" << playerBalance - betAmount << endl; // Afisam balanta player-ului dupa ce a pierdut
                                cout << endl;
                                cout << "=========================================================" << endl;
                                playerBalance -= betAmount; // Scadem suma pariata din variabila cu balanta player-ului
                                UpdatePlayerBalance(username, playerBalance); // Dam update la banii player-ului in fisierul txt folosind functia UpdatePlayerBalance
                                break;
                            }


                            // Verificam daca dealer-ul are peste 21
                            int dealerTotal = CalculateHandTotal(dealerHand);
                            if (dealerTotal > 21)
                            {
                                // Afisam cartile noastre
                                cout << "=========================================================" << endl;
                                cout << " Player's Hand: " << endl;
                                cout << endl;
                                for (auto& card : playerHand)
                                {
                                    card.PrintCard();
                                }
                                cout << endl;
                                cout << " Total: " << CalculateHandTotal(playerHand) << endl;
                                cout << "=========================================================" << endl;
                                cout << endl;
                                cout << "          Dealer busted! You win." << endl;
                                cout << endl;
                                cout << " Previous balance: $" << playerBalance << endl; // Afisam balanta player-ului inainte de a castiga
                                cout << " Your bet: $" << betAmount << endl; // Afisam suma pariata
                                cout << " New balance: $" << playerBalance + betAmount << endl; // Afisam balanta player-ului dupa ce a castigat
                                cout << "=========================================================" << endl;
                                playerBalance += betAmount; // Adaugam suma pariata la variabila cu balanta player-ului
							}
							else
							{
                                // Afisam cartile noastre
                                cout << "=========================================================" << endl;
                                cout << " Player's Hand: " << endl;
                                cout << endl;
                                for (auto& card : playerHand)
                                {
                                    card.PrintCard();
                                }
                                cout << endl;
                                cout << " Total: " << CalculateHandTotal(playerHand) << endl;
                                cout << endl;
                                int playerTotal = CalculateHandTotal(playerHand);
                                int dealerTotal = CalculateHandTotal(dealerHand);
								// Comparam totalul nostru cu al dealer-ului
								if (playerTotal > dealerTotal)
								{
									cout << "=========================================================" << endl;
									cout << "                   You win!" << endl;
                                    cout << endl;
                                    cout << " Previous balance: $" << playerBalance << endl; // Afisam balanta player-ului inainte de a castiga
                                    cout << " Your bet: $" << betAmount << endl; // Afisam suma pariata
                                    cout << " New Balance: $" << playerBalance + betAmount << endl; // Afisam balanta player-ului dupa ce a castigat
									cout << "=========================================================" << endl;
									playerBalance += betAmount; // Adaugam suma pariata la variabila cu balanta player-ului  
								}
								else if (playerTotal < dealerTotal)
								{
									cout << "=========================================================" << endl;
									cout << "                   You lose." << endl;
                                    cout << endl;
                                    cout << " Previous balance: $" << playerBalance << endl; // Afisam balanta player-ului inainte de a castiga
                                    cout << " Your bet: $" << betAmount << endl; // Afisam suma pariata
                                    cout << " New Balance: $" << playerBalance - betAmount << endl; // Afisam balanta player-ului dupa ce a pierdut
									cout << "=========================================================" << endl;
									playerBalance -= betAmount; // Scadem suma pariata din variabila cu balanta player-ului
								}
								else
								{
									cout << "=========================================================" << endl;
									cout << "                   It's a tie." << endl;
                                    cout << " Balance: $" << playerBalance << endl; // Afisam balanta player-ului dupa ce a iesit la egalitate
									cout << "=========================================================" << endl;
								}
							}

							// Dam update la banii player-ului in fisierul txt folosind functia UpdatePlayerBalance
							UpdatePlayerBalance(username, playerBalance);
                            break;
						}
						else
						{
							playerBalance -= betAmount; // Scadem suma pariata din variabila cu balanta player-ului
							UpdatePlayerBalance(username, playerBalance); // Dam update la banii player-ului in fisierul txt folosind functia UpdatePlayerBalance
                            break;
						}
                        system("cls");
						break;
					}

			        else if (choice == 2) // Exit
					{
						break;
					}
			        else
					{
						cout << "=========================================================" << endl;
						cout << "       Invalid choice. Please try again." << endl;
						cout << "=========================================================" << endl;
					}
			    }

			    break;
		    }
		    else
			{
				cout << "=========================================================" << endl;
				cout << "   Invalid username or password. Please try again." << endl;
				cout << "=========================================================" << endl;
			}
	    }
	    else if (choice == 2) // Register
		{
			bool usernameExists = true; // Variabila care ne spune daca username-ul exista sau nu
			while (usernameExists)
			{
				cout << "=========================================================" << endl;
				cout << " Enter a username: ";
				cin >> username;

				if (checkUsernameExists(username))
				{
					cout << "=========================================================" << endl;
					cout << " Username already exists. Please choose a different username." << endl;
					cout << "=========================================================" << endl;
				}
				else
				{
					usernameExists = false; // Daca username-ul nu exista, iesim din while
				}
			}
			cout << "=========================================================" << endl;
			cout << " Enter a password: ";
			cin >> password;
			cout << "=========================================================" << endl;
			registerUser(username, password); // Apelam functia registerUser pentru a inregistra username-ul si parola in fisierul text
		}
	    else if (choice == 3) // Exit
		{
			break;
		}
	    else
		{
			cout << "=========================================================" << endl;
			cout << "        Invalid choice. Please try again." << endl;
			cout << "=========================================================" << endl;
		}
    }

}



int main()
{
    int choice;
    while (true)
    {
        playBlackjack();

        cout << "=========================================================" << endl;
        cout << " 1. Continue" << endl;
        cout << " 2. Exit" << endl;
        cout << "=========================================================" << endl;
        cout << endl;
        cout << " Enter your choice: ";
        cin >> choice;
        cout << endl;
        cout << "=========================================================" << endl;

        if (choice == 1)
        {
            system("cls");
            continue; // Go back to the start of the loop
        }
        else if (choice == 2)
        {
            break; // Exit the loop and end the program
        }
        else
        {
            // existing code...
        }
    }

    return 0;
}