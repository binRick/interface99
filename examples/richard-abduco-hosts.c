
/*  HOSTS */

typedef struct {
  char dummy;
} w1, w2, w3;


/*  HOST FXNS */
const bool w_ok(void) {
  return(false);
}


const bool w1_ok(void) {
  return(w_ok());
}


const bool w2_ok(void) {
  return(w_ok());
}


const bool w3_ok(void) {
  return(true);
}


const int w1_port(void) {
  return(SSH_PORT);
}


const char *w1_name(void) {
  return("web1.vpnservice.company");
}


const int w2_port(void) {
  return(SSH_PORT);
}


const int w3_port(void) {
  return(SSH_PORT);
}


const char *w3_name(void) {
  return("al1");
}


const char *w2_name(void) {
  return("web1.vpntech.net");
}


void w1_connect(AbducoHost ah) {
  log_debug("pre-connect>w1 custom connect!");
  AbducoHost_connect(ah);
  log_debug("post-connect>w1 custom connect!");
}


void w2_connect(AbducoHost ah) {
  log_debug("pre-connect>w2 custom connect!");
  AbducoHost_connect(ah);
  log_debug("post-connect>w2 custom connect!");
}


void w3_connect(AbducoHost ah) {
  log_debug("pre-connect>w3 custom connect!");
  AbducoHost_connect(ah);
  log_debug("post-connect>w3 custom connect!");
}

#define w1_connect_CUSTOM    ()
impl(AbducoHost, w1);
#define w2_connect_CUSTOM    ()
impl(AbducoHost, w2);
#define w3_connect_CUSTOM    ()
impl(AbducoHost, w3);
