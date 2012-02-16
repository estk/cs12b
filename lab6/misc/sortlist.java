// $Id: sortlist.java,v 1.1 2012-02-09 18:54:08-08 - - $

import java.util.Scanner;
import static java.lang.System.*;

class sortlist {

   static class list_t {
      node_t head;
   }
   static class node_t {
      String item;
      node_t link;
   }

   static void insertascending (list_t list, String newitem) {
      node_t prev = null;
      node_t curr = list.head;

      // Find the insertion position.
      while (curr != null) {
         if (curr.item.compareTo (newitem) > 0) break;
         prev = curr;
         curr = curr.link;
      }

      // Do the insertion.
      node_t temp = new node_t();
      temp.item = newitem;
      temp.link = curr;
      if (prev == null) list.head = temp;
                   else prev.link = temp;
   }

   public static void main (String[] args) {
      Scanner stdin = new Scanner (System.in);
      list_t list = new list_t();

      while (stdin.hasNextLine()) {
         String line = stdin.nextLine();
         insertascending (list, line);
      }

      for (node_t curr = list.head; curr != null; curr = curr.link) {
         out.printf ("%s%n", curr.item);
      }
   }

}

/*
//TEST// (echo "{{Note the ordering of special characters.}}" \
//TEST// ;echo "testing the sort" \
//TEST// ;echo "is the output sorted" \
//TEST// ;echo "Output should be in lexicographic order." \
//TEST// ;echo "from this program, is sorted" \
//TEST// ;echo "a last line is given" \
//TEST// ;echo "BUT A CAPITAL LINE COMES FIRST" \
//TEST// ;echo "//Slashes//" \
//TEST// ) | runprog -x sortlist.lis -0- ./sortlist
//TEST// mkpspdf sortlist.ps sortlist.j* sortlist.lis*
*/

