

RemoteHost NewRemoteHost(char *name, int port){
  char ip[100];
  char *host = "UNKNOWN";

  if (strcmp(name, "") == 0) {
    name = "UNKNOWN";
  }

  RemoteHost rh = {
    .name     = name,
    .cfg      = NULL,
    .ok       = false,
    .ssh_port = SSH_PORT
  };

  rh.cfg = SshClientConfig(&rh);

  return(rh);
}
