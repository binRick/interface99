int PrintRemoteHost(RemoteHost rh){
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
  return(0);
}
