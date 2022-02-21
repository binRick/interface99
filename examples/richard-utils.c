#ifndef RICHARD_H
#define RICHARD_H
#define TEST_LOG_FILE    "/tmp/vshell.log"
#include "ansicodes.h"
#include <time.h>

#include "../../bash-loadable-wireguard/src/fs/file2str.c"
#include "../../bash-loadable-wireguard/src/human/bytes.c"
#include "../../bash-loadable-wireguard/src/log/log.c"
#include "socket99.c"


void  log_file_test(){
  FILE *fp = fopen(TEST_LOG_FILE, "a");

  log_add_fp(fp, log_get_level());
  fclose(fp);
  char *dat;

  dat = file2str(TEST_LOG_FILE);
  log_info("log file %s size: %s", TEST_LOG_FILE, bytes_to_string(strlen(dat)));
}


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


int list_func(const int argc, const char **args){
  struct timespec start, end;

  return(0);
}

typedef struct ACTION_FUNCTION {
  const char *name;
  int (*func)(const int argc, const char **args);
} null;

struct ACTION_FUNCTION ActionFunctions[] = {
  { "list", list_func },
  { NULL,   NULL      }
};

struct ACTION_FUNCTION *cur = ActionFunctions;
typedef void ACTION_FUNCTION_HANDLER(const int argc, const char **args);


int RunActionName(char *name, const int argc, const char **argv){
  int                    i    = 0;
  struct ACTION_FUNCTION *cur = ActionFunctions;

  while (cur->name) {
    log_debug(cur->name);
    if (!strcmp(cur->name, name)) {
      log_debug("Running function %s with %d args of %d bytes", cur->name, argc, strlen((char *)argv));
      int res = cur->func(argc, argv);
      if (res == 0) {
        log_debug(AC_GREEN "%s(%d, xxxxxx) => %d", cur->name, argc, res);
      }else{
        log_error(AC_BOLD AC_RED "%s(%d, xxxxxx) => %d", cur->name, argc, res);
      }
      return(res);
    }
    cur = &ActionFunctions[++i];
  }
  log_error("Failed to find function for name '%s'", name);
  return(-1);
}


//RunActionName("list", argc, argv);


int test_abduco_host_socket(){
  char            *host = "127.0.0.1";
  int             port  = 22;

  socket99_config cfg = {
    .host        = host,
    .port        = port,
    .server      = false,
    .nonblocking = true,
  };

  socket99_result res;
  bool            ok = socket99_open(&cfg, &res);
  bool            pass;

  if (!ok) {
    log_error("Failed to connect to %s:%d", host, port);
  }else{
    log_info("connected to %s:%d", host, port);
  }
  return(0);
}
#endif
