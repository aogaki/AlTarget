#!/bin/bash

nEvents=300000000

for T in 70 7
do
  echo "/InSb/Geo/T $T" > tmp.mac
  echo "/run/beamOn $nEvents" >> tmp.mac

  ./example tmp.mac
  hadd -f "resultT$T".root result_t*
done
