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
float numEn = 3;
char oneMoreClear[6] = {0, 0, 0, 0, 0, 0};
short eX[6] = {0, 0, 0, 0, 0, 0};
short eY[6] = {0, 0, 0, 0, 0, 0};
unsigned short peX[6] = {0, 0, 0, 0, 0, 0};
unsigned short peY[6] = {0, 0, 0, 0, 0, 0};

char staminaMax = 50;
char staminaAttack = 30;
char stamina = 50;

char enFlag = 0;
char hitResetMax = 10;
char hitReset = 10;

short dying = 