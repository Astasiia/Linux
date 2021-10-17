#!/bin/sh

IFS=$'\n'

if [ -z "$1" ]
then
  timeSleep=0
else
  timeSleep="$1"
fi

textFile=()
indexStr=()
allLen=0
while read -r textStr
do
  textFile+=($textStr)
  newLen=$(echo ${#textStr})
  allLen=$(($allLen+$newLen))
  indexStr+=($(($allLen)))
done

tput clear
k=0
position=()
while [ "$k" -lt "$allLen" ]
do
  position+=($k)
  k=$(($k+1))
done
k=$(($allLen-1))
while [ "$k" -gt 1 ]
do
  range=$k
  n=$RANDOM%range
  h=${position[$k]}
  position[$k]=${position[$n]}
  position[$n]=$h
  k=$(($k-1))
done

for pos in "${position[@]}"
do
  n=0
  start=0
  for var in "${indexStr[@]}"
  do
    if [ "$pos" -gt "$var" ]
    then
      start=$var
      n=$(($n+1))
    else
      y=$n
      x=$(($pos-$start-1))
      st="${textFile[$y]}"
      sym="${st:$x:1}"
      break
    fi
  done
  k=$(($k+1))
  tput cup $y $x
  echo "$sym"
  sleep $timeSleep
done
maxy=$(echo ${#indexStr[@]})
tput cup $maxy 0
