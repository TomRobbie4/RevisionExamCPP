/** 
 * \file   taxesImmatriculationVPQc.cpp
 * \author Thierry Eude
 */

#include <iostream>
#include "taxesImmatriculationVPQc.h"

using namespace std;

namespace saaq
{
/**
 * \brief permet de trouver les montants de la contribution au transport en commun 
 * et de la taxe sur l'immatriculation des véhicules ou TIV selon la ville
 * @param[in] p_tablesTaxes tableau des montants selon les villes
 * @param[in] p_ville ville recherchée
 * @param[out] p_contributionTransportEnCommun montant de contribution de transport en commun
 * @param[out] p_taxeImmatriculationVehicule taxe sur l'immatriculation des véhicules ou TIV
 * @return true si trouvé false sinon
 */
bool trouverTaxes(const std::map<std::string, Taxes>& p_tablesTaxes, const std::string& p_ville,
                  double& p_contributionTransportEnCommun, double& p_taxeImmatriculationVehicule)
{
    bool trouve{false};
    auto iterateur = p_tablesTaxes.find(p_ville);
    if (iterateur != p_tablesTaxes.end())
    {
//        std::cout << "Trouvé : " << iterateur->first
//                << " -> " << iterateur->second.contributionTransportEnCommun
//                << ", " << iterateur->second.taxeImmatriculationVehicule << "\n";
        p_contributionTransportEnCommun = iterateur->second.contributionTransportEnCommun;
        p_taxeImmatriculationVehicule = iterateur->second.taxeImmatriculationVehicule;
        trouve = true;
    }
    return trouve;
}
}