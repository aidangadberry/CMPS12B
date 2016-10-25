import java.util.Scanner;
import java.io.*;
import java.util.regex.*;
import static java.lang.System.*;

class dllist {

   public enum position {FIRST, PREVIOUS, FOLLOWING, LAST};

   private class node {
      String item;
      node prev;
      node next;
   }

   private node first = null;
   private node current = null;
   private node last = null;
   private int currentposition = 0;

   public void setposition (position pos) {

      switch (pos) {
         case FIRST:       current = first;
                           break;

         case PREVIOUS:    if (current != first){
                              current = current.prev;
                              break;
                           }

         case FOLLOWING:   if (current != last){
                              current = current.next;
                              break;
                           }

         case LAST:        current = last;
                           break;

         default:          break;
      }
   }

   public void printtest (){
      System.out.println (first.item);
      System.out.println (current.item);
      System.out.println (last.item);
   }

   public boolean isempty () {
      return ((first== null) && (last == null));
   }

   public String getitem () {
      if (isempty()){
         throw new java.util.NoSuchElementException();
      }else{
         return current.item;
      }
   }

   public int getposition () {
      if (isempty()){
         throw new java.util.NoSuchElementException();
      }else{
         int i = 0;
         for (node curr = first; curr != current; curr = curr.next){
            i++;
         }
         return i;
      }
   }

   public void delete () {
      if (isempty()){
         throw new java.util.NoSuchElementException();
      }else{
         if (current == last){
            current.prev.next = null;
            last = current.prev;
            current = last;
         }else{
            current.prev.next = current.next;
            current.next.prev = current.prev;
            current = current.next;
         }
      }
   }

   public void printall () {
      for (node curr = first; curr != last; curr = curr.next){
         System.out.println(curr.item);
      }
      System.out.println(last.item);
   }

   public int writefile (PrintWriter write){
      int count = 0;
      for (node curr = first; curr != last; curr = curr.next){
         write.println(curr.item);
         count++;
      }
      if (last.item != null){
         write.println(last.item);
         count++;
      }
      return count;
   }

   public void printcurr () {
      System.out.println(current.item);
   }

   public void insert (String item, position pos) {
      node newnode = new node();
      newnode.item = item;

      if (first == null){
         first = newnode;
      }
      if (last == null){
         last = newnode;
      }
      if (current == null){
         current = newnode;
      }

      switch (pos) {
         case FIRST:       first = newnode;
                           newnode.next = current;
                           current.prev = newnode;
                           current = newnode;
                           break;

         case PREVIOUS:    if (current == first){
                              first = newnode;
                              newnode.next = current;
                              current.prev = newnode;
                              current = newnode;
                              break;
                           }else{
                              current.prev.next = newnode;
                              newnode.prev = current.prev;
                              newnode.next = current;
                              current = newnode;
                              break;
                           }

         case FOLLOWING:   if (current == last){
                              last = newnode;
                              newnode.prev = current;
                              current.next = newnode;
                              current = newnode;
                              break;
                           }else{
                              current.next = newnode;
                              newnode.prev = current;
                              newnode.next = current.next;
                              current = newnode;
                              break;
                           }
                           

         case LAST:        last = newnode;
                           newnode.prev = current;
                           current.next = newnode;
                           current = newnode;
                           break;

         default:          break;
      }
   }
}
