#!/bin/bash

a=`date +%s`

b=`date +%s`

ip=$1
port=$2
ldir=$3
rdir=$4
user=$5
passwd=$6
file=$7
result=$8

logfile=ftp_${a}_${b}.log

echo "error" > ${result}

echo "
open ${ip} ${port}
passive off
prompt off
user ${user} ${passwd}
binary
pwd
cd ${rdir}
pwd
lcd ${ldir}
put ${file} ${file}.tmp 
rename ${file}.tmp ${file}
close
bye
" |ftp -v -n > ${logfile}

str=`cat ${logfile}|grep Windows_NT`

if [ -z "$str" ]
then
    echo "unix"            
    cotr=`cat ${logfile}|grep '150 Ok to send data'`
    if [ -z "$cotr" ]
    then
         echo "error" > ${result}
    else
         echo "sucess" > ${result}

    fi
else
    cotr=`cat ${logfile}|grep '226 Transfer complete'`
    if [ -z "$cotr" ]
    then
         echo "error" > ${result}
    else
         echo "sucess" > ${result} 
     
    fi
fi

rm ${logfile}
