#ifndef RICHARD_H
#define RICHARD_H
#include <time.h>

#include "../../bash-loadable-wireguard/src/fs/file2str.c"
#include "../../bash-loadable-wireguard/src/human/bytes.c"
#include "../../bash-loadable-wireguard/src/log/log.c"
#include "socket99.c"


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
