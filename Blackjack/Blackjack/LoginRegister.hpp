using namespace std;
#include <iostream>
#include <fstream>
#include <string>

// functie care verifica daca exista username sau nu in Accounts.txt
bool checkUsernameExists(const string& username)
{
    ifstream accountsFile("Accounts.txt");
    string line;

    while (getline(accountsFile, line)) // citim din accountsFile si salvam in line
    {
        int pos = line.find(",");
        string existingUsername = line.substr(0, pos);

        if (existingUsername == username) // verificam daca deja exista username-ul ales in fisierul text si returnam True sau False.
        {
            accountsFile.close();
            return true;
        }
    }

    accountsFile.close();
    return false;
}

// functie inregistrare user
void registerUser(const string& username, const string& password)
{
    ofstream accountsFile("Accounts.txt", ios::app); // deschidem fisierul in modul append ca sa putem adauga informatiile noi, peste cele deja existente fara sa dam overwrite
    accountsFile << username << "," << password << endl;
    accountsFile.close();

    ofstream moneyFile("Money.txt", ios::app);
    moneyFile << username << ",1000" << endl; // adaugam 1000 de $ default fiecarui username inregistrat.
    moneyFile.close();

    cout << "Registration successful!" << endl;
}

// functie logare user
bool loginUser(const string& username, const string& password)
{
    ifstream accountsFile("Accounts.txt");
    string line;

    while (getline(accountsFile, line))
    {
        int pos = line.find(",");  // salvam pozitia virgulei intr-o variabila
        string existingUsername = line.substr(0, pos); // salvam username-ul din fisierul text intr-o variabila incepand cu pozitia 0 pana la virgula
        string existingPassword = line.substr(pos + 1); // salvam parola din fisierul text intr-o variabila incepand cu pozitia virgulei + 1

        if (existingUsername == username && existingPassword == password)
        {
            accountsFile.close();
            return true;  // returnam True daca usernameul si parola sunt la fel cu cele din fisierul text
        }
    }

    accountsFile.close();
    return false;
}