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


//===========================================================//
// Secondary functions
//===========================================================//

void T1_Init() // Initiation du Timer1
{

	TIM_TIMERCFG_Type conf_timer;
	TIM_MATCHCFG_Type conf_interrupt;

	conf_timer.PrescaleOption = TIM_PRESCALE_USVAL; //prescale en mS
	conf_timer.PrescaleValue = 100000;

	conf_interrupt.MatchChannel=1;//timer1
	conf_interrupt.IntOnMatch=ENABLE;//enable:interruption sur match
	conf_interrupt.ResetOnMatch=ENABLE;//remise a zero en match
	conf_interrupt.StopOnMatch = DISABLE;
	conf_interrupt.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
	conf_interrupt.MatchValue=1;

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
	else
	{
		flagReset = 1;
	}
	
	if (hitReset<hitResetMax) // Periode d'invulnérabilité
	{
		hitReset++;
	}
	
	enFlag = 1; // Les ennemis attaquent toutes les 100ms (a chaque Timer1 Handler)
	
	if (stamina < staminaMax) // Stamina
	{
		stamina++;
	}
	
	TIM_ClearIntPending(LPC_TIM1, TIM_MR1_INT); // Acquitement
}

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
			FIO_SetDir(joystickPort[i], joystickPin[i], 0); // joystick : Entrée
			FIO_SetMask(joystickPort[i], joystickPin[i], 0); // joystick : Utilisable
		}
}

// Reset map00 position du début
void reset(unsigned char*mX, unsigned char*mY, unsigned short*x, unsigned short *y)
{
	*mX = 0;
	*mY = 0;
	*x = 30;
	*y = 30;
}

//===========================================================//
// Function: Main
//===========================================================//

int main(void)
{
	//=============
	// Definition
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
	unsigned short pBX=pX, pBY=pY;
	
	signed char menu = 1;
	
	char numSave = 0;
	
	//Les enemies bougent 2 fois moins vite
	char iEn=0;
	
	
	uint8_t data[20];
	
	//=============
	// Init
	//=============
	
	lcd_Initializtion(); // init pinsel ecran et init LCD
	touch_init(); // init pinsel tactile et init tactile
	pin_Configuration(); // init pinsel memoire, buzzer, led
	init_i2c_eeprom(); // init mémoire
	T0_Init(); // init timer musique
	T1_Init();
	
	musintro(); // Lance l'intro
	
	if (!check_memory() || !(GPIO_ReadValue(2) & (1<<11))) // (Si la sauvegarde 0 existe : 
	{
		clean_memory();
		create_gamekey();
	}
	//=============
	// Boucle
	//=============
	
	numEn = 3;
	initEnemy(eX, eY, random);
	
	dessiner_rect(0,0,240,320,0,1,Black,Black);
	
	while(1)
	{
		
		if (menu == -1)
		{
			if (mapLoad)
			{
				drawMap(mapX, mapY, &mapLoad);
				pLife = 0;				// On le fait qu'une seule fois pour une question de rapidité d'execution
			}
			
			if (stamina != staminaMax)
				dessiner_rect(8,10, 4, staminaMax-stamina, 0, 1, Grey, Grey);
			
			if (stamina < staminaAttack)
				dessiner_rect(8,10+staminaMax-stamina, 4, stamina, 0, 1, 0x8c71, 0x8c71);
			else
				dessiner_rect(8,10+staminaMax-stamina, 4, stamina, 0, 1, Blue, Blue);
			
			if (pLife != life)
			{
				for (i=0; i<3; i++)
				{
					if(i<life)
					{
						drawPlayer(0, 20*(13+2-i), 30);
					}
					else
					{
						drawPlayer(0, 20*(13+2-i), 31);
					}
				}
				pLife = life;
			}
			
			// Rafraîchir les cases derrière l'ancienne position du personnage pour le faire disparaître
			if (pBX!=pX || pBY != pY)
			{
				clearOldPlayer(pBX, pBY, mapX, mapY);
			}
			
			if (iEn==0)
			{
				if (mapX<250 && (mapX > 0 || mapY > 0))
				{
					for (i=0; i<6; i++)
					{
						if (eX[i] >= 0 || oneMoreClear[i])
						{
							clearOldPlayer(peX[i], peY[i], mapX, mapY);
							oneMoreClear[i]=0;
						}	
						peX[i] = eX[i], peY[i] = eY[i];
					}
				}
			}
			
			// Raffraichir la zone d'effaçage
			pBX=pX, pBY=pY;
			
			// Gestion du joystick
			dir = readJoystick();
			
			// Retourner au menu
			if (dir == 5)
			{
				menu = 1;
				mapLoad = true;
				
				fillup_save(data, numSave, life, mapX, mapY, pX, pY, 0); // Préparation de la sauvegarde "data"
				create_save(numSave,data);
			}
			
			// Attaquer
			if (dir == 6 && stamina >= staminaAttack)
			{
				attack(pX, pY, eX, eY, oneMoreClear, &numEn);
				stamina -= staminaAttack;
			}
			
			// Déplacement du personnage
			if (!isColliding(pX, pY, mapX, mapY, dir))
			{
				if (dir==1)
				{
					pX+=vit;
				}
				else if (dir==2)
				{
					pY+=vit;
				}
				else if (dir==3)
				{
					pX-=vit;
				}
				else if (dir==0)
				{
					pY-=vit;
				}
			}
			else
			{
				dir = 4;
			}
			
			// Changement de tableau
			if (pX >= 220)
			{
				mapY++;
				pX = 10;
				mapLoad = true;
			}
			else if (pX <= 5)
			{
				mapY--;
				pX = 215;
				mapLoad = true;
			}
			else if (pY >= 300)
			{
				mapX++;
				pY = 10;
				mapLoad = true;
			}
			else if (pY <= 5)
			{
				mapX--;
				pY = 295;
				mapLoad = true;
			}
			if (mapLoad)
			{
				numEn = 3;
				initEnemy(eX, eY, random);
			}
			
			// Affiche le joueur sur l'écran
			drawPlayer(pX, pY, dir);//dir
			
			if (iEn==0)
			{
				if (mapX<250 && (mapX > 0 || mapY > 0))
				{
					if (enFlag && hitReset == hitResetMax)
					{
						if (attackE(pX, pY, eX, eY, &life))
						{
							hitReset = 0;
						}
						enFlag = 0;
					}
					if (life == 0)
					{
						life = 3;
						menu = 1;
						mapLoad = 1;
						pX=30;
						pY=30;
						mapX=0;
						mapY=0;
						dying = 1;
						
						fillup_save(data, numSave, life, mapX, mapY, pX, pY, 0); // Préparation de la sauvegarde "data"
						create_save(numSave,data);
					}
					
					vit = (signed char)numEn;
					
					for (i=0; i<6; i++)
					{
						if (eX[i] > 0)
						{
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
							else
							{
								eY[i]>pY?eY[i]--:eY[i]++;
								eX[i]>pX?eX[i]--:eX[i]++;
							}
							
							drawPlayer(eX[i], eY[i], 20);
						}
					}
				}
				else
				{
					vit = 1;
				}
			}
		}
		else
		{
			touch_read();
			
			if (menu == 1)
			{
				if (mapLoad)
				{
					drawMap(250, 0, &mapLoad);
					drawMenu(menu);
				}
				
				// Play 
				// x : 1950 - 2300
				// y : 800 - 1670
				
				if (flagTouch && flagReset == 1)
				{
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
				}
			}
			else if (menu == 2)
			{
				if (mapLoad)
				{
					drawMap(250, 0, &mapLoad);
					drawMenu(menu);
				}
				
				if (flagTouch && flagReset == 1)
				{
					flagTouch = 0;
					
					
					// Save 2
					if (touch_x >= 1900 && touch_x <= 3200
							&& touch_y >= 2650 && touch_y <= 3500)
					{
						mapLoad = true;
						menu = -1;
						numSave = 2;
						if (check_save(2))
						{
							load_save(numSave, data);
							filldown_save(data, numSave, &life, &mapX, &mapY, &pX, &pY, 0); // Chargement de la sauvegarde "data"
						}
						else
						{
							reset(&mapX, &mapY, &pX, &pY);
						}
					}
					
					// Save 1
					if (touch_x >= 1900 && touch_x <= 3200
							&& touch_y >= 1650 && touch_y <= 2650)
					{
						mapLoad = true;
						menu = -1;
						numSave = 1;
						if (check_save(1))
						{
							load_save(numSave, data);
							filldown_save(data, numSave, &life, &mapX, &mapY, &pX, &pY, 0); // Chargement de la sauvegarde "data"
						}
						else
						{
							reset(&mapX, &mapY, &pX, &pY);
						}
					}
					
					// Save 0
					if (touch_x >= 1900 && touch_x <= 3200
							&& touch_y >= 650 && touch_y <= 1650)
					{
						mapLoad = true;
						menu = -1;
						numSave = 0;
						if (check_save(0))
						{
							load_save(numSave, data);
							filldown_save(data, numSave, &life, &mapX, &mapY, &pX, &pY, 0); // Chargement de la sauvegarde "data"
						}
						else
						{
							reset(&mapX, &mapY, &pX, &pY);
						}
					}
				}
			}
			else if (menu == 0)
			{
				if (mapLoad)
				{
					drawMap(250, 0, &mapLoad);
					drawMenu(menu);
				}
				
				if (flagTouch && flagReset == 1)
				{
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
				}
			}
			else
			{
				//menu 3 et 4
				if (mapLoad)
				{
					dessiner_rect(0,0,240,320,0,1,Black, Black);
					mapLoad = 0;
					drawMenu(menu);
				}
				if (flagTouch && flagReset == 1 && touch_x>=10)
				{
					flagTouch = 0;
					mapLoad = true;
					menu = 0;
					flagReset = 0;
				}
			}
		}
	}
}

//---------------------------------------------------------------------------------------------
#ifdef  DEBUG
void check_failed(uint8_t *file, uint32_t line) {while(1);}
#endif
