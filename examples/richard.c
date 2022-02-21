#ifndef RICHARD_C
#define RICHARD_C
#define SSH_PORT    22
#include "richard-utils.c"
#include <arpa/inet.h>
#include <errno.h>  //For errno - the error number
#include <interface99.h>
#include <netdb.h>  //hostent
#include <stdio.h>  //printf
#include <stdlib.h> //for exit(0);
#include <string.h> //memset
#include <sys/socket.h>

#include <assert.h>
#include <stddef.h>

#include "richard-types.c"

#include "richard-ssh-socket.c"

#include "richard-ssh-config.c"

#include "richard-remote-host.c"

#include "richard-dev.c"


int main(const int argc, const char **argv) {
  log_set_level(LOG_TRACE);


  dev1();
  return(0);
}
#endif
