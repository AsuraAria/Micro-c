
//==========================================
//	Prototype
//==========================================

// Procédure d'initialisation des pins (Led0 Haut-Parleur et Mémoire)

void pin_Configuration();

// Procédure permettant de jouer une musique 

void pseudoSleep(unsigned int);	// Pseudo sleep (avec un while)
void note(unsigned int); // Fonctions activant le buzzer à une fréquence donnée

//==========================================
//	Fonction(s)
//==========================================

void pin_Configuration()
{
	// Initialisation des structures pour la mémoire
	PINSEL_CFG_Type memory27;
	PINSEL_CFG_Type memory28;
	
	// Initialisation des bits à activer
	//	Led0
	int ledBit = (1<<3);
	//	Haut-Parleur
	int hpBit = (1<<9);

	FIO_SetDir(0, ledBit, 1); // Led0 : Sortie
	FIO_SetMask(0, ledBit, 0); // Led0 : Utilisable

	FIO_SetDir(1, hpBit, 1); // Haut-Parleur : Sortie
	FIO_SetMask(1, hpBit, 0); // Haut-Patleut : Utilisable

	memory27.Portnum = PINSEL_PORT_0; // GPIO0 => Port 0
	memory27.Pinnum = PINSEL_PIN_27; // Pin 27
	memory27.Funcnum = PINSEL_FUNC_1; // Fonctionnement I2C
	memory27.Pinmode = PINSEL_PINMODE_PULLUP; // Mode Résistance de rappel
	memory27.OpenDrain = PINSEL_PINMODE_NORMAL; // Pas de Drain-Mode
	
	//Configuration du pin 27
	PINSEL_ConfigPin(&memory27);

	memory28.Portnum = PINSEL_PORT_0;  // GPIO0 => Port 0
	memory28.Pinnum = PINSEL_PIN_28; // Pin 28
	memory28.Funcnum = PINSEL_FUNC_1; // Fonctionnement I2C
	memory28.Pinmode = PINSEL_PINMODE_PULLUP; // Mode Résistance de rappel
	memory28.OpenDrain = PINSEL_PINMODE_NORMAL; // Pas de Drain-Mode
	
	//Configuration du pin 28
	PINSEL_ConfigPin(&memory28);

	//==========================================
	//	Test de la led0 et du buzzer (sans Timer)
	//==========================================
	
	// Led Clignotante 1 fois (La Led0 fonctionne)
	FIO_ClearValue(0, ledBit);
	pseudoSleep(10000); // Environ 1s
	FIO_SetValue(0, ledBit);
	pseudoSleep(10000); // Environ 1s
	
	// Début de Au clair de la lune (Le buzzer fonctionne)
	note(38);	//Pseudo Do
	note(38);	//Pseudo Do
	note(38);	//Pseudo Do
	note(34);	//Pseudo Re
	note(30); 	//Pseudo Mi
	note(34);	//Pseudo Re
	note(38);	//Pseudo Do
	note(30); 	//Pseudo Mi
	note(34);	//Pseudo Re
	note(34);	//Pseudo Re
	note(38);	//Pseudo Do
}

// Attente APPROXIMATIVE de 100µs
void pseudoSleep(unsigned int s)
{
	unsigned int i = 0;
	while (i< s*1000) // 100µs d'attente (environ)
		i++;
}

// Emmet un signal en entrée du haut parleur d'une periode 2*t
void note(unsigned int t)
{
	unsigned int i=0;
	for(i=0;i<100;i++)
	{
		FIO_ClearValue(1, (1<<9));
		pseudoSleep(t);
		FIO_SetValue(1, (1<<9));
		pseudoSleep(t);
	}
}