#ifndef RICHARD_C
#define RICHARD_C
#define SSH_PORT    22
#define _GNU_SOURCE 1
#include <unistd.h>
#include <sys/mman.h>
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
#include "fsio.h"
#include "scriptexec.h"

#include "stringfn.h"
#include "strsplit.h"
#include "stringbuffer.h"


#include "stringbuffer.c"
#include "fsio.c"
#include "stringfn.c"
#include "scriptexec.c"
#include "richard-utils.c"

#include "richard-types.c"

#include "richard-ssh-socket.c"

#include "richard-ssh-config.c"

#include "richard-debug.c"

#include "richard-remote-host.c"

#include "richard-dev.c"


int main(){
  log_set_level(LOG_TRACE);


  dev1();
  return(0);
}
#endif
