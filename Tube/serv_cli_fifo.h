#ifndef __SERV_CLI_FIFO
#define __SERV_CLI_FIFO
///// les entêtes fichier systeme
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include <signal.h>

////// definition de constante NMAX et tube nomee fifo1,fifo2
#define NMAX 20
#define DEMANDE "fifo1"
#define REPONSE "fifo2"
////////// definition de stucture demande et reponse
struct demande
{
	int pid_c; // pid_client
	int nombre;// nombre asleatoire donnee par client
};

struct reponse
{
	int pid_s; //pid serveur
	int tab[NMAX];//tableau qui contient n nombre
};
FILE *resultat;
#endif
