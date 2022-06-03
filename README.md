
# Programmes de test des composants

# Guide pratique

## Utilisation sur le Raspberry Pi

### Branchements

**Équipement nécessaire :**
- Raspberry Pi
- Câble d'alimentation du Raspberry Pi
- Clavier
- Souris
- Écran
- Câble d'alimentation de l'écran
- Câble HDMI

Aucune connexion internet n'est nécessaire

### Lancement des programmes

- Une fois branché, le Raspberry Pi s'allume, si ce n'est pas le cas, vérifier que l'écran est allumé ou refaire le branchement<br/>
- Une fois le bureau affiché, ouvrir un terminal avec **Ctrl + Alt + T** ou en cliquant sur l'icone du terminal en haut de l'écran<br/>
- Une fois le terminal ouvert, exécuter la commande suivante : **cd Documents/Drive**<br/>
- Selon le programme désiré, exécuter la commande **cd ComponentTester** ou **cd ManualTester**<br/>
*ComponentTester permet de tester directement les composants du simulateur*<br/>
*ManualTester permet de tester un périphérique USB choisi*<br/>
- Une fois dans le répertoire du programme, exécuter la commande **make**<br/>
*Cette étape n'est nécessaire qu'en l'absence du fichier d'extension **.run** ou après la modification du programme*<br/>

**ComponentTester**
Exécuter la commande **sudo ./ComponentTester.run -v**<br/>
***-v** n'est pas obligatoire et permet d'afficher des informations supplémentaires dans la console*<br/>

**ManualTester**
Exécuter la commande **sudo ./ManualTester.run idVendor idProduct nbInput**<br/>
*Remplacer **idVendor** et **idProduct** par les valeurs correspondantes*<br/>
*idVendor et idProduct peuvent être trouvées sous la forme xxxx:xxxx avec la commande **lsusb***<br/>
*Il faut omettre chaque 0 superflu (exemple: 04D8 -> 4D8, 0050 -> 50)*<br/>
*Remplacer **nbInput** par le nombre de codes à recevoir avant la fermeture du programme*<br/>

### Utilisation des programmes

L'utilisation de ces deux programmes est détaillée dans le guide technique<br/>

### Fermeture des programmes

**ComponentTester**<br/>
Lorsque la fenêtre est ouverte et sélectionnée, la touche **Echap** ferme le programme<br/>
*La fenêtre peut également être fermée avec la croix*<br/>

**ManualTester**<br/>
Le programme se ferme après que **nbInput** codes ont été reçus<br/>
*Le programme peut être fermé de force avec **Ctrl + C** dans le terminal*<br/>

Fermer le terminal avec **Ctrl + D** ou en exécutant la commande **exit**<br/>
Eteindre le Raspberry Pi avec la barre des tâches en haut de l'écran<br/>
Débrancher le Raspberry Pi<br/>

#### Déplacement dans le terminal

Pour se déplacer dans le terminal, utiliser les commandes suivantes :<br/>
- **cd ~ :** Se déplace dans le dossier utilisateur (dossier par défaut à l'ouverture du terminal)<br/>
- **cd / :** Se déplace à la racine de l'ordinateur<br/>
- **cd .. :** Se déplace d'un dossier en arrière<br/>

La touche tab permet de compléter le nom du dossier / fichier et gagner du temps<br/>
Si plusieurs dossiers / fichiers commence par les mêmes lettres, appuyer une seconde fois sur tab pour les afficher<br/>
Il est possible de se déplacer de plusieurs dossiers à la fois (ex: **cd Documents/ComponentTester**)<br/>

**ls :** Affiche les dossiers / fichiers dans le répertoire actuel<br/>
**Ctrl + L :** Efface le terminal<br/>

## Utilisation sur Windows

Il est possible de contrôler le Raspberry Pi à distance depuis un environnement Windows, cela permet d'éviter de nombreux branchements.<br/>
Pour ce faire, il faut :<br/>
- Brancher l'alimentation du Raspberry Pi<br/>
- Allumer un ordinateur Windows<br/>
- S'assurer si nécessaire que les deux appareils sont connectés au même réseau Wi-Fi (configurer préalablement une connexion automatique du Raspberry Pi pour éviter les branchements)<br/>
- S'assurer si nécessaire que le SSH est activé sur le Raspberrry Pi<br/>
- Installer le logiciel PuTTY (https://putty.org/)<br/>
- Une fois le logiciel lancé, entrer l'adresse ip du Raspberry Pi dans la case "Host Name (or IP address)" (l'adresse peut être trouvée avec la commande **ifconfig** sur le Raspberry Pi)<br/>
- Cliquer sur "Save" et choisir un nom (ex: Raspberry Pi)<br/>
- De cette manière, au prochain lancement du logiciel, il suffit de cliquer sur "Raspberry Pi" et "Load"<br/>
- Cliquer sur "Open"<br/>
- Entrer l'identifiant "pi"<br/>
- Entrer le mot de passe "raspberry" (les informations de connexion peuvent être configurées avec la commande **sudo raspi-config** sur le Raspberry Pi)<br/>

Le Raspberry Pi est maintenant accessible depuis un environnement Windows<br/>

# Guide technique

## ComponentTester

Répertoire du projet : ~/Documents/ComponentTester<br/>

### Construire le programme

make<br/>
make clean : supprime les fichiers générés<br/>

### Exécuter le programme

sudo ./ComponentTester.run -v<br/>

**sudo :** libusb requiert les droits d'administrateur<br/>
**-v   :** affiche les informations de débogage<br/>

### Utiliser le programme

**Num0, Num1, ..., Num4 :** sélectionne le composant<br/>
**E :** bascule entre le mode test et le mode édition (utile uniquement pour le MCDU)<br/>

**Mode test :**

**Clic gauche :** Clique sur le bouton pointé, le programme réagit<br/>
**Clic sur une touche du composant sélectionné (physique) :** le programme affiche le code reçu<br/>

**Mode édition :**

**A :** Crée un bouton<br/>
**R :** Supprime le bouton sélectionné<br/>
**Clic gauche :** Sélectionne le bouton pointé<br/>
**Maintien clic gauche + déplacement souris :** Déplace le bouton pointé<br/>
**X :** Augmente la taille horizontale du bouton sélectionné<br/>
**C :** Réduit la taille horizontale du bouton sélectionné<br/>
**Y :** Augmente la taille verticale du bouton sélectionné<br/>
**U :** Réduit la taille verticale du bouton sélectionné<br/>
**V :** Active le changement de valeur du bouton sélectionné<br/>
**Touches alphanumériques :** Si le changement de valeur est activé, détermine sa nouvelle valeur<br/>
**Entrée :** Si le changement de valeur est activé, applique sa nouvelle valeur<br/>

### Ajouter un composant

**Fichier src/ComponentTester.cpp, Ligne 71-75 :** Ajouter une ligne avec les bonnes informations pour prendre en charge un autre composant<br/>
L'ordre des lignes correspond à l'ordre de sélection avec les touches **Num1, Num2, ...**<br/>
Une image **.png 640x480** avec le même nom que celui fourni dans la nouvelle ligne doit être ajoutée dans le dossier **res/textures**<br/>
Reconstruire le projet<br/>
*Si les touches Num4 et Num6 ne fonctionnent pas, modifier les ligne 20 et 22 du fichier **src/ComponentTester.cpp** en remplacant "Quote" et "Hyphen" par "Num4" et "Num6"*<br/>

## ManualTester

Répertoire du projet : ~/Documents/ManualTester<br/>

### Construire le programme

make<br/>
make clean : supprime les fichiers générés<br/>

### Exécuter le programme

sudo ./ManualTester.run [idVendor] [idProduct] [nbInput]<br/>

**sudo :** libusb requiert les droits d'administrateur<br/>
**idVendor :** Id vendor du périphérique<br/><br/>
**idproduct :** Id product du périphérique<br/>
**nbInput :** Nombre de codes à recevoir avant la fermeture du programme<br/>
*idVendor et idProduct peuvent être trouvées sous la forme xxxx:xxxx avec la commande **lsusb***<br/>
*Il faut omettre chaque 0 superflu (exemple: 04D8 -> 4D8, 0050 -> 50)*<br/>

### Utiliser le programme

**Appui sur une touche du périphérique :** Affiche le code associé à la touche<br/>

# Guide d'insallation

Pour configurer les programmes sur un nouvel ordinateur, voici les étapes importantes :<br/>
Le système doit être basé sur Linux et être à jour (**sudo apt update; sudo apt upgrade**)<br/>
*Certaines commandes demandent une confirmation à l'utilisateur sous la forme [O/n] ou [Y/n] selon la langue du système, si tel est le cas, toujours entrer O (ou Y) et appuyer sur la touche Entrée*<br/>
*Lorsque le guide indique d'exécuter une commande, celle-ci doit êtr exécutée depuis un terminal pouvant être ouvert avec **Ctrl + Alt + T** et fermé avec **Ctrl + D***<br/>

**Création d'un lien symbolique vers libusb**

Libusb est installée par défaut, elle est situé dans le dossier "/lib/arm-linux-gnueabihf" et le fichier se nomme "libusb-1.0.so.0.3.0"<br/>
*Sur un ordinateur, il est possible que le dossier ait le nom "x86_64-gnu-linux", dans ce cas, remplacer le nom du dossier pour chaque commande*<br/>
Un lien symbolique du nom de "libusb-1.0.so.0" est également présent à cet emplacement<br/>
Pour pouvoir utiliser libusb dans la construction des programmes, il est nécessaire de créer un lien symbolique dont le nom termine par ".so"<br/>
Dans le dossier "/lib/arm-linux-gnueabihf", exécuter la commande **sudo ln -s /lib/arm-linux-gnueabihf/libusb-1.0.so.0 /lib/arm-linux-gnueabihf/libusb-1.0.so**<br/>
Vérifier l'existence du fichier "libusb-1.0.so" aux côtés des deux autres fichiers<br/>

**Installation de la SFML**

Exécuter la commande **sudo apt install libsfml-dev**<br/>

**Récupération des programmes**

Si les programmes sont sur une clé USB, copier les programmes dans le dossier **~/Documents** (ou autre) via l'explorateur de fichiers<br/>
Si les programmes ne sont pas sur une clé USB, ils sont disponibles sur github à l'adresse "https://github.com/CalixteManaud/"<br/>
Cliquer sur "Branches" permet d'accéder à la branche "main" contenant les programmes python et à la branche "Yvan" permettant d'accéder aux programmes C++<br/>
Il est recommandé de télécharger l'intégralité du dépot à sa racine en cliquant sur le bouton vert "Code" et "Download Zip"<br/>
Une fois le dossier téléchérgé, il faut l'extraire avec clic droit , extraire.<br/>
Pour lancer les programmes, se référer au guide d'utilisation des programmes<br/>
