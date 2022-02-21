#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>


int SshConfigOpen(RemoteHost *rh){
  socket99_result ssh;

  if (socket99_open(&(rh->cfg), &ssh)) {
    if (ssh.fd > 0) {
      return(ssh.fd);
    }
  }

  return(-1);
}


bool SshConfigOk(RemoteHost *rh){
  int fd = SshConfigOpen(rh);

  if (fd > 0) {
    if (close(fd) == 0) {
      return(true);
    }
  }
  return(false);
}

