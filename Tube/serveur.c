#include "serv_cli_fifo.h"
#include "Handlers_Serv.h"

int main(){
/*Déclarations */
int file1;//descripteur sur le tube fifo 1
int file2;//descripteur sur le tube fifo 2
struct demande demande;// variable demande de type structure de message demande
struct reponse reponse;//variable reponse de type structure de message reponse
int i;
int sig;



printf("-------------le serveur de pid à l'écoute  -----------\n");
/* Création des tubes nommés */
if (mkfifo(DEMANDE, 0666) == -1)
{
        perror("cannot create fifo1 file") ;
        
        exit(EXIT_FAILURE) ;
}
if (mkfifo(REPONSE, 0666) == -1 )
{
            perror("cannot create fifo2 file") ;
            
            exit(EXIT_FAILURE) ;
}
/*initialisation du générateur de nombres aléatoires*/
srand(getpid());

/* Ouverture des tubes nommés */

file1 = open(DEMANDE, O_RDONLY );
file2= open(REPONSE , O_WRONLY );
if ( file1 == -1 || file2 == -1)
{
printf (" Ouverture des tubes impossible ");
exit(2);
};
/*installation de handlers */

signal(SIGUSR1,hand_reveil);
for(sig=1;sig<NSIG;sig++)
{ if(sig!=SIGUSR1)
  signal(sig, fin_serveur);// a la reception de signal quelconque on execute la fonction  fin_serveur
}

/* Boucle principale */
while (1){

/* lecture d’une question */

if ( read (file1 ,&demande , sizeof ( struct demande )) <= 0 )// en cas il ya une erreur dans lecteur de fichier
{
close (file1);// il va ferme le fichier file1
file1 = open (DEMANDE, O_RDONLY );// ouvrir une autre fois
continue ; // continue cette operation jusqua que le serveur peur lire de file1
}
/* construction de la réponse */

for (i =0; i < demande.nombre ; i ++)// boucle for pour construire le tableau d'entier aleatoire
{reponse.tab[i]= rand()%50;}//rand()%50 pour donner des entieres aleatoires entre 0..50 }

reponse.pid_s= getpid ();//prend le pid de serveur

/* envoi de la réponse */
if ( write(file2 ,&reponse , sizeof ( struct reponse )) == -1)// ecrire reponse dans file2 et en cas d'erreur il affiche un msg
{
perror (" write");
}
/* envoi du signal SIGUSR1 au client concerné */

printf("le serveur Envoie SIGUSR1 au client numero %d \n",demande.pid_c);
kill(demande.pid_c , SIGUSR1 ); // kill permet t'envoyer un signal SIGUSR1 au client concerné
}

exit(0);
}
