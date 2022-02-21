#ifndef RICHARD_RH
#define RICHARD_RH

socket99_config SshClientConfig(RemoteHost*);

RemoteHost NewRemoteHost(char *name, int port){
  char ip[100];
  char *host = "UNKNOWN";

  if (strcmp(name, "") == 0) {
    name = "UNKNOWN";
  }

  RemoteHost rh = {
    .name     = name,
    .cfg      = NULL,
//(RemoteHost*)void,
    .ok       = false,
    .ssh_port = SSH_PORT
  };

//socket99_config cfg;
socket99_config cfg = SshClientConfig(&rh);
  rh.cfg = cfg;

  return(rh);
}

#endif
