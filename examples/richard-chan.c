#include "chan.c"
#include "queue.c"

chan_t *ip_messages;
chan_t *ip_signals;

void   *ip_msg;


void * ip_worker(){
  void *hostname;

  while (chan_recv(ip_messages, &hostname) == 0) {
    log_debug("request............... hostname:%s", hostname);
    log_debug(AC_GREEN "received hostname request  " AC_RESETALL "'" AC_YELLOW AC_REVERSED "%s" AC_RESETALL "'", hostname);

    char *ip;
    ip = (char *)hostname_to_ip(hostname);
    log_debug(AC_GREEN "Got IP  " AC_RESETALL "'" AC_YELLOW AC_REVERSED "%s" AC_RESETALL "'", ip);
    log_debug("Hostame %s", hostname);
    log_debug("IP %s", ip);
  }

  log_debug("sending responses ");
  chan_send(ip_signals, "1");
  return(NULL);
}


int chan_resolve(const char *ip_msg){
  return(chan_send(ip_messages, (char *)ip_msg));
}

bool chans_initialized = false;


int chan_dev(){
  char *ip;

  if (!chans_initialized) {
    init_chan();
    chans_initialized = true;
  }
  chan_resolve("web1.vpnservice.company");
  chan_recv(ip_signals, ip);
  log_debug(AC_GREEN ">>>>>IP  " AC_RESETALL "'" AC_YELLOW AC_REVERSED "%s" AC_RESETALL "'", ip);
  return(0);
}


void close_chan(){
  chan_dispose(ip_messages);
  chan_dispose(ip_signals);
}


void init_chan(){
  ip_messages = chan_init(0);
  ip_signals  = chan_init(0);


  pthread_t th;

  pthread_create(&th, NULL, ip_worker, NULL);
}

