//#include "musiscien.h"
//a inclure ensuite
//#include<partitions.h>
#include "lpc17xx_timer.h"
#include "musiscien.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx.h"
#include "partitions.h"

//variales globales pour la musique
//a metre dans #include "globaldec.h"

//code notes de tester
//tnote latmp;

//test
int nbperi;//nb periodes de note
int frontmusique;//pointe vers la note qui doit etre joué
LPC_TIM_TypeDef val_reg_timer;//variable globale

int MatchValue;
int Matchrestant;

int silencieu = 1;

tnote * addr_note_actuelle =0;
tnote nsilence;
void jouer_note(tnote note){
  //LPC_TIM_TypeDef val_reg_timer;
  //val_reg_timer = LPC_TIM0; //sans doute pas necessaire
  //uint32_t MatchValue;
	//TIM_Cmd(LPC_TIM0, DISABLE);

  MatchValue =(1000000) / (note.frequence*2 *50) ;//temps d'attente pour une demi periode en 50 aine de uS selon Hz
  //MatchValue = MatchValue /50; //prescale en 50 uS
	nbperi = (note.longueur * 1000)/ (MatchValue*50);
	frontmusique =0;//commence sur front montant
	Matchrestant= MatchValue;
  //TIM_UpdateMatchValue(LPC_TIM0,0,MatchValue);//on modifie les parametres du timer

	//TIM_ResetCounter(LPC_TIM0);
	//TIM_Cmd(LPC_TIM0, ENABLE);

}

void jouer_partition(tpartition partition){
	//tnote nsilence= {100,100};
  if(partition[0].longueur != 0){//on joue la note si cest pas la fin
		if(partition[0].frequence != 0){//si la note nest pas silencieuse
			silencieu = 0;
			addr_note_actuelle = partition;
			jouer_note(*partition);
		}else{//si note silencieuse
			nsilence={100,partition[0].longueur};
			addr_note_actuelle = partition;
			silencieu = 1;
			jouer_note(nsilence);
		}
   /* //!!!!!!!!!!!!a retirer dans le futur !!!!!!!!!!!!!!!
    sleep(30);//attendre 30 ms
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    jouer_partition(&(partition[1]));//on joue la note suivante*/
  }else{
		addr_note_actuelle = 0;
	}
}

void sleep(int s)//ancienne fonction d'attente en ms
{
	int i=0;

	while(i<s*100)
	{
		i++;
	}
}

void T0_Init(){//initiation du timer0

	TIM_TIMERCFG_Type conf_timer;
	TIM_MATCHCFG_Type conf_interrupt;


	conf_timer.PrescaleOption = TIM_PRESCALE_USVAL; //prescale en uS
	conf_timer.PrescaleValue = 1;//precision de 50 uS

	conf_interrupt.MatchChannel=0;//timer0
	conf_interrupt.IntOnMatch=ENABLE;//enable:interruption sur match
	conf_interrupt.ResetOnMatch=ENABLE;//remise a zero en match
	conf_interrupt.StopOnMatch = DISABLE;
	conf_interrupt.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
	conf_interrupt.MatchValue=50;

	NVIC_EnableIRQ(TIMER0_IRQn);

	TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &conf_timer);
  //timer0 en rising avec la config ci-jointe

	TIM_ConfigMatch(LPC_TIM0, &conf_interrupt);

	TIM_Cmd(LPC_TIM0, ENABLE);
	//*/
}

void TIMER0_IRQHandler(){//change tous les timers temps le front


	if(Matchrestant == 0){//une demi periode sest ecoule
		if(frontmusique == 0){//on inverse le front au buzzer
			if(!silencieu){FIO_ClearValue(1,(1<<9));}
			frontmusique = 1;

		}else{
			if(!silencieu){FIO_SetValue(1,(1<<9));}
			frontmusique = 0;
		}
		if(nbperi >0){//Si il reste d'autres periodes, on relance
			Matchrestant = MatchValue;
			nbperi = nbperi -1;
		}else if (addr_note_actuelle!=0){
				jouer_partition(&(addr_note_actuelle[1]));
		}
	}

	if(Matchrestant != -1){
		Matchrestant = Matchrestant -1;
	}



	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);//Acquitement
}

void n(int t)//ancienne fonction note
{
	int i=0;
	for(i=0;i<1000;i++){
			FIO_ClearValue(1,(1<<9));//
			sleep(t);
			FIO_SetValue(1,(1<<9));//
			sleep(t);
		}
}
void musintro(void){
		MatchValue = -1;
		//n(200);
		//latmp.frequence=440;
		//latmp.longueur=400;
		//jouer_note(latmp);
		jouer_partition(ptest);
		//jouer_note(noteautretmp);
		//n(100);
		//n(90);
}

/*void n2(){
	frontmusique =0;
	nbperi = 2000;
	TIM_Cmd(LPC_TIM0, ENABLE);

}*/
//declartions partitions
