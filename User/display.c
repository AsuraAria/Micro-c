#include "display.h"
#include "memory.h"
 
// Defined in .c to avoid defining variables multiple times
#include "texture.h"

//=======================
// Affichage des menus
//=======================
char text[30];

void drawMenu(char m)
{
	unsigned short color = White;
	
	if (m == 1)
	{
		/*sprintf(text,"klmnopqrstuvw");
		drawText(text, 1, TSIZE*2, (unsigned int)(320-12*TSIZE/1)/2);
		sprintf(text,"abcdefghij");
		drawText(text, 1, TSIZE*4, (unsigned int)(320-9*TSIZE/1)/2);*/
		
		
		sprintf(text,"fluffiten's");
		drawText(text, 1, TSIZE*1, (unsigned int)(320-11*TSIZE/1)/2);
		sprintf(text,"adventure");
		drawText(text, 1, TSIZE*2, (unsigned int)(320-9*TSIZE/1)/2);
		
		
		sprintf(text,"play");
		drawText(text, 1, TSIZE*5.5, (unsigned int) 320-TSIZE*2-TSIZE*4);
		sprintf(text,"extra");
		drawText(text, 1, TSIZE*8.5, (unsigned int) 320-TSIZE*2-TSIZE*5);
		
		drawPlayer((unsigned int) TSIZE*5, TSIZE*2, 10);
	}
	else if (m == 2)
	{
		sprintf(text,"choose your");
		drawText(text, 1, TSIZE*1, (unsigned int)(320-11*TSIZE/1)/2);
		sprintf(text,"save");
		drawText(text, 1, TSIZE*2, (unsigned int)(320-4*TSIZE/1)/2);
		
		
		if (check_save(0))
			color = White;
		else
			color = Black;
		dessiner_rect(6*TSIZE,(16-3-2)*TSIZE, 3*TSIZE, 3*TSIZE, 0, 1, color, color);
		
		if (check_save(1))
			color = White;
		else
			color = Black;
		dessiner_rect(6*TSIZE,(16-3*2-2-1.5)*TSIZE, 3*TSIZE, 3*TSIZE, 0, 1, color, color);
		
		if (check_save(2))
			color = White;
		else
			color = Black;
		dessiner_rect(6*TSIZE,(16-3*3-2-3)*TSIZE, 3*TSIZE, 3*TSIZE, 0, 1, color, color);
		
	}
}

// 97-122 : a-z

char unCompressLetter(char v)
{
	switch(v)
	{
		case 0:
			return 8;
		case 1:
			return 7;
		case 2:
			return 12;
		case 3:
			return 250;
	}
}

void drawText(char*s, char l, unsigned short x, unsigned short y)
{
	short i,j,k;
	short len = 0;
	char letterCode = 0;
	
	while (*s)
	{
		len ++;
		s++;
	}
	s--;
	
	for (k=0;k<len;k++)
	{
		for(i=0; i<TSIZE/l; i++)
		{
			lcd_SetCursor(x,y+k*TSIZE/l+i);
			rw_data_prepare();
			
			for(j=0; j<TSIZE/l; j++)
			{
				//sprintf(chaine,"%d - %d ",touch_x , touch_y);
				//LCD_write_english_string(30,30,chaine,White,Blue);
				
				if (*s >= 97 && *s <=122)
				{
					letterCode = unCompressLetter((a[(*s)-97][j][(short)i/4]>>((i*2)%8))&3);
					if (letterCode != 250)
					{
						lcd_SetCursor(x+j,y+k*TSIZE/l+i);
						rw_data_prepare();
						write_data(getColor(letterCode));
					}
				}
				else
				{
					if (*s == 39)
					{
						letterCode = unCompressLetter((a[26][j][(short)i/4]>>((i*2)%8))&3);
						if (letterCode != 250)
						{
							lcd_SetCursor(x+j,y+k*TSIZE/l+i);
							rw_data_prepare();
							write_data(getColor(letterCode));
						}
					}
					if (*s == 126)
					{
						letterCode = unCompressLetter((a[27][j][(short)i/4]>>((i*2)%8))&3);
						if (letterCode != 250)
						{
							lcd_SetCursor(x+j,y+k*TSIZE/l+i);
							rw_data_prepare();
							write_data(getColor(letterCode));
						}
					}
				}
			}
		}
		s--;
	}
}

//=======================
// Affichage des maps
//=======================

unsigned short getColor(unsigned char c)
{
	unsigned short color;
	
	switch(c)
	{
		case 0:
			color = 0x9f80;
			break;
		case 1:
			color = 0x34cc;
			break;
		case 2:
			color = 0x2de2;
			break;
		case 3:
			color = 0x2c46;
			break;
		case 4:
			color = 0xb596;
			break;
		case 5:
			color = 0x8c71;
			break;
		case 6:
			color = 0x8410;
			break;
		case 7:
			color = 0x0000;
			break;
		case 8:
			color = 0xffff;
			break;
		case 9:
			color = 0x98ba;
			break;
		case 10:
			color = 0xf800;
			break;
		case 11:
			color = 0xc618;
			break;
		case 12:
			color = 0x9492;
			break;
		case 13:
			color = 0x4a69;
			break;
	}
	
	return color; 
}

void drawTexture(unsigned short x, unsigned short y, char tex)
{
	unsigned char i,j;
	unsigned char c;
	
	for(i=0; i<TSIZE; i++)
	{
		lcd_SetCursor(x,y+i);
		rw_data_prepare();
		
		for(j=0; j<TSIZE; j++)
		{
			switch(tex)
			{
				case 0:
					write_data(getColor((grass[j][(short)i/4]>>((i*2)%8))&3));
					//write_data(getColor(grass[j][i]));
					break;
				case 1:
					write_data(getColor((bush[j][(short)i/4]>>((i*2)%8))&3));
					//write_data(getColor(bush[j][i]));
					break;
				case 2:
					c = (stone[j][(short)i/4]>>((i*2)%8))&3;
					write_data(getColor(c!=0?c+3:c));
					//write_data(getColor(stone[j][i]));
					break;
				case 7:
					write_data(getColor(7));
					break;
				case 8:
					write_data(getColor(8));
					break;
			}
		}
	}
}

unsigned short getMap(unsigned char x, unsigned char y, unsigned short i, unsigned short j)
{
	if (x==0 && y==0)
		return t00[i][j];
	else if (x==1 && y==0)
		return t10[i][j];
	else if (x==0 && y==1)
		return t01[i][j];
	else if (x==250)
		return tMenu[i][j];
	
	return 0;
}

void drawMap(unsigned char x, unsigned char y, bool * notDone)
{
	unsigned char i,j;
	
	for(i=0; i<MSIZEY; i++)
	{
		for(j=0; j<MSIZEX; j++)
		{
			drawTexture(j*TSIZE, i*TSIZE, getMap(x,y,j,i));  
		}
	}
	
	*notDone = false;
}

//=======================
// Affichage du personnage
//=======================

void drawPlayer(unsigned short x, unsigned short y, unsigned char d)
{
	int i,j;
	
	if (d <= 5)
	{
		for(i=0; i<PSIZE; i++)
		{
			//lcd_SetCursor(x,y+i);
			//rw_data_prepare();
			
			for(j=0; j<PSIZE; j++)
			{
				switch(d)
				{
					case 1:
						if (pDown[j][i] != 250)
						{
							lcd_SetCursor(x+j,y+i);
							rw_data_prepare();
							write_data(getColor(pDown[j][i]));
						}
						break;
					case 0:
						if (pLeft[j][i] != 250)
						{
							lcd_SetCursor(x+j,y+i);
							rw_data_prepare();
							write_data(getColor(pLeft[j][i]));
						}
						break;
					case 3:
						if (pUp[j][i] != 250)
						{
							lcd_SetCursor(x+j,y+i);
							rw_data_prepare();
							write_data(getColor(pUp[j][i]));
						}
						break;
					case 2:
						if (pRight[j][i] != 250)
						{
							lcd_SetCursor(x+j,y+i);
							rw_data_prepare();
							write_data(getColor(pRight[j][i]));
						}
						break;
					case 4:
						if (pDown[j][i] != 250)
						{
							lcd_SetCursor(x+j,y+i);
							rw_data_prepare();
							write_data(getColor(pDown[j][i]));
						}
						break;
					default:
						break;
				}
			}
		}
	}
	else if (d == 10)
	{
		for(i=0; i<PSIZE*6; i++)
		{
			for(j=0; j<PSIZE*6; j++)
			{
				if (pDown[(int)(j/6)][(int)(i/6)] != 250)
				{
					lcd_SetCursor(x+j,y+i);
					rw_data_prepare();
					write_data(getColor(pDown[(int)(j/6)][(int)(i/6)]));
				}
			}
		}
	}
}


void clearOldPlayer(unsigned short x, unsigned short y, unsigned char mx, unsigned char my)
{
	drawTexture(floor((x-1)/TSIZE)*TSIZE, floor((y-1)/TSIZE)*TSIZE, getMap(mx,my,floor((x-1)/TSIZE),floor((y-1)/TSIZE)));
	drawTexture(floor((x+PSIZE+1)/TSIZE)*TSIZE, floor((y-1)/TSIZE)*TSIZE, getMap(mx,my,floor((x+PSIZE+1)/TSIZE),floor((y-1)/TSIZE)));
	drawTexture(floor((x-1)/TSIZE)*TSIZE, floor((y+PSIZE+1)/TSIZE)*TSIZE, getMap(mx,my,floor((x-1)/TSIZE),floor((y+PSIZE+1)/TSIZE)));
	drawTexture(floor((x+PSIZE+1)/TSIZE)*TSIZE, floor((y+PSIZE+1)/TSIZE)*TSIZE, getMap(mx,my,floor((x+PSIZE+1)/TSIZE),floor((y+PSIZE+1)/TSIZE)));
}


//=======================
// Affichage des ennemis
//=======================



//=======================
// Déplacement personnage
//=======================

char readJoystick()
{
	if (!(GPIO_ReadValue(2) & (1<<12)))
	{
		return 0;
	}
	else if (!(GPIO_ReadValue(1) & (1<<21)))
	{
		return 1;
	}
	else if (!(GPIO_ReadValue(2) & (1<<13)))
	{
		return 2;
	}
	else if (!(GPIO_ReadValue(2) & (1<<8)))
	{
		return 3;
	}
	else if (!(GPIO_ReadValue(2) & (1<<11)))
	{
		return 5;
	}
	else
	{
		return 4;
	}
}

bool isColliding(unsigned short x, unsigned short y, unsigned char mx, unsigned char my, char d)
{
	switch(d)
	{
		case 0:
			if (getMap(mx,my,floor((x+3)/TSIZE),floor((y-1)/TSIZE))==0 && getMap(mx,my,floor((x+PSIZE-3)/TSIZE),floor((y-1)/TSIZE))==0)
			{
				return false;
			}
			else
			{
				return true;
			}
		case 1:
			if (getMap(mx,my,floor((x+PSIZE+1)/TSIZE),floor((y+3)/TSIZE))==0 && getMap(mx,my,floor((x+PSIZE+1)/TSIZE),floor((y+PSIZE-3)/TSIZE))==0)
			{
				return false;
			}
			else
			{
				return true;
			}
		case 2:
			if (getMap(mx,my,floor((x+3)/TSIZE),floor((y+PSIZE+1)/TSIZE))==0 && getMap(mx,my,floor((x+PSIZE-3)/TSIZE),floor((y+PSIZE+1)/TSIZE))==0)
			{
				return false;
			}
			else
			{
				return true;
			}
		case 3:
			if (getMap(mx,my,floor((x-1)/TSIZE),floor((y+3)/TSIZE))==0 && getMap(mx,my,floor((x-1)/TSIZE),floor((y+PSIZE-3)/TSIZE))==0)
			{
				return false;
			}
			else
			{
				return true;
			}
		default:
			return true;
	}
}

//========================================
// Fin
//========================================
