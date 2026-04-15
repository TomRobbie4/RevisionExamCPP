/** 
 * \file    VehiculePromenade.cpp
 * \brief   Implémentation des méthodes de la classe VehiculePromenade
 * \author  Thomas Robert
 * \date    13 mars 2026
 */

#include "VehiculePromenade.h"
#include "validationFormat.h"
#include "ContratException.h"
#include <sstream>


using namespace saaq;

const double TARIFICATIONRENOUVELLEMENTIMMATRICULATION = 217.41;

/**
 * \brief Constructeur de VehiculePromenade
 * \param[in] p_niv Le numéro d'identification du véhicule (NIV)
 * \param[in] p_immatriculation Le numéro de la plaque d'immatriculation du véhicule
 * \param[in] p_nbPlaces Le nombre de places dans le véhicule de promenade
 */
VehiculePromenade::VehiculePromenade(const std::string& p_niv, const std::string& p_immatriculation, int p_nbPlaces)
    : Vehicule(p_niv, p_immatriculation), m_nbPlaces(p_nbPlaces),
        m_tarificationRenouvellementImmatriculation(TARIFICATIONRENOUVELLEMENTIMMATRICULATION),
        m_contributionTransportEnCommun(0.0), m_taxeLocale(0.0)
{
    PRECONDITION(validerImmatriculationPromenade(p_immatriculation));
    PRECONDITION(p_nbPlaces > 0 && p_nbPlaces <= 9);

    POSTCONDITION(m_nbPlaces == p_nbPlaces);

    INVARIANTS();
}

/**
 * \brief Accesseur en lecture du nombre de places
 * \return Le nombre de places du véhicule de promenade
 */
int VehiculePromenade::reqNbPlaces() const
{
    return m_nbPlaces;
}

/**
 * \brief Accesseur en lecture de la tarification de renouvellement d'immatriculation
 * \return Le montant de base pour le renouvellement
 */
double VehiculePromenade::reqTarificationRenouvellementImmatriculation() const
{
    return m_tarificationRenouvellementImmatriculation;
}

/**
 * \brief Accesseur en lecture de la contribution au transport en commun
 * \return Le montant de la contribution au transport en commun
 */
double VehiculePromenade::reqContributionTransportEnCommun() const
{
    return m_contributionTransportEnCommun;
}

/**
 * \brief Accesseur en lecture de la taxe locale
 * \return Le montant de la taxe locale
 */
double VehiculePromenade::reqTaxeLocale() const
{
    return m_taxeLocale;
}

/**
 * \brief Mutateur du numéro d'immatriculation
 * \param[in] p_immatriculation La nouvelle plaque d'immatriculation du véhicule
 */
void VehiculePromenade::asgImmatriculation(const std::string& p_immatriculation)
{
    PRECONDITION(validerImmatriculationPromenade(p_immatriculation));
    
    Vehicule::asgImmatriculation(p_immatriculation);
        
    INVARIANTS();
}

/**
 * \brief Mutateur de la contribution au transport en commun
 * \param[in] p_contribution Le nouveau montant de la contribution
 */
void VehiculePromenade::asgContributionTransportEnCommun(double p_contribution)
{
    m_contributionTransportEnCommun = p_contribution;
    POSTCONDITION(m_contributionTransportEnCommun == p_contribution);
    INVARIANTS();
}

/**
 * \brief Mutateur de la taxe locale
 * \param[in] p_taxeLocale Le nouveau montant de la taxe locale
 */
void VehiculePromenade::asgTaxeLocale(double p_taxeLocale) 
{
    m_taxeLocale = p_taxeLocale;
    POSTCONDITION(m_taxeLocale == p_taxeLocale);
    INVARIANTS();
}

/**
 * \brief Calcule la tarification annuelle
 * \return La tarification annuelle totale du véhicule de promenade
 */
double VehiculePromenade::calculerTarificationAnnuelle() const
{
    // j'additionne les couts totale.
    return m_tarificationRenouvellementImmatriculation + m_contributionTransportEnCommun + m_taxeLocale;
}

/**
 * \brief Accesseur qui formate le VehiculePromenade
 * \return Retourne le véhicule de promenade formaté sous forme de chaîne de caractères
 */
std::string VehiculePromenade::reqVehiculeFormate() const 
{
    std::ostringstream os;

    os << "Vehicule de promenade" << std::endl;
    os << Vehicule::reqVehiculeFormate() << std::endl;
    os << "Nombre de places : " << m_nbPlaces << std::endl;
    os << "Paiement : " << calculerTarificationAnnuelle() << "$";

    return os.str();
}

/**
 * \brief Crée et retourne une copie dynamique du véhicule de promenade
 * \return Un pointeur intelligent (std::unique_ptr) contenant la copie du véhicule
 */
std::unique_ptr<Vehicule> VehiculePromenade::clone() const 
{
    return std::make_unique<VehiculePromenade>(*this);
}

/**
 * \brief Vérifie les invariants pour le véhicule de promenade
 */
void VehiculePromenade::verifieInvariant() const 
{
    INVARIANT(m_nbPlaces > 0 && m_nbPlaces <= 9);
    INVARIANT(validerImmatriculationPromenade(reqImmatriculation()));
}