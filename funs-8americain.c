#include "funs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Définition des couleurs (Coeur, Carreau, Trèfle, Pic) et des valeurs du jeu de cartes
const char *couleurs[NUM_COULEURS] = {"♥", "♦", "♣", "♠"};
const char *valeurs[NUM_VALEURS] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Valet", "Dame", "Roi", "As"};

// Fonction pour mélanger un jeu de cartes
// Paramètre : deck - un tableau de cartes à mélanger
void melangerDeck(Carte *deck) {
    // Parcourt chaque carte dans le deck
    for (int i = 0; i < NUM_CARTES; i++) {
        // Sélectionne une carte aléatoire parmi le deck
        int j = rand() % NUM_CARTES;
        // Échange la carte courante avec la carte sélectionnée aléatoirement
        Carte temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

// Fonction pour initialiser un jeu de cartes
// Paramètre : deck - un tableau de cartes à initialiser
void initialiserDeck(Carte *deck) {
    // Parcourt chaque couleur
    for (int i = 0; i < NUM_COULEURS; i++) {
        // Parcourt chaque valeur
        for (int j = 0; j < NUM_VALEURS; j++) {
            // Associe une couleur et une valeur à chaque carte du deck
            deck[i * NUM_VALEURS + j].couleur = (char *)couleurs[i];
            deck[i * NUM_VALEURS + j].valeur = (char *)valeurs[j];
        }
    }
}

// Fonction pour distribuer les cartes aux joueurs
// Paramètres : 
// - deck : un tableau de cartes à distribuer
// - joueurs : un tableau de joueurs qui recevront les cartes
// - indexDeck : un pointeur sur l'index de la prochaine carte à distribuer dans le deck
void distribuerCartes(Carte *deck, Joueur *joueurs, int *indexDeck) {
    // Parcourt chaque joueur
    for (int i = 0; i < NUM_JOUEURS; i++) {
        // Donne à chaque joueur le nombre initial de cartes
        for (int j = 0; j < TAILLE_MAIN_INITIALE; j++) {
            // Associe la prochaine carte du deck à la main du joueur
            joueurs[i].main[j] = deck[(*indexDeck)++];
            // Augmente la taille de la main du joueur
            joueurs[i].tailleMain++;
        }
    }
}

// Fonction pour afficher la main d'un joueur
// Paramètre : joueur - le joueur dont on veut afficher la main
void afficherMain(Joueur joueur) {
    printf("Main du joueur:\n");
    // Parcourt chaque carte dans la main du joueur
    for (int i = 0; i < joueur.tailleMain; i++) {
        // Affiche la position, la valeur et la couleur de la carte
        printf("%d: %s de %s\n", i + 1, joueur.main[i].valeur, joueur.main[i].couleur);
    }
}

// Fonction pour vérifier si une carte peut être jouée
// Paramètres : 
// - carte : la carte que le joueur veut jouer
// - carteActuelle : la carte actuelle sur le dessus du tas
// Retourne : 1 si la carte peut être jouée, 0 sinon
int peutJouerCarte(Carte carte, Carte carteActuelle) {
    // Vérifie si la couleur ou la valeur de la carte correspond à celle de la carte actuelle
    return (strcmp(carte.couleur, carteActuelle.couleur) == 0 || strcmp(carte.valeur, carteActuelle.valeur) == 0);
}

// Fonction pour appliquer les règles spécifiques d'une carte
// Paramètres : 
// - carte : la carte jouée
// - carteActuelle : la carte actuelle sur le dessus du tas (sera mise à jour si nécessaire)
// - direction : pointeur sur la direction actuelle du jeu (sera modifié si nécessaire)
// - sauterProchainJoueur : pointeur sur l'indicateur de saut du prochain joueur (sera modifié si nécessaire)
// - penalitePioche : pointeur sur la pénalité de pioche (sera modifié si nécessaire)
// - rejouer : pointeur sur l'indicateur de rejouer (sera modifié si nécessaire)
void appliquerRegles(Carte *carte, Carte *carteActuelle, int *direction, int *sauterProchainJoueur, int *penalitePioche, int *rejouer) {
    // Si la carte jouée est un As
    if (strcmp(carte->valeur, "As") == 0) {
        *penalitePioche += 2;  // Applique une pénalité de pioche de 2 cartes
    // Si la carte jouée est un 8
    } else if (strcmp(carte->valeur, "8") == 0) {
        char nouvelleCouleur[10];
        int couleurValide = 0;
        // Demande au joueur de choisir une nouvelle couleur
        while (!couleurValide) {
            printf("Choisissez une nouvelle couleur (♥, ♦, ♣, ♠): ");
            scanf("%s", nouvelleCouleur);
            // Vérifie si la couleur entrée est valide
            if (strcmp(nouvelleCouleur, "♥") == 0 || strcmp(nouvelleCouleur, "♦") == 0 || strcmp(nouvelleCouleur, "♣") == 0 || strcmp(nouvelleCouleur, "♠") == 0) {
                couleurValide = 1;
                carteActuelle->couleur = strdup(nouvelleCouleur);  // Met à jour la couleur actuelle
            } else {
                printf("Entrée invalide. Veuillez copier-coller le signe de la couleur souhaitée.\n");
            }
        }
    // Si la carte jouée est un Valet
    } else if (strcmp(carte->valeur, "Valet") == 0) {
        *direction *= -1;  // Change la direction du jeu
    // Si la carte jouée est un 7
    } else if (strcmp(carte->valeur, "7") == 0) {
        *sauterProchainJoueur = 1;  // Saute le prochain joueur
    // Si la carte jouée est un 10
    } else if (strcmp(carte->valeur, "10") == 0) {
        *rejouer = 1;  // Permet au joueur de rejouer
    }
}

// Fonction pour jouer un tour
// Paramètres : 
// - joueur : le joueur qui joue ce tour
// - carteActuelle : la carte actuelle sur le dessus du tas
// - deck : le deck de cartes
// - indexDeck : pointeur sur l'index de la prochaine carte à tirer dans le deck
// - direction : pointeur sur la direction actuelle du jeu
// - sauterProchainJoueur : pointeur sur l'indicateur de saut du prochain joueur
// - penalitePioche : pointeur sur la pénalité de pioche
// Retourne : 1 si le joueur peut rejouer, 0 sinon
int jouerTour(Joueur *joueur, Carte *carteActuelle, Carte *deck, int *indexDeck, int *direction, int *sauterProchainJoueur, int *penalitePioche) {
    printf("Carte actuelle: %s de %s\n", carteActuelle->valeur, carteActuelle->couleur);
    afficherMain(*joueur);

    int choix;
    // Demande au joueur de choisir une carte à jouer ou de tirer une nouvelle carte
    printf("Choisir une carte à jouer (1-%d) ou 0 pour tirer: ", joueur->tailleMain);
    scanf("%d", &choix);

    // Si le joueur choisit de tirer une carte
    if (choix == 0) {
        if (*indexDeck < NUM_CARTES) {
            joueur->main[joueur->tailleMain++] = deck[(*indexDeck)++];  // Ajoute la prochaine carte du deck à la main du joueur
            printf("Vous avez tiré une carte.\n");
        } else {
            printf("La pioche est vide, vous ne pouvez pas tirer de carte.\n");
        }
        return 0;  // Le joueur ne peut pas rejouer
    }

    choix--;

    // Si le joueur choisit une carte valide de sa main
    if (choix >= 0 && choix < joueur->tailleMain) {
        // Vérifie si la carte peut être jouée
        if (peutJouerCarte(joueur->main[choix], *carteActuelle)) {
            *carteActuelle = joueur->main[choix];  // Met à jour la carte actuelle avec la carte jouée
            printf("Vous avez joué: %s de %s\n", carteActuelle->valeur, carteActuelle->couleur);

            // Supprime la carte jouée de la main du joueur
            for (int i = choix; i < joueur->tailleMain - 1; i++) {
                joueur->main[i] = joueur->main[i + 1];
            }
            joueur->tailleMain--;

            int rejouer = 0;
            // Applique les règles spécifiques de la carte jouée
            appliquerRegles(carteActuelle, carteActuelle, direction, sauterProchainJoueur, penalitePioche, &rejouer);

            // Si la carte jouée permet de rejouer
            if (rejouer) {
                printf("Vous avez joué une carte 10, vous pouvez rejouer.\n");
                return 1;  // Le joueur peut rejouer
            }
        } else {
            printf("Vous ne pouvez pas jouer cette carte. Réessayez.\n");
            return 1;  // Le joueur doit rejouer une carte valide
        }
    }

    return 0;  // Le joueur ne peut pas rejouer
}

// Fonction pour gérer la boucle de jeu
// Paramètres : 
// - deck : le deck de cartes
// - joueurs : un tableau de joueurs
// - indexDeck : pointeur sur l'index de la prochaine carte à tirer dans le deck
// - carteActuelle : la carte actuelle sur le dessus du tas
// - joueurActuel : pointeur sur l'index du joueur actuel
// - direction : pointeur sur la direction actuelle du jeu
// - sauterProchainJoueur : pointeur sur l'indicateur de saut du prochain joueur
// - penalitePioche : pointeur sur la pénalité de pioche
void boucleDeJeu(Carte *deck, Joueur *joueurs, int *indexDeck, Carte *carteActuelle, int *joueurActuel, int *direction, int *sauterProchainJoueur, int *penalitePioche) {
    while (1) {
        printf("\nTour du joueur %d:\n", *joueurActuel + 1);

        // Si le joueur actuel doit piocher des cartes en pénalité
        if (*penalitePioche > 0) {
            printf("Le joueur %d pioche %d cartes en pénalité.\n", *joueurActuel + 1, *penalitePioche);
            // Ajoute les cartes en pénalité à la main du joueur actuel
            for (int i = 0; i < *penalitePioche; i++) {
                if (*indexDeck < NUM_CARTES) {
                    joueurs[*joueurActuel].main[joueurs[*joueurActuel].tailleMain++] = deck[(*indexDeck)++];
                } else {
                    printf("Le deck est vide, impossible de piocher plus de cartes.\n");
                    break;
                }
            }
            *penalitePioche = 0;  // Réinitialise la pénalité de pioche
        }

        // Si le prochain joueur doit être sauté
        if (*sauterProchainJoueur) {
            printf("Le joueur %d doit rejouer.\n", *joueurActuel + 1);
            *sauterProchainJoueur = 0;  // Réinitialise l'indicateur de saut du prochain joueur
        } else {
            // Joue le tour pour le joueur actuel
            int rejoue = jouerTour(&joueurs[*joueurActuel], carteActuelle, deck, indexDeck, direction, sauterProchainJoueur, penalitePioche);

            // Vérifie si le joueur actuel a gagné
            if (joueurs[*joueurActuel].tailleMain == 0) {
                printf("Le joueur %d gagne!\n", *joueurActuel + 1);
                break;  // Terminer la boucle de jeu
            }

            // Si le joueur peut rejouer, continue le tour pour le même joueur
            if (rejoue) {
                continue;
            }
        }

        // Passe au joueur suivant en fonction de la direction actuelle
        *joueurActuel = (*joueurActuel + *direction + NUM_JOUEURS) % NUM_JOUEURS;
    }
}
