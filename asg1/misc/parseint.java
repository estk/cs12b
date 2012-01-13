// $Id: parseint.java,v 1.6 2012-01-05 19:31:08-08 - - $

//
// Illustrate try-catch convert args to integers.
// Iterate over each element of args and attempt to convert it to
// an integer.  If it succeeds, print the integer.  If not, catch
// the error and print an error message.
//

import static java.lang.System.*;

class parseint {
   public static void main (String[] args) {
      for (int argi = 0; argi < args.length; ++argi) {
         String arg = args[argi];
         out.printf ("args[%d] = \"%s\": ", argi, arg);
         try {
            int value = Integer.parseInt (arg);
            out.printf ("is int %d%n", value);
         }catch (NumberFormatException error) {
            out.printf ("NumberFormatException: %s%n",
                        error.getMessage());
         }
      }
   }
}

//TEST// ./parseint 214748 hello -33 '' 987 >parsetest.out
//TEST// mkpspdf parsetest.ps parseint.java parsetest.out

