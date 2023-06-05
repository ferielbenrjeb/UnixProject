#ifndef __HANDLERS_SERV
#define __HANDLERS_SERV

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include <signal.h>
#include <stdlib.h>



/// fonction hand_reveil qui permet de reveil un serveur
void hand_reveil(int sig)
{
printf("le serveur est reveillé \n");
}
/// cette fonction permet le fin serveur
void fin_serveur(int sig)
{

  printf("fin de serveur \n");
  unlink(DEMANDE);
  unlink(REPONSE);
  exit(2);
}

#endif
