/**
 * \file    validationFormat.h
 * \brief   Déclaration des fonctions de validation de format
 * \author  Thomas Robert
 * \date    6 février 2026
 */

#ifndef VALIDATIONFORMAT_H
#define VALIDATIONFORMAT_H

#include <string>

namespace saaq {

    /**
     * \brief Valide le format du numéro d'immatriculation d'un camion
     * \param[in] p_immatriculation Le numéro de la plaque d'immatriculation à valider
     * \return Vrai si le format est valide (commence par 'L' suivi de 6 chiffres), faux sinon
     */
    bool validerImmatriculationCamion(const std::string& p_immatriculation);
    
    /**
     * \brief Valide le format du numéro d'immatriculation d'un véhicule de promenade
     * \param[in] p_immatriculation Le numéro de la plaque d'immatriculation à valider
     * \return Vrai si le format correspond à un des modèles acceptés, faux sinon
     */
    bool validerImmatriculationPromenade(const std::string& p_immatriculation);
    
    /**
     * \brief Valide le Numéro d'Identification du Véhicule (NIV)
     * \param[in] p_niv Le NIV à valider
     * \return Vrai si le NIV est valide selon les règles de calcul (longueur, caractères, clé de contrôle), faux sinon
     */
    bool validerNiv(const std::string& p_niv);
    
    /**
     * \brief Valide le format complet du fichier ou flux d'entrée (NIV puis Plaque)
     * \param[in] p_is Le flux d'entrée représentant le fichier à valider
     * \return Vrai si l'en-tête, la date et tous les véhicules sont correctement formatés, faux sinon
     */
    bool validerFormatFichier(std::istream& p_is);

} 

#endif /* VALIDATIONFORMAT_H */