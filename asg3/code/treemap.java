// $Id: treemap.java,v 1.1 2012-02-07 15:43:17-08 - - $

// Development version of treemap.
// To be deleted and replaced by an actual implementation that
// does *NOT* use java.util.TreeMap.

import static java.lang.System.*;

class treemap {

   class tree {
      String key;
      String value;
      tree left;
      tree right;
   }
   tree root = null;

   java.util.TreeMap <String, String> tree
         = new java.util.TreeMap <String, String> ();

   public String get (String key) {
      return tree.get (key);
   }

   public String put (String key, String value) {
      return tree.put (key, value);
   }

   public void debug_tree () {
      debug_tree_recur (root, 0);
   }

   private void debug_tree_recur (tree node, int depth) {
   }

}
