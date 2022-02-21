
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
