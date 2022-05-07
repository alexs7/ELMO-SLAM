#!/bin/bash
pathDatasetKITTI='/media/ziwen/T7/kitti_data_odometry_gray/sequences' #Example, it is necesary to change it by the dataset path
# Single Session Example

#mkdir ostechnix.com-$(date +"%d-%m-%Y")

END=${1:-1}

#By default only iterate once

ARG1=${2:-default}




#mkdir "$ARG1"-$(date +"%d-%m-%Y")

for ((i=1;i<=END;i++)); do
    echo $i
    uuid=$(uuidgen)




    if [ -d "$ARG1"-"$(date +"%d-%m-%Y")" ]
    then
        echo "Directory /path/to/dir exists. skip creating"
    else
        echo "Error: Directory does not exists, creating"
        echo mkdir "$ARG1"-"$(date +"%d-%m-%Y")"
        mkdir "$ARG1"-"$(date +"%d-%m-%Y")"
    fi




    echo mkdir "$ARG1"-"$(date +"%d-%m-%Y")"/"$uuid"
    mkdir "$ARG1"-"$(date +"%d-%m-%Y")"/"$uuid"
    touch "$ARG1"-"$(date +"%d-%m-%Y")"/"$uuid"/time.txt
    timefile="$ARG1"-"$(date +"%d-%m-%Y")"/"$uuid"/time.txt
    echo "$timefile" is
    DIRECOTRY="$ARG1"-"$(date +"%d-%m-%Y")"/"$uuid"
    echo "$DIRECOTRY"

    for j in {00..10}; do
      echo $j
#https://stackoverflow.com/questions/12821715/convert-string-into-integer-in-bash-script-leading-zero-number-error/12821845#12821845
      if [[ 10#$j -ge 00 ]] && [[ 10#$j -le 02 ]]
      then
        Vocabulary_file="KITTI00-02.yaml"
        echo "The variable is betwee 0-2."
      elif  [[ 10#$j -eq 03 ]]
      then
        Vocabulary_file="KITTI03.yaml"
        echo "The variable is equal to 3."
      else
        Vocabulary_file="KITTI04-12.yaml"
        echo "The variable is bigger than 3."
      fi

    echo "Launching kiiti $j with Monocular sensor" | tee -a $timefile
#https://unix.stackexchange.com/questions/12068/how-to-measure-time-of-program-execution-and-store-that-inside-a-variable
    TIME_START=$(date +%s.%N)
    ./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/"$Vocabulary_file" "$pathDatasetKITTI"/"$j" ./"$DIRECOTRY"/sh_raw_kitti_mono_"$j".txt
    TIME_END=$(date +%s.%N)
#    DIFF=$(echo "$END - $START" | bc)
      DIFF=$(echo "$TIME_END - $TIME_START" | bc)
#    DIFF=$("$START $END" | awk '{print $2 - $1}')
    echo $DIFF | tee -a $timefile
    done


    done
#
#    echo "Launching kiiti 00 with Monocular sensor"
#    ./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI00-02.yaml "$pathDatasetKITTI"/00 ./"$DIRECOTRY"/sh_raw_kitti_mono_00.txt
#    echo "------------------------------------"
#    echo "Launching kitti 01 with Monocular sensor"
#    ./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI00-02.yaml "$pathDatasetKITTI"/01  ./"$DIRECOTRY"/sh_raw_kitti_mono_01.txt
#    echo "------------------------------------"
#    echo "Launching kitti 02 with Monocular sensor"
#    ./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI00-02.yaml "$pathDatasetKITTI"/02 ./"$DIRECOTRY"/sh_raw_kitti_mono_02.txt
#
#
#    echo "Launching kiiti 03 with Monocular sensor"
#    ./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI03.yaml "$pathDatasetKITTI"/03 ./"$DIRECOTRY"/sh_raw_kitti_mono_03.txt
#    echo "------------------------------------"
#
#    echo "Launching kitti 04 with Monocular sensor"
#    ./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI04-12.yaml "$pathDatasetKITTI"/04  ./"$DIRECOTRY"/sh_raw_kitti_mono_04.txt
#    echo "------------------------------------"
#
#    echo "Launching kitti 05 with Monocular sensor"
#    ./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI04-12.yaml "$pathDatasetKITTI"/05  ./"$DIRECOTRY"/sh_raw_kitti_mono_05.txt
#    echo "------------------------------------"
#    echo "Launching kitti 06 with Monocular sensor"
#    ./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI04-12.yaml "$pathDatasetKITTI"/06 ./"$DIRECOTRY"/sh_raw_kitti_mono_06.txt
#
#    echo "Launching kitti 07 with Monocular sensor"
#    ./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI04-12.yaml "$pathDatasetKITTI"/07 ./"$DIRECOTRY"/sh_raw_kitti_mono_07.txt
#
#    echo "Launching kiiti 08 with Monocular sensor"
#    ./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI04-12.yaml "$pathDatasetKITTI"/08 ./"$DIRECOTRY"/sh_raw_kitti_mono_08.txt
#    echo "------------------------------------"
#    echo "Launching kitti 09 with Monocular sensor"
#    ./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI04-12.yaml "$pathDatasetKITTI"/09  ./"$DIRECOTRY"/sh_raw_kitti_mono_09.txt
#    echo "------------------------------------"
#    echo "Launching kitti 10 with Monocular sensor"
#    ./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI04-12.yaml "$pathDatasetKITTI"/10 ./"$DIRECOTRY"/sh_raw_kitti_mono_10.txt
#    echo "------------------------------------"
#
#
#
#
#
#done

#Todo save uuid list


echo mkdir "$ARG1"-"$(date +"%d-%m-%Y")"
echo "$ARG1"




#echo "Raw kitti finished"
#python evaluation/evaluate_ate_scale.py "$pathDatasetTUM_VI"/magistrale1_512_16/mav0/mocap0/data.csv f_dataset-magistrale1_512_stereoi.txt --plot magistrale1_512_stereoi.pdf
