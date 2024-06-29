# 8americain
Sujet projet:
Ecrire en groupe de 3 un programme implémentant un jeu (directement en commande line), de quelques centaines de lignes (pas plus de 1000). Vous devrez utiliser la plupart des concepts vu pendant le cours: pointeurs, structures, tableaux, allocation dynamique, fonctions, Makefile ou CMake (liste non exhaustive). Vérifier qu'il n'y a pas de fuite mémoire avec Valgrind, et ajouter une (ou des) ligne de compilation pour compiler avec les flags de debug. Utilisez plusieurs fichiers et faites des fonctions courtes (~20 lignes), pensez à être expressifs dans le nommage de vos fonctions et de vos variables. Lors de la dernière séance nous travaillerons par groupe de projet afin de terminer le projet et résoudre les derniers problèmes. Le rendu pourra se faire avec un lien vers un repo git (github/gitlab) ou une archive .zip ou .tar.gz.

!!!!!!!!!!!!!!!! Avant de lancer le make, il faut run la commande ci-dessous !!!!!!!!!!!!!!!!
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH

Jeu choisi : 
Le 8 américain se joue avec un jeu de 52 cartes. Le but étant comme au Uno de se débarrasser de toutes ses cartes. De nombreuses variantes et règles différentes existent. Voici la règle que nous pratiquons.

Règles :
Les joueurs jouent chacun leur tour dans le sens horaire (ou antihoraire si une carte spéciale l'indique).
À votre tour, vous devez jouer une carte de votre main qui correspond soit à la couleur (cœur, carreau, trèfle, pique) soit à la valeur (2, 3, 4, etc.) de la carte sur le talon.
Après avoir piocher, il n'est pas possible de rejouer, c'est le tour de la personne suivante.
Le premier joueur à se débarrasser de toutes ses cartes remporte la partie.

Cartes spéciales :
- Le 7 permet de passer le tour du joueur suivant.
- Le 8 permet de changer la couleur.
- Le 10 permet de rejouer.
- Le Valet change le sens.
- L'As fait piocher 2 cartes au joueur suivant.
