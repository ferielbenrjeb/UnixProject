#ifndef __HANDLERS_CLI
#define __HANDLERS_ CLI

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include <signal.h>

/// fonction hand_reveil qui permet de reveil le client
void hand_reveil(int sig)
{
//printf("Le client est reveillé");
printf("Le client est reveillé \n");
printf("\n" );
}


#endif
