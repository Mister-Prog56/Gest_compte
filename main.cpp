#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>

#include "Compte_bancaire.h"

using namespace std;


int main()
{
    int Reveniraumenuprincipal;
do
{
    cout <<"\nBIENVENUE DANS LE PROGRAMME DE GESTION DE COMPTE\n\n";
    cout <<"\nOperations possibles:\n";//Menu du programme
    cout <<"\t1- Creer un nouveau compte\n\t2- Acceder a son compte\n\t3- Effectuer un versement\n";
    cout <<"\t4- Effectuer un retrait\n\t5- Fermer son compte\n\t0- Pour quitter le programme\n\n";
    cout <<"faite votre choix  :  ";
    int choix;
    cin>>choix;
    cin.ignore();

    //Nom des fichiers
    string const FichierCompte("FichierCompte.txt");
    string const FichierNumeroCOmpte("FichierNumeroCompte.txt");
   //Déclaration de l'objet Client
    Client Personne;

    switch(choix)
    {
        case 0://QUITTER LE PROGRAMME
            {
            break;
            }
        case 1://Création Nouveau compte
            {
                system("pause");

            int reponse=0;
            do
            {
                system("cls");
                cout <<"\n******** CREATION D'UN NOUVEAU COMPTE **********\n";
                 //Nom des variables de remplissage
                string codeCompte,codeConfirmation,nomClient,prenom,ContactCLient;
                int NumeroCompte;

                cout <<"\nEntrez votre nom  :  ";
                cin >>nomClient;
                cout <<"\nEntrez votre prenom  :  ";
                cin >>prenom; cin.ignore();
                cout <<"\nEntrez vos contacts separer par /   :  ";
                getline(cin,ContactCLient);
                cout <<"\nEntrez votre code secret  :  ";
                cin >>codeCompte;
                cout <<"\nConfirmez votre code secret  :  ";
                cin >>codeConfirmation;
                while(codeCompte!=codeConfirmation)
                {
                    cout <<"\nErreur, Confirmez votre code secret  :  ";
                    cin >>codeConfirmation;
                }
                cout <<"\nEntrez le montant a verser sur votre compte des l'ouverture  :  ";
                unsigned int montant;
                cin >>montant;

                std::string DayToday;
                DayToday=DateDuJour();
                NumeroCompte=NumCompte(FichierNumeroCOmpte);

                cout <<"\nCompte a ete cree le  "<<DayToday<<" .\nVotre numero de compte est :"<<NumeroCompte<<endl;
                cout <<"Vous devrez connaitre ce numero et votre mot de passe pour pouvoir vous connectez a votre compte\n\n\n";

                Personne.NouveauCompte(FichierCompte,NumeroCompte,codeConfirmation,nomClient,prenom,ContactCLient,DayToday,montant);
                cout <<"\nVous pouvez passer a une verification ....";

                cout <<"\n\nVoulez-vous creer un nouveau compte ?\nTaper \t 1-oui \t 0-non\nReponse : ";
                cin >>reponse;
            }while(reponse==1);
                //Déclaration compte bancaire
            system("pause");
            system("cls");
            cout <<"\n\nVoulez-vous revenir au Menu Principal?\n\n";
            cout <<"0-pour fermer      1-menu principal\nReponse : ";
            cin >>Reveniraumenuprincipal;
            if(Reveniraumenuprincipal==1)
            {
                system("cls");
            }

        break;
            }
        case 2: //Accès au compte
            {
            system("pause");
            int reponse=0;
            do
            {
                system("cls");
                cout <<"\n\n***** ACCES A SON COMPTE *******  \n\n";
                cout <<"Entrer votre numero de compte : ";
                unsigned int Numero;
                cin >>Numero;
                cout <<"\nEntrez votre code secret  :  ";
                std::string mdp;
                cin >>mdp;
                cout <<endl;
                //Déclaration compte bancaire
                system("pause");
                system("cls");

                Personne.SoldeClient(FichierCompte,Numero,mdp);
                cout <<"\n\nVerification effectuee!!!!!\n\n";

                cout <<"\n\nVoulez-vous consulter un autre compte ?\nTaper \t 1-oui \t 0-non\nReponse : ";
                cin >>reponse;
            }while(reponse==1);
                cout <<"\n\nVoulez-vous revenir au Menu Principal?\n\n";
                cout <<"0-pour fermer      1-menu principal\nReponse : ";
                cin >>Reveniraumenuprincipal;
                if(Reveniraumenuprincipal==1)
                {
                    system("cls");
                }

            break;
            }
        case 3://EFFECTUER UN VERSEMENT
            {
                system("pause");
            int reponse=0;
            do
            {
                system("cls");
                cout <<"\n***** EFFECTUER UN VERSEMENT *******  \n\n";

                cout <<"Entrer votre numero de compte : ";
                unsigned int Numero;
                cin >>Numero;
                cout <<"Entrer le montant a verser sur votre compte : ";
                unsigned int vers;
                cin >>vers;
                cout <<"\nEntrez votre code secret  :  ";
                std::string mdp;
                cin >>mdp;
                cout <<endl;
                //Déclaration compte bancaire
                system("pause");
                system("cls");
                Personne.Versement(FichierCompte,Numero,mdp,vers);

                cout <<"\n\nVoulez-vous effectuer un autre versement ?\nTaper \t 1-oui \t 0-non\nReponse : ";
                cin >>reponse;
            }while(reponse==1);

                cout <<"\n\nVoulez-vous revenir au Menu Principal?\n\n";
                cout <<"0-pour fermer      1-menu principal\nReponse : ";
                cin >>Reveniraumenuprincipal;
                if(Reveniraumenuprincipal==1)
                {
                    system("cls");
                }

            break;
            }
        case 4://EFFECTUER UN RETRAIT
            {
                system("pause");
            int reponse=0;
            do
            {
                system("cls");
                cout <<"\n***** EFFECTUER UN RETRAIT *******  \n\n";

                cout <<"Entrer votre numero de compte : ";
                unsigned int Numero;
                cin >>Numero;
                cout <<"Entrer le montant a retirer sur votre compte : ";
                unsigned int retrait;
                cin >>retrait;
                cout <<"\nEntrez votre code secret  :  ";
                std::string mdp;
                cin >>mdp;
                cout <<endl;
                //Déclaration compte bancaire
                system("pause");
                system("cls");
                Personne.Retrait(FichierCompte,Numero,mdp,retrait);

                cout <<"\n\nVoulez-vous effectuer un autre retrait ?\nTaper \t 1-oui \t 0-non\nReponse : ";
                cin >>reponse;

            }while(reponse==1);

            cout <<"\n\nVoulez-vous revenir au Menu Principal?\n\n";
            cout <<"0-pour fermer      1-menu principal\nReponse : ";
            cin >>Reveniraumenuprincipal;
            if(Reveniraumenuprincipal==1)
                {
                    system("cls");
                }

            break;
            }
        case 5://FERMER SON COMPTE
            {

                system("pause");
                int reponse=0;
            do
            {
                system("cls");
                cout <<"\n***** FERMER SON COMPTE POUR TOUJOURS *******  \n\n";

                cout <<"Entrer votre numero de compte : ";
                unsigned int Numero;
                cin >>Numero;

                cout <<"\nEntrez votre code secret  :  ";
                std::string mdp;
                cin >>mdp;
                cout <<endl;
                //Déclaration compte bancaire
                system("pause");
                system("cls");
               Personne.FermetureCompte(FichierCompte,Numero,mdp);

                cout <<"\n\nVoulez-vous fermeture un autre compte ?\nTaper \t 1-oui \t 0-non\nReponse : ";
                cin >>reponse;

            }while(reponse==1);
            cout <<"\n\nVoulez-vous revenir au Menu Principal?\n\n";
            cout <<"0-pour fermer      1-menu principal\nReponse : ";
            cin >>Reveniraumenuprincipal;
            if(Reveniraumenuprincipal==1)
                {
                    system("cls");
                }

                break;
            }
        default:
            {
                cout <<"Aucun choix effectue !!!!";
            }
    }

}while(Reveniraumenuprincipal==1);

    return 0;//Ajouter choix quitter le programme
    //Pour le cas 1 tant que repose==1 ou 0 répéter
}
