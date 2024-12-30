#!/bin/bash

if ! [ -e $1 ]; then
        mkdir -p $1
else
        echo "heb heb"
fi
rnd_num=$(( RANDOM % 30 + 1 ))
echo "$rnd_num"

for (( i=1; i<=$rnd_num; i++)); do
        m=$1/${2}-$i.txt
        touch "$m" && chmod 777 "$m"
        echo "$m created"       
done

for num in "$@"; do
   File=$1/${2}-$num.txt

   if [ -f $File ]; then
           rm "$File"
           echo "$File removed"
   fi
done
