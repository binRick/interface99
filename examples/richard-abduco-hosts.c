
/*  HOSTS */


/*  HOST FXNS */
bool w_ok(void) {
  return(false);
}


bool w1_ok(void) {
  return(w_ok());
}


bool w2_ok(void) {
  return(w_ok());
}


bool w3_ok(void) {
  return(true);
}


const char *w1_name(void) {
  return("web1.vpnservice.company");
}


int w2_port(AbducoHost ah) {
  return(SSH_PORT + 10);
}


int w3_port(AbducoHost ah) {
  log_debug("w3 port>%s", ah.vptr->name());
  return(SSH_PORT + 3);
}


const char *w3_name(void) {
  return("al1");
}


const char *w2_name(void) {
  return("web1.vpntech.net");
}


void w2_connect(AbducoHost ah) {
  log_debug("pre-connect>w2 custom connect!");
  AbducoHost_connect(ah);
  log_debug("post-connect>w2 custom connect!");
}


#define w2_connect_CUSTOM    ()
#define w2_port_CUSTOM       ()
#define w3_port_CUSTOM       ()

typedef struct {
  char dummy;
} w1, w2, w3;
impl(AbducoHost, w1);
impl(AbducoHost, w2);
impl(AbducoHost, w3);

