#include "scriptexec.h"

#define AbducoHost_IFACE                       \
  vfunc(const char *, name, void)              \
  vfuncDefault(const int, port, AbducoHost ah) \
  vfuncDefault(bool, ok, AbducoHost ah)        \
  vfuncDefault(void, connect, AbducoHost ah)   \
  vfuncDefault(const char *, sessions, AbducoHost ah)

interface(AbducoHost);

#define SshAuth_IFACE                       \
  vfunc(const char *, name, void)              \
  vfuncDefault(const int, auth, AbducoHost ah) \

interface(SshAuth);

void init_auth(){
//  AbducoHost hh = DYN(w1, AbducoHost, &(w1){ 0 });
}

bool AbducoHost_ok(AbducoHost ah) {
  log_debug("checking ok on %s:%d", ah.vptr->name(), ah.vptr->port(ah));
  return(true);
}


char * AbducoHost_sessions(AbducoHost ah) {
  log_debug("listing sessions on %s", ah.vptr->name());
}


const int AbducoHost_port(AbducoHost ah) {
  int p = SSH_PORT;

  log_debug("gettting port.........%s=>%d", ah.vptr->name(), p);

  if (p > 0) {
    return(p);
  }

  return(SSH_PORT);
}


void AbducoHost_connect(AbducoHost ah) {
  log_debug("Connecting to %s on port %d...", ah.vptr->name(), ah.vptr->port(ah));
}

#include "richard-abduco-hosts.c"

struct ScriptExecResult  result;
struct ScriptExecOptions options;

int dev3(){
options = scriptexec_create_options();
char *cmd = "find /etc";
log_debug(cmd);
  options.runner            = "sh";
  options.working_directory = "/";
  options.exit_on_error     = true;
  options.print_commands    = false;
  result                    = scriptexec_run_with_options(cmd, options);
  if ((int)strlen(result.out) > 0) {
    result.outs = stringfn_split_lines_and_trim(stringfn_trim(result.out));
  }
  if ((int)strlen(result.err) > 0) {
    result.errs = stringfn_split_lines_and_trim(stringfn_trim(result.err));
  }
  log_debug("Code: %d\nOutput:\n%s\nError:\n%s\nDur:%ldms\nstarted:%ld|ended:%ld\n", result.code, result.out, result.err, result.dur, result.start, result.end);
  log_debug("   out len: %d\n", (int)strlen(result.out));
  log_debug("   outs qty: %d\n", result.outs.count);
  log_debug("   err len: %d\n", (int)strlen(result.err));
  log_debug("   errs qty: %d\n", result.errs.count);
return 0;
}
int dev2(){
  AbducoHost h1 = DYN(w1, AbducoHost, &(w1){ 0 });

  AbducoHost_connect(h1);

  AbducoHost h2 = DYN(w2, AbducoHost, &(w2){ 0 });

  VCALL_OBJ(h2, connect);

  AbducoHost h3 = DYN(w3, AbducoHost, &(w3){ 0 });

  AbducoHost_connect(h3);

  return(0);
}


int dev1(){
  return(dev3());
  return(dev2());

  RemoteHost web1 = NewRemoteHost("web1.vpnservice.company", SSH_PORT);

  PrintRemoteHost(web1);

  if (false) {
    RemoteHost web2 = NewRemoteHost("web1.vpntech.net", 0);
    PrintRemoteHost(web2);
  }

  return(0);
}

