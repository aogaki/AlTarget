#!/bin/bash

nEvents=1000000

for T in 200 250 300 350 400 450 500 550 600
do
  for ((ene=1;ene<=100;ene++))
  do
    echo "/InSb/Geo/T $T" > tmp.mac
    echo "/InSb/Primary/K $ene" >> tmp.mac
    echo "/run/beamOn $nEvents" >> tmp.mac

    ./example tmp.mac
    hadd -f "resultT$T""Ene$ene".root result_t*
  done
done
