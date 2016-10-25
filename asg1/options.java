// Aidan Gadberry --- agadberr //

import static java.lang.System.*;

class options {
    boolean insensitive = false;
    boolean filename_only = false;
    boolean number_lines = false;
    boolean reverse_match = false;
    String regex;
    String[] filenames;

    options (String[] args){
        if (args.length == 0){ 
            err.printf ("Usage: %s [-ilnv] regex [filename...]%n",
                        messages.program_name);
            exit (messages.EXIT_FAILURE);
        }
        if (args[0].charAt(0) == '-'){
            if (args[0].contains("i")){
                insensitive = true;
            }
            if (args[0].contains("l")){
                filename_only = true;
            }
            if (args[0].contains("n")){
                number_lines = true;
            }
            if (args[0].contains("v")){
                reverse_match = true;
            }
            regex = args[1];
            filenames = new String[args.length - 2];
            for (int argi = 2; argi < args.length; ++argi){
                filenames[argi - 2] = args[argi];
            }
            for (int i = 1; i < args[0].length() - 1; i++){
                char c = args[0].charAt(i);
                if (!((c == 'i') || (c == 'l') || (c == 'n') ||
                    (c == 'v'))){
                    err.printf ("Usage: %s [-ilnv] regex[filename...]
                                %n", messages.program_name);
                    break;
                }
            }
        }else{
            regex = args[0];
            filenames = new String[args.length - 1];
            for (int argi = 1; argi < args.length; ++argi){
                filenames[argi - 1] = args[argi];
            }
        }
    }
}
