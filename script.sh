#!/bin/bash

nEvents=1000000000
echo "/run/beamOn $nEvents" > tmp.mac

for (( i=0; i<100; i++ ))
do
  ./example tmp.mac
  hadd -f "result$i".root result_t*
done
