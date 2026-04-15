/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/testFiles/simpletest.cpp to edit this template
 */

/* 
 * File:   CamionTesteur.cpp
 * Author: etudiant
 *
 * Created on 25 mars 2026, 10 h 48
 */

#include <stdlib.h>
#include <gtest/gtest.h>
#include <iostream>
#include "Camion.h"
#include "ContratException.h"
#include <string>

using namespace saaq;

/**
 * @brief Test du constructeur de Camion
 * Cas valide : NIV conforme, Immatriculation 'L', poids > 3000, essieux >= 2
 */
TEST(Camion, Constructeur_Valide_AttributsCorrects) {
    // Données provenant des exemples de l'énoncé ou du TP1
    std::string nivValide = "3AK5641C9SH571177"; 
    std::string immatValide = "L000000";
    double poidsValide = 20000.0;
    int essieuxValide = 4;

    Camion unCamion(nivValide, immatValide, poidsValide, essieuxValide);

    EXPECT_EQ(unCamion.reqNiv(), nivValide);
    EXPECT_EQ(unCamion.reqImmatriculation(), immatValide);
    EXPECT_EQ(unCamion.reqPoids(), poidsValide);
    EXPECT_EQ(unCamion.reqNbEssieux(), essieuxValide);
}

/**
 * @brief Test des préconditions du constructeur
 * Cas invalide : Poids insuffisant (<= 3000 kg)
 */
TEST(Camion, Constructeur_PoidsInvalide_LanceException) {
    EXPECT_THROW(Camion("3AK5641C9SH571177", "L000000", 3000.0, 2), PreconditionException);
}

/**
 * @brief Test des préconditions du constructeur
 * Cas invalide : Nombre d'essieux insuffisant (< 2)
 */
TEST(Camion, Constructeur_EssieuxInvalide_LanceException) {
    EXPECT_THROW(Camion("3AK5641C9SH571177", "L000000", 5000.0, 1), PreconditionException);
}

/**
 * @brief Test de la méthode calculerTarificationAnnuelle
 * Vérifier si le calcul correspond aux tarifs de la SAAQ mentionnés
 */
TEST(Camion, CalculerTarificationAnnuelle_Valide) {
    // Exemple de l'énoncé : Camion 4 essieux, 20000kg -> 2626.57$
    Camion unCamion("3AK5641C9SH571177", "L000000", 20000.0, 4);
    EXPECT_NEAR(unCamion.calculerTarificationAnnuelle(), 2626.57, 0.001);
}

/**
 * @brief Test de la méthode clone
 * Vérifie que l'objet cloné est une copie identique mais avec une adresse différente
 */
TEST(Camion, Clone_CopieIdentique) {
    Camion original("3AK5641C9SH571177", "L000000", 5000.0, 2);
    auto copie = original.clone();

    EXPECT_EQ(original.reqVehiculeFormate(), copie->reqVehiculeFormate());
    EXPECT_NE(&original, copie.get()); // Vérifie que c'est bien un nouvel objet en mémoire
}

/**
 * @brief Test de l'affichage formaté spécifique au Camion
 */
TEST(Camion, ReqVehiculeFormate_FormatCorrect) {
    Camion unCamion("3AK5641C9SH571177", "L000000", 20000.0, 4);
    std::string formatte = unCamion.reqVehiculeFormate();
    
    // Vérifie la présence de mots clés spécifiques définis dans l'énoncé
    EXPECT_NE(formatte.find("Camion"), std::string::npos);
    EXPECT_NE(formatte.find("Nombre d'essieux : 4"), std::string::npos);
    EXPECT_NE(formatte.find("Poids : 20000"), std::string::npos);
    EXPECT_NE(formatte.find("Paiement : 2626.57$"), std::string::npos);
}