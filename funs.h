// Vérifie si FUNS_H est déjà défini pour éviter les inclusions multiples
#ifndef FUNS_H
// Définit FUNS_H si non défini
#define FUNS_H

// Définitions des constantes pour le jeu

// Nombre de couleurs dans le jeu
#define NUM_COULEURS 4
// Nombre de valeurs par couleur
#define NUM_VALEURS 13
// Nombre total de cartes
#define NUM_CARTES (NUM_COULEURS * NUM_VALEURS)
// Nombre de joueurs
#define NUM_JOUEURS 3
// Nombre de cartes dans la main initiale de chaque joueur
#define TAILLE_MAIN_INITIALE 7 

// Structure représentant une carte avec une couleur et une valeur
typedef struct {
    char *couleur;
    char *valeur;
} Carte;

// Structure représentant un joueur avec sa main de cartes et la taille de sa main
typedef struct {
    Carte *main;
    int tailleMain;
} Joueur;

// Fonctions pour le jeu
void melangerDeck(Carte *deck); // Mélange le deck de cartes
// Initialise le deck de cartes
void initialiserDeck(Carte *deck);
// Distribue les cartes aux joueurs
void distribuerCartes(Carte *deck, Joueur *joueurs, int *indexDeck);
// Affiche la main d'un joueur
void afficherMain(Joueur joueur);
// Vérifie si une carte peut être jouée
int peutJouerCarte(Carte carte, Carte carteActuelle);
// Joue un tour de jeu
int jouerTour(Joueur *joueur, Carte *carteActuelle, Carte *deck, int *indexDeck, int *direction, int *sauterProchainJoueur, int *penalitePioche);
// Boucle principale du jeu
void boucleDeJeu(Carte *deck, Joueur *joueurs, int *indexDeck, Carte *carteActuelle, int *joueurActuel, int *direction, int *sauterProchainJoueur, int *penalitePioche);

#endif