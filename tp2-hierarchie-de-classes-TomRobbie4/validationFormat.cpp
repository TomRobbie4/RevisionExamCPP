/**
 * \file    validationFormat.cpp
 * \brief   Implémentation des fonctions de validation de format
 * \author  Thomas Robert
 * \date    6 février 2026
 */

#include "validationFormat.h"
#include <iostream>
#include <array>

namespace saaq {

    /**
     * \brief Valide le format du numéro d'immatriculation d'un camion
     * \param[in] p_immatriculation Le numéro de la plaque d'immatriculation à valider
     * \return Vrai si le format est valide (commence par 'L' suivi de 6 chiffres), faux sinon
     */
    bool validerImmatriculationCamion(const std::string& p_immatriculation) {
        bool valid = false;
        if (p_immatriculation[0] == 'L' && p_immatriculation.length() == 7) {
            valid = true;
            for (char i = 1; i < 7; i++) {
                if (!std::isdigit(p_immatriculation[i])) valid = false;
            }
        }
        return valid;
    }

    /**
     * \brief Valide le format du numéro d'immatriculation d'un véhicule de promenade
     * \param[in] p_immatriculation Le numéro de la plaque d'immatriculation à valider
     * \return Vrai si le format correspond à un des modèles acceptés, faux sinon
     */
    bool validerImmatriculationPromenade(const std::string& p_immatriculation) {
        bool valid = false;
        std::string im_ok = "";

        if (p_immatriculation.length() == 7) {
            valid = true;
        }

        for (unsigned char c : p_immatriculation) {
            if (std::isdigit(c)) {
                im_ok += '0';
            } else if (c == ' ') {
                im_ok += ' ';
            } else if (std::isalpha(c) && (std::toupper(c) != 'I' && std::toupper(c) != 'O' && std::toupper(c) != 'U')) {
                im_ok += 'A';
            }
        }
        // trois type de plaque
        // 000 ABC
        // AAA 000
        // A00 ABC
        // 000H000
        if (im_ok != "000 AAA" && im_ok != "AAA 000" && im_ok != "A00 AAA" && im_ok != "000A000") {
            valid = false;
        }

        return valid;
    }

    /**
     * \brief Valide le Numéro d'Identification du Véhicule (NIV)
     * \param[in] p_niv Le NIV à valider
     * \return Vrai si la longueur, les caractères et la clé de contrôle du NIV sont valides, faux sinon
     */
    bool validerNiv(const std::string& p_niv) {
        bool valid = false;
        int checksum{0};
        int alphaValue[26] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 2, 3, 4, 5, 6, 7, 8, 9};
        int weight[17] = {8, 7, 6, 5, 4, 3, 2, 10, 0, 9, 8, 7, 6, 5, 4, 3, 2};

        if (p_niv.length() == 17) {
            valid = true;
            for (int i = 0; i < 17; i++) {
                if (std::isdigit(p_niv[i])) {
                    checksum += (p_niv[i] - '0') * weight[i];
                } else if (std::isalpha(p_niv[i]) && std::toupper(p_niv[i]) != 'I' && std::toupper(p_niv[i]) != 'O' && std::toupper(p_niv[i]) != 'Q') {
                    checksum += alphaValue[std::toupper(p_niv[i]) - 'A'] * weight[i];
                } else {
                    valid = false;
                }
            }

            // vérifier le checkum
            checksum %= 11;
            if (checksum == 10) {
                checksum = 'X';
            } else checksum += 0x30;

            if (p_niv[8] != checksum) valid = false;
        }
        return valid;
    }

    /**
     * \brief Valide le format complet du fichier (NIV puis Plaque)
     * \param[in] p_is Le flux d'entrée représentant le fichier à valider
     * \return Vrai si l'en-tête, la date et tous les véhicules sont correctement formatés, faux sinon
     */
    bool validerFormatFichier(std::istream& p_is) {
        bool valid = true;
        std::string buffer;
        int jour, mois, annee;

        // En-tête : Nom, Prénom, Ville
        for (int i = 0; i < 3; ++i) {
            if (!(std::getline(p_is, buffer) && !buffer.empty())) valid = false;
        }

        // Date
        if (valid) {
            p_is >> jour >> mois >> annee;
            if (p_is.fail()) valid = false;
            p_is.ignore(256, '\n'); // Nettoie la ligne après la date
        }

        // Boucle des véhicules
        while (valid && std::getline(p_is, buffer)) {
            if (buffer.empty()) continue;

            std::string niv = buffer; // 1. NIV
            std::string plaque; // 2. Plaque

            if (!validerNiv(niv) || !std::getline(p_is, plaque) || plaque.empty()) {
                valid = false;
            } else {
                if (validerImmatriculationCamion(plaque)) {
                    int poids, essieux;
                    p_is >> poids >> essieux;
                    if (p_is.fail()) valid = false;
                    p_is.ignore(256, '\n');
                } else if (validerImmatriculationPromenade(plaque)) {
                    int places;
                    p_is >> places;
                    if (p_is.fail()) valid = false;
                    p_is.ignore(256, '\n');
                } else {
                    valid = false;
                }
            }
        }
        return valid;
    }
}