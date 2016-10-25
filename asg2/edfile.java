import java.util.Scanner;
import java.io.*;
import java.util.regex.*;
import static java.lang.System.*;

class edfile{

   public static int exit_status = 0;

   public static void main (String[] args) {
      System.out.printf("File name: %s.java%n", auxlib.program_name());
      boolean want_echo = false;
      dllist lines = new dllist ();

      if(args.length > 0){
         if ((args[0].charAt(0) == '-') && (args[0].charAt(1) == 'e')){
            want_echo = true;
            if (args.length > 1){
               for (int i = 1; i < args.length; i++){
                  try{
                     String filename = args[i];
                     Scanner input = new Scanner (new File (filename));
                     fileread(input,lines);
                     input.close();
                  }catch (IOException error){
                     err.printf ("java.io.FileNotFoundException");
                     exit_status = 1;
                  }
               }
            }
         }else{
            for (int i = 0; i < args.length; i++){
               try{
                  String filename = args[i];
                  Scanner input = new Scanner (new File (filename));
                  fileread(input,lines);
                  input.close();
               }catch (IOException error){
                  err.printf ("java.io.FileNotFoundException");
                  exit_status = 1;
               }
            }
         }
      }

      Scanner stdin = new Scanner (in);
      for (;;) {
         out.printf ("%s: ", auxlib.program_name());
         if (! stdin.hasNextLine()) break;
         String inputline = stdin.nextLine();
         if (want_echo) out.printf ("%s%n", inputline);
         if (inputline.matches ("^\\s*$")) continue;
         char command = inputline.charAt(0);
         switch (command) {
            case '#': break;
            case '$': lines.setposition(dllist.position.LAST);
                      lines.printcurr();
                      break;
            case '*': lines.setposition(dllist.position.LAST);
                      lines.printall();
                      break;
            case '.': lines.printcurr();
                      break;
            case '0': lines.setposition(dllist.position.FIRST); 
                      lines.printcurr();
                      break;
            case '<': lines.setposition(dllist.position.PREVIOUS); 
                      lines.printcurr();
                      break;
            case '>': lines.setposition(dllist.position.FOLLOWING);
                      lines.printcurr();
                      break;
            case 'a': lines.insert(inputline.substring(1), 
                                   dllist.position.FOLLOWING);
                      lines.setposition(dllist.position.FOLLOWING);
                      lines.printcurr();
                      break;
            case 'd': lines.delete();
                      break;
            case 'i': lines.insert(inputline.substring(1),
                                   dllist.position.PREVIOUS);
                      lines.setposition(dllist.position.PREVIOUS);
                      lines.printcurr();
                      break;
            case 'r': try{
                         String filename = inputline.substring(1);
                         Scanner input = new Scanner (new File 
                                                      (filename));
                         fileread(input,lines);
                         lines.setposition(dllist.position.LAST);
                         input.close();
                      }catch (IOException error){
                         err.printf ("java.io.FileNotFoundException%n"
                                     );
                         exit_status = 1;
                      }

                      break;
            case 'w': System.out.println(filewrite(
                                         inputline.substring(1),lines)
                                         + " lines written");
                      break;
            default : System.out.println("Invalid command: " + 
                                         command);
                      exit_status = 1;
                      break;
         }
      }
      exit (exit_status);
   }

   public static void fileread(Scanner input, dllist lines){
      int linecount = 0;
      while(input.hasNextLine()){
         String line = input.nextLine();
         lines.insert(line,dllist.position.FOLLOWING);
         linecount++;
      }
      System.out.println(linecount + " lines read");
   }

   public static int filewrite(String filename, dllist lines){
      try{
         PrintWriter writer = new PrintWriter(filename + ".txt",
                                              "UTF-8");
         int count = lines.writefile(writer);
         writer.close();
         return count;
      }catch (IOException error){
         err.printf ("java.io.FileNotFoundException%n");
         exit_status = 1;
         return 0;
      }
   }
}
