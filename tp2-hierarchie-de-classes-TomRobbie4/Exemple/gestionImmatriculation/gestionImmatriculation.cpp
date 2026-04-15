/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   gestionImmatriculation.cpp
 * Author: Thomas Robert
 *
 * Created on 4 avril 2026, 17 h 09
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "Proprietaire.h"
#include "Camion.h"
#include "VehiculePromenade.h"
#include "validationFormat.h"
#include "taxesImmatriculationVPQc.h" 

using namespace std;
using namespace saaq;

/**
 * \brief Charge les données du dossier (NIV puis Plaque)
 */
bool chargeDossier(const string& nomFichier, Proprietaire& proprietaire) {
    ifstream fichier(nomFichier);
    if (!fichier.is_open()) return false;
    if (!validerFormatFichier(fichier)) return false;

    fichier.clear();
    fichier.seekg(0);

    string nom, prenom, ville, niv, plaque;
    int j, m, a;

    getline(fichier, nom);
    getline(fichier, prenom);
    getline(fichier, ville);
    fichier >> j >> m >> a;
    fichier.ignore(256, '\n');

    proprietaire = Proprietaire(nom, prenom, ville);

    while (getline(fichier, niv) && !niv.empty()) {
        getline(fichier, plaque);
        
        if (validerImmatriculationCamion(plaque)) {
            int poids, essieux; // Utilise bien int ici
            fichier >> poids >> essieux;
            fichier.ignore(256, '\n');
            Camion c(niv, plaque, poids, essieux);
            proprietaire.ajouterVehicule(c);
        } else {
            int places;
            fichier >> places;
            fichier.ignore(256, '\n');
            
            // --- C'EST CETTE PARTIE QUI MANQUAIT ---
            double contributionTransport = 0.0;
            double taxeImmatriculation = 0.0;
            if (!trouverTaxes(TAXE_IMMATRICULATION, ville, contributionTransport, taxeImmatriculation)) {
                return false;
            }
            
            VehiculePromenade vp(niv, plaque, places);
            vp.asgContributionTransportEnCommun(contributionTransport);
            vp.asgTaxeLocale(taxeImmatriculation);
            // ----------------------------------------
            
            proprietaire.ajouterVehicule(vp);
        }
    }
    return true;
}

void saisirNouveauCamion(Proprietaire& leProprio) {
    cout << "\n--- AJOUT D'UN CAMION ---" << endl;
    
    string niv, plaque;
    double poids;
    int essieux;

    do {
        cout << "Entrez le NIV (17 caracteres) : ";
        cin >> niv;
        if (!validerNiv(niv)) cout << "-> Erreur : Le NIV est invalide. Reessayez." << endl;
    } while (!validerNiv(niv));

    do {
        cout << "Entrez la plaque (doit commencer par L, ex: L123456) : ";
        getline(cin >> ws, plaque); 
        if (!validerImmatriculationCamion(plaque)) cout << "-> Erreur : La plaque est invalide. Reessayez." << endl;
    } while (!validerImmatriculationCamion(plaque));

    do {
        cout << "Entrez le poids (kg, minimum 3000) : ";
        cin >> poids;
        if (poids < 3000) cout << "-> Erreur : Le poids doit etre d'au moins 3000 kg." << endl;
    } while (poids < 3000);

    do {
        cout << "Entrez le nombre d'essieux (minimum 2) : ";
        cin >> essieux;
        if (essieux < 2) cout << "-> Erreur : Un camion a au moins 2 essieux." << endl;
    } while (essieux < 2);

    Camion nouveauCamion(niv, plaque, poids, essieux);
    leProprio.ajouterVehicule(nouveauCamion);
    cout << "✅ Camion ajoute avec succes au dossier de " << leProprio.reqNom() << " !" << endl;
}

void saisirNouveauVehiculePromenade(Proprietaire& leProprio) {
    cout << "\n--- AJOUT D'UN VÉHICULE DE PROMENADE ---" << endl;
    
    string niv, plaque;
    int places;

    do {
        cout << "Entrez le NIV (17 caracteres) : ";
        cin >> niv;
        if (!validerNiv(niv)) cout << "-> Erreur : Le NIV est invalide. Reessayez." << endl;
    } while (!validerNiv(niv));

    do {
        cout << "Entrez la plaque (ex: 000 ABC) : ";
        getline(cin >> ws, plaque);
        if (!validerImmatriculationPromenade(plaque)) cout << "-> Erreur : La plaque est invalide. Reessayez." << endl;
    } while (!validerImmatriculationPromenade(plaque));

    do {
        cout << "Entrez le nombre de places (entre 1 et 9) : ";
        cin >> places;
        if (places <= 0 || places > 9) cout << "-> Erreur : Le nombre de places doit etre entre 1 et 9." << endl;
    } while (places <= 0 || places > 9);

    double contriTransport = 0.0;
    double taxeLocale = 0.0;
    
    if (trouverTaxes(TAXE_IMMATRICULATION, leProprio.reqVille(), contriTransport, taxeLocale)) {
        VehiculePromenade nouveauVP(niv, plaque, places);
        nouveauVP.asgContributionTransportEnCommun(contriTransport);
        nouveauVP.asgTaxeLocale(taxeLocale);
        
        leProprio.ajouterVehicule(nouveauVP);
        cout << "✅ Vehicule de promenade ajoute avec succes au dossier !" << endl;
    } else {
        cout << "❌ Erreur critique : Impossible de trouver les taxes pour la ville de " << leProprio.reqVille() << endl;
    }
}

int main(int argc, char** argv) {
    cout << "--- DÉBUT DU PROGRAMME SAAQ ---" << endl << endl;

    Proprietaire leProprio("NomParDefaut", "PrenomParDefaut", "VilleParDefaut");
    bool fichierCharge = false;
    
    fichierCharge = chargeDossier("Proprietaire.txt", leProprio);
    
    if (!fichierCharge) {
        return -1;
    }
    
    cout << leProprio.reqProprietaireFormate() << endl;
    
    saisirNouveauCamion(leProprio);
    saisirNouveauVehiculePromenade(leProprio);

    cout << "\n--- DOSSIER MIS À JOUR ---" << endl;
    cout << leProprio.reqProprietaireFormate() << endl;
    
    cout << flush;
    return 0;
}

