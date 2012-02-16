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

   //java.util.TreeMap <String, String> tree
         //= new java.util.TreeMap <String, String> ();

   public String get (String key) {
      tree res = find(root, key);
      out.println("got: " + res.key + res.value);
      if (res == null) return null;
      return res.value;
   }

   private tree find (tree curr, String key) {
      if (curr == null) return null;
      out.println("looking at: " + curr.value);

      if (key.compareTo(curr.key) < 0) {
        return find (curr.left, key);
      } else if (key.compareTo(curr.key) > 0) {
        return find (curr.right, key);
      }
      out.println("returning: " + curr.key); return curr;
   }

   public String put (String key, String value) {
      if (root == null) {
         tree tmp = new tree();
         tmp.key = key; tmp.value = value;
         root = tmp;
         return value;
      }
      return put_recur(root, key, value);
   }

   private String put_recur (tree curr, String key, String value) {
      if (curr == null) return null;

      if (key.compareTo(curr.key) < 0) {
        if (curr.left == null) {
          tree tmp = new tree();
          tmp.key = key; tmp.value = value;
          curr.left = tmp;
          out.println(curr.key+ ".left" +"->"+ tmp.key);
          return curr.value;
        } else {
        return put_recur (curr.left, key, value);
        }
      } else if (key.compareTo(curr.key) > 0) {
        if (curr.right == null) {
          tree tmp = new tree();
          tmp.key = key; tmp.value = value;
          curr.right = tmp;
          out.println(curr.key+ "right" +"->"+ tmp.key);
          return curr.value;
        } else {
        return put_recur (curr.right, key, value);
        }
      } else {
        String res = curr.value;
        curr.value = value;
        return res;
      }
   }

   private void inorder(tree node, int depth) {
      if (node == null) return;
      inorder(node.left, depth+1);

      out.printf("%3d \"%s\" \"%s\" %s %s%n",
              depth, node.key, node.value, node.left, node.right);

      inorder(node.right, depth+1);
   }

   public void debug_tree () {
      out.println("in debug fun");
      inorder(root, 0);
   }

   //private void debug_tree_recur (tree node, int depth) {
   //}

}
