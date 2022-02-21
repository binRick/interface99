
#define AbducoHost_IFACE                                 \
  vfunc(const char *, name, void)                        \
  vfunc(const int, port, void)                           \
  vfunc(const bool, ok, AbducoHost ah)                   \
  vfuncDefault(void, connect, AbducoHost ah)             \
  vfuncDefault(const char *, sessions, AbducoHost ah)

interface(AbducoHost);

bool AbducoHost_ok(AbducoHost ah) {
  log_debug("checking ok on %s", ah.vptr->name());
  return true;
}
char * AbducoHost_sessions(AbducoHost ah) {
  log_debug("listing sessions on %s", ah.vptr->name());
}

void AbducoHost_connect(AbducoHost ah) {
  log_debug("Connecting to %s on port %d...", ah.vptr->name(), ah.vptr->port());
}

#include "richard-abduco-hosts.c"


int dev2(){
  AbducoHost h1 = DYN(w1, AbducoHost, &(w1){ 0 });
  VCALL_OBJ(h1, connect);
  /*
  AbducoHost h2 = DYN(w2, AbducoHost, &(w2){ 0 });
  VCALL_OBJ(h2, connect);
  AbducoHost h3 = DYN(w3, AbducoHost, &(w3){ 0 });
  VCALL_OBJ(h3, connect);*/

  return(0);
}


int dev1(){
  return(dev2());

  RemoteHost web1 = NewRemoteHost("web1.vpnservice.company", SSH_PORT);

  PrintRemoteHost(web1);

  if (false) {
    RemoteHost web2 = NewRemoteHost("web1.vpntech.net", 0);
    PrintRemoteHost(web2);
  }

  return(0);
}

