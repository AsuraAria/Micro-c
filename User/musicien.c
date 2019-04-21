#include "lpc17xx_timer.h"
#include "musicien.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx.h"
#include "partitions.h"

//variables globales

short nbperi;//nb periodes de la note en cours
short frontmusique;//pointe vers la note qui doit etre joué
LPC_TIM_TypeDef val_reg_timer;//variable globale pour initialiser le timer

short MatchValue;//nombres de fronts de timer a attendre pour un front sonore
short Matchrestant;//nombres de fronts de timer restant a atendre pour un front sonore

char silencieux = 1;//indique si le timer est silencieux

tnote * addr_note_actuelle =0;//pointe vers la tnote que l'on est en train de jouer
tpartition pactuelle;//indique la partition que l'on est en train de jouer
char on_repeat =0;//indique si la partition actuelle est en mode repeat

tnote nsilence;//variable temporaire indiquant lorsque la note est silencieuxse


void jouer_note(tnote note){
  //parametre les variables globales pour que le handler joue note
	//La frequence est divisée par 2 pour des raisons d'économies de memoires
  MatchValue =(1000000) / (note.frequence*2*2 *50) ;//temps d'attente pour une demi periode en 50 aine de uS selon Hz
	nbperi = (note.longueur*10 * 1000)/ (MatchValue*50);//nb de periode de timer a jouer
	frontmusique =0;//commence sur front montant
	Matchrestant= MatchValue;
}


void jouer_partition(tpartition partition){

  if(partition[0].longueur != 0){//on joue la note si cest pas la fin

		if(partition[0].frequence != 0){//si la note nest pas silencieuse
			silencieux = 0;
			addr_note_actuelle = partition;
			jouer_note(*partition);

		}else{//si note est silencieuxse
			nsilence=partition[0];
			nsilence.frequence=100;
			addr_note_actuelle = partition;
			silencieux = 1;//on joue une note a 100hz qui n'est pas entendue
			jouer_note(nsilence);
		}

  }else{//si c'est la fin de la partiton alors on ne joue rien
		addr_note_actuelle = 0;
	}

}


void T0_Init(){
  //initiation du timer0

	TIM_TIMERCFG_Type conf_timer;
	TIM_MATCHCFG_Type conf_interrupt;


	conf_timer.PrescaleOption = TIM_PRESCALE_USVAL; //prescale en uS
	conf_timer.PrescaleValue = 1;//precision de 1 uS

	conf_interrupt.MatchChannel=0;//timer0
	conf_interrupt.IntOnMatch=ENABLE;//enable:interruption sur match
	conf_interrupt.ResetOnMatch=ENABLE;//remise a zero en match
	conf_interrupt.StopOnMatch = DISABLE;//le timer ne s'arrete pas lors d'un match
	conf_interrupt.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;//aucune sortie lors du match
	conf_interrupt.MatchValue=50;//on attend 50 fois p1us

	NVIC_EnableIRQ(TIMER0_IRQn);//activation du handler

	TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &conf_timer);
  //timer0 en rising avec la config ci-jointe

	TIM_ConfigMatch(LPC_TIM0, &conf_interrupt);//configuration du match

	TIM_Cmd(LPC_TIM0, ENABLE);//lancement du timer

	MatchValue = -1;//on commence sans jouer de musique
}


void TIMER0_IRQHandler(){
  //change tous les "timers temps" le front auw bornes du buzzer


	if(Matchrestant == 0){//une demi periode sest ecoule
		if(frontmusique == 0){//on inverse le front au buzzer si on n'est pas en mode silence

      if(!silencieux){FIO_ClearValue(1,(1<<9));}

      frontmusique = 1;

		}else{
			if(!silencieux){FIO_SetValue(1,(1<<9));}

      frontmusique = 0;

    }


		if(nbperi >0){//Si il reste d'autres periodes a jouer, on relance le timer

			Matchrestant = MatchValue;
			nbperi = nbperi -1;

		}else if (addr_note_actuelle!=0){//si il ne reste aucune autre periode a jouer:
        //on passe a la note suivante
				jouer_partition(&(addr_note_actuelle[1]));

		}
	}

	if(Matchrestant != -1){//on decremente le nombre de match avant le prochain front sonor
		Matchrestant = Matchrestant -1;
	}

	if ((addr_note_actuelle==0)&&on_repeat){//si on est a la fin de la partition et en repeat alors on repete la partition
			jouer_partition(pactuelle);
	}

	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);//Acquitement de l'interruption
}


void musintro(void){
  //joue la musique d'intro
		jouer_en_repeat(thprincipal);
}


void jouer_en_repeat(tpartition partition){
  //joue la partition designe en mode repeat
	on_repeat=1;
	pactuelle = partition;
	jouer_partition(partition);

}


void arreter_repeat(){
  //arrete le repeat du morceau
	on_repeat=0;
}


void jouer_1_fois(tpartition partition){
  //joue une seule fois la partition
	on_repeat=0;
	jouer_partition(partition);
}
