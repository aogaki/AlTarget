#!/bin/bash

oldClassName=$1
newClassName=$2

for file in `find . -name "$oldClassName*"`
do
    echo $file
    sed -i -e "s/$oldClassName/$newClassName/g" $file
    newFileName=${file/$oldClassName/$newClassName}
    echo $newFileName
    mv $file $newFileName
done

sed -i -e "s/$oldClassName/$newClassName/g" ./main.cpp
