//===========================================================//
// Imports
//===========================================================//
#include "stdint.h"
//===========================================================//
// Function: Prototypes
//===========================================================//

void init_i2c_eeprom();
/*********************************************************************//**
 * @brief			Set I2C initialisation and exchange
 * @param[in]	None
 * @return		None
 *
 * Note:
 * - All remaining bits that are not affected in bitValue (value '0')
 * will not be effected by this function.
 **********************************************************************/

void i2c_eeprom_write(uint16_t, uint8_t*, int);
/*********************************************************************//**
 * @brief			Write in memory
 * @param[in]	uint16_t, write address
 *						uint8_t*, data address
 *						int, number of cases to write
 * @return		Aknowledge
 *
 * Note:
 * - None.
 **********************************************************************/

void i2c_eeprom_read(uint16_t, uint8_t*, int);
/*********************************************************************//**
 * @brief			Read in memory
 * @param[in]	uint16_t, read address
 *						uint8_t*, read data address
 *						int, number of case to read
 * @return		Aknowledge
 *
 * Note:
 * - None.
 **********************************************************************/

void clean_memory();
/*********************************************************************//**
 * @brief			Re-initialisation of memory
 * @param[in]	None
 * @return		None
 *
 * Note:
 * - Self explanatory.
 **********************************************************************/

void create_gamekey();
/*********************************************************************//**
 * @brief			Create gamekey
 * @param[in]	None
 * @return		None
 *
 * Note:
 * - None.
 **********************************************************************/

int check_memory();
/*********************************************************************//**
 * @brief			Check gamekey
 * @param[in]	None
 * @return		int; 0 for succes, 1 for error
 *
 * Note:
 * - None.
 **********************************************************************/

void fillup_save(uint8_t*, char, unsigned char, unsigned char, unsigned char, unsigned short, unsigned short, char);
/*********************************************************************//**
 * @brief			fill structure with wanted parameter
 * @param[in]	uint8_t*, buffer pointer
 *						char, save num
 *						unsigned char, life
 *						unsigned char, Map_x
 *						unsigned char, Map_y
 *						unsigne short, Location_x
 *						unsigne short, Location_y
 *						char, score
 * @return		None
 *
 * Note:
 * - None
 **********************************************************************/

void filldown_save(uint8_t*, char, unsigned char *,unsigned char*,unsigned char*, unsigned short *, unsigned short *,char *);
/*********************************************************************//**
 * @brief			fill local structure with save
 * @param[in]	uint8_t*, buffer pointer
 *						char, save num
 *						unsigned char, life
 *						unsigned char, Map_x
 *						unsigned char, Map_y
 *						unsigne short, Location_x
 *						unsigne short, Location_y
 *						char, score
 * @return		None
 *
 * Note:
 * - None
 **********************************************************************/

void create_save(char, uint8_t*);
/*********************************************************************//**
 * @brief			Replace existing save by backup save
 * @param[in]	char, save number
 *						uint8_t*, backup pointer
 * @return		None
 *
 * Note:
 * - None
 **********************************************************************/

int check_save(char);
/*********************************************************************//**
 * @brief			Check key
 * @param[in]	char, save number
 * @return		int; 0 for succes, 1 for error
 *
 * Note:
 * - None.
 **********************************************************************/

void load_save(char, uint8_t*);
/*********************************************************************//**
 * @brief			Load a save if uncorrupted
 * @param[in]	char, save number
 * @return		int; 0 for succes, 1 for error
 *
 * Note:
 * - If an error is seen no loading will be done.
 **********************************************************************/

void restaure_backup(char);
/*********************************************************************//**
 * @brief			Replace existing save by backup save
 * @param[in]	char, save number
 * @return		None
 *
 * Note:
 * - Use create_save.
 **********************************************************************/

//========================================
// Fin
//========================================
