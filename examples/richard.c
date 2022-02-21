#ifndef RICHARD_C
#define RICHARD_C
#define SSH_PORT    22
#include "richard-utils.c"
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


#define TEST_LOG_FILE    "/tmp/vshell.log"


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

//#define AbducoHost_IFACE \
//  vfunc(void, exec, VSelf, char *cmd)

//interface(AbducoHost);

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

//typedef struct {
//  char *name;
//} AbducoHost;

typedef struct {
  char            *name;
  int             ssh_port;
  bool            ok;
  Connection      conn;
  socket99_config cfg;
} RemoteHost;


socket99_config SshSocket(const RemoteHost *rh){
  socket99_config cfg = {
    .host        = hostname_to_ip(rh->name),
    .port        = rh->ssh_port,
    .server      = false,
    .nonblocking = true,
  };

  return(cfg);
}


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
  bool            ok          = socket99_open(&(rh->cfg), &ssh);
  bool            send_packet = false;

  if (ok) {
    if (send_packet) {
      const char *msg     = "hello\n";
      size_t     msg_size = strlen(msg);
      ssize_t    sent     = send(ssh.fd, msg, msg_size, 0);
      bool       pass     = ((size_t)sent == msg_size);
      log_debug("sent %zu bytes!", sent);
    }
    close(ssh.fd);
    log_debug("ssh conn closed!");
  }
  return(ok);
}


Connection NewConnection(char *host, int port){
  Connection conn = {
    .host = (host != NULL) ? host : "UNKNOWN",
    .port = (port != 0 && port > 1 && port < 65535) ? port : 22,
    .ok   = false
  };

  if (conn.port > 0 && conn.port < 65535) {
    conn.ok = true;
  }

  return(conn);
}


int PrintRemoteHost(const RemoteHost rh){
  int fd = SshConfigOpen(&rh);

  close(fd);

  log_info("\n"
           "name: %s\n"
           "      - cfg:      %s:%d\n"
           "      - ok?       %s\n"
           "      - fd:       %d\n"
           "",
           rh.name,
           rh.cfg.host, rh.cfg.port,
           SshConfigOk(&rh) ? "Yes" : "No",
           fd
           );
}


RemoteHost NewRemoteHost(char *name, int port){
  char ip[100];
  char *host = "UNKNOWN";

  if (strcmp(name, "") == 0) {
    name = "UNKNOWN";
  }

  RemoteHost      rh = {
    .name     = name,
    .conn     = NULL,
    .cfg      = NULL,
    .ok       = false,
    .ssh_port = SSH_PORT
  };
  socket99_config cfg = SshSocket(&rh);

  rh.cfg = SshSocket(&rh);

  return(rh);
}


void dev1(){
  RemoteHost web1 = NewRemoteHost("web1.vpnservice.company", SSH_PORT);

  PrintRemoteHost(web1);

  if (false) {
    RemoteHost web2 = NewRemoteHost("web1.vpntech.net", 0);
    PrintRemoteHost(web2);
  }
}


int main(void) {
  log_set_level(LOG_TRACE);

  dev1();
}
