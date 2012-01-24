// $Id: jxref.java,v 1.11 2012-01-19 19:43:07-08 - - $

import java.io.*;
import java.util.Iterator;
import java.util.Map.Entry;
import java.util.NoSuchElementException;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import static java.lang.System.*;

class jxref {
   // Static program constants.
   private static final String STDIN_FILENAME = "-";
   private static final String JARNAME = get_jarname();
   private static final int EXIT_SUCCESS = 0;
   private static final int EXIT_FAILURE = 1;

   // Static exit status variable.
   private static int exit_status = EXIT_SUCCESS;

   // A basename is the final component of a pathname.
   // If a java program is run from a jar, the classpath is the
   // pathname of the jar.
   private static String get_jarname() {
      String jarpath = getProperty ("java.class.path");
      int lastslash = jarpath.lastIndexOf ('/');
      if (lastslash < 0) return jarpath;
      return jarpath.substring (lastslash + 1);
   }


   private static final String WORD_REGEX = "\\w+([-'.:/]\\w+)*";
   private static final Pattern WORD_PATTERN
                      = Pattern.compile (WORD_REGEX);
   private static void xref_file (String filename, Scanner file) {
      err.printf ("TRACE: filename = %s%n", filename);
      listmap map = new listmap();
      for (int linenr = 1; file.hasNextLine(); ++linenr) {
         String line = file.nextLine();
         err.printf ("TRACE: %s: %4d: %s%n", filename, linenr, line);
         Matcher match = WORD_PATTERN.matcher (line);
         while (match.find()) {
            String word = match.group();
            err.printf ("TRACE: word = %s%n", word);
         }
      }
      for (Entry<String, intqueue> entry: map) {
         err.printf ("STUB: %s (%s, %s)%n", entry,
                     entry.getKey(), entry.getValue());
      }
   }

   // For each filename, open the file, cross reference it, and print.
   private static void xref_filename (String filename) {
      if (filename.equals (STDIN_FILENAME)) {
         xref_file (filename, new Scanner (System.in));
      }else {
         try {
            Scanner file = new Scanner (new File (filename));
            xref_file (filename, file);
            file.close();
         }catch (IOException error) {
            exit_status = EXIT_FAILURE;
            err.printf ("%s: %s%n", JARNAME, error.getMessage());
         }
      }
   }

   // Main function scans arguments to cross reference files.
   public static void main (String[] args) {
      if (args.length == 0) {
         // No files specified on the command line.
         xref_filename (STDIN_FILENAME);
      }else {
         // Iterate over each filename given on the command line.
         for (int argi = 0; argi < args.length; ++argi) {
            xref_filename (args[argi]);
         }
      }
      exit (exit_status);
   }

}

