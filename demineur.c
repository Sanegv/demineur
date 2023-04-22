#include "demineur.h"

void place_mine(Jeu jeu, int x, int y){
    jeu.grille[y][x] = -1;
    for(int i = y-1; i < y+2; i++){
        for(int j = x-1; j < x+2; j++){
            if(i >= 0 && j >= 0 && i < jeu.y && j < jeu.x && jeu.grille[i][j] >= 0) jeu.grille[i][j]++;
        }
    }
}

void place_mines(Jeu jeu){
    int x, y;
    for(int i = 0; i < jeu.mines; i++){
        do {
            x = rand()%jeu.x;
            y = rand()%jeu.y;
        } while(jeu.grille[y][x] < 0);
        place_mine(jeu, x, y);
    }
}

Jeu init_jeu(int x, int y, int mines){
    int** grille = malloc(y*sizeof(int*));
    char** masque = malloc(y*sizeof(char*));
    if((!grille) || (!masque)) exit(1);
    for(int i = 0; i < y; i++){
        grille[i] = calloc(x, sizeof(int));
        masque[i] = malloc(x*sizeof(char));
        if((!grille[i]) || (!masque[i])) exit(1);
        for(int j = 0; j < x; j++) masque[i][j] = 1;
    }
    Jeu jeu;
    jeu.x = x;
    jeu.y = y;
    jeu.mines = mines;
    jeu.grille = grille;
    jeu.masque = masque;

    place_mines(jeu);

    return jeu;
}

void free_jeu(Jeu jeu){
    for(int i = 0; i < jeu.y; i++) {
        free(jeu.grille[i]);
        free(jeu.masque[i]);
    }
    free(jeu.grille);
    free(jeu.masque);
}

void print_case(Jeu jeu, int x, int y){
    if(jeu.masque[y][x]) {
        printf("■ ");
        return;
    }
    if(jeu.grille[y][x] == -1) printf(("X "));
    else printf("%d ", jeu.grille[y][x]); 
}

void print_jeu(Jeu jeu){
    printf("    ");
    for(int i = 0; i < jeu.x; i++) printf("%d ", i);
    printf("\n    ");
    for(int i = 0; i < jeu.x; i++) printf("_ ");
    printf("\n");
    for(int i = 0; i < jeu.y; i++){
        printf("%d | ", i);
        for(int j = 0; j < jeu.x; j++){
            print_case(jeu, j, i);
        }
        printf("\n");
    }
    printf("\n");
}

int check_victory(Jeu jeu){
    for(int i = 0; i < jeu.y; i++){
        for(int j = 0; j < jeu.x; j++){
            if(jeu.masque[i][j] && (jeu.grille[i][j] >= 0)) return 0;
        }
    }

    return 1;
}

int reveal_tile(Jeu jeu, int x, int y){
    jeu.masque[y][x] = 0; //on révèle la case
    if(jeu.grille[y][x] == -1) return 1; //si elle contenait une mine, perdu !

    //si elle contenait un 0, on libère les cases alentours
    if(jeu.grille[y][x] == 0) {
        for(int i = y-1; i < y+2; i++) {
            if(i < 0 || i >= jeu.y) continue;
            for(int j = x-1; j < x+2; j++){
                if(j < 0 || j >= jeu.x) continue;
                if(jeu.masque[i][j]) reveal_tile(jeu, j, i);
            }
        }
    }
    
    return 0;
}

void game(int size_x, int size_y, int mines){
    Jeu jeu = init_jeu(size_x, size_y, mines);
    char non_defaite = 1;
    do {
        non_defaite = guess(jeu);
    } while(non_defaite && !check_victory(jeu)); //tant que le joueur n'a ni gagné, ni perdu, la partie continue

    print_jeu(jeu);
    non_defaite ? (printf("Félicitations !\n")) : (printf("BOOM !\n"));
    free_jeu(jeu);
}

int guess(Jeu jeu){
    int x, y;
    print_jeu(jeu);
    do {
        printf("Coordonnées (x y) de la case à réveler ?\n>");
        scanf("%d %d", &x, &y);
    } while (x < 0 || y < 0 || x >= jeu.x || y >= jeu.y || !jeu.masque[y][x]);

    if(reveal_tile(jeu, x, y)) return 0;
    return 1;
}