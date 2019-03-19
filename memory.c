//===========================================================//
// Imports
//===========================================================//
#include "stdint.h"
#include "lpc17xx_i2c.h"
//===========================================================//
// Function: Define
//===========================================================//
#define MAX_BUFFER 25
//===========================================================//
// Function: Prototypes
//===========================================================//

void init_i2c_eeprom()
{
	I2C_Init(LPC_I2C0, 1000000);
	I2C_Cmd (LPC_I2C0, ENABLE);
}

void i2c_eeprom_write(uint16_t addr, uint8_t* data, int length)
{
	// Declarations //
	I2C_M_SETUP_Type transferCfg;
	uint8_t buffer[MAX_BUFFER];
	int i;
	
	// Buffer //
	buffer[0]=addr&0xFF;
	
	// Boucle
	for (i=1;i<length+1;i++)
	{
		buffer[i]=data[i-1];
	}
	
	// Configuration de *transferCfg //
	
	/* Addresse esclave en 7bit
	   0xA0 correspond � 1010, le d�calage de 1 correspond � l'ecriture en 7bits 1010xxx
	   addr&0x700 est un mask sur l'element suivant et nous donne la page, decalage de 8 pour qu'ils deviennent les 3bits de fin xxx??? */
  transferCfg.sl_addr7bit=(0xA0>>1)|(addr&0x700)>>8;
	
	/* Pointer to Transmit data - NULL if data transmit is not used
     will transfer the whole tab know as buffer*/
  transferCfg.tx_data=buffer;
	
	// Transmit data length - 0 if data transmit is not used //
  transferCfg.tx_length=length+1;

	// Pointer to Receive data - NULL if data receive is not used //
  transferCfg.rx_data=NULL;
	
	// Receive data length - 0 if data receive is not used //
  transferCfg.rx_length=0;

	// Max Re-Transmission value //
	transferCfg.retransmissions_max=1;
	
	// Op�rations //
	I2C_MasterTransferData(LPC_I2C0,&transferCfg,I2C_TRANSFER_POLLING);

}

void i2c_eeprom_read(uint16_t addr, uint8_t* data, int length)
{
	// Declaration //
	I2C_M_SETUP_Type transferCfg;
	uint8_t addresse=addr&0xFF;
	// *transferCfg configuration //
	
	/* Slave address in 7bit mode
	   0xA0 correspond � 1010, le d�calage de 1 correspond � l'ecriture en 7bits 1010xxx
	   addr&0x700 est un mask sur l'element suivant et nous donne la page, decalage de 8 pour qu'ils deviennent les 3bits de fin xxx??? */
  transferCfg.sl_addr7bit=(0xA0>>1)|(addr&0x700)>>8;
	
	/* Pointer to Transmit data - NULL if data transmit is not used
     will transfer the whole tab know as buffer*/
  transferCfg.tx_data=&addresse;
	
	// Transmit data length - 0 if data transmit is not used //
  transferCfg.tx_length=1;

	// Pointer to Receive data - NULL if data receive is not used //
  transferCfg.rx_data=data;
	
	// Receive data length - 0 if data receive is not used //
  transferCfg.rx_length=length+1;

	transferCfg.retransmissions_max=1;
	// Op�rations //
	I2C_MasterTransferData(LPC_I2C0,&transferCfg,I2C_TRANSFER_POLLING);

}

void clean_memory()
{
		int i;
		uint8_t clef[12]={'m','a','r','c','d','i','v','i','t','o','n','y'};
		uint8_t C0[1]={0};
		i2c_eeprom_write(0, clef, 12);
		for (i=12;i<2048;i++)
		{
				i2c_eeprom_write(i, C0,1);
		}
}
int check_save(int num)
{
	uint8_t clefcheck[12];
	i2c_eeprom_read(20*num,clefcheck,12);
	if(
		clefcheck[0]=='m'
		&&
		clefcheck[1]=='a'
		&&
		clefcheck[2]=='r'
		&&
		clefcheck[3]=='c'
		&&
		clefcheck[4]=='d'
		&&
		clefcheck[5]=='i'
		&&
		clefcheck[6]=='v'
		&&
		clefcheck[7]=='i'
		&&
		clefcheck[8]=='t'
		&&
		clefcheck[9]=='o'
		&&
		clefcheck[10]=='n'
		&&
		clefcheck[11]=='y'
		)
		{return 0;}
	else
		{return 1;}
}

int load_save(int num, uint8_t* Current_save)
{
	if (num<3 && check_save(num)==0)
	{
		num--;
		i2c_eeprom_read(20*num, Current_save,20);
		return 0;
	}
	else
	{return 0;}
}

void create_save(int num, uint8_t* Current_save)
{
	i2c_eeprom_write(20*(num+3), Current_save,20); //creation of a backup
	i2c_eeprom_write(20*num, Current_save,20); //creation of a backup
}
void restaure_backup(int num)
{
	uint8_t BK_save[20];
	i2c_eeprom_read(20*(num+3), BK_save,20);
	create_save(num, BK_save);	
}
void fillup_save(uint8_t* Buffer, int num, int life, unsigned int Map_x, unsigned int Map_y, unsigned int Location_x, unsigned int Location_y,unsigned int score)
{
	Buffer[0]='m';
	Buffer[1]='a';
	Buffer[2]='r';
	Buffer[3]='c';
	Buffer[4]='d';
	Buffer[5]='i';
	Buffer[6]='v';
	Buffer[7]='i';
	Buffer[8]='t';
	Buffer[9]='o';
	Buffer[10]='n';
	Buffer[11]='y';
	Buffer[12]=(uint8_t)num;
	Buffer[13]=(uint8_t)life;
	Buffer[14]=(uint8_t)Map_x;
	Buffer[15]=(uint8_t)Map_y;
	Buffer[16]=(uint8_t)Location_x;
	Buffer[17]=(uint8_t)Location_y;
	Buffer[18]=(uint8_t)score;
	Buffer[19]='x';
}
int check_memory()
{
	uint8_t clefcheck[12];
	i2c_eeprom_read(2037,clefcheck,10);
	if(
		clefcheck[0]=='f'
		&&
		clefcheck[1]=='l'
		&&
		clefcheck[2]=='u'
		&&
		clefcheck[3]=='f'
		&&
		clefcheck[4]=='f'
		&&
		clefcheck[5]=='i'
		&&
		clefcheck[6]=='t'
		&&
		clefcheck[7]=='t'
		&&
		clefcheck[8]=='e'
		&&
		clefcheck[9]=='n'
		)
		{return 0;}
	else
		{return 1;}
}

void create_gamekey()
{
	uint8_t GK[10];
	GK[0]='f';
	GK[1]='l';
	GK[2]='u';
	GK[3]='f';
	GK[4]='f';
	GK[5]='i';
	GK[6]='t';
	GK[7]='t';
	GK[8]='e';
	GK[9]='n';
	i2c_eeprom_write(2037, GK, 10);
}