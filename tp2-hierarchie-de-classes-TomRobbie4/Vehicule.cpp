/** 
 * \file    Vehicule.cpp
 * \brief   Implémentation des méthodes de la classe Vehicule
 * \author  Thomas Robert
 * \date    10 mars 2026
 */

#include "Vehicule.h"
#include "validationFormat.h"
#include "ContratException.h"

#include <sstream>

using namespace saaq;

/**
 * \brief Constructeur de Vehicule
 * \param[in] p_niv Le numéro d'identification du véhicule (NIV)
 * \param[in] p_immatriculation Le numéro de la plaque d'immatriculation du véhicule
 */
Vehicule::Vehicule(const std::string& p_niv, const std::string& p_immatriculation)
: m_niv(p_niv), m_immatriculation(p_immatriculation) {
    PRECONDITION(validerNiv(p_niv));

    POSTCONDITION(m_niv == p_niv);
    POSTCONDITION(m_immatriculation == p_immatriculation);

    INVARIANTS();
}

/**
 * \brief Accesseur en lecture du numéro d'identification (NIV)
 * \return Le numéro d'identification du véhicule
 */
std::string Vehicule::reqNiv() const {
    return m_niv;
}

/**
 * \brief Accesseur en lecture du numéro d'immatriculation
 * \return Le numéro d'immatriculation du véhicule
 */
std::string Vehicule::reqImmatriculation() const {
    return m_immatriculation;
}

/**
 * \brief Mutateur du numéro d'immatriculation
 * \param[in] p_immatriculation La nouvelle plaque d'immatriculation du véhicule
 */
void Vehicule::asgImmatriculation(const std::string& p_immatriculation) {
    m_immatriculation = p_immatriculation;

    POSTCONDITION(m_immatriculation == p_immatriculation);
    INVARIANTS();
}

/**
 * \brief Opérateur d'égalité
 * \param[in] p_vehicule Le véhicule à comparer avec l'instance courante
 * \return Vrai si les deux véhicules ont le même NIV, faux sinon
 */
bool Vehicule::operator==(const Vehicule& p_vehicule) const {
    return m_niv == p_vehicule.m_niv;
}

/**
 * \brief Accesseur qui formate le Vehicule
 * \return Retourne les informations de base du véhicule formatées sous forme de chaîne de caractères
 */
std::string Vehicule::reqVehiculeFormate() const {
    std::ostringstream os;
    os << "Numéro d'identification : " << m_niv << std::endl;
    os << "Numéro d'immatriculation : " << m_immatriculation;
    return os.str();
}

/**
 * \brief Vérifie les invariants pour le véhicule
 */
void Vehicule::verifieInvariant() const {
    INVARIANT(validerNiv(m_niv));
}