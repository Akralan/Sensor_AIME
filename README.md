# Solution IoT pour un capteur de gaz connecté

## 1. Introduction
**Contexte et Motivation :**  
Ce projet propose une solution IoT complète autour d’un capteur de gaz, intégrant la conception électronique (PCB, amplification, filtrage), le développement logiciel (firmware embarqué sur ESP32, interface Node-RED) et une application mobile (AppInventor).

**Description Générale :**  
Le système permet de mesurer la concentration de gaz via un capteur dédié, de conditionner le signal et de transmettre les données via LoRa ou Bluetooth. L’utilisateur peut ensuite visualiser les mesures en temps réel et interagir avec le dispositif depuis une interface Node-RED ou une application mobile.

---

## 2. Table des Matières
- [1. Introduction](#1-introduction)
- [2. Table des Matières](#2-table-des-matières)
- [3. Aperçu du Projet](#3-apercu-du-projet)
- [4. Matériel (Hardware)](#4-matériel-hardware)
- [5. Logiciel (Software)](#5-logiciel-software)
- [6. Installation et Mise en Service](#6-installation-et-mise-en-service)
- [7. Utilisation](#7-utilisation)
- [8. Contacts et Auteurs](#8-contacts-et-auteurs)

---

## 3. Aperçu du Projet

**Résumé Fonctionnel :**  
1. Mesure de gaz via un capteur spécifique et circuits d’acquisition (amplification, filtrage).  
2. Traitement et envoi des données par un microcontrôleur (ESP32).  
3. Visualisation en temps réel sur Node-RED et application mobile (AppInventor).

**Architecture Globale :**  
- **Capteur de Gaz** : Convertit la concentration de gaz en signal électrique.
- **Chaîne d’Acquisition** : Simulations LTSpice et conception PCB (fichiers dans `Chaine acquisition` et `PCB`).  
- **Microcontrôleur (ESP32)** : Gère la communication (LoRa/BLE) et le traitement des mesures avant l'enregistrement dans la base de données (code dans `Code/AIME`).  
- **Interface Node-RED** : Flows pour l’affichage des donneés dans une interface web simpliste (dossier `NodeRed`).  
- **Application Mobile** : Réalisée sous AppInventor (dossier `AppInventor` à la racine).


---

## 4. Matériel (Hardware)

**Liste des Composants :**
- **Capteur de gaz** (spécifique au projet ou type MQ)  
- **ESP32** (ou carte équivalente)  
- **Modules de communication** (LoRa, Bluetooth, etc.)  
- **Composants d’amplification et filtrage** (ex. LTC1050, résistances, condensateurs)  
- **PCB** (dossier `PCB`)  
  - Fichiers KiCad (ex. `GazSensor.kicad_pro`)  
  - Dossier `pcb_aime` pour les fichiers de fabrication

**Design et Schémas :**  
- Fichiers KiCad dans le dossier `PCB`.  
- Simulations LTSpice dans `Chaine acquisition`.

**Procédure d’Assemblage :**  
- Ouvrir le projet KiCad pour consulter le routage et générer les fichiers Gerber.  
- Souder les composants en suivant le BOM (Bill Of Materials) et le placement défini par le PCB.

---

## 5. Logiciel (Software)

**Composants Logiciels :**
- **Firmware Embarqué** : Dossier `Code/AIME` (PlatformIO)  
- **Interface Node-RED** : Fichier `flows.json` dans le dossier `NodeRed`  
- **Application Mobile** : Dossier `AppInventor` (fichiers sources AppInventor)

**Organisation du Code :**
- `Code/AIME/`
  - **platformio.ini** : Fichier de configuration PlatformIO  
  - **src/** : Code source principal (ex. `main.cpp`, `gaz_sensor.cpp`)  
  - **include/** : Fichiers d’en-tête (ex. `gaz_sensor.h`)  
  - **lib/** : Bibliothèques locales (si nécessaires)  
  - **test/** : Éventuels tests unitaires  
  - **.vscode/** : Paramètres spécifiques VS Code pour PlatformIO

---

## 6. Installation et Mise en Service

### Prérequis
- **Visual Studio Code (VS Code)**
- **PlatformIO IDE** : Extension à installer dans VS Code
- **C/C++ Extension** (recommandée)
- **Bibliothèques** : Spécifiées dans la section `[lib_deps]` du fichier `platformio.ini`

### Guide Pas-à-Pas
1. **Cloner le Dépôt**  
    (Depuis un terminal)
    
    ```
    git clone https://github.com/<user>/Sensor_AIME.git
    ```

2. **Ouvrir le Projet avec VS Code**  
    - Lancer VS Code  
    - Sélectionner *Open Folder* et choisir `Sensor_AIME/Code/AIME`

3. **Installer PlatformIO**  
    - Dans VS Code, aller dans l’onglet *Extensions*  
    - Rechercher “PlatformIO IDE” et cliquer sur *Install*

4. **Compiler le Firmware**  
    - Ouvrir la palette de commandes (Ctrl+Shift+P)  
    - Taper `PlatformIO: Build`  
    - Vérifier que la compilation se déroule sans erreur

5. **Téléverser le Firmware**  
    - Connecter la carte ESP32 au PC via USB  
    - Dans la palette de commandes, sélectionner `PlatformIO: Upload`  
    - Vérifier que le port série est correctement configuré dans `platformio.ini`

6. **Configurer Node-RED**  
    - Installer Node-RED si besoin (ex. `npm install -g node-red`)  
    - Lancer Node-RED via la commande `node-red`  
    - Importer le flow depuis `NodeRed/flows.json`

7. **Installer l’Application Mobile (AppInventor)**  
    - Le dossier `AppInventor` se trouve à la racine du dépôt  
    - Ouvrir le projet AppInventor sur [ai2.appinventor.mit.edu](https://ai2.appinventor.mit.edu/)  
    - Compiler le projet et installer l’APK sur un smartphone Android
