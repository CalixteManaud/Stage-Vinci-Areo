
# ComponentTester

## Guide pratique

### Branchements

**Équipement nécessaire :**
- Raspberry Pi
- Câble d'alimentation du Raspberry Pi
- Clavier
- Souris
- Écran
- Câble d'alimentation de l'écran
- Câble HDMI

### Lancement des programmes

Une fois branché, le Raspberry Pi s'allume, si ce n'est pas le cas, vérifier que l'écran est allumé ou refaire le branchement
Une fois le bureau affiché, ouvrir un terminal avec **Ctrl + Alt + T** ou en cliquant sur l'icone du terminal en haut de l'écran
Une fois le terminal ouvert, exécuter la commande suivante : **cd Documents/Drive**
Selon le programme désiré, exécuter la commande **cd ComponentTester** ou **cd ManualTester**
*ComponentTester permet de tester directement les composants du simulateur*
*ManualTester permet de tester un périphérique USB choisi*
Une fois dans le répertoire du programme, exécuter la commande **make**
*Cette étape n'est nécessaire qu'en l'absence du fichier d'extension **.run** ou après la modification du programme*

**ComponentTester**
Exécuter la commande **sudo ./ComponentTester.run -v**
***-v** n'est pas obligatoire et permet d'afficher des informations supplémentaires dans la console*

**ManualTester**
Exécuter la commande **sudo ./ManualTester.run idVendor idProduct nbInput**
*Remplacer **idVendor** et **idProduct** par les valeurs correspondantes*
*idVendor et idProduct peuvent être trouvées sous la forme xxxx:xxxx avec la commande **lsusb***
*Il faut omettre chaque 0 superflu (exemple: 04D8 -> 4D8, 0050 -> 50)*
*Remplacer **nbInput** par le nombre de codes à recevoir avant la fermeture du programme*

### Utilisation des programmes

L'utilisation de ces deux programmes est détaillée dans le guide technique

### Fermeture des programmes

**ComponentTester**
Lorsque la fenêtre est ouverte et sélectionnée, la touche **Echap** ferme le programme
*La fenêtre peut également être fermée avec la croix*

**ManualTester**
Le programme se ferme après que **nbInput** codes ont été reçus
*Le programme peut être fermé de force avec **Ctrl + C** dans le terminal*

Fermer le terminal avec **Ctrl + D** ou en exécutant la commande **exit**
Eteindre le Raspberry Pi avec la barre des tâches en haut de l'écran
Débrancher le Raspberry Pi

## Guide technique

### Répertoire du projet : ~/Documents/ComponentTester

### Construire le programme

make
make clean : supprime les fichiers générés

### Exécuter le programme

sudo ./ComponentTester.run -v

**sudo :** libusb requiert les droits d'administrateur
**-v   :** affiche les informations de débogage

### Utiliser le programme

**Num0, Num1, ..., Num4 :** sélectionne le composant
**E :** bascule entre le mode test et le mode édition (utile uniquement pour le MCDU)

**Mode test :**

**Clic gauche :** Clique sur le bouton pointé, le programme réagit
**Clic sur une touche du composant sélectionné (physique) :** le programme affiche le code reçu

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
Reconstruire le projet

# ManualTester

### Répertoire du projet : ~/Documents/ManualTester

### Construire le programme

make
make clean : supprime les fichiers générés

### Exécuter le programme

sudo ./ManualTester.run [idVendor] [idProduct] [nbInput]

**sudo :** libusb requiert les droits d'administrateur<br/>
**idVendor :** Id vendor du périphérique<br/><br/>
**idproduct :** Id product du périphérique<br/>
**nbInput :** Nombre de codes à recevoir avant la fermeture du programme<br/>
*idVendor et idProduct peuvent être trouvées sous la forme xxxx:xxxx avec la commande **lsusb***<br/>
*Il faut omettre chaque 0 superflu (exemple: 04D8 -> 4D8, 0050 -> 50)*<br/>

### Utiliser le programme

**Appui sur une touche du périphérique :** Affiche le code associé à la touche
