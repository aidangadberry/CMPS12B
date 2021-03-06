#!/bin/sh
# $Id: mk,v 1.9 2014-04-30 17:37:19-07 - - $
#
# This script takes the names of C source files and compiles them
# into executable images.  Each source must be a complete program.
#

export PATH=$PATH:/afs/cats.ucsc.edu/courses/cmps012b-wm/bin
GCC='gcc -g -O0 -Wall -Wextra -std=gnu99'

for CSOURCE in *.c
do
   EXECBIN=${CSOURCE%.c}
   if [ "$CSOURCE" == "$EXECBIN" ]
   then
      echo $0: $CSOURCE: is not a C source file
   else
      echo CSOURCE=$CSOURCE EXECBIN=$EXECBIN
      set -x
      cid + $CSOURCE
      checksource $CSOURCE
      $GCC $CSOURCE -o $EXECBIN -lm 2>&1 | tee $CSOURCE.log 2>&1
      set +x
      echo ============================================================
   fi
done
