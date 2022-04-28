#!/bin/bash
pathDatasetKITTI='/media/ziwen/T7/kitti_data_odometry_gray/sequences/' #Example, it is necesary to change it by the dataset path
# Single Session Example

#mkdir ostechnix.com-$(date +"%d-%m-%Y")

look_up_dir=${1:-./}

#By default only iterate once
label=${2:-default}


sequence=${3:-00}

pattern="*$label*"

echo $look_up_dir
echo $label
echo $sequence
echo $pattern

lines=$(find . -type d -name $pattern | wc -l)
echo $lines
if test $lines -eq 0
then
  echo "Cannot find directory with the given keyword, check argument 1 and 2"

elif test $lines -eq 1
  then
  echo "find single directory of $(find . -type d -name $pattern )"

else
   echo "find more than one directory as below, try again with more specific keyword"
   echo  $(find . -type d -name $pattern )
   exit 0
fi

#
#
#if [ -d "$ARG1"-"$(date +"%d-%m-%Y")" ]
#then
#    echo "Locating result file in  /path/to/dir exists. skip creating"
#else
#    echo "Error: Directory does not exists, creating"
#    echo mkdir "$ARG1"-"$(date +"%d-%m-%Y")"
#    mkdir "$ARG1"-"$(date +"%d-%m-%Y")"
#fi


#mkdir "$ARG1"-$(date +"%d-%m-%Y")
