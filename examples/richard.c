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


socket99_config SshSocket(const RemoteHost *rh){
  socket99_config cfg = {
    .host        = hostname_to_ip(rh->name),
    .port        = rh->ssh_port,
    .server      = false,
    .nonblocking = true,
  };

  return(cfg);
}


int SshConfigOpen(const RemoteHost *rh){
  socket99_result ssh;
  bool            ok = socket99_open(&(rh->cfg), &ssh);

  if (ok && ssh.fd > 0) {
    return(ssh.fd);
  }

  return(-1);
}


bool SshConfigOk(const RemoteHost *rh){
  socket99_result ssh;
  bool            ok = socket99_open(&(rh->cfg), &ssh);

  if (ok) {
    close(ssh.fd);
  }
  return(ok);
}


int PrintRemoteHost(const RemoteHost rh){
  int fd = SshConfigOpen(&rh);

  close(fd);

  log_info("\n"
           "name: %s\n"
           "      - cfg:      %s:%d\n"
           "      - ok?       %s\n"
           "      - fd:       %d\n"
           "",
           rh.name,
           rh.cfg.host, rh.cfg.port,
           SshConfigOk(&rh) ? "Yes" : "No",
           fd
           );
}


RemoteHost NewRemoteHost(char *name, int port){
  char ip[100];
  char *host = "UNKNOWN";

  if (strcmp(name, "") == 0) {
    name = "UNKNOWN";
  }

  RemoteHost      rh = {
    .name     = name,
    .cfg      = NULL,
    .ok       = false,
    .ssh_port = SSH_PORT
  };
  socket99_config cfg = SshSocket(&rh);

  rh.cfg = SshSocket(&rh);

  return(rh);
}


#include "richard-dev.c"


int main(const int argc, const char **argv) {
  log_set_level(LOG_TRACE);


  dev1();
  return(0);
}
#endif
