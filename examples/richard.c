#ifndef RICHARD_C
#define RICHARD_C
#define SSH_PORT       22
#define _GNU_SOURCE    1
#include "fsio.h"
#include "scriptexec.h"
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>  //For errno - the error number
#include <interface99.h>
#include <netdb.h>  //hostent
#include <stddef.h>
#include <stdio.h>  //printf
#include <stdlib.h> //for exit(0);
#include <string.h> //memset
#include <sys/mman.h>
#include <sys/socket.h>
#include <unistd.h>

#include "stringbuffer.h"
#include "stringfn.h"
#include "strsplit.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "chan.h"

#include "fsio.c"
#include "richard-utils.c"
#include "scriptexec.c"
#include "stringbuffer.c"
#include "stringfn.c"

#include "richard-types.c"

#include "richard-ssh-socket.c"

#include "richard-ssh-config.c"

#include "richard-debug.c"

#include "richard-remote-host.c"

#include "richard-chan.c"
#include "richard-dev.c"


int main(){
  log_set_level(LOG_TRACE);
  dev1();
  return(0);
}
#endif
