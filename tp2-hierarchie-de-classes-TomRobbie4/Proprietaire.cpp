/** 
 * \file    Proprietaire.cpp
 * \brief   Implémentation des méthodes de la classe Proprietaire
 * \author  Thomas Robert
 * \date    1 avril 2026
 */

#include "Proprietaire.h"
#include "ContratException.h"
#include <sstream>
#include <iomanip>
#include <memory>

namespace saaq {

/**
 * \brief Constructeur avec paramètres 
 * \param[in] p_nom Le nom du propriétaire
 * \param[in] p_prenom Le prénom du propriétaire
 * \param[in] p_villeDomicile La ville de domicile du propriétaire
 */
Proprietaire::Proprietaire(const std::string& p_nom, const std::string& p_prenom, const std::string& p_villeDomicile)
    : m_nom(p_nom), m_prenom(p_prenom), m_villeDomicile(p_villeDomicile), m_paiementTotal(0.0) {
    PRECONDITION(!p_nom.empty()); 
    PRECONDITION(!p_prenom.empty()); 
    POSTCONDITION(m_nom == p_nom);
    POSTCONDITION(m_paiementTotal == 0.0);
    verifieInvariant();
}

/**
 * \brief Constructeur de copie (Copie profonde pour unique_ptr) 
 * \param[in] p_source Le propriétaire à copier
 */
Proprietaire::Proprietaire(const Proprietaire& p_source)
    : m_nom(p_source.m_nom), m_prenom(p_source.m_prenom), 
      m_villeDomicile(p_source.m_villeDomicile), m_paiementTotal(p_source.m_paiementTotal) {
    for (const auto& v : p_source.m_vehicules) {
        m_vehicules.push_back(v->clone()); 
    }
    verifieInvariant();
}

/**
 * \brief Opérateur d'assignation 
 * \param[in] p_source Le propriétaire à assigner
 * \return L'instance courante du propriétaire (*this)
 */
Proprietaire& Proprietaire::operator=(const Proprietaire& p_source) {
    if (this != &p_source) {
        m_nom = p_source.m_nom;
        m_prenom = p_source.m_prenom;
        m_villeDomicile = p_source.m_villeDomicile;
        m_paiementTotal = p_source.m_paiementTotal;
        
        m_vehicules.clear(); // Libère l'ancienne mémoire
        for (const auto& v : p_source.m_vehicules) {
            m_vehicules.push_back(v->clone());
        }
    }
    verifieInvariant();
    return *this;
}

/**
 * \brief Accesseur en lecture du nom
 * \return Le nom du propriétaire
 */
const std::string& Proprietaire::reqNom() const {
    return m_nom;
}

/**
 * \brief Accesseur en lecture du prénom
 * \return Le prénom du propriétaire
 */
const std::string& Proprietaire::reqPrenom() const {
    return m_prenom;
}

/**
 * \brief Accesseur en lecture de la ville de domicile
 * \return La ville de domicile du propriétaire
 */
const std::string& Proprietaire::reqVille() const {
    return m_villeDomicile;
}

/**
 * \brief Accesseur en lecture du nombre de véhicules
 * \return Le nombre de véhicules possédés par le propriétaire
 */
size_t Proprietaire::reqNbVehicules() const {
    return m_vehicules.size();
}

/**
 * \brief Accesseur en lecture du paiement total
 * \return Le montant total à payer pour les véhicules
 */
double Proprietaire::reqPaiementTotal() const {
    return m_paiementTotal;
}

/**
 * \brief Ajoute un véhicule au dossier en le clonant 
 * \param[in] p_nouveauVehicule Le nouveau véhicule à ajouter
 */
void Proprietaire::ajouterVehicule(const Vehicule& p_nouveauVehicule) {
    m_vehicules.push_back(p_nouveauVehicule.clone());
    m_paiementTotal += p_nouveauVehicule.calculerTarificationAnnuelle(); 
    verifieInvariant();
}

/**
 * \brief Retourne les infos du propriétaire et de ses véhicules 
 * \return Retourne le propriétaire et ses véhicules formatés sous forme de chaîne de caractères
 */
std::string Proprietaire::reqProprietaireFormate() const {
    std::ostringstream os;
    os << "Propriétaire" << std::endl; 
    os << "Nom : " << m_nom << std::endl; 
    os << "Prénom : " << m_prenom << std::endl; 
    os << "Domicile : " << m_villeDomicile << std::endl; 
    
    for (const auto& v : m_vehicules) {
        os << "----------------------------------" << std::endl;
        os << v->reqVehiculeFormate() << std::endl;
    }
    
    os << "----------------------------------" << std::endl;
    os << "Paiement total : " << m_paiementTotal << "$"; 
    
    return os.str();
}


/**
 * \brief Vérifie les invariants pour le propriétaire
 */
void Proprietaire::verifieInvariant() const {
    INVARIANT(!m_nom.empty());
    INVARIANT(!m_prenom.empty());
    INVARIANT(m_paiementTotal >= 0);
}

} // namespace saaq