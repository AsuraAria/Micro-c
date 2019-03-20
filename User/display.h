#include <stdbool.h>
#include <math.h>
#include <stdio.h>

#include "touch/ili_lcd_general.h"
#include "touch/lcd_api.h"
#include "touch/touch_panel.h"
#include "touch\lcd_api.h"

#include "affichagelcd.h"
//#include "globaldec.h" // fichier contenant toutes les d�clarations de variables globales

//================================================================================================
// Fichier contenants les prototypes des fonctions d'affichages
//================================================================================================

// Ecran 320*240

//========================================
// Definitions des structures
//========================================

//========================================
// Definitions des prototypes
//========================================

//=======================
// Affichage des menus
//=======================

// Tactile
// x : 180-3850
// y : 380-3850

void drawMenu(char);
char unCompressLetter(char);
void drawText(char*, char, unsigned short, unsigned short);

//=======================
// Affichage des maps
//=======================

// Renvoie la valeur réelle de la couleur demandé
unsigned short getColor(unsigned char);

// Dessine un carré de texture 20x20px (case aux coordonées x et y)
void drawTexture(unsigned short, unsigned short, char);

// Permet la gestion des maps (aux coordonnées x et y)						
unsigned short getMap(unsigned char, unsigned char, unsigned short, unsigned short);
														
// Dessine un des tableaux de la map (tableau aux coordonnées x et y)
void drawMap(unsigned char, unsigned char, bool*);

//=======================
// Affichage du personnage
//=======================

void drawPlayer(unsigned short, unsigned short, unsigned char);

void clearOldPlayer(unsigned short, unsigned short, unsigned char, unsigned char);

//=======================
// Déplacement personnage
//=======================

char readJoystick();

bool isColliding(unsigned short, unsigned short, unsigned char, unsigned char, char);

//========================================
// Fin
//========================================

