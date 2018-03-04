#include<iostream>
#include<stdlib.h>
#include <fstream>
#include <string>

using namespace std;

class Client
{

    int Numero_Compte;
    string Code_Client;
    string Nom_Client;
    string Contact_Client;
    string Date_Ouverture;

    public: Client(int NumeroCompte,string CodeClient,string NomClient,string ContactClient,string DateOuverture)
    {
        Numero_Compte=NumeroCompte;
          Code_Client=CodeClient;
           Nom_Client=NomClient;
       Contact_Client=ContactClient;
       Date_Ouverture=DateOuverture;

    }

    void NouveauCompte(string const , int ,string , string ,string ,string );
    void SoldeClient(string const ,int ,string );

};
