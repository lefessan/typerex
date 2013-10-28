(*
TODO: currently, trying to fix several errors in the same file will
fail, as the next errors have incorrect locations since we fixed the file.

We should probably check if the next lines contain an error in the same
file, in which case we should move Emacs error pointer forward.

Another solution would be to Sha1 the compilation buffer, and if we have to
fix the same file with the same compilation buffer, we should stop.
*)

open ErrorLocation
open FixEmacs
open OCamlApproxLexer

(* Try to find if we can get rid of this pattern easily: lex the file
   until we find the longest pattern sequence including this pattern.
   and then, check whether this pattern is part of an or-pattern, in
   which case we can remove it !
*)

(* INT -> x | INT -> x *)

let rec fix_one_pattern loc =
  let file = loc.loc_file in
  let begin_pos = loc.loc_begin_pos in
  let end_pos = loc.loc_end_pos in

  let rec find_bar pos =
    if pos < 0 then 0 else
      match file.file_content.[pos] with
          ' ' | '\t' | '\n' | '\r' -> find_bar (pos-1)
        | '|' -> pos
        | _ -> pos+1
  in
  let begin_pos = find_bar (begin_pos-1) in
  let rec find_end pos =
    if pos < String.length file.file_content then
      match file.file_content.[pos] with
          ' ' | '\n' | '\r' | '\t' -> find_end (pos+1)
        | _ -> pos-1
    else pos
  in
  let end_pos = find_end (end_pos+1) in
  Printf.fprintf stderr "begin_pos = %d/end_pos = %d/%d\n%!"
    begin_pos end_pos (String.length file.file_content);
  Printf.fprintf stderr "PATTERN TO REMOVE: [%s]\n%!"
    (String.sub file.file_content begin_pos (end_pos - begin_pos + 1));
  FixUtils.(
    with_elisp
      [
        find_file loc.loc_file;
        delete_region loc.loc_file (begin_pos+1) (end_pos+2);
        next_error;
      ])

let rec fix loc dirname next_lines =
  fix_one_pattern loc;

  match next_lines with
    |  location_line :: error_line :: next_lines when
        OcpString.starts_with error_line
          "Warning 12: this sub-pattern is unused"
        ->
      let loc = ErrorLocation.parse_location dirname location_line in
      fix loc dirname next_lines

    | _ ->
      FixEmacs.(
        with_elisp
          [
            save_current_buffer;
            print_message "Unused patterns underscored, saved.";
          ])


