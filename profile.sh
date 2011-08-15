#!/bin/bash

ramindex=/tmp/ramdisk/wiki
index=../index/wiki

if [ ! -d $index ] ; then
    sudo mount -t tmpfs -o size=256M tmpfs /tmp/ramdisk
    cp -r $index $ramindex
fi

rm gmon.out
{ for i in `seq 1 10` ; do echo -ne "test\nq\n" ; done } | bin/searchfiles -index $ramindex -repeat 10000
mv profile.txt profile.txt.bak
gprof bin/searchfiles > profile.txt
