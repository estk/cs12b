// $Id: jfmt.java,v 1.1 2012-01-05 18:38:44-08 - - $
//
// Starter code for the jfmt utility.  This program is similar
// to the example code jcat.java, which iterates over all of its
// input files, except that this program shows how to use
// String.split to extract non-whitespace sequences of characters
// from each line.
//

import java.io.*;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;
import static java.lang.System.*;

class jfmt {
   // Static variables keeping the general status of the program.
   public static final String JAR_NAME = get_jarname ();
   public static final int EXIT_SUCCESS = 0;
   public static final int EXIT_FAILURE = 1;
   public static int exit_status = EXIT_SUCCESS;
   public static int width = 65;
   
        public static void set_width(String[] args) {
                try {
                        width = Integer.parseInt( args[0].substring(1) );
                }catch (NumberFormatException error) {
                        out.printf ("NumberFormatException: %s%n",
                            error.getMessage());
                }
        }

   // A basename is the final component of a pathname.
   // If a java program is run from a jar, the classpath is the
   // pathname of the jar.
   static String get_jarname () {
      String jarpath = getProperty ("java.class.path");
      int lastslash = jarpath.lastIndexOf ('/');
      if (lastslash < 0) return jarpath;
      return jarpath.substring (lastslash + 1);
   }
   
   // prints an array of words that comprise a paragraph.
   static void printParagraph(StringBuffer strBuf) {
           String str = strBuf.toString();
           str = str.replaceAll("\\s+\n", "\n");
           str = str.replaceAll("\\s+$", "");
           out.printf( "%s%n", str );
   }

   static void format (Scanner infile) {
           out.printf("%n");
           StringBuffer strBuf = new StringBuffer();
           int wcount = 0;
           boolean blankline = false;
           for (int linenr = 1; infile.hasNextLine (); ++ linenr) {
                   String line = infile.nextLine ();
                   List<String> words = new LinkedList<String> ();
                   for (String word : line.split("\\s+")) {
                           if (word.length () == 0) continue;
                           words.add(word);
                   }
                   if (words.size() == 0) {
                           if (blankline) { continue; }
                           else {
                                   printParagraph(strBuf);
                                   out.printf("%n");
                                   blankline = true;
                                   strBuf = new StringBuffer();
                                   wcount = 0;
                           }
                   }
                   else {
                      for (String word : words) {
                                  // out.println("wcount == " + wcount);
                                  if (wcount + word.length() > width) { strBuf.append("\n"); wcount = 0; }
                                  strBuf.append(word + " ");
                                   blankline = false;
                                  wcount += word.length() + 1;
                          }
               }
           }
           if (!blankline) printParagraph(strBuf);
   }


   // Main function scans arguments and opens/closes files.
   public static void main (String[] args) {
      if (args.length == 0) {
         // There are no filenames given on the command line.
         out.printf ("FILE: -%n");
         format (new Scanner (in));
      }else {
         // Check for width option
                 if (args[0].startsWith("-")) {
                    set_width(args);
                        if (args.length == 1) {
                    // There are no filenames given on the command line.
                    out.printf ("FILE: -%n");
                    format (new Scanner (in));
                        }
                        else {
                        String[] tmp = new String[args.length-1];
                        for (int i = 0 ; i < tmp.length; ++i) tmp[i] = args[i+1];
                        args = tmp;
                        // out.print("width: " + width); // debug
                        }
                 }
                 
         // Iterate over each filename given on the command line.
         for (int argix = 0; argix < args.length; ++argix) {
            String filename = args[argix];
            if (filename.equals ("-")) {
               // Treat a filename of "-" to mean System.in.
               out.printf ("FILE: -%n");
               format (new Scanner (in));
            }else {
               // Open the file and read it, or error out.
               try {
                  Scanner infile = new Scanner (new File (filename));
                  // out.printf ("FILE: %s%n", filename); // debug
                  format (infile);
                  infile.close ();
               }catch (IOException error) {
                  exit_status = EXIT_FAILURE;
                  err.printf ("%s: %s%n", JAR_NAME,
                              error.getMessage ());
               }
            }
         }
      }
      exit (exit_status);
   }

}
