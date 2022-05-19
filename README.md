# ComponentTester<br/>

### Répertoire du projet : ~/Documents/ComponentTester<br/>

### Construire le programme<br/>

make<br/>
make clean : supprimer les fichiers générés<br/>

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
