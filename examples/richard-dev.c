
#define AbducoHost_IFACE                       \
  vfunc(const char *, name, void)              \
  vfuncDefault(const int, port, AbducoHost ah) \
  vfuncDefault(const bool, ok, AbducoHost ah)  \
  vfuncDefault(void, connect, AbducoHost ah)   \
  vfuncDefault(const char *, sessions, AbducoHost ah)

interface(AbducoHost);


bool AbducoHost_ok(AbducoHost ah) {
  log_debug("checking ok on %s", ah.vptr->name());
  return(true);
}


char * AbducoHost_sessions(AbducoHost ah) {
  log_debug("listing sessions on %s", ah.vptr->name());
}


const int AbducoHost_port(AbducoHost ah) {
  int p = SSH_PORT;

  log_debug("gettting port.........%s=>%d", ah.vptr->name(), p);

  if (p > 0) {
    return(p);
  }

  return(SSH_PORT);
}


void AbducoHost_connect(AbducoHost ah) {
  log_debug("Connecting to %s on port %d...", ah.vptr->name(), ah.vptr->port(ah));
}

#include "richard-abduco-hosts.c"


int dev2(){
  AbducoHost h1 = DYN(w1, AbducoHost, &(w1){ 0 });

  AbducoHost_connect(h1);

  AbducoHost h2 = DYN(w2, AbducoHost, &(w2){ 0 });

  VCALL_OBJ(h2, connect);

  AbducoHost h3 = DYN(w3, AbducoHost, &(w3){ 0 });

  AbducoHost_connect(h3);

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

