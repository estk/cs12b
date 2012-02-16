//
// Starter code for the airport utility.
//

import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;

class airport {
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


   public static treemap load_database (String database_name) {
      treemap tree = new treemap ();
      try {
         Scanner database = new Scanner (new File (database_name));
         for (int linenr = 1; database.hasNextLine(); ++linenr) {
            String line = database.nextLine();
            if (line.matches ("^\\s*(#.*)?$")) continue;
            String[] keyvalue = line.split (":");
            if (keyvalue.length != 2) {
               exit_status = EXIT_FAILURE;
               err.printf ("%s: %s:%d: invalid line", 
                           JARNAME, database_name, linenr);
               continue;
            }
            tree.put (keyvalue[0], keyvalue[1]);
         }
         database.close();
      }catch (IOException error) {
         exit_status = EXIT_FAILURE;
         err.printf ("%s: %s%n", JARNAME, error.getMessage());
      }
      return tree;
   } 

   public static void main (String[] args) {
      String database = null;
      boolean debug = false;

      if (args.length > 2) usage();
      else if (args.length == 2) {
        if ( args[0] != "-d" ) usage();
        if ( args[1].charAt(0) == '-' ) usage();
        debug = true;
        database = args[1];
      }
      else if (args.length == 1) {
         if ( args[0].charAt(0) == '-' ) usage();
         database = args[0];
      }
      else usage();

      treemap tree = load_database (database);
      Scanner stdin = new Scanner (in);

      if (!debug) {
      while (stdin.hasNextLine()) {
         String airport = stdin.nextLine().toUpperCase().trim();
         String airport_name = tree.get (airport);
         if (airport_name == null) {
            out.printf ("%s: no such airport%n", airport);
         }else {
            out.printf ("%s = %s%n", airport, airport_name);
         }
      }
      }else {
      tree.debug_tree ();
      exit (exit_status);
      }
   }

   static void usage() {
     out.println("airport [-d] database");
     exit(0);
   }
}
