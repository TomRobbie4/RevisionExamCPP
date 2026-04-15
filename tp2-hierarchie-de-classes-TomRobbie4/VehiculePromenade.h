/**
 * \file    VehiculePromenade.h
 * \brief   Déclaration de la classe VehiculePromenade
 * \author  Thomas Robert
 * \date    13 mars 2026
 */

#ifndef VEHICULEPROMENADE_H
#define VEHICULEPROMENADE_H

#include "Vehicule.h"
#include <memory>

namespace saaq {

/**
 * \brief Classe représentant un véhicule de promenade, qui hérite de Vehicule
 */
class VehiculePromenade : public Vehicule 
{
public:
    /**
     * \brief Constructeur de VehiculePromenade
     * \param[in] p_niv Le numéro d'identification du véhicule (NIV)
     * \param[in] p_immatriculation Le numéro de la plaque d'immatriculation du véhicule
     * \param[in] p_nbPlaces Le nombre de places dans le véhicule de promenade
     */
    VehiculePromenade(const std::string& p_niv, const std::string& p_immatriculation, int p_nbPlaces);
    
    /**
     * \brief Destructeur virtuel
     */
    virtual ~VehiculePromenade() {};
    
    /**
     * \brief Accesseur en lecture du nombre de places
     * \return Le nombre de places du véhicule de promenade
     */
    int reqNbPlaces() const;
    
    /**
     * \brief Accesseur en lecture de la tarification de renouvellement d'immatriculation
     * \return Le montant de base pour le renouvellement
     */
    double reqTarificationRenouvellementImmatriculation() const;
    
    /**
     * \brief Accesseur en lecture de la contribution au transport en commun
     * \return Le montant de la contribution au transport en commun
     */
    double reqContributionTransportEnCommun() const;
    
    /**
     * \brief Accesseur en lecture de la taxe locale
     * \return Le montant de la taxe locale
     */
    double reqTaxeLocale() const;
    
    /**
     * \brief Mutateur du numéro d'immatriculation
     * \param[in] p_immatriculation La nouvelle plaque d'immatriculation du véhicule
     */
    void asgImmatriculation(const std::string& p_immatriculation);
    
    /**
     * \brief Mutateur de la contribution au transport en commun
     * \param[in] p_contribution Le nouveau montant de la contribution
     */
    void asgContributionTransportEnCommun(double p_contribution);
    
    /**
     * \brief Mutateur de la taxe locale
     * \param[in] p_taxeLocale Le nouveau montant de la taxe locale
     */
    void asgTaxeLocale(double p_taxeLocale);
    
    /**
     * \brief Calcule la tarification annuelle
     * \return La tarification annuelle totale du véhicule de promenade
     */
    double calculerTarificationAnnuelle() const;
    
    /**
     * \brief Accesseur qui formate le VehiculePromenade
     * \return Retourne le véhicule de promenade formaté sous forme de chaîne de caractères
     */
    virtual std::string reqVehiculeFormate() const;
    
    /**
     * \brief Crée et retourne une copie dynamique du véhicule de promenade
     * \return Un pointeur intelligent (std::unique_ptr) contenant la copie du véhicule
     */
    std::unique_ptr<Vehicule> clone() const;

private:
    int m_nbPlaces;
    double m_tarificationRenouvellementImmatriculation; // Constante?
    double m_contributionTransportEnCommun;
    double m_taxeLocale;

    /**
     * \brief Vérifie les invariants pour le véhicule de promenade
     */
    void verifieInvariant() const;
};

}

#endif /* VEHICULEPROMENADE_H */