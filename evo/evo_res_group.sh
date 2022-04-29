#!/bin/bash
pathDatasetKITTI='/media/ziwen/T7/kitti_data_odometry_gray/sequences/' #Example, it is necesary to change it by the dataset path
# Single Session Example

#mkdir ostechnix.com-$(date +"%d-%m-%Y")

look_up_dir=${1:-./}

#By default only iterate once
label=${2:-default}


sequence=${3:-00}

sequence_pattern="*$sequence*"

pattern="*$label*"

echo "$look_up_dir"
echo "$label"

echo "$sequence"
echo "$pattern"


lines=$(find "$look_up_dir" -type d -name  "$pattern" | wc -l)
echo find "$look_up_dir" -type d -name  "$pattern"
echo "$lines"
if test "$lines" -eq 0
then
  echo "Cannot find directory with the given keyword, check argument 1 and 2"
  exit 0
elif test "$lines" -eq 1
  then
  echo find single directory of "$(find "$look_up_dir" -type d -name "$pattern")"
#  echo $(basename $(find $look_up_dir -type d -name $pattern))

else
   echo "find more than one directory as below, try again with more specific keyword:"
   echo  "$(find "$look_up_dir" -type d -name "$pattern")"
   exit 0
fi

found_dir=$(find "$look_up_dir" -type d -name "$pattern")
echo " $found_dir"
lines=$(find "$look_up_dir" -name "$pattern" | wc -l)
echo "find $lines: at $found_dir"
echo $(find "$found_dir" -name "$sequence_pattern")


result_folder="$(basename $(find "$look_up_dir" -type d -name "$pattern"))"_result
echo  "$result_folder"

if [ -d "$result_folder" ]
then
    echo "Result folder $result_folder exists. skip creating and processing result text file"
else
    echo "Make directory for containign result file with name $result_folder"
    mkdir "$result_folder"

    IFS=$'\n'
    for i in $(find "$found_dir" -name "$sequence_pattern");
    do
#        echo "$i"
        evo_ape tum /home/ziwen/elmo_ws/ELMO-SLAM/evo/test_set/data_odometry_poses/dataset/poses/kitt_"$sequence"_tum.txt "$i" -as --save_results "$result_folder"/$(basename $(dirname "$i"))_"$sequence"_result.zip
    #     --plot  --plot_mode xz
    done
    unset IFS

fi



evo_res "$result_folder"/*.zip -p --use_filenames


