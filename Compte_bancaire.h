#ifndef COMPTE_BANCAIRE_H_INCLUDED
#define COMPTE_BANCAIRE_H_INCLUDED
#include<string>

class Client
{

    int Numero_Compte;
    std::string Code_Client;
    std::string Nom_Client;
    std::string Contact_Client;
    std::string Date_Ouverture;
    int Montant_Ouverture;

public:
    Client()
    {
        Numero_Compte=0;
          Code_Client="";
           Nom_Client="";
       Contact_Client="";
       Date_Ouverture="";
       Montant_Ouverture=0;

    }

 public:
    void NouveauCompte(std::string const Nomfichier,int identifiantBancaire,std::string codeclient, std::string nomclient,std::string prenom,std::string contactclient,std::string dateOuvertureCompte,unsigned int MontantOuverture);
    void SoldeClient(std::string const Nomfichier, unsigned int NumeroCompte, std::string codeclient);
    void Versement(std::string const Nomfichier,unsigned int NumeroCompte ,std::string codeClient,unsigned int montantAVerser);
    void Retrait(std::string const Nomfichier,unsigned int NumeroCompte ,std::string codeClient,unsigned int montantARetirer);
    void FermetureCompte(std::string const Nomfichier,unsigned int NumeroCompte ,std::string codeClient);
};
//FONCTION GENERATRICE DE NUMERO DE COMPTE BANCAIRE
int NumCompte(std::string const NomFichier);
//FONCTION GENERATRICE DE LA DATE EN COURS
std::string DateDuJour();

#endif // COMPTE_BANCAIRE_H_INCLUDED
