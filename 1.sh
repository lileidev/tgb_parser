#!/bin/bash

clear 

deleted=`cat result.txt | grep delete | awk '{print $2}'`

result=`cat result.txt`

for i in ${deleted};
do
  echo ${i}
  result=`echo ${result} | sed 's/'"${i}"'/ /g'`
done

echo ${result}
