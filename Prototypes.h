#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTYPES_H_INCLUDED
#include <string>

int NumCompte(std::string const NomFichier);
void NouveauCompte(std::string const Nomfichier,int identifiantBancaire,std::string codeclient, std::string nomclient,std::string contactclient,std::string dateOuvertureCompte);
void SoldeClient(std::string const Nomfichier,int identifiantBancaire,std::string codeclient);


#endif // PROTOTYPES_H_INCLUDED
