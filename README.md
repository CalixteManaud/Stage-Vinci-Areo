# ComponentTester

### Répertoire du projet : ~/Documents/ComponentTester

### Construire le programme

make
make clean : supprimer les fichiers générés

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
**A :** Crée un bouton
**R :** Supprime le bouton sélectionné
**Clic gauche :** Sélectionne le bouton pointé
**Maintien clic gauche + déplacement souris :** Déplace le bouton pointé
**X :** Augmente la taille horizontale du bouton sélectionné
**C :** Réduit la taille horizontale du bouton sélectionné
**Y :** Augmente la taille verticale du bouton sélectionné
**U :** Réduit la taille verticale du bouton sélectionné
**V :** Active le changement de valeur du bouton sélectionné
**Touches alphanumériques :** Si le changement de valeur est activé, détermine sa nouvelle valeur
**Entrée :** Si le changement de valeur est activé, applique sa nouvelle valeur

### Ajouter un composant

**Fichier src/ComponentTester.cpp, Ligne 71-75 :** Ajouter une ligne avec les bonnes informations pour prendre en charge un autre composant
L'ordre des lignes correspond à l'ordre de sélection avec les touches **Num1, Num2, ...**
Une image **.png 640x480** avec le même nom que celui fourni dans la nouvelle ligne doit être ajoutée dans le dossier **res/textures**
Reconstruire le projet
