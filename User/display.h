#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "touch/ili_lcd_general.h"
#include "touch/lcd_api.h"
#include "touch/touch_panel.h"
#include "touch\lcd_api.h"

#include "affichagelcd.h"
#include "memory.h"

//================================================================================================
// Fichier contenants les prototypes des fonctions d'affichages
//================================================================================================

//=======================
// Affichage des menus
//=======================

void drawMenu(char);
/*********************************************************************//**
 * @brief			Draw the menu 
 * @param[in]	char, menu number
 * @return		None
 *
 * Note:
 * - None
 **********************************************************************/

char unCompressLetter(char);
/*********************************************************************//**
 * @brief			Uncompress letter matrix color code
 * @param[in]	char, "compressed" letter color code
 * @return		char, real color code
 *
 * Note:
 * - All pixels are coded on 2 bits with value : 0, 1, 2 and 3
 * But real color codes are respectively : 8, 7, 12 and 250
 **********************************************************************/

void drawText(char*, char, unsigned short, unsigned short);
/*********************************************************************//**
 * @brief			Draw text on the screen in landscape orientation
 * @param[in]	char*, text to write
 *						char, size of the text is divided by this number
 *						unsigned short, x position of the upper of the text
 *						unsigned short, y position of the right of the text
 * @return		None
 *
 * Note:
 * - The text is drawn at the (x,y) position of the screen, 
 * which is the position of the upper RIGHT corner of the text.
 **********************************************************************/

//=======================
// Affichage des maps
//=======================

unsigned short getColor(unsigned char);
/*********************************************************************//**
 * @brief			uncompress color
 * @param[in]	unsigned char, "compressed" color code
 * @return		unsigned short, real color value 
 *
 * Note:
 * - All pixels are coded on char variable (8 bits)
 * But real color are coded in unsigned short (16 bits)
 * This allows to use less memory !
 **********************************************************************/

void drawTexture(unsigned short, unsigned short, char);
/*********************************************************************//**
 * @brief			Draw a texture square (20x20px) at the (x,y) CELL coordinates
 * @param[in]	unsigned short, x coordinate of the cell (0-11)
 *						unsigned short, y coordinate of the cell (0-15)
 *						char, texture identifier
 * @return		None
 *
 * Note:
 * - None
 **********************************************************************/
 
unsigned short getMap(unsigned char, unsigned char, unsigned char, unsigned char);
/*********************************************************************//**
 * @brief			Get the map located at the (x,y) MAP coordinates
 * @param[in]	unsigned char, x coordinate of the map (0-255)
 * 						unsigned char, y coordinate of the map (0-255)
 * 						unsigned char, j coordinate of the texture (0-11)
 * 						unsigned char, i coordinate of the texture (0-15)
 * @return		None
 *
 * Note:
 * - Uncompressing process is used in this function
 * (An explication of the process is done in the PDF)
 **********************************************************************/
 
void drawMap(unsigned char, unsigned char, bool*);
/*********************************************************************//**
 * @brief			Draw the map located at the (x,y) MAP coordinates 1 time
 * @param[in]	unsigned char, x coordinate of the map (0-255)
 * 						unsigned char, y coordinate of the map (0-255)
 *						bool, reset variable to draw the map only 1 time
 * @return		None
 *
 * Note:
 * - None
 **********************************************************************/

//=======================
// Affichage du personnage
//=======================

unsigned char playerColor(unsigned char);
/*********************************************************************//**
 * @brief			Uncompress color code
 * @param[in]	unsigned char, color code on 4bits
 * @return		unsigned char, color code on 5bits (or more)
 *
 * Note:
 * - None
 **********************************************************************/
 
void drawPlayer(unsigned short, unsigned short, unsigned char);
/*********************************************************************//**
 * @brief			Draw player (or enemies) sprite at the (x,y) SCREEN coordinates
 * @param[in]	unsigned short, x coordinate of the player(0-239)
 * 						unsigned short, y coordinate of the player (0-319)
 *						unsigned char, direction to draw the right sprite (0,1,2,3)
 * @return		None
 *
 * Note:
 * - This function is used for multiple reasons :
 * 0,1,2,3 => Down, Left, Up, Right sprite of the player
 * 10 => Draw the player sprite looking down 6 time the normal scale
 * 20 => Draw the enemie sprite
 **********************************************************************/
 
void clearOldPlayer(unsigned short, unsigned short, unsigned char, unsigned char);
/*********************************************************************//**
 * @brief			Clear player (or enemies) sprite at the (x,y) SCREEN coordinates
 *            by redrawing cells of the current map over the sprite targeted
 * @param[in]	unsigned char, x coordinate of the sprite (0-239)
 * 						unsigned char, y coordinate of the sprite (0-319)
 *            unsigned char, x coordinate of the map (0-255)
 * 						unsigned char, y coordinate of the map (0-255)
 * @return		None
 *
 * Note:
 * - This function redraw only cells which was behind old player sprite when it moves
 * to prevent redrawing all the map and so allows a fast refreshing
 **********************************************************************/

//=======================
// Gestion du joueur
//=======================

char readJoystick();
/*********************************************************************//**
 * @brief			Get joystick (and buttons) inputs to move the player and choose what sprite is used
 * @param[in]	None
 * @return		char, joystick input : 0,1,2,3,4,5
 *
 * Note:
 * - Multiple use :
 * 0,1,2,3,4 => Down, Left, Up, Right, No move (Down sprite will be display)
 **********************************************************************/
 
bool isColliding(unsigned short, unsigned short, unsigned char, unsigned char, char);
/*********************************************************************//**
 * @brief			Test a collision between the player and the map (bush or stone)
 * @param[in]	unsigned short, x coordinate (0-239)
 * 						unsigned short, y coordinate (0-319)
 * @return		bool; true - player is colliding, false - player is not colliding
 *
 * Note:
 * - None
 **********************************************************************/
 
void attack(unsigned short, unsigned short, short[6], short[6], char[6], float*);
 /*********************************************************************//**
 * @brief			Player attack
 * @param[in]	unsigned short, x coordinates of the player(0-239)
 * 						unsigned short, y coordinates of the player(0-319)
 *						short[3], x coordinates of enemies(0-239)
 * 						short[3], y coordinates of enemies(0-319)
 * 						char, number of enemies still alive
 * @return		None
 *
 * Note:
 * - None
 **********************************************************************/
 
//========================================
// Gestion enemies
//========================================

void initEnemy(short[6], short[6], unsigned int);
/*********************************************************************//**
 * @brief			Initialize enemies position on the map
 * @param[in]	short[3], x coordinates of enemies(0-239)
 * 						short[3], y coordinates of enemies(0-319)
 * 						unsigned int, random seed
 * @return		None
 *
 * Note:
 * - None
 **********************************************************************/

char attackE(unsigned short, unsigned short, short[6], short[6], unsigned char*);
/*********************************************************************//**
 * @brief			Enemies attack
 * @param[in]	unsigned short, x coordinates of the player (0-239)
 * 						unsigned short, y coordinates of the player (0-319)
 *						short[3], x coordinates of enemies (0-239)
 * 						short[3], y coordinates of enemies (0-319)
 *						unsigned char, life of player
 * @return		None
 *
 * Note:
 * - None
 **********************************************************************/
 
//========================================
// Fin
//========================================
