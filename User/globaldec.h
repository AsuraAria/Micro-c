#include "constantes.h" // fichier contenant toutes les constantes du projet
#include <stdint.h>
#include "lpc17xx_i2c.h"
#include <stdbool.h>

// mettez ici toutes les déclarations de variables globales

char chaine[30]; // buffer pour l'affichage sur le LCD
uint16_t touch_x, touch_y ;
char flagTouch = 0;
char flagReset = 1;

//=============
// Definitions
//=============

char i;

// Variable pour savoir si un tableau doit être affiché
bool mapLoad = true;
// Variables des coordonnées du tableau à afficher
unsigned char mapX=0, mapY=0;

// Coordonnées du joueur et direction pour afficher le sprite
unsigned short pX=30, pY=30;
signed char dir=4, vit=1;
unsigned char life = 3;
unsigned char pLife = 0;
// Coordonnées de l'ancienne position du joueur
unsigned short pBX=30, pBY=0;

signed char menu = 1;

char numSave = 0;

//Les enemies bougent 2 fois moins vite
char iEn=0;

uint8_t data[20];

unsigned int random = 0;
/*unsigned int random2 = 1;
char iRandom = 0;
short randValue[20];*/

//Ennemies
float numEn = 3;
char oneMoreClear[6] = {0, 0, 0, 0, 0, 0};
short eX[6] = {0, 0, 0, 0, 0, 0};
short eY[6] = {0, 0, 0, 0, 0, 0};
unsigned short peX[6] = {0, 0, 0, 0, 0, 0};
unsigned short peY[6] = {0, 0, 0, 0, 0, 0};

//Gestion du stamina
char staminaMax = 50;
char staminaAttack = 30;
char stamina = 50;

char enFlag = 0;
char hitResetMax = 10;
char hitReset = 10;

char dying = 0;