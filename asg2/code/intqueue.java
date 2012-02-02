// $Id: intqueue.java,v 1.4 2012-01-19 19:43:07-08 - - $

import java.util.Iterator;
import java.util.NoSuchElementException;

class intqueue implements Iterable<Integer> {

   private int count = 0;
   private node front = null;
   private node rear = null;
   private class node {
      int linenr;
      node link;
   }

   public void insert (int number) {
      ++count;
      node tmp = new node ();
      tmp.linenr = number;
      tmp.link = null;
      if (rear == null) front = tmp;
      else rear.link = tmp;
      rear = tmp;
   }

   public boolean empty() {
      return count == 0;
   }

   public int getcount() {
      return count;
   }

   public String toString() {
      String res = String.format("[%s]", count);
      for (int n : this) {
         res += " " + n;
      }
      return res;
   }

   public Iterator<Integer> iterator() {
      return new itor();
   }

   private class itor implements Iterator<Integer> {
      node curr = front;

      public boolean hasNext() {
         return curr != null;
      }

      public Integer next() {
         if (curr == null) throw new NoSuchElementException();
         Integer next = curr.linenr;
         curr = curr.link;
         return next;
      }

      public void remove() {
         throw new UnsupportedOperationException();
      }
   }

}

