#include "serv_cli_fifo.h"
#include "Handlers_Cli.h"

int main(){
/* Déclarations */
int file1;// descripteur sur le tube fifo1
int file2;// descripteur sur le tube fifo 2
struct demande demande;// variable demande de type structure de message demande
struct reponse reponse;//variable reponse de type structure de message reponse
int i;
int sig;

/* Ouverture des tubes nommés */
resultat=fopen("test.txt","w");

file1 = open(DEMANDE,O_WRONLY );
file2 = open (REPONSE, O_RDONLY );
if ( file1 == -1 || file2 == -1)
{
fprintf (resultat," Ouverture des tubes impossible ");
printf("\n" );
exit (2);
};

/* installation de handlers */
signal(SIGUSR1,hand_reveil );//reveillé le client lors de l'envoi de signal SIGUSR1

/* Construction et envoi d’une question */

srand ( getpid ());
demande.pid_c= getpid();// prend pid de client
demande.nombre= 1 + rand ()% NMAX ;//pour nombre prend valeur qui n'est pas grand
if ( write (file1,&demande , sizeof(struct demande )) == -1){//envoi le message et en cas d'erreur afffiche write
perror ("write");
fprintf(resultat,"write");
exit (2);
}
/* Attente de la réponse */
pause();
/* Lecture de la réponse */

if (read( file2,&reponse , sizeof (struct reponse ) ) <= 0 )// lire la reponse avec commande read et en cas d'erreur affiche read
 {
perror ("read");
fprintf(resultat,"read");
 exit (2);
 };
 /* Envoi du signal SIGUSR1 au serveur */
 //printf("le client Envoie SIGUSR1 au serveur");
fprintf(resultat,"le client Envoie SIGUSR1 au serveur \n");

kill (reponse.pid_s, SIGUSR1 );// kill permet t'envoyer un signal SIGUSR1 au serveur
/* Traitement local de la réponse */

fprintf(resultat,"Client de pid  % d  recois % d nombres  :  \n", demande.pid_c,demande.nombre);

for ( i =0; i <demande.nombre ; i ++)
{
fprintf(resultat,"--- %d ) %d\n",i,reponse.tab[i]);
}

fclose(resultat);
exit (0);
}
