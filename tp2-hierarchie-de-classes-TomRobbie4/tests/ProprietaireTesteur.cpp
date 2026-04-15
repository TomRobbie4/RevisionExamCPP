/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/testFiles/simpletest.cpp to edit this template
 */

/* 
 * File:   ProprietaireTesteur.cpp
 * Author: etudiant
 *
 * Created on 4 avril 2026, 12 h 06
 */

#include <stdlib.h>
#include <iostream>
#include <gtest/gtest.h>
#include "Proprietaire.h"
#include "Camion.h" // On utilise Camion pour tester l'ajout et le polymorphisme
#include "ContratException.h"
#include <string>

using namespace saaq;

/**
 * @brief Test du constructeur avec paramètres
 * Cas valide : Nom, prénom et ville non vides. Le paiement total doit être à 0.
 */
TEST(Proprietaire, Constructeur_Valide_AttributsCorrects) {
    Proprietaire unProprio("Blo", "Joe", "Québec");

    EXPECT_EQ("Blo", unProprio.reqNom());
    EXPECT_EQ("Joe", unProprio.reqPrenom());
    EXPECT_EQ("Québec", unProprio.reqVille());
    EXPECT_EQ(0, unProprio.reqNbVehicules());
    EXPECT_DOUBLE_EQ(0.0, unProprio.reqPaiementTotal());
}

/**
 * @brief Test des préconditions du constructeur
 * Cas invalide : Nom vide
 */
TEST(Proprietaire, Constructeur_NomVide_LanceException) {
    EXPECT_THROW(Proprietaire("", "Joe", "Québec"), PreconditionException);
}

/**
 * @brief Test des préconditions du constructeur
 * Cas invalide : Prénom vide
 */
TEST(Proprietaire, Constructeur_PrenomVide_LanceException) {
    EXPECT_THROW(Proprietaire("Blo", "", "Québec"), PreconditionException);
}

/**
 * @brief Test de la méthode ajouterVehicule
 * Vérifie que le compteur augmente et que le paiement total est mis à jour.
 */
TEST(Proprietaire, AjouterVehicule_Valide_MetAJourCompteurEtPaiement) {
    Proprietaire unProprio("Blo", "Joe", "Québec");
    
    // On crée un camion (le tarif pour 4 essieux selon l'énoncé est de 2626.57$)
    Camion unCamion("3AK5641C9SH571177", "L000000", 20000, 4);
    
    unProprio.ajouterVehicule(unCamion);

    EXPECT_EQ(1, unProprio.reqNbVehicules());
    EXPECT_NEAR(unProprio.reqPaiementTotal(), 2626.57, 0.001);
}

/**
 * @brief Test du constructeur de copie (Forme de Coplien)
 * Vérifie que la copie est profonde (les véhicules sont clonés, pas juste référencés).
 */
TEST(Proprietaire, ConstructeurCopie_CopieProfonde) {
    Proprietaire original("Blo", "Joe", "Québec");
    Camion unCamion("3AK5641C9SH571177", "L000000", 20000, 4);
    original.ajouterVehicule(unCamion);

    // Utilisation du constructeur de copie
    Proprietaire copie(original);

    // Vérification des attributs de base
    EXPECT_EQ(copie.reqNom(), original.reqNom());
    EXPECT_EQ(copie.reqNbVehicules(), original.reqNbVehicules());
    EXPECT_DOUBLE_EQ(copie.reqPaiementTotal(), original.reqPaiementTotal());

    // Pour prouver la copie profonde, on ajoute un autre véhicule à l'original
    Camion unAutreCamion("1FUJHWDC6DP000000", "L333333", 3200, 2);
    original.ajouterVehicule(unAutreCamion);

    // La copie ne doit pas avoir été affectée
    EXPECT_EQ(original.reqNbVehicules(), 2);
    EXPECT_EQ(copie.reqNbVehicules(), 1);
}

/**
 * @brief Test de l'opérateur d'assignation (Forme de Coplien)
 * Vérifie que la copie est profonde et remplace bien l'ancien contenu.
 */
TEST(Proprietaire, OperateurAssignation_CopieProfonde) {
    Proprietaire original("Blo", "Joe", "Québec");
    Camion unCamion("3AK5641C9SH571177", "L000000", 20000, 4);
    original.ajouterVehicule(unCamion);

    Proprietaire assigne("Tremblay", "Paul", "Montréal");
    
    // Utilisation de l'opérateur =
    assigne = original;

    EXPECT_EQ("Blo", assigne.reqNom());
    EXPECT_EQ("Joe", assigne.reqPrenom());
    EXPECT_EQ(1, assigne.reqNbVehicules());
    EXPECT_DOUBLE_EQ(assigne.reqPaiementTotal(), original.reqPaiementTotal());
}

/**
 * @brief Test du formatage reqProprietaireFormate
 * Vérifie la structure globale de l'affichage avec les séparateurs.
 */
TEST(Proprietaire, ReqProprietaireFormate_FormatCorrect) {
    Proprietaire unProprio("Blo", "Joe", "Québec");
    Camion unCamion("3AK5641C9SH571177", "L000000", 20000, 4);
    unProprio.ajouterVehicule(unCamion);

    std::string formatte = unProprio.reqProprietaireFormate();

    // Vérification des éléments clés de la chaîne retournée 
    EXPECT_NE(formatte.find("Propriétaire"), std::string::npos);
    EXPECT_NE(formatte.find("Nom : Blo"), std::string::npos);
    EXPECT_NE(formatte.find("Prénom : Joe"), std::string::npos);
    EXPECT_NE(formatte.find("Domicile : Québec"), std::string::npos);
    EXPECT_NE(formatte.find("----------------------------------"), std::string::npos); // Séparateur
    EXPECT_NE(formatte.find("Paiement total : 2626.57$"), std::string::npos); // Somme finale avec 2 décimales
}
