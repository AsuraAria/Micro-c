//===========================================================//
// Projet Micro - INFO1 - ENSSAT - S2 2018							 //
//===========================================================//
// File                : Fluffy
// Hardware Environment: Open1768
// Build Environment   : Keil uVision (EVALUATION LICENSE ONLY 32K)
//===========================================================//

//===========================================================//
// Includes
//===========================================================//

#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_timer.h"
#include "touch\ili_lcd_general.h"
#include "touch\lcd_api.h"
#include "affichagelcd.h"
#include "touch\touch_panel.h"

#include "memory.h"
#include "musicien.h"
// Fichier contenant toutes les declarations de variables globales
#include "globaldec.h"
#include <stdio.h>
#include "display.h"

// Each possibility of menu variable
#define Game -1
#define MainMenu 1
#define SaveMenu 2
#define BonusMenu 0
#define TutorialMenu 3
#define StoryMenu 4

//
//===========================================================//
// Main prototypes
//===========================================================//

// Timer functions
void T1_Init();
void TIMER1_IRQHandler();

// Initialize (Timers, pins, LCD, TouchScreen, I2C) and reset function
void initAll();
void pin_Configuration();
void reset(unsigned char*, unsigned char*, unsigned short*, unsigned short*, unsigned char*);

// Game functions
void game();

void mapManagement();
void staminaManagement();
void lifeManagement();

void clearPlayer();
void clearEnemies();

void joystickManagement();
void mapChange();

void enemiesManagement();
void playerManagement();

// Menu functions
void menuManagement(signed char);
void buttonManagement(signed char);

//
//===========================================================//
// Main function
//===========================================================//

int main(void)
{
	// Init pins, variables, timers, I2C
	initAll();
	
	while(1)
	{
		if (menu == Game) // If we are in the game, the user can play
		{
			game(); // Display the game
		}
		else // If not in game
		{
			// Use of touch screen (beacause we are on a menu)
			touch_read();
			
			// Manage each menu and each button
			menuManagement(menu);
			buttonManagement(menu);
		}
	}
}


//
//===========================================================//
// Timer functions
//===========================================================/

void T1_Init() // Initiation du Timer1
{
	TIM_TIMERCFG_Type conf_timer;
	TIM_MATCHCFG_Type conf_interrupt;

	conf_timer.PrescaleOption = TIM_PRESCALE_USVAL; //prescale en uS
	conf_timer.PrescaleValue = 20000; // Precision de 20 mS

	conf_interrupt.MatchChannel=1;//timer1
	conf_interrupt.IntOnMatch=ENABLE;//enable:interruption sur match
	conf_interrupt.ResetOnMatch=ENABLE;//remise a zero en match
	conf_interrupt.StopOnMatch = DISABLE;
	conf_interrupt.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
	conf_interrupt.MatchValue = 5; // Lancement de l'interruption toutes les 100ms

	NVIC_EnableIRQ(TIMER1_IRQn);

	TIM_Init(LPC_TIM1, TIM_TIMER_MODE, &conf_timer);
  //timer0 en rising avec la config ci-jointe

	TIM_ConfigMatch(LPC_TIM1, &conf_interrupt);

	TIM_Cmd(LPC_TIM1, ENABLE);
}

void TIMER1_IRQHandler() // Timer1 Handler
{
	if (!(GPIO_ReadValue(0) & (1<<19))) // Flag tactile
	{
		flagTouch = 1;
	}
	else // When user stay on screen, flagReset allow only one entry
	{
		flagReset = 1;
	}
	
	if (hitReset<hitResetMax) // Invulnérability time
	{
		hitReset++;
	}
	
	enFlag = 1; // Enemies attack only each 100ms
	
	if (stamina < staminaMax) // Stamina rise to max
	{
		stamina++;
	}
	
	TIM_ClearIntPending(LPC_TIM1, TIM_MR1_INT); // Acknowledge
}

//
//===========================================================//
// Function used in main
//===========================================================//

// Initialize all
void initAll()
{
	lcd_Initializtion(); // Pinsel and LCD init
	touch_init(); // Touchscreen init
	pin_Configuration(); // Led, buzzer and I2D init
	init_i2c_eeprom(); // Memory init
	T0_Init(); // Music timer init
	T1_Init(); // Game/Touchscreen init
	
	musintro(); // Start the theme song
	
	initEnemy(eX, eY, random); // Init enemies positions
	
	// Init memory => Reset if bad or if manual request
	if (!check_memory() || !(GPIO_ReadValue(2) & (1<<11)))
	{
		clean_memory();
		create_gamekey();
	}
	
	// Black Background
	dessiner_rect(0,0,240,320,0,1,Black,Black);
}

// Init pins
void pin_Configuration()
{
		unsigned char i; // Pour la boucle for des configs de pins
	
		PINSEL_CFG_Type memory27;
		PINSEL_CFG_Type memory28;

		int ledBit = (1<<3);
		int hpBit = (1<<9);
	
		// Joystick et boutons
		int joystickPort[6] = {2, 2, 2, 2, 2, 1}; //Port
		int joystickPin[6] = {10, 12, 13, 8, 11, 21}; //Pin
	
		FIO_SetDir(2, (1<<11), 0); // Bouton Menu : Entrée
		FIO_SetMask(2, (1<<11), 0); // Bouton Menu : Utilisable
		
		FIO_SetDir(0, ledBit, 1); // Led0 : Sortie
		FIO_SetMask(0, ledBit, 0); // Led0 : Utilisable

		FIO_SetDir(1, hpBit, 1); // Haut-Parleur : Sortie
		FIO_SetMask(1, hpBit, 0); // Haut-Patleut : Utilisable

		// Mémoire
		memory27.Funcnum = PINSEL_FUNC_1;
		memory27.OpenDrain = PINSEL_PINMODE_NORMAL;
		memory27.Pinmode = PINSEL_PINMODE_PULLUP;
		memory27.Pinnum = PINSEL_PIN_27;
		memory27.Portnum = PINSEL_PORT_0; // GPIO0
		PINSEL_ConfigPin(&memory27);

		memory28.Funcnum = PINSEL_FUNC_1;
		memory28.OpenDrain = PINSEL_PINMODE_NORMAL;
		memory28.Pinmode = PINSEL_PINMODE_PULLUP;
		memory28.Pinnum = PINSEL_PIN_28;
		memory28.Portnum = PINSEL_PORT_0; // GPIO0
		PINSEL_ConfigPin(&memory28);
		
		// Congifuration joystick et boutons
		for (i=0; i<6; i++)
		{
			FIO_SetDir(joystickPort[i], joystickPin[i], 0); // Joystick : Inputs
			FIO_SetMask(joystickPort[i], joystickPin[i], 0); // Joystick : Usable
		}
}

// Reset : map00, initial position
void reset(unsigned char*mX, unsigned char*mY, unsigned short*x, unsigned short*y, unsigned char*l)
{
	// Map coordinates
	*mX = 0;
	*mY = 0;
	// Player coordinates on the map
	*x = 30;
	*y = 30;
	*l = 3;
}

// Game functions
void game()
{
	// Manage map
	mapManagement();
	// Manage Stamina
	staminaManagement();
	// Manage life
	lifeManagement();
	
	// Clean up old player sprite
	clearPlayer();
	// Clean up old enemy sprites
	clearEnemies();
	
	// Joystick management
	joystickManagement();
	
	// Map change
	mapChange();
	
	// Player management
	playerManagement();
	// Enemies management
	enemiesManagement();
}

//
// In game functions
void mapManagement()
{
	if (mapLoad) // If this is the first display
	{
		drawMap(mapX, mapY, &mapLoad); // Display map and give the value "False" to mapLoad to display only 1 time
		pLife = 0; // Old life count, to refresh the life display only when it change (to speed up the game)
	}
}

void staminaManagement()
{
	// If stamina is not at is max : display the grey part of the stamina bar
	if (stamina != staminaMax)
		dessiner_rect(8,10, 4, staminaMax-stamina, 0, 1, Grey, Grey);
	
	// If there is enough stamina to attack, display the bar in blue 
	// Else display it in dark grey
	if (stamina < staminaAttack)
		dessiner_rect(8,10+staminaMax-stamina, 4, stamina, 0, 1, 0x8c71, 0x8c71);
	else
		dessiner_rect(8,10+staminaMax-stamina, 4, stamina, 0, 1, Blue, Blue);
}

void lifeManagement()
{
	// If the number of lives has changed: display it again 
	if (pLife != life)
	{
		// 3 life max : Life still available are white sheeps and life lost are black sheeps
		for (i=0; i<3; i++)
		{
			if(i<life)
			{
				// Draw white sheeps
				drawPlayer(0, 20*(13+2-i), 30);
			}
			else
			{
				// Draw black sheeps
				drawPlayer(0, 20*(13+2-i), 31);
			}
		}
		// Reset old life count to new life count (Draw sheeps only when the life count changes)
		pLife = life;
	}
}

void clearPlayer()
{
	// If the player has moved
	if (pBX!=pX || pBY != pY)
	{
		// Clean old player sprite
		clearOldPlayer(pBX, pBY, mapX, mapY);
	}
	// Reset old position to new position (Clean sprite only when player moves)
	pBX=pX, pBY=pY;
}

void clearEnemies()
{
	// This condition is used to reduce the speed of enemies (See at the end of this function)
	if (iEn==0)
	{
		/* If player is not on the first map (map00 is enemy safe)
		 * In addition, mapX=250 is the menu map, so no enemies should be cleaned.
		*/
		if (mapX<250 && (mapX > 0 || mapY > 0))
		{
			// Display 6 enemies
			for (i=0; i<6; i++)
			{
				/* When an enemy dies, he is teleported outside the screen (eX = -100 and eY = -100)
				 * so if eX[i]>=0 then the enemy [i] is not dead	
				 *
				 * BUT when an enemy dies, he need to be clean one more time : so oneMoreClear[i] will 
				 * be at "1" if the enemiy [i] just died
				*/
				if (eX[i] >= 0 || oneMoreClear[i])
				{
					// Clear the enemy [i]
					clearOldPlayer(peX[i], peY[i], mapX, mapY);
					// Reset oneMoreClear[i] because the enemy has been cleaned
					oneMoreClear[i]=0;
				}
				// Reset old position to new position (Clean sprite only when enemy moves)
				peX[i] = eX[i], peY[i] = eY[i];
			}
		}
	}
	
	// Divide enemy speed by the number to the right of "%".
	// iEn=(iEn+1)%1;
}

void joystickManagement()
{
	/* Get the current input used : Button or Joystick (Only one can be detected at 
	 * the same time) so there is a priority for each one (See inside the function)
	*/
	dir = readJoystick();
	
	// If key1 : Go back to menu
	if (dir == 5)
	{
		// Set the menu to main menu
		menu = MainMenu ;
		// Reset mapLoad boolean to draw menu
		mapLoad = true;
		
		// Save the new player position (map and pixel coordinates) into the current save
		fillup_save(data, numSave, life, mapX, mapY, pX, pY, 0);
		create_save(numSave,data);
	}
	
	// If key0 AND if player has enough stamina : Attack
	if (dir == 6 && stamina >= staminaAttack)
	{
		attack(pX, pY, eX, eY, oneMoreClear, &numEn);
		// Take off stamina used
		stamina -= staminaAttack;
	}
	
	// If player is not colliding with the map : Move the player
	if (!isColliding(pX, pY, mapX, mapY, dir))
	{
		if (dir==1)
		{
			// Go up
			pX+=vit;
		}
		else if (dir==2)
		{
			// Go right
			pY+=vit;
		}
		else if (dir==3)
		{
			// Go down
			pX-=vit;
		}
		else if (dir==0)
		{
			// Go left
			pY-=vit;
		}
	}
	else
	{
		// Default direction (The player does not move)
		dir = 4;
	}
}

void mapChange()
{
	// If the player is in the bottom cell of the screen : Jump to the next map
	if (pX >= 220)
	{
		mapY++;
		pX = 10;
		mapLoad = true;
	}
	// If the player is in the top cell of the screen : Jump to the next map
	else if (pX <= 5)
	{
		mapY--;
		pX = 215;
		mapLoad = true;
	}
	// If the player is in the far left cell of the screen
	else if (pY >= 300)
	{
		mapX++;
		pY = 10;
		mapLoad = true;
	}
	// If the player is in the far right cell of the screen
	else if (pY <= 5)
	{
		mapX--;
		pY = 295;
		mapLoad = true;
	}
	
	// If mapLoad=True then player has changed map
	if (mapLoad)
	{
		/* Set the "pseudo number of ennemies" to 3 (It is not the real number of enemies which are 6)
		 * numEn is equal to the number of enemies divided by 2
		 *
		 * It is used to define the player's speed which is relative to the number of enemies due to 
		 * the time required to display them.
		*/ 
		numEn = 3;
		// Init random position for each of them
		initEnemy(eX, eY, random);
	}
}

void playerManagement()
{
	// Draw the player sprite
	drawPlayer(pX, pY, dir);
}

void enemiesManagement()
{
	// This condition is used to reduce the speed of enemies (See in clearEnemies function)
	if (iEn==0)
	{
		/* If player is not on the first map (map00 is enemy safe)
		 * In addition, mapX=250 is the menu map, so no enemies should be displayed.
		*/
		if (mapX<250 && (mapX > 0 || mapY > 0))
		{
			// If flag is activate (each 100ms) and the player is not invulnerabilty mode : Enemies attack 1 time
			if (enFlag && hitReset == hitResetMax)
			{
				// Enemies attack
				if (attackE(pX, pY, eX, eY, &life))
				{
					// If the player is within range of one of them: the player becomes invulnerable for a period of time.
					hitReset = 0;
				}
				// Reset flag and so wait 100ms
				enFlag = 0;
			}
			
			// If life count is at zero
			if (life == 0)
			{
				// Reset all variables : life count, position of player, an go to menu
				menu = 1;
				mapLoad = 1;
				reset(&mapX, &mapY, &pX, &pY, &life);
				dying = 1;
				
				// Save the new player position : which are equivalent to inital position
				fillup_save(data, numSave, life, mapX, mapY, pX, pY, 0); // Préparation de la sauvegarde "data"
				create_save(numSave,data);
			}
			
			// Define the player speed in relation to the number of enemies still alive.
			vit = (signed char)numEn;
			
			// For each enemy
			for (i=0; i<6; i++)
			{
				// If enemy is not dead (See in clearEnemies function)
				if (eX[i] > 0)
				{
					// For enemy [0], [3] : AI is defined to go VERTICALLY THEN HORIZONTALLY
					if (i%3==0)
					{
						if (eX[i] != pX)
						{
							eX[i]>pX?eX[i]--:eX[i]++;
						}
						else
						{
							eY[i]>pY?eY[i]--:eY[i]++;
						}
					}
					// For enemy [1], [4] : AI is defined to go HORIZONTALLY THEN VERTICALLY
					else if (i%3 == 1)
					{
						if (eY[i] != pY)
						{
							eY[i]>pY?eY[i]--:eY[i]++;
						}
						else
						{
							eX[i]>pX?eX[i]--:eX[i]++;
						}
					}
					// For enemy [2], [5] : AI is defined to MOVE DIAGONALLY
					else
					{
						eY[i]>pY?eY[i]--:eY[i]++;
						eX[i]>pX?eX[i]--:eX[i]++;
					}
					
					//Draw each enemy
					drawPlayer(eX[i], eY[i], 20);
				}
			}
		}
		// If enemy should not be displayed : then set player speed to 1
		else
		{
			vit = 1;
		}
	}
}

// Menu function
void menuManagement(signed char m)
{
	if (mapLoad)
	{
		// In Tutorial and Story menu : draw a black background
		if (m != StoryMenu && m != TutorialMenu)
		{
			drawMap(250, 0, &mapLoad);
		}
		// Else : draw the map
		else
		{
			dessiner_rect(0,0,240,320,0,1,Black, Black);
			mapLoad = 0;
		}
		
		// Draw the menu: Text and button
		drawMenu(m);
	}
}

void buttonManagement(signed char m)
{
	// If flagTouch is enabled and touch screen has already been reset
	if (flagTouch && flagReset == 1)
	{
		// Manage button 
		switch(menu)
		{
			case MainMenu:
				flagTouch = 0;
				
				if (touch_x>=1650 && touch_x<=2500
						&& touch_y>=700 && touch_y<=1700)
				{
					mapLoad = true;
					menu = 2;
					flagReset = 0;
				}
				
				if (touch_x>=2500 && touch_x<=3400
						&& touch_y>=700 && touch_y<=1700)
				{
					mapLoad = true;
					menu = 0;
					flagReset = 0;
				}
				break;
			case SaveMenu:
				flagTouch = 0;
				
				/* =============================
				 * Save 2 Button
				 * =============================
				*/
				
				if (touch_x >= 1900 && touch_x <= 3200
						&& touch_y >= 2650 && touch_y <= 3500)
				{
					// Load the save 2
					mapLoad = true;
					menu = -1;
					numSave = 2;
					
					// If the save exists : load it
					if (check_save(2))
					{
						load_save(numSave, data);
						filldown_save(data, numSave, &life, &mapX, &mapY, &pX, &pY, 0); // Chargement de la sauvegarde "data"
					}
					// Else : set initial player position
					else
					{
						reset(&mapX, &mapY, &pX, &pY, &life);
					}
				}
				
				/* =============================
				 * Save 1 Button
				 * =============================
				*/
				
				if (touch_x >= 1900 && touch_x <= 3200
						&& touch_y >= 1650 && touch_y <= 2650)
				{
					mapLoad = true;
					menu = -1;
					numSave = 1;
					
					// If the save exists : load it
					if (check_save(1))
					{
						// Load the save 1
						load_save(numSave, data);
						filldown_save(data, numSave, &life, &mapX, &mapY, &pX, &pY, 0); // Chargement de la sauvegarde "data"
					}
					// Else : set initial player position
					else
					{
						reset(&mapX, &mapY, &pX, &pY, &life);
					}
				}
				
				/* =============================
				 * Save 0 Button
				 * =============================
				*/
				if (touch_x >= 1900 && touch_x <= 3200
						&& touch_y >= 650 && touch_y <= 1650)
				{
					// Load the save 0
					mapLoad = true;
					menu = -1;
					numSave = 0;
					
					// If the save exists : load it
					if (check_save(0))
					{
						load_save(numSave, data);
						filldown_save(data, numSave, &life, &mapX, &mapY, &pX, &pY, 0); // Chargement de la sauvegarde "data"
					}
					// Else : set initial player position
					else
					{
						reset(&mapX, &mapY, &pX, &pY, &life);
					}
				}
				break;
			case BonusMenu:
				flagTouch = 0;
				
				// Tutorial
				if (touch_x>=1650 && touch_x<=2500
						&& touch_y>=700 && touch_y<=2200)
				{
					mapLoad = true;
					menu = 3;
					flagReset = 0;
				}
				
				// Story
				if (touch_x>=2500 && touch_x<=3400
						&& touch_y>=700 && touch_y<=1700)
				{
					mapLoad = true;
					menu = 4;
					flagReset = 0;
				}
				
				// Back
				if (touch_x>=2500 && touch_x<=3400
						&& touch_y>=2200 && touch_y<=3800)
				{
					mapLoad = true;
					menu = 1;
					flagReset = 0;
				}
				break;
			case TutorialMenu:
			case StoryMenu:
				if (touch_x>=10)
				{
					flagTouch = 0;
					mapLoad = true;
					menu = 0;
					flagReset = 0;
				}
				break;	
		}
	}
}

//
//===========================================================//
// End
//===========================================================//

//---------------------------------------------------------------------------------------------
#ifdef  DEBUG
void check_failed(uint8_t *file, uint32_t line) {while(1);}
#endif
