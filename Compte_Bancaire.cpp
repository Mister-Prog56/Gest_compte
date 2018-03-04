#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <time.h>
#include "Compte_bancaire.h"

using namespace std;
//*************************************************************************************************************************************************************************
//*************************************************************************************************************************************************************************

std::string DateDuJour()
{
    time_t now=time(NULL);
    struct tm tm_now= *localtime(&now);
    char s_now[sizeof "JJ/MM/AAAA HH:MM:SS"];
    strftime(s_now,sizeof s_now,"%d/%m/%Y %H:%M:%S",&tm_now);
    return s_now;
}

//*************************************************************************************************************************************************************************
//Générer compte bancaire
int NumCompte(std::string const NomFichier)
{
    ifstream NomFluxFichier(NomFichier.c_str());
    int compte;
    if(NomFluxFichier)
    {
        NomFluxFichier>>compte;
        NomFluxFichier.close();
    }
    else
    {
        cout <<"ERREUR lors de l'ouverture du fichier pour la lecture !!!\n";
        return EXIT_FAILURE;
    }
    ofstream NomFluxEcriture(NomFichier.c_str());
    if(NomFluxEcriture)
    {
       compte++;
       NomFluxEcriture<<compte;
       NomFluxEcriture.close();
    }
    else
    {
        cout <<"ERREUR lors de l'ouverture du fichier pour l'écriture !!!\n";
        return EXIT_FAILURE;
    }
    return compte;
}

//*************************************************************************************************************************************************************************
//FONCTION NOUVEAU COMPTE
void Client::NouveauCompte(std::string const Nomfichier,int identifiantBancaire,std::string codeclient,
                           std::string nomclient,std::string prenom,std::string contactclient,std::string dateOuvertureCompte,unsigned int MontantOuverture)
{
    ofstream NomFluxFichier(Nomfichier.c_str(),ios::app);
    if(NomFluxFichier)
    {
        //Vérification de l'existence du compte

        //Enregistrement du compte....
        NomFluxFichier <<identifiantBancaire<<"   "<<codeclient<<"   "<<nomclient<<"   "<<prenom<<"   "<<contactclient<<"   "<<dateOuvertureCompte<<"  "<<MontantOuverture<<endl;
        cout <<"\nVotre compte a ete cree avec succes, Merci a vous pour votre confiance\n\n";
    }
    else
    {
        cout <<"ERREUR lors de l'ouverture du fichier !!\n";
    }
}

//*************************************************************************************************************************************************************************
//SOLDE COMPTE
void Client::SoldeClient(std::string const Nomfichier,unsigned int NumeroCompte,std::string codeclient)
{
    ifstream NomFluxFichier(Nomfichier.c_str());
    if(NomFluxFichier)
    {
        std::string chaine;
        std::string chaineprincip;
        int compteur(0);
        cout<<"\n\n";
        while(getline(NomFluxFichier,chaine))
        {
            ofstream fic_solde("fic_solde.txt");
            if(fic_solde)
            {
                fic_solde<<chaine;
                fic_solde.close();
            }
            else{cout<<"Impossible d'ouvrir le fichier pour la lecture du compte";}
            ifstream fic_solde_lecture("fic_solde.txt");
            if(fic_solde_lecture)
            {
                unsigned int codeC;
                fic_solde_lecture>>codeC;
                string codeCl;
                fic_solde_lecture>>codeCl;
                if(codeCl==codeclient && codeC==NumeroCompte)
                {
                    getline(fic_solde_lecture,chaineprincip);
                    cout <<chaine<<endl;
                    compteur++;
                }
            }
            else{cout<<"Impossible d'ouvrir le fichier pour la lecture du compte";}
        }
        if(compteur==0)
        {
            cout <<"Compte inexistant,veuillez reessayer !";
        }

    }
    else{cout <<"ERREUR lors de l'ouverture du fichier pour la lecture !!!\n";}
}
//*************************************************************************************************************************************************************************
// VERSEMENT //Gérer le cas où la personne n'existe pas avec la var compteur
void Client::Versement(std::string const Nomfichier,unsigned int NumeroCompte ,std::string codeClient,unsigned int montantAVerser)
{//GERER L'ORDRE AVEC UN COMPTEUR INCREMENTER DONNANT LA POSITION A CHAQUE VERIFICATION
    ifstream NomFluxFichier(Nomfichier.c_str());//fichier principal compte

    int compteur(0); //Compteur vérifiant la présence de notre compte
    if(NomFluxFichier)
    {

        std::string chaineprincip; //Les chaines de lecture
        std::string chaine;

        while(getline(NomFluxFichier,chaine))
        {
            ofstream fic_solde("fic_solde.txt");
            if(fic_solde)
            {
                fic_solde<<chaine;
                fic_solde.close();
            }
            else{cout<<"Impossible d'ouvrir le fichier pour la lecture du compte";}

            ifstream fic_solde_lecture("fic_solde.txt");//Lecture de fichier auxiliaire pour la vérification des infos

            if(fic_solde_lecture)
            {
                unsigned int NumCompte;
                fic_solde_lecture>>NumCompte;
                string codeclient;
                fic_solde_lecture>>codeclient;
                string nomclient;                   /*On lit toutes les données pour une vérification */
                fic_solde_lecture>>nomclient;
                string nomclient2;
                fic_solde_lecture>>nomclient2;
                string contactclient;
                fic_solde_lecture>>contactclient;
                string dateOuvertureCompte;
                fic_solde_lecture>>dateOuvertureCompte;
                string dateOuvertureCompte2;
                fic_solde_lecture>>dateOuvertureCompte2;
                unsigned int MontantOuverture;
                fic_solde_lecture>>MontantOuverture;

                if(NumCompte==NumeroCompte && codeclient==codeClient)
                {
                    unsigned int Res;
                    Res=MontantOuverture+montantAVerser;
                    ofstream NomFluxAux2("fic2.txt",ios::app);//fichier auxiliaire pour les comptes concernés
                    if(NomFluxAux2)
                    {   //On copie les donnees dans un fichier pour fait le versement fic1.txt
                        NomFluxAux2<<NumCompte<<"   "<<codeclient<<"  "<<nomclient<<" "<<nomclient2<<"   "<<contactclient<<"   "<<dateOuvertureCompte<<"   "<<dateOuvertureCompte2<<"   "<<Res;
                        NomFluxAux2.close();
                    }else{cout<<"Impossible d'ouvrir le fichier pour la lecture du compte";}
                    compteur++;
                }
                else //Sinon si le compte n'est pas concerné on le copie dans un autre fichier fic.txt
                {
                   ofstream NomFluxAux("fic.txt",ios::app);//fichier auxiliaire pour les comptes pas concernés
                   if(NomFluxAux)
                   {
                      fic_solde_lecture.seekg(0,ios::beg);
                      getline(fic_solde_lecture,chaineprincip);
                      NomFluxAux<<chaineprincip<<endl;
                   }else{cout<<"Impossible d'ouvrir le fichier pour la lecture du compte";}
                }
            }
        }

        NomFluxFichier.close();
        }else{cout <<"ERREUR lors de l'ouverture du fichier pour la lecture !!!\n";}

    if(compteur==0)
    {
        /*
        Si le compte n'existe
        */
        cout<<"Compte inexistant,veuillez reessayer !";
        /*ifstream Lecture1("fic.txt");
        if(Lecture1)
        {
            ofstream Ouverture(Nomfichier.c_str());
            string ligne;
            if(Ouverture)
            {
                while(getline(Lecture1,ligne))
                {
                    Ouverture<<ligne<<endl;
                }
            }
            else{cout <<"ERREUR lors de l'ouverture du fichier pour la lecture !!!\n";}
        }
        else{cout <<"ERREUR lors de l'ouverture du fichier pour la lecture !!!\n";}
*/
    }
    else
    {
        ofstream Ouverture(Nomfichier.c_str());  //Ouverture du fichier compte
        if(Ouverture)
        {
            ifstream Lecture1("fic.txt");
            Lecture1.seekg(0,ios::beg);
            if(Lecture1)
            {
                string ligne;
                while(getline(Lecture1,ligne))
                {
                    Ouverture<<ligne<<endl;
                }
            }else{cout <<"ERREUR lors de l'ouverture du fichier pour la lecture !!!\n";}

            ifstream Lecture2("fic2.txt");
            Lecture2.seekg(0,ios::beg);
            if(Lecture2)
            {
                string ligne;
                 while(getline(Lecture2,ligne))
                    {
                        Ouverture<<ligne<<endl;
                    }
            }else{cout <<"ERREUR lors de l'ouverture du fichier pour la lecture !!!\n";}
        }
        cout <<"\n\nVersement effectuee, veuillez verifier!!!!!\n\n";
    }


        ofstream W1("fic.txt");
        ofstream W2("fic2.txt");
        ofstream W3("fic_solde.txt");
        if(W1)
        {
            W1 <<"";
        }
        if(W2)
        {
           W2 <<"";
        }
        if(W3)
        {
           W3 <<"";
        }

}

//*************************************************************************************************************************************************************************
//*************************************************************************************************************************************************************************
//RETRAIT D'ARGENT
void Client::Retrait(std::string const Nomfichier,unsigned int NumeroCompte ,std::string codeClient,unsigned int montantARetirer)
{//GERER L'ORDRE AVEC UN COMPTEUR INCREMENTER DONNANT LA POSITION A CHAQUE VERIFICATION

    ifstream NomFluxFichier(Nomfichier.c_str());//fichier principal compte

    int compteur(0); //Compteur vérifiant la présence de notre compte
    if(NomFluxFichier)
    {

        std::string chaineprincip; //Les chaines de lecture
        std::string chaine;

        while(getline(NomFluxFichier,chaine))
        {
            ofstream fic_solde("fic_solde.txt");
            if(fic_solde)
            {
                fic_solde<<chaine;
                fic_solde.close();
            }
            else{cout<<"Impossible d'ouvrir le fichier pour la lecture du compte";}

            ifstream fic_solde_lecture("fic_solde.txt");//Lecture de fichier auxiliaire pour la vérification des infos

            if(fic_solde_lecture)
            {
                unsigned int NumCompte;
                fic_solde_lecture>>NumCompte;
                string codeclient;
                fic_solde_lecture>>codeclient;
                string nomclient;                   /*On lit toutes les données pour une vérification */
                fic_solde_lecture>>nomclient;
                string nomclient2;
                fic_solde_lecture>>nomclient2;
                string contactclient;
                fic_solde_lecture>>contactclient;
                string dateOuvertureCompte;
                fic_solde_lecture>>dateOuvertureCompte;
                string dateOuvertureCompte2;
                fic_solde_lecture>>dateOuvertureCompte2;
                unsigned int MontantOuverture;
                fic_solde_lecture>>MontantOuverture;

                if(NumCompte==NumeroCompte && codeclient==codeClient)
                {
                    unsigned int Res;
                    Res=MontantOuverture-montantARetirer;
                    ofstream NomFluxAux2("fic2.txt",ios::app);//fichier auxiliaire pour les comptes concernés
                    if(NomFluxAux2)
                    {   //On copie les donnees dans un fichier pour fait le versement fic1.txt
                        NomFluxAux2<<NumCompte<<"   "<<codeclient<<"  "<<nomclient<<" "<<nomclient2<<"   "<<contactclient<<"   "<<dateOuvertureCompte<<"   "<<dateOuvertureCompte2<<"   "<<Res<<endl;
                        NomFluxAux2.close();
                    }else{cout<<"Impossible d'ouvrir le fichier pour la lecture du compte";}
                    compteur++;
                }
                else //Sinon si le compte n'est pas concerné on le copie dans un autre fichier fic.txt
                {
                   ofstream NomFluxAux("fic.txt",ios::app);//fichier auxiliaire pour les comptes pas concernés
                   if(NomFluxAux)
                   {
                      fic_solde_lecture.seekg(0,ios::beg);
                      getline(fic_solde_lecture,chaineprincip);
                      NomFluxAux<<chaineprincip<<endl;
                   }else{cout<<"Impossible d'ouvrir le fichier pour la lecture du compte";}
                }
            }
        }

        NomFluxFichier.close();
        }else{cout <<"ERREUR lors de l'ouverture du fichier pour la lecture !!!\n";}

    if(compteur==0)
    {
        /*
        Si le compte n'existe
        */
        cout<<"Compte inexistant,veuillez reessayer !";

    }
    else
    {
        ofstream Ouverture(Nomfichier.c_str());  //Ouverture du fichier compte
        if(Ouverture)
        {
            ifstream Lecture1("fic.txt");
            Lecture1.seekg(0,ios::beg);
            if(Lecture1)
            {
                string ligne;
                while(getline(Lecture1,ligne))
                {
                    Ouverture<<ligne<<endl;
                }
            }else{cout <<"ERREUR lors de l'ouverture du fichier pour la lecture !!!\n";}

            ifstream Lecture2("fic2.txt");
            Lecture2.seekg(0,ios::beg);
            if(Lecture2)
            {
                string ligne;
                 while(getline(Lecture2,ligne))
                    {
                        Ouverture<<ligne<<endl;
                    }
            }else{cout <<"ERREUR lors de l'ouverture du fichier pour la lecture !!!\n";}
        }
       cout <<"\n\nRetrait effectue, veuillez verifier!!!!!\n\n";
    }


        ofstream W1("fic.txt");
        ofstream W2("fic2.txt");
        ofstream W3("fic_solde.txt");
        if(W1)
        {
            W1 <<"";
        }
        if(W2)
        {
           W2 <<"";
        }
        if(W3)
        {
           W3 <<"";
        }
}

//******************************************************************************************************************************
//******************************************************************************************************************************
void Client::FermetureCompte(std::string const Nomfichier,unsigned int NumeroCompte ,std::string codeClient)
{//GERER L'ORDRE AVEC UN COMPTEUR INCREMENTER DONNANT LA POSITION A CHAQUE VERIFICATION
    ifstream NomFluxFichier(Nomfichier.c_str());//fichier principal compte

    int compteur(0); //Compteur vérifiant la présence de notre compte
    if(NomFluxFichier)
    {

        std::string chaineprincip; //Les chaines de lecture
        std::string chaine;

        while(getline(NomFluxFichier,chaine))
        {
            ofstream fic_solde("fic_solde.txt");
            if(fic_solde)
            {
                fic_solde<<chaine;
                fic_solde.close();
            }
            else{cout<<"Impossible d'ouvrir le fichier pour la lecture du compte";}

            ifstream fic_solde_lecture("fic_solde.txt");//Lecture de fichier auxiliaire pour la vérification des infos

            if(fic_solde_lecture)
            {
                unsigned int NumCompte;
                fic_solde_lecture>>NumCompte;
                string codeclient;
                fic_solde_lecture>>codeclient;

                if(NumCompte==NumeroCompte && codeclient==codeClient)
                {
                    compteur++;
                }
                else //Sinon si le compte n'est pas concerné on le copie dans un autre fichier fic.txt
                {
                   ofstream NomFluxAux("fic.txt",ios::app);//fichier auxiliaire pour les comptes pas concernés
                   if(NomFluxAux)
                   {
                      fic_solde_lecture.seekg(0,ios::beg);
                      getline(fic_solde_lecture,chaineprincip);
                      NomFluxAux <<chaineprincip<<endl;
                   }else{cout<<"Impossible d'ouvrir le fichier pour la lecture du compte";}
                }
            }
        }

        NomFluxFichier.close();
        }else{cout <<"ERREUR lors de l'ouverture du fichier pour la lecture !!!\n";}

    if(compteur==0)
    {
        /*
        Si le compte n'existe
        */
        cout<<"Compte inexistant,veuillez reessayer !";

    }
    else
    {
        ofstream Ouverture(Nomfichier.c_str());  //Ouverture du fichier compte
        if(Ouverture)
        {
            ifstream Lecture1("fic.txt");
            Lecture1.seekg(0,ios::beg);
            if(Lecture1)
            {
                string ligne;
                while(getline(Lecture1,ligne))
                {
                    Ouverture<<ligne<<endl;
                }
            }else{cout <<"ERREUR lors de l'ouverture du fichier pour la lecture !!!\n";}

        }
    cout <<"\n\nSuppression du compte effectuee, Merci a vous pour votre confiance en nous...!!!!!\n\n";
    }


        ofstream W1("fic.txt");
        ofstream W3("fic_solde.txt");
        if(W1)
        {
            W1 <<"";
        }
        if(W3)
        {
           W3 <<"";
        }
}

