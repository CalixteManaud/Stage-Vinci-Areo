# ComponentTester<br/>

### Répertoire du projet : ~/Documents/ComponentTester<br/>

### Construire le programme<br/>

make<br/>
make clean : supprime les fichiers générés<br/>

### Exécuter le programme<br/>

sudo ./ComponentTester.run -v<br/>

**sudo :** libusb requiert les droits d'administrateur<br/>
**-v   :** affiche les informations de débogage<br/>

### Utiliser le programme<br/>

**Num0, Num1, ..., Num4 :** sélectionne le composant<br/>
**E :** bascule entre le mode test et le mode édition (utile uniquement pour le MCDU)<br/>

**Mode test :**<br/>
**Clic gauche :** Clique sur le bouton pointé, le programme réagit<br/>
**Clic sur une touche du composant sélectionné (physique) :** le programme affiche le code reçu<br/>

**Mode édition :**<br/>
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

### Ajouter un composant<br/>

**Fichier src/ComponentTester.cpp, Ligne 71-75 :** Ajouter une ligne avec les bonnes informations pour prendre en charge un autre composant<br/>
L'ordre des lignes correspond à l'ordre de sélection avec les touches **Num1, Num2, ...**<br/>
Une image **.png 640x480** avec le même nom que celui fourni dans la nouvelle ligne doit être ajoutée dans le dossier **res/textures**<br/>
Reconstruire le projet<br/>

# ManualTester<br/>

### Répertoire du projet : ~/Documents/ManualTester<br/>

### Construire le programme<br/>

make<br/>
make clean : supprime les fichiers générés<br/>

### Exécuter le programme<br/>

sudo ./ManualTester.run [idVendor] [idProduct] [nbInput]<br/>

**sudo :** libusb requiert les droits d'administrateur<br/>
**idVendor :** Id vendor du périphérique<br/>
**idproduct :** Id product du périphérique<br/>
**nbInput :** Nombre de codes à recevoir avant la fermeture du programme<br/>
*Les id vendor et product peuvent être trouvés sous la forme xxxx:xxxx avec la commande **lsusb***<br/>
*Il faut omettre chaque 0 superflu (exemple: 04D8 -> 4D8, 0050 -> 50)*<br/>

### Utiliser le programme<br/>

**Appui sur une touche du périphérique :** Affiche le code associé à la touche<br/>

