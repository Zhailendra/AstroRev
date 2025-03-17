# AstroRev

🚀 **AstroRev** est un jeu de course intergalactique où tu pilotés des véhicules futuristes à travers l'espace en split screen, avec des mécaniques de course innovantes, comme la simulation des physiquse de flottement par rapport au sol, des boosts, et des zones de gravité réduite. Développe tes compétences de pilote à travers des environnements dynamiques et compétitifs. Construit avec **Unreal Engine** en utilisant **C++** et **Blueprints**, AstroRev te plonge dans une expérience de course épique à travers l'univers ! 🌌🏎️✨

## 🎮 Fonctionnalités
- **Course Spatiale Intense** – Traverse des parcours intergalactiques, en affrontant des adversaires dans des courses de haute vitesse.
- **Simulations de Physique de Flottement** – Ressens l'effet de la gravité réduite et de la gravité normale tout en adaptant ton hovercraft aux conditions de chaque terrain.
- **Boosts et Zones de Gravité** – Utilise des boosts pour accélérer et traverse des zones où la gravité est réduite pour prendre de l'avance !
- **Personnalisation du Véhicule** – Améliore les capacités de ton hovercraft entre les courses pour gagner en vitesse, contrôle et efficacité.
- **Environnements Dynamiques** – Des pistes avec des effets de gravité différents, des obstacles et des boosts disséminés tout au long des niveaux.

## 🛠️ Détails du Développement
- Construit avec **Unreal Engine**.
- Gameplay principal codé en **C++**.
- Interface utilisateur développée avec **Blueprints**.
- **Codebase Modulaire** – Les véhicules dérivent tous de la classe `BaseCar`, permettant une grande flexibilité pour l’ajout de nouveaux véhicules et comportements.
                         – Les PowerUps dérivent de la class `BasePowerUp`.

### 📂 Fichiers Importants
- **Classe de Véhicule Principal :** [BaseCar](Source\AstroRev\Public\Pawns\BaseCar.h)
- **Classe de PowerUp Principale :** [BasePowerUp](Source\AstroRev\Public\PowerUp\BasePowerUp.h)
- **Système de Boosts :** [BoosterPowerUp](Source\AstroRev\Public\PowerUp\BoosterPowerUp.h)
- **Simulation de Gravité Réduite :** [ZeroGravityPowerUp](Source\AstroRev\Public\PowerUp\ZeroGravityPowerUp.h)
- **Système de Moteur :** [HovercraftMovementComponents](Source\AstroRev\Public\Components)

## 🚀 Ajouter du Contenu
AstroRev est conçu pour une extension facile :
- **Ajouter des Niveaux :** Étends la liste des niveaux et configure les zones de gravité, obstacles et PowerUp pour chaque circuit.
- **Créer de Nouveaux Véhicules :** Hérite de `BaseCar`, définis des comportements uniques pour ton hovercraft et intègre-les dans le jeu.
- **Utiliser le Système de PowerUp :** Ajoute de nouveaux types de PowerUp ou objets en héritant de `BasePowerUp`.

## 👥 Contributeurs
- [@Zhailendra](https://github.com/Zhailendra)
- [@BySkullZ](https://github.com/BySkullZ)
- [@46Yuu](https://github.com/46Yuu)
