// $Id: jxref.java,v 1.1 2014-01-16 17:44:47-08 - - $

import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;

class jxref {
   static final String STDIN_NAME = "-";

   static class printer implements visitor <String, queue <Integer>> {
      public void visit (String key, queue <Integer> value) {
         out.printf ("%s %s", key, value);
         for (int linenr: value) out.printf (" %d", linenr);
         out.printf ("%n");
      }
   }

   static void xref_file (String filename, Scanner scan) {
      treemap <String, queue <Integer>> map =
            new treemap <String, queue <Integer>> ();
      for (int linenr = 1; scan.hasNextLine (); ++linenr) {
         for (String word: scan.nextLine().split ("\\W+")) {
            if (word.matches ("^\\d*$")) continue;
            out.printf ("%s: %d: %s%n", filename, linenr, word);
         }
      }
      visitor <String, queue <Integer>> print_fn = new printer ();
      map.do_visit (print_fn);
   }

   public static void main (String[] args) {
      if (args.length == 0) {
         xref_file (STDIN_NAME, new Scanner (in));
      }else {
         for (int argi = 0; argi < args.length; ++argi) {
            String filename = args[argi];
            if (filename.equals (STDIN_NAME)) {
               xref_file (STDIN_NAME, new Scanner (in));
            }else {
               try {
                  Scanner scan = new Scanner (new File (filename));
                  xref_file (filename, scan);
                  scan.close ();
               }catch (IOException error) {
                  auxlib.warn (error.getMessage ());
               }
            }
         }
      }
      auxlib.exit ();
   }

}