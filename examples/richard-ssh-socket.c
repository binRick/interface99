

socket99_config SshClientConfig(RemoteHost *rh){
  socket99_config cfg = {
    .host        = hostname_to_ip(rh->name),
    .port        = rh->ssh_port,
    .server      = false,
    .nonblocking = true,
  };

  return(cfg);
}

