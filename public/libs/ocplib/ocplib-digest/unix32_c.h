/******************************************************************************/
/*                                                                            */
/*                          TypeRex OCaml Tools                               */
/*                                                                            */
/*                               OCamlPro                                     */
/*                                                                            */
/*    Copyright 2011-2012 OCamlPro                                            */
/*    All rights reserved.  See accompanying files for the terms under        */
/*    which this file is distributed. In doubt, contact us at                 */
/*    contact@ocamlpro.com (http://www.ocamlpro.com/)                         */
/*                                                                            */
/******************************************************************************/

#if !defined(_UNIX32_C_H)
#define _UNIX32_C_H


#if defined(__MINGW32__)

#define FD_SETSIZE 256

#include <winsock.h>

struct filedescr {
  union {
    HANDLE handle;
    SOCKET socket;
  } fd;
  enum { KIND_HANDLE, KIND_SOCKET } kind;
};

#define Fd_val(v) (((struct filedescr *) Data_custom_val(v))->fd.handle)
#define Socket_val(v) (((struct filedescr *) Data_custom_val(v))->fd.socket)

typedef HANDLE OS_FD;
typedef SOCKET OS_SOCKET;
typedef unsigned int uint;
extern void win32_maperr(unsigned long errcode);

#else


#define Fd_val(v) Int_val(v)
#define Socket_val(v) Int_val(v)

typedef int OS_FD;
typedef int OS_SOCKET;

#endif


#include <caml/fail.h>


#include <errno.h>
#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/alloc.h>
#include <caml/memory.h>
#include <signal.h>

#ifdef HAS_SIGNALS_H
#include <signals.h>
#endif

#include <sys/types.h>
#ifdef HAS_SYS_TIME_H
#include <sys/time.h>
#endif

#ifdef HAS_SYS_SELECT_H
#include <sys/select.h>
#endif

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef HAS_UNISTD
#include <unistd.h>
#else
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#endif

#if defined(__OpenBSD__) || defined(__FreeBSD__)
#include <string.h>
#endif

#if defined(HAS_SYS_MMAN_H)
#include <sys/mman.h>
#endif


#define Nothing ((value) 0)

extern void unix_error (int errcode, char * cmdname, value arg) Noreturn;
extern void uerror (char * cmdname, value arg) Noreturn;

static int seek_command_table[] = {
  SEEK_SET, SEEK_CUR, SEEK_END
};

extern int64 os_getfilesize(char *path);
extern int64 os_getfdsize(OS_FD fd);
#endif
