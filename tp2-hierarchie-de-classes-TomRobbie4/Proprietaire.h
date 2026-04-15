/**
 * \file    Proprietaire.h
 * \brief   Déclaration de la classe Proprietaire
 * \author  Thomas Robert
 * \date    1 avril 2026
 */

#ifndef PROPRIETAIRE_H
#define PROPRIETAIRE_H

#include <string>
#include <vector>
#include <memory>
#include "Vehicule.h"

namespace saaq {

/**
 * \brief Classe gérant un dossier de véhicules pour un individu
 */
class Proprietaire {
public:
    /**
     * \brief Constructeur de Proprietaire
     * \param[in] p_nom Le nom du propriétaire
     * \param[in] p_prenom Le prénom du propriétaire
     * \param[in] p_villeDomicile La ville de domicile du propriétaire
     */
    Proprietaire(const std::string& p_nom, const std::string& p_prenom, const std::string& p_villeDomicile);
    
    // Forme de Coplien
    
    /**
     * \brief Constructeur de copie
     * \param[in] p_source Le propriétaire à copier
     */
    Proprietaire(const Proprietaire& p_source);
    
    /**
     * \brief Destructeur virtuel par défaut
     */
    virtual ~Proprietaire() = default; // Les unique_ptr gèrent la suite
    
    /**
     * \brief Opérateur d'assignation
     * \param[in] p_source Le propriétaire à assigner
     * \return L'instance courante du propriétaire (*this)
     */
    Proprietaire& operator=(const Proprietaire& p_source);

    // Accesseurs
    
    /**
     * \brief Accesseur en lecture du nom
     * \return Le nom du propriétaire
     */
    const std::string& reqNom() const;
    
    /**
     * \brief Accesseur en lecture du prénom
     * \return Le prénom du propriétaire
     */
    const std::string& reqPrenom() const;
    
    /**
     * \brief Accesseur en lecture de la ville de domicile
     * \return La ville de domicile du propriétaire
     */
    const std::string& reqVille() const;
    
    /**
     * \brief Accesseur en lecture du nombre de véhicules
     * \return Le nombre de véhicules possédés par le propriétaire
     */
    size_t reqNbVehicules() const;
    
    /**
     * \brief Accesseur en lecture du paiement total
     * \return Le montant total de la tarification pour l'ensemble des véhicules
     */
    double reqPaiementTotal() const;

    // Méthodes publiques
    
    /**
     * \brief Ajoute un véhicule au dossier en le clonant
     * \param[in] p_nouveauVehicule Le nouveau véhicule à ajouter
     */
    void ajouterVehicule(const Vehicule& p_nouveauVehicule);
    
    /**
     * \brief Retourne les informations du propriétaire et de ses véhicules
     * \return Retourne le propriétaire et ses véhicules formatés sous forme de chaîne de caractères
     */
    std::string reqProprietaireFormate() const;

private:
    std::string m_nom;
    std::string m_prenom;
    std::string m_villeDomicile;
    double m_paiementTotal;
    std::vector<std::unique_ptr<Vehicule>> m_vehicules;

    /**
     * \brief Vérifie les invariants pour le propriétaire
     */
    void verifieInvariant() const;
};

} // namespace saaq

#endif /* PROPRIETAIRE_H */