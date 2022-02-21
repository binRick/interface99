
#define AbducoHost_IFACE          \
  vfunc(const char *, name, void) \
  vfunc(const int, port, void)    \
  vfuncDefault(void, connect, AbducoHost droid)

interface(AbducoHost);


void AbducoHost_connect(AbducoHost droid) {
  log_debug("Connecting to %s on port %d...", droid.vptr->name(), droid.vptr->port());
}


typedef struct {
  char dummy;
} w1;


const int w1_port(void) {
  return(22);
}


const char *w1_name(void) {
  return("web1.vpnservice.company");
}

impl(AbducoHost, w1);

typedef struct {
  char dummy;
} w2;


const int w2_port(void) {
  return(23);
}


const char *w2_name(void) {
  return("web1.vpntech.net");
}


void w2_connect(AbducoHost droid) {
  AbducoHost_connect(droid);
  puts("Waaaaoow!");
}


#define w2_connect_CUSTOM    ()
impl(AbducoHost, w2);


int dev2(){
  AbducoHost h1 = DYN(w1, AbducoHost, &(w1){ 0 });

  VCALL_OBJ(h1, connect);

  AbducoHost h2 = DYN(w2, AbducoHost, &(w2){ 0 });

  VCALL_OBJ(h2, connect);
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

