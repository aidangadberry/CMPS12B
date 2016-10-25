// Aidan Gadberry --- agadberr //

import static java.lang.System.*;

class messages{
    public static final int EXIT_SUCCESS = 0;
    public static final int EXIT_FAILURE = 1;
    public static final int EXIT_ERROR = 2;
    public static final String program_name =  "jgrep.java";
    public static int exit_status = EXIT_FAILURE;

    //
    // constructor - prevents instantiation: only static fns allowed.
    //
    private messages(){
        throw new UnsupportedOperationException();
    }

    //
    // basename - strips the dirname and returns only the basename.
    //                See:  man -s 3c basename
    //
    public static String basename (String pathname){
        if (pathname == null || pathname.length () == 0) return ".";
            String[] paths = pathname.split ("/");
        for (int index = paths.length - 1; index >= 0; --index) {
            if (paths[index].length () > 0) return paths[index];
        }
        return "/";
    }

    public static void success (){
        exit_status = EXIT_SUCCESS;
    }
    //
    // warn - print a warning and set exit status to failure.
    //
    public static void warn (Object... args){
        exit_status = EXIT_ERROR;
        err.printf ("%s", program_name);
        for (Object arg: args) err.printf (": %s", arg);
        err.printf ("%n");
    }

    //
    // die - print a warning and exit program.
    //
    public static void die (Object... args){
        warn (args);
        exit (exit_status);
    }
}
