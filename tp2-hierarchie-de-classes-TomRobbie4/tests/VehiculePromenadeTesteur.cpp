/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/testFiles/simpletest.cpp to edit this template
 */

/* 
 * File:   VehiculePromenadeTesteur.cpp
 * Author: etudiant
 *
 * Created on 1 avril 2026, 09 h 57
 */

#include <stdlib.h>
#include <iostream>
#include <gtest/gtest.h>
#include "VehiculePromenade.h"
#include "ContratException.h"
#include <string>

/*
 * Simple C++ Test Suite
 */

using namespace saaq;

/**
 * @brief Test du constructeur de VehiculePromenade
 * Cas valide : NIV conforme, Immatriculation promenade, nbPlaces entre 1 et 9.
 */
TEST(VehiculePromenade, Constructeur_Valide_AttributsCorrects) {
    std::string nivValide = "5GZCZ43D13S812715"; 
    std::string immatValide = "E00 VEA";
    int nbPlacesValide = 5;

    VehiculePromenade unVP(nivValide, immatValide, nbPlacesValide);

    EXPECT_EQ(unVP.reqNiv(), nivValide);
    EXPECT_EQ(unVP.reqImmatriculation(), immatValide);
    EXPECT_EQ(unVP.reqNbPlaces(), nbPlacesValide);
    
    // Vérification des valeurs initialisées par défaut
    EXPECT_DOUBLE_EQ(unVP.reqContributionTransportEnCommun(), 0.0);
    EXPECT_DOUBLE_EQ(unVP.reqTaxeLocale(), 0.0);
}

/**
 * @brief Test des préconditions du constructeur
 * Cas invalide : Trop de places (> 9)
 */
TEST(VehiculePromenade, Constructeur_TropDePlaces_LanceException) {
    EXPECT_THROW(VehiculePromenade("5GZCZ43D13S812715", "E00 VEA", 10), PreconditionException);
}

/**
 * @brief Test des préconditions du constructeur
 * Cas invalide : Pas assez de places (<= 0)
 */
TEST(VehiculePromenade, Constructeur_PasAssezDePlaces_LanceException) {
    EXPECT_THROW(VehiculePromenade("5GZCZ43D13S812715", "E00 VEA", 0), PreconditionException);
}

/**
 * @brief Test des mutateurs pour les taxes
 */
TEST(VehiculePromenade, MutateursTaxes_ModifientValeurs) {
    VehiculePromenade unVP("5GZCZ43D13S812715", "E00 VEA", 5);
    
    unVP.asgContributionTransportEnCommun(30.0);
    unVP.asgTaxeLocale(61.10);

    EXPECT_DOUBLE_EQ(unVP.reqContributionTransportEnCommun(), 30.0);
    EXPECT_DOUBLE_EQ(unVP.reqTaxeLocale(), 61.10);
}

/**
 * @brief Test de la tarification annuelle
 * Formule : Tarif fixe (217.41) + contribution + taxe locale
 */
TEST(VehiculePromenade, CalculerTarificationAnnuelle_CalculCorrect) {
    VehiculePromenade unVP("5GZCZ43D13S812715", "E00 VEA", 7);
    
    // Exemple de l'énoncé : 217.41 (fixe) + 30.00 + 61.10 = 308.51$
    unVP.asgContributionTransportEnCommun(30.00);
    unVP.asgTaxeLocale(61.10);

    EXPECT_NEAR(unVP.calculerTarificationAnnuelle(), 308.51, 0.001);
}

/**
 * @brief Test de la méthode clone
 */
TEST(VehiculePromenade, Clone_CopieIdentique) {
    VehiculePromenade original("5GZCZ43D13S812715", "E00 VEA", 4);
    auto copie = original.clone();

    EXPECT_EQ(original.reqVehiculeFormate(), copie->reqVehiculeFormate());
    EXPECT_NE(&original, copie.get());
}

/**
 * @brief Test de l'affichage formaté spécifique
 */
TEST(VehiculePromenade, ReqVehiculeFormate_FormatCorrect) {
    VehiculePromenade unVP("5GZCZ43D13S812715", "E00 VEA", 7);
    unVP.asgContributionTransportEnCommun(30.00);
    unVP.asgTaxeLocale(61.10);
    
    std::string formatte = unVP.reqVehiculeFormate();
    
    EXPECT_NE(formatte.find("Vehicule de promenade"), std::string::npos);
    EXPECT_NE(formatte.find("Nombre de places : 7"), std::string::npos);
    EXPECT_NE(formatte.find("Paiement : 308.51$"), std::string::npos);
}