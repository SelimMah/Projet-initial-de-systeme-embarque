# 📖 README - Projet Robotique

## 🎥 Vidéos du Projet
<div style="display: flex; gap: 20px;">
  <div>
    <h4>Vidéo 1 : IMG_1659.mov</h4>
    <video controls width="50%">
      <source src="ReadMeCaptures/IMG_1659.mov" type="video/mp4">
      Votre navigateur ne supporte pas l'élément vidéo.
    </video>
  </div>

  <div>
    <h4>Vidéo 2 : IMG_1664.mov</h4>
    <video controls width="50%">
      <source src="ReadMeCaptures/IMG_1664.mov" type="video/mp4">
      Votre navigateur ne supporte pas l'élément vidéo.
    </video>
  </div>
</div>

---

## 🤖 Présentation du projet
Ce projet consiste à implémenter deux robots (R1 et R2) capables de réaliser des tâches spécifiques en utilisant des capteurs, moteurs et microcontrôleurs programmés en C++. 

- **R1** : Exploration et détection d'obstacles.
- **R2** : Suivi de ligne et transmission des données collectées.

Les spécifications complètes des robots et de leurs états sont détaillées ci-dessous.

---

## 📂 Structure du projet

### Fichiers principaux

- `R1.cpp` : Code source pour le robot R1.
- `R2.cpp` : Code source pour le robot R2.
- `LISEZMOI.txt` : Documentation technique sur le fonctionnement et les branchements des robots.
- `Librairie/` : Répertoire réservé pour les bibliothèques externes nécessaires. *(Voir ci-dessous)*

---

## 📜 Description des robots

### 🟦 Robot R1

**Fonctionnalité principale** : 
- Utilisation d'un capteur de distance pour explorer un environnement.
- Analyse des données collectées et dessin des trajectoires.

**États :**  
1. **FIND_DISTANCE** : Localisation du point central rouge.  
2. **SWEEPING** : Balayage pour détecter l'ouverture.  
3. **WAITING** : Signal infrarouge en attente.  
4. **RECEPTIONIR** : Réception des données de R2.  
5. **RS_232** : Transmission des données au PC.

**Branchements :** 
- Capteur de distance connecté au PORT A.  
- Moteurs reliés au PORT B.  
- LED et récepteur infrarouge connectés au PORT D.  

---

### 🟩 Robot R2

**Fonctionnalité principale** :  
- Suivi d'une ligne noire pour détecter et mesurer des segments.  
- Transmission des données via infrarouge ou RS-232.

**États :**  
1. **Parcour** : Suivi de la ligne et mesure des segments.  
2. **Waiting** : Mode attente avec LED rouge.  
3. **SendIR** : Transmission des données à R1 via infrarouge.  
4. **SendRS232** : Transmission des données au PC via RS-232.

**Branchements :**  
- Bouton connecté au PORTC PIN 3.  
- LED infrarouge sur PORTD PIN 6.  
- Capteurs de ligne sur PORTA PIN 3 à 7.  
- Moteurs connectés au PORT B.

---

## 🛠️ Bibliothèque du Projet

### 📁 Fichiers et Description

#### 🔘 `Button.h`
Classe dédiée à la gestion des boutons du robot, avec des fonctionnalités pour :
- Configurer des interruptions basées sur différents types de déclenchements (montée, descente, etc.).
- Détecter si un bouton est pressé ou relâché.
- Gérer les rebonds pour assurer une lecture précise des états du bouton.

#### 🎛️ `can.h`
Interface permettant d'utiliser le convertisseur analogique-numérique (ADC) intégré au microcontrôleur pour :
- Convertir les signaux analogiques en données numériques précises.
- Gérer jusqu'à 8 canaux d'entrée pour collecter des données simultanément.

#### 🐞 `Debug.h`
Fichier essentiel pour le débogage en temps réel. Fournit des outils comme :
- Initialisation des périphériques UART pour afficher des messages sur un terminal.
- Envoi de valeurs et de messages à des fins de diagnostic.
- Macros flexibles pour activer ou désactiver les messages de débogage.

#### 📡 `DistanceSensor.h`
Module central pour le traitement des données issues des capteurs de distance. Ses fonctionnalités incluent :
- Détection précise des objets dans l'environnement immédiat.
- Gestion des états comme la recherche de distance ou le balayage.
- Communication avec d'autres modules pour coordonner les actions.

#### 🖋️ `Draw.h`
Outil graphique pour représenter visuellement les trajets ou objets sur un écran connecté. Capacités :
- Dessiner des formes comme des rectangles, des lignes verticales/horizontales.
- Afficher des robots et des trajets sous forme de caractères.
- Gérer les coordonnées et les bordures internes/externes.

#### 🚗 `Driver.h`
Pilote des moteurs du robot avec :
- Routines pour avancer, reculer, tourner ou effectuer des manœuvres complexes.
- Gestion des corrections pour maintenir une trajectoire précise.
- Commandes pour des mouvements fluides et contrôlés.

#### 📥 `IR_Recption.h`
Module pour la réception infrarouge :
- Décodage des signaux IR pour extraire les données transmises.
- Vérification d'intégrité des données reçues à l'aide de CRC.
- Gestion des données pour les transmettre à d'autres modules.

#### 📤 `IR_Transmission.h`
Responsable de l'envoi de données par infrarouge, ce fichier propose :
- Génération de séquences IR spécifiques avec codage et synchronisation.
- Gestion des fréquences pour une communication stable.

#### 💡 `LED.h`
Classe permettant de contrôler les LEDs du robot. Principales fonctions :
- Allumer des LEDs en rouge, vert ou ambre selon l'état du robot.
- Définir des délais personnalisés pour les clignotements.

#### 🛤️ `LineFollower.h`
Module pour le suivi de ligne, avec des fonctionnalités avancées comme :
- Suivi précis des lignes noires grâce à plusieurs capteurs.
- Gestion des bifurcations et des segments ajoutés.
- Ajustements automatiques pour rester sur la trajectoire.

#### 🧠 `memoire_24.h`
Gestion de la mémoire EEPROM I2C avec des fonctionnalités pour :
- Lire et écrire des données sur des mémoires EEPROM (24C128, 24C256, etc.).
- Assurer une communication stable sur le bus I2C.
- Gérer les blocs de mémoire pour des écritures ou lectures groupées.

#### 🔄 `Motor.h`
Classe pour contrôler les moteurs :
- Avancer ou reculer avec un contrôle précis de la vitesse.
- Fonction d'arrêt rapide pour des manœuvres sûres.

#### 🧰 `Progmem.h`
Gestion des instructions en mémoire flash :
- Lecture d'instructions stockées.
- Implémentation de routines pour contrôler les LEDs, moteurs, ou exécuter des boucles programmées.

#### 🎚️ `PWM.h`
Interface pour la modulation de largeur d'impulsion (PWM) :
- Configuration et contrôle de la puissance délivrée aux moteurs.
- Ajustement dynamique des paramètres PWM pour s'adapter aux besoins du robot.

#### 🤖 `Robot.h`
Classe regroupant les principales fonctionnalités du robot :
- Gestion centralisée des composants comme les LEDs, moteurs et capteurs.
- Simplification de l'interaction entre les différents modules matériels.

#### 🎵 `Sing.h`
Module pour produire des tonalités ou musiques :
- Génération de fréquences précises pour créer des sons.
- Prise en charge de différentes notes musicales.

#### ⏱️ `Timer.h`
Classe de gestion des minuteries matérielles :
- Configuration et démarrage de temporisateurs pour des routines spécifiques.
- Supporte plusieurs temporisateurs matériels avec différentes fréquences d'horloge.

#### 📨 `UART.h`
Module de communication série :
- Envoi et réception de données via UART.
- Initialisation et gestion des paramètres pour une communication fluide.

---

## ⚙️ Instructions pour l'utilisation

1. **Compilation** : Utilisez un compilateur compatible AVR pour compiler les fichiers source.
2. **Chargement** : Flashez le microcontrôleur avec les fichiers binaires générés.
3. **Configuration des branchements** : Vérifiez les branchements selon les schémas détaillés dans `LISEZMOI.txt`.
4. **Exécution** : Lancez les robots en suivant les instructions fournies dans la documentation technique.

---

## 👥 Équipe de développement

- Selim Mahjoub - 2193614  
- Mohamed Afandi - 2291005  
- Bryan Alexandre Tavares - 2291297  
- Brice Tangmouo Manfo - 2275762  

