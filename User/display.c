#include "display.h"

// Defined in .c to avoid defining variables multiple times
#include "texture.h"

//=======================
// Affichage des menus
//=======================
//char text[20];
char text1[5];

void drawMenu(char m)
{
	unsigned short color = White;
	
	if (m == 1)
	{
		/*sprintf(text,"klmnopqrstuvw");
		drawText(text, 1, TSIZE*2, (unsigned short)(320-12*TSIZE/1)/2);
		sprintf(text,"abcdefghij");
		drawText(text, 1, TSIZE*4, (unsigned short)(320-9*TSIZE/1)/2);*/
		
		drawText("fluffiten's", 1, TSIZE*1, (unsigned short)(320-11*TSIZE/1)/2);
		drawText("adventure", 1, TSIZE*2, (unsigned short)(320-9*TSIZE/1)/2);
		
		
		drawText("play", 1, TSIZE*5.5, (unsigned short) 320-TSIZE*2-TSIZE*4);
		drawText("extra", 1, TSIZE*8.5, (unsigned short) 320-TSIZE*2-TSIZE*5);
		
		drawPlayer((unsigned short) TSIZE*5, TSIZE*2, 10);
	}
	else if (m == 2)
	{
		drawText("choose your", 1, TSIZE*1, (unsigned short)(320-11*TSIZE/1)/2);
		drawText("save", 1, TSIZE*2, (unsigned short)(320-4*TSIZE/1)/2);
		
		if (check_save(0))
		{
			color = getColor(9);
			sprintf(text1,"load");
		}
		else
		{
			color = getColor(4);
			sprintf(text1,"new");
		}
		dessiner_rect(5.5*TSIZE,(16-3-2.5)*TSIZE, 4*TSIZE, 4*TSIZE, 0, 1, color, color);
		drawText("a", 1, 7*TSIZE,(12)*TSIZE);
		drawText(text1, 1, 8.5*TSIZE,(text1[0]=='l'?10.5:11)*TSIZE);
		
		if (check_save(1))
		{
			color = getColor(9);
			sprintf(text1,"load");
		}
		else
		{
			color = getColor(4);
			sprintf(text1,"new");
		}
		dessiner_rect(5.5*TSIZE,(16-3*2-2-2)*TSIZE, 4*TSIZE, 4*TSIZE, 0, 1, color, color);
		drawText("b", 1, 7*TSIZE,(7.5)*TSIZE);
		drawText(text1, 1, 8.5*TSIZE,(text1[0]=='l'?6:6.5)*TSIZE);
		
		if (check_save(2))
		{
			color = getColor(9);
			sprintf(text1,"load");
		}
		else
		{
			color = getColor(4);
			sprintf(text1,"new");
		}
		dessiner_rect(5.5*TSIZE,(16-3*3-2-3.5)*TSIZE, 4*TSIZE, 4*TSIZE, 0, 1, color, color);
		drawText("c", 1, 7*TSIZE,(3)*TSIZE);
		drawText(text1, 1, 8.5*TSIZE,(text1[0]=='l'?1.5:2)*TSIZE);
		
	}
	else if (m == 0)
	{
		drawText("extra", 1, TSIZE*1.5, (unsigned short)(320-5*TSIZE/1)/2);
		
		drawText("tutorial", 1, TSIZE*5.5, (unsigned short) 320-TSIZE*2-TSIZE*8);
		drawText("story", 1, TSIZE*8.5, (unsigned short) 320-TSIZE*2-TSIZE*5);
		drawText("back", 1, TSIZE*8.5, (unsigned short) TSIZE*2);		
	}
	else if (m == 3)
	{
		drawText("tutorial", 1, TSIZE*0, (unsigned short)(320-8*TSIZE/1)/2);
		
		drawText("read readme.txt", 2, TSIZE*6, TSIZE*4.25);
		/*drawText("use the joystick to move", 2, TSIZE*2, TSIZE*3.5);
		drawText("use the joystick click to", 2, TSIZE*4, TSIZE*3);
		drawText("attack", 2, TSIZE*5, TSIZE*12.5);
		drawText("you can only attack if your", 2, TSIZE*6, TSIZE*2);
		drawText("stamina is full ~ in blue", 2, TSIZE*7, TSIZE*3);
		
		drawText("you've only some life so stay", 2, TSIZE*9, TSIZE*1);
		drawText("safe ~ left up corner", 2, TSIZE*10, TSIZE*5);*/
	}
	else if (m == 4)
	{
		drawText("story", 1, TSIZE*0, (unsigned short)(320-5*TSIZE/1)/2);
		
		drawText("fluffy is a fluffitten.", 2, TSIZE*2, TSIZE*4.5);
		drawText("a devine race born from the", 2, TSIZE*3, TSIZE*2.5);
		drawText("witch of madness long ago in", 2, TSIZE*4, TSIZE*2);
		drawText("this sorrowful and maimed world.", 2, TSIZE*5, TSIZE*0);
		
		drawText("in this day and age the world", 2, TSIZE*7, TSIZE*1.5);
		drawText("is starting to darn himself and", 2, TSIZE*8, TSIZE*0.5);
		drawText("reclaim its peace. nonetheless", 2, TSIZE*9, TSIZE*1);
		drawText("fluffy's duty is to protect the", 2, TSIZE*10, TSIZE*0.5);
		drawText("fluffillage.", 2, TSIZE*11, TSIZE*10);
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
					letterCode = unCompressLetter((a[(*s)-97][j*l][(short)(i*l)/4]>>(((i*l)*2)%8))&3);
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
						letterCode = unCompressLetter((a[26][j*l][(short)i*l/4]>>(((i*l)*2)%8))&3);
						if (letterCode != 250)
						{
							lcd_SetCursor(x+j,y+k*TSIZE/l+i);
							rw_data_prepare();
							write_data(getColor(letterCode));
						}
					}
					if (*s == 46)
					{
						letterCode = unCompressLetter((a[27][j*l][(short)i*l/4]>>(((i*l)*2)%8))&3);
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

//
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
			color = 0x8800;
			break;
		case 14:
			color = 0xedae;
			break;
		case 15:
			color = 0x98c1;
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

unsigned short getMap(unsigned char x, unsigned char y, unsigned char j, unsigned char i)
{
	if (x==0 && y==0)
		return (t00[j][(short)i/4]>>((i*2)%8))&3;
		//return t00[j][i];
	else if (x==1 && y==0)
		return (t10[j][(short)i/4]>>((i*2)%8))&3;
		//return t10[j][i];
	else if (x==0 && y==1)
		return (t01[j][(short)i/4]>>((i*2)%8))&3;
		//return t01[j][i];
	else if (x==250)
		return (tMenu[j][(short)i/4]>>((i*2)%8))&3;
		//return tMenu[j][i];
	
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

//
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
						if (pRight[j][PSIZE-i-1] != 250)
						{
							lcd_SetCursor(x+j,y+i);
							rw_data_prepare();
							write_data(getColor(pRight[j][PSIZE-i-1]));
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
	else if (d == 20)
	{
		for(i=0; i<PSIZE; i++)
		{
			for(j=0; j<PSIZE; j++)
			{
				if (en[j][i] != 250)
				{
					lcd_SetCursor(x+j,y+i);
					rw_data_prepare();
					write_data(getColor(en[j][i]));
				}
			}
		}
	}
	else if (d == 30 || d == 31)
	{
		for(i=0; i<TSIZE; i++)
		{
			for(j=0; j<TSIZE; j++)
			{
				if ((d==30?mouton[j][i]:demouton[j][i]) != 250)
				{
					lcd_SetCursor(x+j,y+i);
					rw_data_prepare();
					write_data(getColor(d==30?mouton[j][i]:demouton[j][i]));
				}
			}
		}
	}
}


void clearOldPlayer(unsigned short x, unsigned short y, unsigned char mx, unsigned char my)
{
	if ((x-1)/TSIZE != 0 || ((y-1)/TSIZE > 3 &&  (y-1)/TSIZE < 11))
	{
		drawTexture(floor((x-1)/TSIZE)*TSIZE, floor((y-1)/TSIZE)*TSIZE, getMap(mx,my,floor((x-1)/TSIZE),floor((y-1)/TSIZE)));
	}
	drawTexture(floor((x+PSIZE+1)/TSIZE)*TSIZE, floor((y-1)/TSIZE)*TSIZE, getMap(mx,my,floor((x+PSIZE+1)/TSIZE),floor((y-1)/TSIZE)));
	if ((x-1)/TSIZE != 0 || ((y-1)/TSIZE > 3 &&  (y-1)/TSIZE < 11))
	{
		drawTexture(floor((x-1)/TSIZE)*TSIZE, floor((y+PSIZE+1)/TSIZE)*TSIZE, getMap(mx,my,floor((x-1)/TSIZE),floor((y+PSIZE+1)/TSIZE)));
	}
	drawTexture(floor((x+PSIZE+1)/TSIZE)*TSIZE, floor((y+PSIZE+1)/TSIZE)*TSIZE, getMap(mx,my,floor((x+PSIZE+1)/TSIZE),floor((y+PSIZE+1)/TSIZE)));
}


//
//=======================
// Gestion personnage
//=======================

char readJoystick()
{
	if (!(GPIO_ReadValue(2) & (1<<11)))
	{
		return 6;
	}
	
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
	else if (!(GPIO_ReadValue(2) & (1<<10)))
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
			if (getMap(mx,my,floor((x+PSIZE+3)/TSIZE),floor((y+3)/TSIZE))==0 && getMap(mx,my,floor((x+PSIZE+3)/TSIZE),floor((y+PSIZE-3)/TSIZE))==0)
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
			if (getMap(mx,my,floor((x-3)/TSIZE),floor((y+3)/TSIZE))==0 && getMap(mx,my,floor((x-3)/TSIZE),floor((y+PSIZE-3)/TSIZE))==0)
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

void attack(unsigned short x, unsigned short y, short eX[6], short eY[6], char clearEn[6], float* eN)
{
	char i=0;
	
	for(i=0; i<6; i++)
	{
		if (sqrt((x-eX[i])*(x-eX[i])+(y-eY[i])*(y-eY[i]))<=30)
		{
			eX[i] = -100;
			eY[i] = -100;
			
			clearEn[i] = 1;
			
			if (*eN > 1)
			{
				(*eN) -= 0.2;
			}
		}
	}
}

//
//========================================
// Gestion enemies
//========================================

void initEnemy(short x[6], short y[6], unsigned int r)
{
	char i;
	srand(r);
	
	for (i=0; i<6; i++)
	{
		x[i] = rand()%160+40;
		y[i] = rand()%240+40;
	}
}

char attackE(unsigned short x, unsigned short y, short eX[6], short eY[6], unsigned char * l)
{
	char i;
	char reset = 1;
	char hit = 0;
	
	for (i=0; i<6; i++)
	{
		if (sqrt((x-eX[i])*(x-eX[i])+(y-eY[i])*(y-eY[i]))<=20)
		{
			if ((*l)!= 0 && reset)
			{
				reset = 0;
				(*l)--;
				hit = 1;
			}
		}
	}
	
	return hit;
}

//
//========================================
// Fin
//========================================
