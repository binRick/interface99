
#include <arpa/inet.h>
#include <errno.h>  //For errno - the error number
#include <interface99.h>
#include <netdb.h>  //hostent
#include <stdio.h>  //printf
#include <stdlib.h> //for exit(0);
#include <string.h> //memset
#include <sys/socket.h>

#include <assert.h>
#include <stddef.h>


#include "../../bash-loadable-wireguard/src/fs/file2str.c"
#include "../../bash-loadable-wireguard/src/human/bytes.c"
#include "../../bash-loadable-wireguard/src/log/log.c"

#ifndef LF
#define TEST_LOG_FILE    "/tmp/vshell.log"
#define LF               1


void  log_file_test(){
  FILE *fp = fopen(TEST_LOG_FILE, "a");

  log_add_fp(fp, log_get_level());
  fclose(fp);
  char *dat;

  dat = file2str(TEST_LOG_FILE);
  log_info("log file %s size: %s", TEST_LOG_FILE, bytes_to_string(strlen(dat)));
}
#endif


char * hostname_to_ip(char *hostname){
  struct hostent *he;
  struct in_addr **addr_list;
  int            i;

  if ((he = gethostbyname(hostname)) == NULL) {
    herror("gethostbyname");
    return(NULL);
  }

  addr_list = (struct in_addr **)he->h_addr_list;

  for (i = 0; addr_list[i] != NULL; i++) {
    return(inet_ntoa(*addr_list[i]));
  }
  return("");
}

#define AbducoHost_IFACE \
  vfunc(void, exec, VSelf, char *cmd)

interface(AbducoHost);

typedef struct {
  char *cmd;
  bool ok;
  int  code;
} Exec;

typedef struct {
  char *host;
  int  port;
  bool ok;
} Connection;

typedef struct {
  char *name;
} AbducoHost;

typedef struct {
  char       *name;
  bool       ok;
  Connection conn;
} RemoteHost;


void RemoteHost_exec(VSelf, char *cmd) {
  VSELF(AbducoHost);
  log_debug("remotehost [exec] <%s> Running cmd '%s'", self->name, cmd);
}

impl(AbducoHost, RemoteHost);


/*
 * void RemoteHost_list(VSelf, char *cmd) {
 * VSELF(RemoteHost);
 * log_debug("[list] <%s> Running cmd '%s'", self->name, cmd);
 * }*/


Connection NewConnection(char *host, int port){
  Connection conn = {
    .host = (host != NULL) ? host : "UNKNOWN",
    .port = (port != NULL && port > 1 && port < 65535) ? port : 22,
    .ok   = false
  };

  if (conn.port > 0 && conn.port < 65535) {
    conn.ok = true;
  }

  return(conn);
}


int PrintRemoteHost(const RemoteHost rh){
  log_info(""
           "name: %s"
           "|conn:%s:%d|ok?%s|",
           rh.name,
           rh.conn.host, rh.conn.port,
           (rh.conn.ok ? "Yes" : "No")
           );
}


RemoteHost NewRemoteHost(char *name, int port){
  char ip[100];
  char *host = "UNKNOWN";

  if (name == NULL || name == "") {
    name = "UNKNOWN";
  }


  RemoteHost rh = {
    .name = name,
    .conn = NewConnection(hostname_to_ip(name),port),
    .ok   = false
  };

  return(rh);
}


void dev1(){
  RemoteHost web1 = NewRemoteHost("web1.vpnservice.company", 22);

  PrintRemoteHost(web1);

  RemoteHost web2 = NewRemoteHost("web1.vpntech.net", NULL);

  PrintRemoteHost(web2);
}


void dev2(){
  AbducoHost web1 = DYN(
    RemoteHost, AbducoHost, &(RemoteHost){
    .name = "web1.vpnservice.company"
  });

  VCALL(web1, exec, "pwd");
}


void dev3(){
//  VCALL(web1, exec, "pwd");
}


int main(void) {
  log_set_level(LOG_TRACE);


  //dev1();
  dev2();
}
