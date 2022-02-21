
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

