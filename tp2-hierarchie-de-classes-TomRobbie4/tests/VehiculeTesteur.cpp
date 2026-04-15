#include <gtest/gtest.h>
#include <memory>
#include "Vehicule.h"
#include "ContratException.h"
#include <memory>

using namespace saaq;

/**
 * @brief Classe factice (Mock) pour tester la classe abstraite Vehicule.
 * Elle permet d'instancier un objet dérivé et d'accéder à la méthode protégée.
 */
class VehiculeDeTest : public Vehicule {
public:
    VehiculeDeTest(const std::string& p_niv, const std::string& p_immatriculation)
        : Vehicule(p_niv, p_immatriculation) {}

    // Implémentation obligatoire des méthodes pures
    virtual std::unique_ptr<Vehicule> clone() const override {
        return std::make_unique<VehiculeDeTest>(*this);
    }
    
    virtual double calculerTarificationAnnuelle() const override {
        return 0.0;
    }

    // Méthode relais (wrapper) pour tester la méthode protégée asgImmatriculation
    void testAsgImmatriculation(const std::string& p_immatriculation) {
        asgImmatriculation(p_immatriculation);
    }
};

/**
 * @brief Test du Constructeur
 */
TEST(Vehicule, Constructeur_Valide_AttributsAssignes) {
    std::string nivValide = "1HGCM82633A004352"; 
    std::string immatValide = "ABC 000";

    // On utilise la classe factice au lieu de Vehicule
    VehiculeDeTest v(nivValide, immatValide);

    EXPECT_EQ(nivValide, v.reqNiv());
    EXPECT_EQ(immatValide, v.reqImmatriculation());
}

/**
 * @brief Test du Constructeur (Invalide)
 */
TEST(Vehicule, Constructeur_NivInvalide_LancePreconditionException) {
    std::string nivInvalide = "NIV_INVALIDE_TROP_COURT"; 
    std::string immatValide = "ABC 000";

    // On s'attend à ce que l'instanciation de la classe factice lance l'exception
    EXPECT_THROW(VehiculeDeTest(nivInvalide, immatValide), PreconditionException);
}

/**
 * @brief Test du mutateur asgImmatriculation
 */
TEST(Vehicule, AsgImmatriculation_Valide_ModifieImmatriculation) {
    VehiculeDeTest v("1HGCM82633A004352", "ABC 000");
    std::string nouvellePlaque = "XYZ 999";

    // On appelle la méthode relais publique de notre classe factice
    v.testAsgImmatriculation(nouvellePlaque);

    EXPECT_EQ(nouvellePlaque, v.reqImmatriculation());
}

/**
 * @brief Test de l'opérateur d'égalité == (Vrai)
 */
TEST(Vehicule, OperateurEgalite_MemeNiv_RetourneVrai) {
    VehiculeDeTest v1("1HGCM82633A004352", "ABC 000");
    VehiculeDeTest v2("1HGCM82633A004352", "XYZ 999");

    bool sontEgaux = (v1 == v2);
    EXPECT_TRUE(sontEgaux);
}

/**
 * @brief Test de l'opérateur d'égalité == (Faux)
 */
TEST(Vehicule, OperateurEgalite_NivDifferent_RetourneFaux) {
    VehiculeDeTest v1("1HGCM82633A004352", "ABC 000");
    VehiculeDeTest v2("5GZCZ43D13S812715", "ABC 000");

    bool sontEgaux = (v1 == v2);
    EXPECT_FALSE(sontEgaux);
}

/**
 * @brief Test de la méthode reqVehiculeFormate
 */
TEST(Vehicule, ReqVehiculeFormate_Valide_RetourneBonFormat) {
    VehiculeDeTest v("1HGCM82633A004352", "ABC 000");
    std::string resultat = v.reqVehiculeFormate();

    std::string attendu = "Numéro d'identification : 1HGCM82633A004352\n"
                          "Numéro d'immatriculation : ABC 000"; // Ajoute un \n à la fin si ta méthode en met un
    
    EXPECT_EQ(attendu, resultat);
}