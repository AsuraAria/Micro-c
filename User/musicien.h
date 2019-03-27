 //une note est une frequence pendant un certain temps
typedef struct
   {
     char frequence;//en hertz
     char longueur;//en ms
	} tnote;

//une partition est un tableaux de notes se terminant par une note de longueur 0
typedef tnote * tpartition;

//note de fin de partition
#define finp {42,0}

//notes de musique
//Frequence divise par 2
#define do3 261/2
#define re3 293/2
#define mi3 330/2
#define fa3 350/2
#define sol2 196/2
#define sol3 392/2
#define la2 220/2


#define usil {0,3} //petit silence de coupure entre deux notes identiques

//joue une note
void jouer_note(tnote);
/*********************************************************************//**
 * @brief			configure les variables utilisees par le handler pour jouer une note
 * @param[in]	tnote
 * @return		None
 *
 * Note:
 * n'attend pas que la precedente note soit finie
 * pour commencer la nouvelle
 **********************************************************************/
void jouer_partition(tpartition);
/*********************************************************************//**
 * @brief			procedure intermediaire joue une tpartition
 * @param[in]	tpartition
 * @return		None
 *
 * Note:
 * arrete de jouer a la fin de la partition
 * ne fais plus rien ensuite
 **********************************************************************/

void T0_Init();
/*********************************************************************//**
 * @brief			initialise le timer0 en mode interruption
 * @param[in]	None
 * @return		None
 *
 * Note:
 * Interruptions toutes les 50microsecondes
 **********************************************************************/

void TIMER0_IRQHandler();
/*********************************************************************//**
 * @brief			Handler des interruptions du timer0
 * @param[in]	None
 * @return		None
 *
 * Note:
 * -s'occuppe directement de la manipulation du buzzer
 * -utilise des variables globales pour fonctionner
 **********************************************************************/

void musintro();
/*********************************************************************//**
 * @brief			joue le son lors du demarrage
 * @param[in]	None
 * @return		None
 *
 * Note:
 * joue le theme principal en boucle
 **********************************************************************/

void jouer_en_repeat(tpartition p);
/*********************************************************************//**
 * @brief			joue une tpartition en repeat
 * @param[in]	None
 * @return		None
 *
 * Note:
 * le fonctionnement est le meme que jouer_partition()
 * mais en repeat
 **********************************************************************/
void arreter_repeat();
/*********************************************************************//**
 * @brief			stope le mode repeat
 * @param[in]	None
 * @return		None
 *
 * Note:
 * La partition en cours continuera jusqu'a la fin
 **********************************************************************/

 void jouer_1_fois(tpartition);
 /*********************************************************************//**
  * @brief			joue une partition une seule fois
  * @param[in]	None
  * @return		None
  *
  * Note:
  * a utiliser a la place de jouer_partition()
  **********************************************************************/
