

typedef struct {
  char *cmd;
  bool ok;
  int  code;
} Exec;

typedef struct {
  char            *name;
  int             ssh_port;
  bool            ok;
  socket99_config cfg;
} RemoteHost;

