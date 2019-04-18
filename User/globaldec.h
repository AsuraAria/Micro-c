#include "constantes.h" // fichier contenant toutes les constantes du projet
#include <stdint.h>
#include "lpc17xx_i2c.h"
#include <stdbool.h>

// Global main.c variables

//char chaine[30]; // buffer for LCD writting
uint16_t touch_x, touch_y ;
// Flag for touchscreen to activate the detection
char flagTouch = 0;
// Reset flag to activate 1 touch and wait for the user to wait for the 
// user to remove his finger before reactivating the detection
char flagReset = 1;

//=============
// Definitions
//=============

// Loop variables
char i;

// Variable to know if a map should be displayed (to display it only one time)
bool mapLoad = true;
// Variables of the coordinates of the map to be displayed
unsigned char mapX=0, mapY=0;

// Player's coordinates
unsigned short pX=30, pY=30;
// Player direction to display sprite and travel speed
signed char dir=4, vit=1;
// Number of lives and Number of Previous lives: to reset the display only 
// when changing
unsigned char life = 3;
unsigned char pLife = 0;
// Coordinates of the former player's position
unsigned short pBX=30, pBY=0;

// Menu variable: Main menu, Save menu, Extra menu, Tutorial menu, History menu
signed char menu = 1;

// Save number to load and save
char numSave = 0;

// Number of enemies : To change the player speed because more enemies are 
// displayed, lower are the player speed.
char iEn=0;

// Data variable to load and save on I2C memory
uint8_t data[20];

// Random
unsigned int random = 0;

// Ennemies variables
float numEn = 3;
char oneMoreClear[6] = {0, 0, 0, 0, 0, 0};
short eX[6] = {0, 0, 0, 0, 0, 0};
short eY[6] = {0, 0, 0, 0, 0, 0};
unsigned short peX[6] = {0, 0, 0, 0, 0, 0};
unsigned short peY[6] = {0, 0, 0, 0, 0, 0};

// Stamina management
char staminaMax = 50;
char staminaAttack = 30;
char stamina = 50;

char enFlag = 0;
char hitResetMax = 10;
char hitReset = 10;

char dying = 0;