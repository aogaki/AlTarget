#!/bin/bash

nEvents=100000000
echo "/run/beamOn $nEvents" > tmp.mac

for (( i=0; i<10; i++ ))
do
  ./example tmp.mac
  hadd -f "Data$i".root result_t*
done
