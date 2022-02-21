#include "scriptexec.h"

#define AbducoHost_IFACE                       \
  vfunc(const char *, name, void)              \
  vfuncDefault(const int, port, AbducoHost ah) \
  vfuncDefault(bool, ok, AbducoHost ah)        \
  vfuncDefault(void, connect, AbducoHost ah)   \
  vfuncDefault(const char *, sessions, AbducoHost ah)

interface(AbducoHost);

#define SshAuth_IFACE                          \
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


int cmd_dev(char *buf, char *c){
  char cmd[1024];

  sprintf(&cmd, "%s", c);
  struct ScriptExecResult  result;
  struct ScriptExecOptions options;

  options = scriptexec_create_options();

  options.runner            = "sh";
  options.working_directory = "/";
  options.exit_on_error     = true;
  options.print_commands    = false;
  result                    = scriptexec_run_with_options(cmd, options);
  log_debug(AC_YELLOW "%s|%d/%s|123 outs", cmd, result.code, result.out);
  if (strlen(result.out) > 0) {
    memcpy(buf, result.out, strlen(result.out));
  }
  free(result.out);
  free(result.err);
  return(result.code);

  exit(result.code);
  if ((int)strlen(result.out) > 0) {
    result.outs = stringfn_split_lines(result.out);
    //   memcpy(r->out, &result.out, strlen(result.out));
  }
  if ((int)strlen(result.err) > 0) {
    result.errs = stringfn_split_lines(result.err);
//    memcpy(r->err, &result.err, strlen(result.err));
  }
  return(true);

  log_debug("Code: %d\nOutput:\n%s\nError:\n%s\nDur:%ldms\nstarted:%ld|ended:%ld\n", result.code, result.out, result.err, result.dur, result.start, result.end);
  log_debug("   out len: %d\n", (int)strlen(result.out));
  log_debug("   outs qty: %d\n", result.outs.count);
  log_debug("   err len: %d\n", (int)strlen(result.err));
  log_debug("   errs qty: %d\n", result.errs.count);
//sprintf(r->dur,"%d",123);
//memcpy(r->code, 123, 3);
//  log_debug("Code: %d\nOutput:\n%s\nError:\n%s\nDur:%ldms\nstarted:%ld|ended:%ld\n", r->code, r->out, r->err, r->dur, r->start, r->end);
//memcpy(r->dur, result.dur, sizeof(r->dur));
/*
 * return(0);
 */
} /* cmd_dev */


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
  return(chan_dev());

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


int dev3(){
  struct ScriptExecResult r1;
  char                    *cmd = "";
  char                    cmd_sb[256];
  char                    cmd_sb_r[256];

  cmd = "hostname -f;id -nu;find /etc/sysconfig";
  char *u = "u1001";

  sprintf(&cmd_sb, "/usr/bin/env passh sudo -u %s \~%s/.bin/sb -r -l", u, u);
  sprintf(&cmd_sb_r, "/usr/bin/env passh sudo -u %s \~%s/.bin/sb -r -l", "root", "root");
  char outbuf[1024 * 32];
  char outbuf_sb[1024 * 32];
  char outbuf_sb_r[1024 * 32];
  int  code_sb   = cmd_dev(&outbuf_sb, cmd_sb);
  int  code_sb_r = cmd_dev(&outbuf_sb_r, cmd_sb_r);
  int  code      = cmd_dev(&outbuf, cmd);

  log_debug("cmd:%s", cmd);
  log_debug("code:%d", code);
  log_debug("stdout:%s", outbuf);
  log_debug(AC_YELLOW "> %d byte screen buffer:\n%s", strlen(outbuf_sb), outbuf_sb);
  log_debug(AC_BLUE "> %d byte screen buffer:\n%s", strlen(outbuf_sb_r), outbuf_sb_r);
  return(code);
}

