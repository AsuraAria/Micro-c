#include "constantes.h" // fichier contenant toutes les constantes du projet
#include <stdint.h>
#include "lpc17xx_i2c.h"

// mettez ici toutes les déclarations de variables globales

char chaine[30]; // buffer pour l'affichage sur le LCD
uint16_t touch_x, touch_y ;
char flagTouch = 0;
char flagReset = 1;

unsigned int random = 0;
/*unsigned int random2 = 1;
char iRandom = 0;
short randValue[20];*/

//Ennemies
char numEn = 3;
unsigned short eX[3] = {0, 0, 0};
unsigned short eY[3] = {0, 0, 0};
unsigned short peX[3] = {0, 0, 0};
unsigned short peY[3] = {0, 0, 0};