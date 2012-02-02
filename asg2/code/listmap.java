// $Id: listmap.java,v 1.13 2012-01-19 19:43:07-08 - - $

import java.util.Iterator;
import java.util.Map.Entry;
import java.util.NoSuchElementException;
import static java.lang.System.*;

class listmap implements Iterable<Entry<String, intqueue>> {

   private node head = null;
   private class node implements Entry<String, intqueue> {
      String key;
      intqueue queue = new intqueue();
      node link;
      public String getKey() {
         return key;
      }
      public intqueue getValue() {
         return queue;
      }
      public intqueue setValue (intqueue queue) {
         throw new UnsupportedOperationException();
      }
   }

   public listmap() {
      err.printf ("TRACE: new %s%n", this);
   }

   public void insert (String key, int linenr) {
      if (head == null) {
         head = new node ();
         head.key = key;
         head.queue.insert(linenr);
         err.println(head.queue); // debug
         return;
      }
      node prev = null;
      node curr = head;
      int cmp = 1;
      // Phase 1 - find insertion point. -- O(n)
      while (curr != null) {
         cmp = curr.key.compareTo (key);
         if (cmp >= 0) break;
         prev = curr;
         curr = curr.link;
      }
      if (cmp == 0) {
         curr.queue.insert(linenr);
      }
      // Phase 2 - insert if not already there. -- O(1)
      else {
         node tmp = new node ();
         tmp.key = key;
         tmp.queue.insert(linenr);
         tmp.link = curr;
         err.println(head.queue); // debug
         if (prev == null) head = tmp;
         else prev.link = tmp;
      }         
      err.printf ("STUB: insert (%s, %s)%n", key, linenr);
   }

   public Iterator<Entry<String, intqueue>> iterator() {
      return new itor();
   }

   private class itor implements Iterator<Entry<String, intqueue>> {
      node curr = head;

      public boolean hasNext() {
         return curr != null;
      }

      public Entry<String, intqueue> next() {
         if (curr == null) throw new NoSuchElementException();
         node next = curr;
         curr = curr.link;
         return next;
      }

      public void remove() {
         throw new UnsupportedOperationException();
      }

   }

}
