/**
 * \file    Vehicule.h
 * \brief   Déclaration de la classe Vehicule
 * \author  Thomas Robert
 * \date    10 mars 2026
 */

#ifndef VEHICULE_H
#define VEHICULE_H

#include <string>
#include <memory>

namespace saaq {

/**
 * \brief Classe de base abstraite représentant un véhicule
 */
class Vehicule {
public:
    /**
     * \brief Constructeur de Vehicule
     * \param[in] p_niv Le numéro d'identification du véhicule (NIV)
     * \param[in] p_immatriculation Le numéro de la plaque d'immatriculation du véhicule
     */
    Vehicule(const std::string& p_niv, const std::string& p_immatriculation);
    
    /**
     * \brief Destructeur virtuel
     */
    virtual ~Vehicule() {};

    /**
     * \brief Accesseur en lecture du numéro d'identification (NIV)
     * \return Le numéro d'identification du véhicule
     */
    std::string reqNiv() const;
    
    /**
     * \brief Accesseur en lecture du numéro d'immatriculation
     * \return Le numéro d'immatriculation du véhicule
     */
    std::string reqImmatriculation() const;

    /**
     * \brief Opérateur d'égalité basé sur le NIV
     * \param[in] p_vehicule Le véhicule à comparer avec l'instance courante
     * \return Vrai si les deux véhicules ont le même NIV, faux sinon
     */
    bool operator==(const Vehicule& p_vehicule) const; // compare le NIV

    /**
     * \brief Accesseur qui formate le Vehicule
     * \return Retourne les informations de base du véhicule formatées sous forme de chaîne de caractères
     */
    virtual std::string reqVehiculeFormate() const;
    
    /**
     * \brief Méthode virtuelle pure pour créer une copie dynamique du véhicule
     * \return Un pointeur intelligent (std::unique_ptr) contenant la copie du véhicule
     */
    virtual std::unique_ptr<Vehicule> clone() const = 0; 
    
    /**
     * \brief Méthode virtuelle pure pour calculer la tarification annuelle
     * \return La tarification annuelle du véhicule
     */
    virtual double calculerTarificationAnnuelle() const = 0; 

protected:
    /**
     * \brief Mutateur du numéro d'immatriculation
     * \param[in] p_immatriculation La nouvelle plaque d'immatriculation du véhicule
     */
    void asgImmatriculation(const std::string& p_immatriculation);

private:
    std::string m_niv;
    std::string m_immatriculation;

    /**
     * \brief Vérifie les invariants pour le véhicule (Méthode pour la théorie du contrat)
     */
    void verifieInvariant() const;
};

} 

#endif /* VEHICULE_H */