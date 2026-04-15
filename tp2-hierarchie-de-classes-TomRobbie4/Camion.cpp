/** 
 * \file    Camion.cpp
 * \brief   Implémentation des méthodes de la classe Camion
 * \author  Thomas Robert
 * \date    11 mars 2026
 */

#include "Camion.h"
#include "validationFormat.h"
#include "ContratException.h"
#include <sstream>

using namespace saaq;

const double TARIF_CAMION_2_ESSIEUX = 673.69;
const double TARIF_CAMION_4_ESSIEUX = 2626.57;

/**
 * \brief Constructeur de Camion
 * \param[in] p_niv est le numéro d'indentification du camion
 * \param[in] p_immatriculation est le numéro de la plaque du camion
 * \param[in] p_poids est le poids du camion
 * \param[in] p_nbEssieux est le nombre d'essieux du camion
 */
Camion::Camion(const std::string& p_niv, const std::string& p_immatriculation, 
        int p_poids, int p_nbEssieux) : Vehicule(p_niv, p_immatriculation),
        m_poids(p_poids), m_nbEssieux(p_nbEssieux) 
{
    PRECONDITION(validerImmatriculationCamion(p_immatriculation));
    PRECONDITION(p_poids > 3000);
    PRECONDITION(p_nbEssieux >= 2);

    POSTCONDITION(m_poids == p_poids);
    POSTCONDITION(m_nbEssieux == p_nbEssieux);

    INVARIANTS();
}

/**
 * \brief Accesseur en lecture du poids
 * \return Le poids du camion
 */
int Camion::reqPoids() const
{
    return m_poids;
}

/**
 * \brief Accesseur en lecture du nombre d'essieux
 * \return Le nombre d'essieux du camion
 */
int Camion::reqNbEssieux() const
{
    return m_nbEssieux;
}

/**
 * \brief Mutateur du numéro d'immatriculation
 * \param[in] p_immatriculation La nouvelle plaque d'immatriculation du camion
 */
void Camion::asgImmatriculation(const std::string& p_immatriculation)
{
    PRECONDITION(validerImmatriculationCamion(p_immatriculation));
    
    Vehicule::asgImmatriculation(p_immatriculation);
        
    verifieInvariant();
}

/**
 * \brief Calcule la tarification annuelle
 * \return La tarification annuelle du camion
 */
double Camion::calculerTarificationAnnuelle() const
{
    if(m_nbEssieux <= 2) return TARIF_CAMION_2_ESSIEUX;
    else return TARIF_CAMION_4_ESSIEUX;
}

/**
 * \brief Accesseur qui formate le Camion
 * \return Retourne le camion formaté sous forme de chaîne de caractères
 */
std::string Camion::reqVehiculeFormate() const
{
    std::ostringstream os;
    os << "Camion" << std::endl;
    os << Vehicule::reqVehiculeFormate() << std::endl;
    os << "Nombre d'essieux : " << m_nbEssieux << std::endl;
    os << "Poids : " << m_poids << std::endl;
    os << "Paiement : " << calculerTarificationAnnuelle() << "$";
    
    return os.str();
}

/**
 * \brief Crée et retourne une copie dynamique du camion.
 * \return Un pointeur intelligent (std::unique_ptr) contenant la copie du camion.
 */
std::unique_ptr<Vehicule> Camion::clone() const
{
    return std::make_unique<Camion>(*this);
}

/**
 * \brief Vérifie les invariants pour le camion
 */
void Camion::verifieInvariant() const 
{
    INVARIANT(m_poids > 3000);
    INVARIANT(m_nbEssieux >= 2);
    INVARIANT(validerImmatriculationCamion(reqImmatriculation()));
}