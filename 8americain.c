// Inclusion de la bibliothèque standard d'entrée et de sortie
#include <stdio.h>
// Inclusion de la bibliothèque standard pour l'allocation dynamique de mémoire    
#include <stdlib.h>
// Inclusion de la bibliothèque pour gérer le temps   
#include <time.h>
// Inclusion du fichier d'en-tête contenant les déclarations de fonctions spécifiques
#include "funs.h"

int main() {
    // Initialiser le générateur de nombres aléatoires avec l'heure actuelle
    srand(time(0));

    // Déclaration d'un tableau de cartes représentant le deck
    Carte deck[NUM_CARTES];

    // Initialiser le deck avec les cartes
    initialiserDeck(deck);

    // Mélanger le deck pour randomiser l'ordre des cartes
    melangerDeck(deck);

    // Déclaration d'un tableau de joueurs
    Joueur joueurs[NUM_JOUEURS] = {0};

    // Allouer de la mémoire pour la main de chaque joueur
    for (int i = 0; i < NUM_JOUEURS; i++) {
        joueurs[i].main = malloc(NUM_CARTES * sizeof(Carte));
        // Vérifier si l'allocation de mémoire a échoué
        if (joueurs[i].main == NULL) {
            // Afficher un message d'erreur et retourner une valeur indiquant l'échec du programme
            printf("Erreur d'allocation de mémoire.\n");
            return 1;
        }
    }

    // Initialiser l'index du deck à 0
    int indexDeck = 0;
    // Distribuer les cartes aux joueurs
    distribuerCartes(deck, joueurs, &indexDeck);

    // Afficher les mains de chaque joueur
    for (int i = 0; i < NUM_JOUEURS; i++) {
        printf("Joueur %d:\n", i + 1);
        afficherMain(joueurs[i]);
        printf("\n");
    }

    // Sélectionner la carte initiale pour commencer le jeu
    Carte carteActuelle = deck[indexDeck++];
    // Afficher la carte de départ
    printf("Carte de départ: %s de %s\n", carteActuelle.valeur, carteActuelle.couleur);

    // Initialiser les variables de jeu
    int joueurActuel = 0;
    int direction = 1; // 1 pour le sens horaire, -1 pour le sens antihoraire
    int sauterProchainJoueur = 0;
    int penalitePioche = 0;

    // Boucle principale du jeu
    boucleDeJeu(deck, joueurs, &indexDeck, &carteActuelle, &joueurActuel, &direction, &sauterProchainJoueur, &penalitePioche);

    // Libérer la mémoire allouée pour la main de chaque joueur
    for (int i = 0; i < NUM_JOUEURS; i++) {
        free(joueurs[i].main);
    }

    // Retourner 0 pour indiquer que le programme s'est terminé avec succès
    return 0;
}