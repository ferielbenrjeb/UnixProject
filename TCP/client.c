#include "serv_cli_sock.h"
#include <unistd.h>

int main(){

resultat=fopen("test1.txt","w");
if(resultat==NULL){
	fprintf(resultat,"Erreur d'ouverture de fichier");
	exit(1);
}

  char *ip = "127.0.0.1"; //ip address
  int port = 9000; //port
  int e; 
  
  int sockfd; //client socket
  struct sockaddr_in server_addr; //abstract address type
  
  int question[2];
  int response[2000];//contains the numbers received from the server
  srand(getpid());
  
  question[0]=(rand()%NMAX)+1;
  question[1]=getpid();
  // socket create and verification
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    fprintf(resultat," Erreur dans le socket");
    exit(1);
  }
  fprintf(resultat,"Socket serveur créé avec succès\n");
  // assign IP, PORT
  server_addr.sin_family = AF_INET; //address family
  server_addr.sin_port = port; //port number
  server_addr.sin_addr.s_addr = inet_addr(ip); //ip address

  //connect the client socket to server socket
  e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)); 
  if(e == -1) {
    fprintf(resultat,"Erreur dans le socket");
    exit(1);
  }
  fprintf(resultat,"je suis le client n° %d et je demande au serveur de m'envoyer %d numbers.\n",question[1],question[0]);
  
  //write the number on the connected socket 
  if (send(sockfd, &question, sizeof(question), 0) == -1) { 
    fprintf(resultat,"Erreur lors de l'envoi du numéro");
    exit(1);
   }
   fprintf(resultat,"Demande envoyée avec succès.\n");
   
   //stores the resultat
   int n = recv(sockfd, &response, sizeof(response), 0); 
   if (n <= 0){
    fprintf(resultat," Erreur de réception");
   }
  
  //printf de resultat
  fprintf(resultat,"La réponse du serveur: \n");
  for(int i=0; i<question[0]; i++){
    fprintf(resultat,"--- %d ) %d\n",i,response[i]);
  }
  
 
  close(sockfd);

  return 0;
}
