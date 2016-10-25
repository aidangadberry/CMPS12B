// Aidan Gadberry --- agadberr //

import java.io.*;
import java.util.Scanner;
import java.util.regex.*;
import static java.lang.System.*;

class jgrep {

    static void scanfile (Scanner input, String filename,
                          Pattern pattern, options opts){
        int line_number = 1;
        while (input.hasNextLine()){
            String line = input.nextLine();
            boolean matches = pattern.matcher (line).find();
            if (opts.reverse_match){
                matches = !matches;
            }
            if (matches){
                messages.success();
                if (opts.filename_only && opts.number_lines){
                    out.printf ("%s%n", filename);
                    break;
                }else if (opts.number_lines){
                    if (opts.filenames.length == 1){
                        out.printf ("%d:%s%n",
                                    line_number, line);
                    }else{
                        out.printf ("%s:%d:%s%n", filename,
                                    line_number, line);
                    }
                }else if (opts.filename_only){
                    out.printf ("%s%n", filename);
                    break;
                }else{
                    out.printf ("%s%n", line);
                }
            }
            line_number++;
        }
    }

    public static void main (String[] args){
        options opts = new options (args);
        try{
            Pattern pattern = Pattern.compile (opts.regex);
            if (opts.insensitive){
                pattern = Pattern.compile (opts.regex,
                                           Pattern.CASE_INSENSITIVE);
            }
            if (opts.filenames.length == 0){
                scanfile (new Scanner (in), "<stdin>", pattern, opts);
            }else{
                for (int argi = 0; argi < opts.filenames.length;
                     ++argi){
                    try{
                        String filename = opts.filenames[argi];
                        Scanner input = new Scanner (new File
                                                     (filename));
                        scanfile (input, filename, pattern, opts);
                        input.close();
                    }catch (IOException error){
                        messages.warn (error.getMessage());
                    }
                }
            }
        }catch (PatternSyntaxException error){
            messages.die (error.getMessage());
        }
        exit (messages.exit_status);
    }

}
