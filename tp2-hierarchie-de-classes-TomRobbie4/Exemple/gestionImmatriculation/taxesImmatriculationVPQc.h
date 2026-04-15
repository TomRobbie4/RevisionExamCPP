/**
 * \file taxesImmatriculationVPQc.h
 * \author Thierry Eude
 * \brief Tarifs de renouvellement des immatriculations pour les véhicules de promenade
 */

#ifndef TAXESIMMATRICULATIONVPQC_H
#define TAXESIMMATRICULATIONVPQC_H

#include<map>

namespace saaq
{

struct Taxes
{
double contributionTransportEnCommun;
double taxeImmatriculationVehicule;
};

const std::map<std::string,Taxes>TAXE_IMMATRICULATION
{
{"Baie-d'Urfé",{30,153.45}},
{"Beaconsfield",{30,153.45}},
{"Beauharnois",{30,153.45}},
{"Beloeil",{30,153.45}},
{"Blainville",{30,153.45}},
{"Boisbriand",{30,153.45}},
{"Bois-des-Filion",{30,153.45}},
{"Boucherville",{30,153.45}},
{"Brossard",{30,153.45}},
{"Calixa-Lavallée",{0,153.45}},
{"Candiac",{30,153.45}},
{"Cantley",{30,0}},
{"Carignan",{30,153.45}},
{"Chambly",{30,153.45}},
{"Charlemagne",{30,153.45}},
{"Châteauguay",{30,153.45}},
{"Chelsea",{30,0}},
{"Contrecœur",{30,153.45}},
{"Côte-Saint-Luc",{30,153.45}},
{"Delson",{30,153.45}},
{"Deux-Montagnes",{30,153.45}},
{"Dollard-des-Ormeaux",{30,153.45}},
{"Dorval",{30,153.45}},
{"Gatineau",{30,90}},
{"Hampstead",{30,153.45}},
{"Hudson",{30,153.45}},
{"L'Ancienne-Lorette",{30,0}},
{"L'Assomption",{30,153.45}},
{"L'Île-Cadieux",{0,153.45}},
{"L'Île-Dorval",{30,153.45}},
{"L'Île-Perrot",{30,153.45}},
{"LaPrairie",{30,153.45}},
{"Laval",{30,153.45}},
{"Léry",{30,153.45}},
{"LesCèdres",{0,153.45}},
{"Lévis",{30,0}},
{"Longueuil",{30,153.45}},
{"Lorraine",{30,153.45}},
{"Mascouche",{30,153.45}},
{"McMasterville",{30,153.45}},
{"Mercier",{30,153.45}},
{"Mirabel",{30,153.45}},
{"Mont-Royal",{30,153.45}},
{"Mont-Saint-Hilaire",{30,153.45}},
{"Montréal",{30,153.45}},
{"Montréal-Est",{30,153.45}},
{"Montréal-Ouest",{30,153.45}},
{"Notre-Dame-de-l'Île-Perrot",{30,153.45}},
{"Oka",{0,153.45}},
{"OtterburnPark",{30,153.45}},
{"Pincourt",{30,153.45}},
{"Pointe-Calumet",{30,153.45}},
{"Pointe-Claire",{30,153.45}},
{"Pointe-des-Cascades",{0,153.45}},
{"Prévost",{0,37.70}},
{"Québec",{30,61.1}},
{"Repentigny",{30,153.45}},
{"Richelieu",{30,153.45}},
{"Rosemère",{30,153.45}},
{"Saguenay",{30,0}},
{"Saint-Amable",{30,153.45}},
{"Saint-Augustin-de-Desmaures",{30,0}},
{"Saint-Basile-le-Grand",{30,153.45}},
{"Saint-Bruno-de-Montarville",{30,153.45}},
{"Saint-Colomban",{0,37.70}},
{"Saint-Constant",{30,153.45}},
{"Saint-Eustache",{30,153.45}},
{"Saint-Hippolyte",{0,37.70}},
{"Saint-Isidore",{0,153.45}},
{"Saint-Jean-Baptiste",{0,153.45}},
{"Saint-Jérôme",{30,153.45}},
{"Saint-Joseph-du-Lac",{30,153.45}},
{"Saint-Lambert",{30,153.45}},
{"Saint-Lazare",{30,153.45}},
{"Saint-Mathias-sur-Richelieu",{30,153.45}},
{"Saint-Mathieu",{0,153.45}},
{"Saint-Mathieu-de-Belœil",{0,153.45}},
{"Saint-Philippe",{30,153.45}},
{"Saint-Sulpice",{30,153.45}},
{"Sainte-Anne-de-Bellevue",{30,153.45}},
{"Sainte-Anne-des-Plaines",{30,153.45}},
{"Sainte-Catherine",{30,153.45}},
{"Sainte-Julie",{30,153.45}},
{"Sainte-Marthe-sur-le-Lac",{30,153.45}},
{"Sainte-Sophie",{0,37.70}},
{"Sainte-Thérèse",{30,153.45}},
{"Senneville",{30,153.45}},
{"Sherbrooke",{30,34.75}},
{"Terrasse-Vaudreuil",{30,153.45}},
{"Terrebonne",{30,153.45}},
{"Trois-Rivières",{30,0}},
{"Varennes",{30,153.45}},
{"Vaudreuil-Dorion",{30,153.45}},
{"Vaudreuil-sur-le-Lac",{0,153.45}},
{"Verchères",{30,153.45}},
{"Westmount",{30,153.45}},
{"Wôlinak",{30,0}}
};

bool trouverTaxes(const std::map<std::string,Taxes>&p_tablesTaxes,const std::string& p_ville,
double& p_contributionTransportEnCommun,double& p_taxeImmatriculationVehicule);
}
#endif/*TAXESIMMATRICULATIONVPQC_H*/

