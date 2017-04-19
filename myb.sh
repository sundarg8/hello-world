#!/bin/bash

for thr in {1..4..1}
do
    echo "PROCESS and THREADs Time started ---------------------"
    sleep 3;
    tries=$(( 1200/thr ))
    rm *.o; make && for i in {1..5}; do ./myb_je_malloc $thr $tries  $1 | grep Time; sleep 2; done
done

for thr in {6..12..6}
do
    echo "PROCESS and THREADs Time started ---------------------"
    sleep 3;
    tries=$(( 1200/thr ))
    rm *.o; make && for i in {1..5}; do ./myb_je_malloc $thr $tries  $1 | grep Time; sleep 2; done
done
