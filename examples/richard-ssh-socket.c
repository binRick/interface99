

socket99_config SshSocket(const RemoteHost *rh){
  socket99_config cfg = {
    .host        = hostname_to_ip(rh->name),
    .port        = rh->ssh_port,
    .server      = false,
    .nonblocking = true,
  };

  return(cfg);
}

