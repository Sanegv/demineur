#ifndef DEF_DEMINEUR
#define DEF_DEMINEUR

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief les variables requises pour faire tourner le Jeu
 * 
 * @param grille double tableau de char
 * @param masque tableau de booléens qui indique si une case est masquée ou non
 * @param x la largeur du tableau
 * @param y la hauteur du tableau
 * @param mines le nombre de mines dans la grille
 * 
 */
typedef struct Jeu {
    int** grille;
    char** masque;
    int x;
    int y;
    int mines;
} Jeu;

/**
 * @brief créée un tableau de taille x*y, le masque, assigne toutes les valeurs aux variables de Jeu, et renvoie le résultat
 * 
 * @param x 
 * @param y 
 * @param mines 
 * @return Jeu 
 */
Jeu init_jeu(int x, int y, int mines);

/**
 * @brief libère la mémoire de la grille
 * 
 * @param j 
 */
void free_jeu(Jeu j);

/**
 * @brief affiche la grille de Jeu dans le terminal
 * 
 * @param j 
 */
void print_jeu(Jeu j);

/**
 * @brief vérifie si les seules cases encore masquées contiennent des mines
 * 
 * @param j 
 * @return int 
 */
int check_victory(Jeu j);

/**
 * @brief révèle la case donnée en entrée. Renvoie 1 s'il y avait une mine. Si la case contenait un 0, révèle également les cases alentours.
 * 
 * @param jeu 
 * @param x 
 * @param y 
 * @return int 
 */
int reveal_tile(Jeu jeu, int x, int y);

/**
 * @brief représente un tour d'un humain :
 * demande au joueur la case qu'il veut révéler tant qu'il n'a pas proposé de case valide,
 * puis vérifie s'il a perdu. Renvoie 0 si c'est le cas.
 * 
 * @param jeu 
 * @return int
 */
int guess(Jeu jeu);

/**
 * @brief Créée une partie avec les paramètres spécifiés
 * 
 * @param x 
 * @param y 
 * @param mines 
 */
void game(int x, int y, int mines);
#endif