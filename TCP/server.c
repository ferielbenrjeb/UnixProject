#include "serv_cli_sock.h"

int main(){

	
	
	resultat=fopen("test1.txt","w");
	if(resultat==NULL){
		fprintf(resultat,"(serveur)-> Erreur lors de l'ouverture du fichier !");
		printf("(serveur)-> Erreur lors de l'ouverture du fichier !\n");
		exit(1);
	}
	
  char *ip = "127.0.0.1"; //ip address
  int port = 9000; //port
  int e; //error
  
  int sockfd, new_sock;
  struct sockaddr_in server_addr, new_addr;
  socklen_t addr_size;
  
  int question[2];   
  int response[2000]; 
  int n1; 

  srand(getpid());
  
  // socket create and verification
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    fprintf(resultat,"(serveur)-> Erreur dans le socket");
    printf("(serveur)-> Erreur dans le socket\n");
    exit(1);
  }
  fprintf(resultat,"(serveur)-> Socket de serveur créé avec succès\n");
  printf("(serveur)-> Socket de serveur créé avec succès\n");
  // assign IP, PORT
  server_addr.sin_family = AF_INET; //address family
  server_addr.sin_port = port; //port
  server_addr.sin_addr.s_addr = inet_addr(ip); //ip address

  // Binding newly created socket to given IP and verification
  e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e < 0) {
    fprintf(resultat,"(serveur)-> Erreur bind");
     printf("(serveur)-> Erreur bind\n");
    exit(1);
  }
  fprintf(resultat,"(serveur)-> Bind avec succès\n");
  printf("(serveur)-> Bind avec succès\n");


        // Now server is ready to listen and verificatio
 	if(listen(sockfd, 10) == 0){
		fprintf(resultat,"(serveur)-> Écoute...\n");
		printf("(serveur)-> Écoute...\n");
	}else{
		fprintf(resultat,"(serveur)-> Erreur d'écoute\n");
		printf("(serveur)-> Erreur d'écoute\n");
    		exit(1);
	}
	while(1){
	  // Accept the data packet from client and verification
	  addr_size = sizeof(new_addr);
	  new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
	  
	 	 int  n = recv(new_sock, &question, SIZE, 0); //n length of the received msg
		    if (n <= 0){
		      break;
		    }
		    fprintf(resultat,"The client n° %d is asking for %d numbers.\n",question[1],question[0]);
      int pid=fork();
      if (pid < 0) {
         fprintf(resultat,"(serveur)-> fork erreur");
         printf("(serveur)-> fork erreur\n");
         exit(1);
      }
      if (pid == 0) {
	    
		    //generating the numbers randomly and storing them in response
		    for(int i=0;i<question[0];i++){
			   	response[i]=(rand()%NMAX)+1;
			   	}
	            //writing outgoing numbers on the accepted socket new_socket   	
		    if (send(new_sock,&response , sizeof(response), 0) == -1) {
		      fprintf(resultat,"[-](serveur)-> Erreur dans l'envoi des numéros.");
		      printf("(serveur)-> Erreur dans l'envoi des numéros\n");
		      exit(1);
		    }
	  	fprintf(resultat,"(serveur)-> Numéros envoyés au client avec succès.\n");
	  	printf("(serveur)-> Numéros envoyés au client avec succès.\n");
      }
	  

}  return 0;
}
