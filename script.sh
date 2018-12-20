#!/bin/bash

nEvents=300000000

for T in 70 7
do
<<<<<<< HEAD
  echo "/InSb/Geo/T $T" > tmp.mac
  echo "/run/beamOn $nEvents" >> tmp.mac

  ./example tmp.mac
  hadd -f "resultT$T".root result_t*
=======
  for ((ene=1;ene<=100;ene++))
  do
    echo "/InSb/Geo/T $T" > tmp.mac
    echo "/run/beamOn $nEvents" >> tmp.mac

    ./example tmp.mac
    hadd -f "resultT$T".root result_t*
  done
>>>>>>> 1627419f87ffa3710814b37af82865b69f566662
done
