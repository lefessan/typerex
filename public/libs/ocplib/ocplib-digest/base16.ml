(******************************************************************************)
(*                                                                            *)
(*                          TypeRex OCaml Tools                               *)
(*                                                                            *)
(*                               OCamlPro                                     *)
(*                                                                            *)
(*    Copyright 2011-2012 OCamlPro                                            *)
(*    All rights reserved.  See accompanying files for the terms under        *)
(*    which this file is distributed. In doubt, contact us at                 *)
(*    contact@ocamlpro.com (http://www.ocamlpro.com/)                         *)
(*                                                                            *)
(******************************************************************************)

    open Checksum

    let hexa_digit x =
      if x >= 10 then Char.chr (Char.code 'A' + x - 10)
      else Char.chr (Char.code '0' + x)

    let to_string s =
      let hash_length = String.length s in
      let p = String.create (hash_length * 2) in
      for i = 0 to hash_length - 1 do
        let c = s.[i] in
        let n = int_of_char c in
        let i0 = (n/16) land 15 in
        let i1 = n land 15 in
        p.[2 * i] <- hexa_digit i0;
        p.[2 * i+1] <- hexa_digit i1;
      done;
      p

    let hexa_digit_case upper x =
      if x >= 10 then Char.chr (Char.code (
            if upper then 'A' else 'a')+ x - 10)
      else Char.chr (Char.code '0' + x)

    let to_string_case upper s =
      let hash_length = String.length s in
      let p = String.create (hash_length * 2) in
      for i = 0 to hash_length - 1 do
        let c = s.[i] in
        let n = int_of_char c in
        let i0 = (n/16) land 15 in
        let i1 = n land 15 in
        p.[2 * i] <- hexa_digit_case upper i0;
        p.[2 * i+1] <- hexa_digit_case upper i1;
      done;
      p

    let of_string s =
      let hash_length = String.length s / 2 in
      let p = String.create hash_length in
      for i = 0 to hash_length - 1 do
        let c0 = s.[2*i] in
        let c1 = s.[2*i+1] in
        p.[i] <- char_of_int ((16 * digit_hexa c0) + digit_hexa c1);
      done;
      p
