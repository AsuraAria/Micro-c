//===========================================================//
// Projet Micro - INFO1 - ENSSAT - S2 2018							 //
//===========================================================//
// File                : Programme de départ
// Hardware Environment: Open1768	
// Build Environment   : Keil µVision
//===========================================================//

#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_timer.h"
#include "touch\ili_lcd_general.h"
#include "touch\lcd_api.h"
#include "affichagelcd.h"
#include "touch\touch_panel.h"


#include "globaldec.h" // fichier contenant toutes les déclarations de variables globales
#include <stdio.h>

void pseudoSleep(int s)
{
	int i = 0;
	while (i< s*10000000)
		i++;
}

void pinInit()
{
		FIO_SetDir(0, (1<<0)|(1<<1), 1);
		FIO_SetMask(0, (1<<0)|(1<<1), 1);
		FIO_SetValue(0, (1<<0));
		pseudoSleep(5);
		FIO_SetValue(0, (1<<0));
}

//===========================================================//
// Function: Main
//===========================================================//
int main(void)
{	  
	  int n; 
		int x=0, y=0, d=0;
		int px=0, py=0;
		int tx = 20, ty = 20;
	
	  // Init(); // init variable globales et pinsel son et IR => à faire
	  lcd_Initializtion(); // init pinsel ecran et init LCD
		// affichage sur l'écran d'un exemple de 4 carrés de couleur et d'une chaine de caractère
	  n=sprintf(chaine,"Ceci est un exemple      ");
	  LCD_write_english_string (32,30,chaine,White,Blue);
	  dessiner_rect(10,60,110,110,2,1,Black,Blue);
	  dessiner_rect(120,60,110,110,2,1,Black,Green);
	  dessiner_rect(10,170,110,110,2,1,Black,Blue);
	  dessiner_rect(120,170,110,110,2,1,Black,Red);
		
	  touch_init(); // init pinsel tactile et init tactile 
	  
		dessiner_rect(0,0,240,360,0,1,Black,Black);
	
    while(1)
		{
				dessiner_rect(px,py,tx,ty,0,1,Black,Black);
				dessiner_rect(x,y,tx,ty,0,1,Black,Yellow);
				
				px = x, py = y;
				
				//320*240
				switch(d)
				{
					case 0:
						x++;
						y++;
						if (x >= 230-tx)	d = (d+1)%4;
						if (y >= 310-ty)	d = (d+3)%4;
						break;
					case 1:
						x--;
						y++;
						if (y >= 310-ty)	d = (d+1)%4;
						if (x <= 10)	d = (d+3)%4;
						break;
					case 2:
						x--;
						y--;
						if (x <= 10)	d = (d+1)%4;
						if (y <= 10)	d = (d+3)%4;
						break;
					case 3:
						x++;
						y--;
						if (y <= 10)	d = (d+1)%4;
						if (x >= 230-tx)	d = (d+3)%4;
						break;
					default:
						break;
				}
		}
}

//---------------------------------------------------------------------------------------------	
#ifdef  DEBUG
void check_failed(uint8_t *file, uint32_t line) {while(1);}
#endif
