 //une note est une frequence pendant un certain temps
typedef struct
   {
     int frequence;//en hertz
     int longueur;//en ms
	} tnote;

//une partition est un tableaux de notes se terminant par une note de longueur 0
typedef tnote * tpartition;

//note de fin
#define finp {42,0}

//notes de musique

#define do_1 16
#define do0 32
#define do1 65
#define do2 130
#define do3 261
#define do4 523
#define do5 1046
#define do6 2093
#define do7 4186
#define do8 8372
#define do9 16744

#define dod_1 17
#define dod0 34
#define dod1 69
#define dod2 138
#define dod3 277
#define dod4 554
#define dod5 1108
#define dod6 2217
#define dod7 4434
#define dod8 8 869
#define dod9 17 739

#define re4 587

#define red4 622

#define mi4 659

#define fa4 698

#define fad4 739

#define sol4 783

#define sold4 830

#define la4 880

#define lad4 932

#define si4 987

#define usil {0,30} //petit silence de coupure

//joue une note
void jouer_note(tnote);

void jouer_partition(tpartition);

 void sleep(int s);

 void T0_Init();

 void TIMER0_IRQHandler();

 void n(int t);

 void musintro();

 //void n2();
