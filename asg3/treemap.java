// $Id: treemap.java,v 1.1 2014-01-16 17:44:47-08 - - $

import static java.lang.System.*;

class treemap <key_t extends Comparable <key_t>, value_t> {

   private class node {
      key_t key;
      value_t value;
      node left;
      node right;
   }
   private node root;

   private void debug_dump_rec (node tree, int depth) {
      throw new UnsupportedOperationException ();
   }

   private void do_visit_rec (visitor <key_t, value_t> visit_fn,
                              node tree) {
      throw new UnsupportedOperationException ();
   }

   public value_t get (key_t key) {
      throw new UnsupportedOperationException ();
   }

   public value_t put (key_t key, value_t value) {
      throw new UnsupportedOperationException ();
   }

   public void debug_dump () {
      debug_dump_rec (root, 0);
   }

   public void do_visit (visitor <key_t, value_t> visit_fn) {
      do_visit_rec (visit_fn, root);
   }

}