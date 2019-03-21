 //une note est une frequence pendant un certain temps
typedef struct
{
	char frequence;//en hertz
	char longueur;//en ms
} tnote;

//une partition est un tableaux de notes se terminant par une note de longueur 0
typedef tnote * tpartition;

//note de fin
#define finp {42,0}

//notes de musique

//Frequence divisé par 2

#define do3 261/2

#define re3 293/2

#define mi3 330/2

#define fa3 350/2

#define sol2 196/2

#define sol3 392/2 //730 //784 en vrai

#define la2 220/2


#define usil {0,3} //petit silence de coupure

//joue une note
void jouer_note(tnote);

void jouer_partition(tpartition);

void T0_Init();

void TIMER0_IRQHandler();

void n(int t);

void musintro();

void jouer_en_repeat(tpartition p);
 //void n2();
