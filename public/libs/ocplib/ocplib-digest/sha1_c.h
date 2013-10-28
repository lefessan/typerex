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

#ifndef _SHA1_H
#define _SHA1_H

#include <caml/mlvalues.h>
#include <caml/fail.h>
#include <caml/alloc.h>
#include <caml/memory.h>

#include <errno.h>
#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/alloc.h>
#include <caml/memory.h>
#include <signal.h>

/*
 *
 * This file comes from RFC 3174. Inclusion in gtk-gnutella is:
 */

#if __STDC_VERSION__ >= 199901L
#include <stdint.h>
#else
#endif

typedef unsigned char uint8;

/*
 * If you do not have the ISO standard stdint.h header file, then you
 * must typdef the following:
 *    name              meaning
 *  guint32         unsigned 32 bit integer
 *  guint8          unsigned 8 bit integer (i.e., unsigned char)
 *  gint    		integer of >= 16 bits
 *
 */

#ifndef _SHA_enum_
#define _SHA_enum_
enum
{
    shaSuccess = 0,
    shaNull,            /* Null pointer parameter */
    shaInputTooLong,    /* input data too long */
    shaStateError       /* called Input after Result */
};
#endif
#define SHA1HashSize 20

/*
 *  This structure will hold context information for the SHA-1
 *  hashing operation
 */
typedef struct sha1_context
{
    uint32 Intermediate_Hash[SHA1HashSize/4]; /* Message Digest  */

    uint32 Length_Low;            /* Message length in bits      */
    uint32 Length_High;           /* Message length in bits      */

                               /* Index into message block array   */
    int Message_Block_Index;
    uint8 Message_Block[64];      /* 512-bit message blocks      */

    int Computed;               /* Is the digest computed?         */
    int Corrupted;             /* Is the message digest corrupted? */
} sha1_context;

typedef struct sha1_context SHA1_CTX;


int sha1_begin(SHA1_CTX*);
int sha1_hash(SHA1_CTX*, const unsigned char [], unsigned long);
int sha1_end(SHA1_CTX*, unsigned char hval[]);


#endif
