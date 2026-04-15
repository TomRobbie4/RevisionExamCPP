/**
 * \file    Camion.h
 * \brief   Déclaration de la classe Camion
 * \author  Thomas Robert
 * \date    11 mars 2026
 */

#ifndef CAMION_H
#define CAMION_H

#include "Vehicule.h"
#include <memory>

namespace saaq {
    
    /**
     * \brief Classe représentant un camion, qui hérite de Vehicule
     */
    class Camion : public Vehicule
    {
    public:
        /**
         * \brief Constructeur de Camion
         * \param[in] p_niv Le numéro d'identification du camion (NIV)
         * \param[in] p_immatriculation Le numéro de la plaque d'immatriculation du camion
         * \param[in] p_poids Le poids du camion en kilogrammes
         * \param[in] p_nbEssieux Le nombre d'essieux du camion
         */
        Camion(const std::string& p_niv, const std::string& p_immatriculation, int p_poids, int p_nbEssieux);
        
        /**
         * \brief Destructeur virtuel
         */
        virtual ~Camion() {};
        
        /**
         * \brief Accesseur en lecture du poids
         * \return Le poids du camion
         */
        int reqPoids() const;
        
        /**
         * \brief Accesseur en lecture du nombre d'essieux
         * \return Le nombre d'essieux du camion
         */
        int reqNbEssieux() const;
        
        /**
         * \brief Mutateur du numéro d'immatriculation
         * \param[in] p_immatriculation La nouvelle plaque d'immatriculation du camion
         */
        void asgImmatriculation(const std::string &p_immatriculation);
        
        /**
         * \brief Accesseur qui formate le Camion
         * \return Retourne le camion formaté sous forme de chaîne de caractères
         */
        virtual std::string reqVehiculeFormate() const;
                
        /**
         * \brief Calcule la tarification annuelle
         * \return La tarification annuelle du camion
         */
        double calculerTarificationAnnuelle() const;
        
        /**
         * \brief Crée et retourne une copie dynamique du camion
         * \return Un pointeur intelligent (std::unique_ptr) contenant la copie du camion
         */
        std::unique_ptr<Vehicule> clone() const;
        
    private:
        int m_poids;
        int m_nbEssieux;
        
        /**
         * \brief Vérifie les invariants pour le camion
         */
        void verifieInvariant() const;
    };
    
}

#endif /* CAMION_H */