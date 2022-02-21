
/*  HOSTS */

typedef struct {
  char dummy;
} w1, w2;


/*  HOST FXNS */


const int w1_port(void) {
  return(SSH_PORT);
}


const char *w1_name(void) {
  return("web1.vpnservice.company");
}


const int w2_port(void) {
  return(SSH_PORT);
}


const char *w2_name(void) {
  return("web1.vpntech.net");
}


void w2_connect(AbducoHost droid) {
  AbducoHost_connect(droid);
  puts("Waaaaoow!");
}

impl(AbducoHost, w1);
#define w2_connect_CUSTOM    ()
impl(AbducoHost, w2);
