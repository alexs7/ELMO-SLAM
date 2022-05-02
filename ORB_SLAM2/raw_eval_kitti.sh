#!/bin/bash
pathDatasetKITTI='/media/ziwen/T7/kitti_data_odometry_gray/sequences/' #Example, it is necesary to change it by the dataset path
# Single Session Example


echo "Launching kiiti 00 with Monocular sensor"
./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI00-02.yaml "$pathDatasetKITTI"/00 2sh_raw_kitti_mono_00.txt
echo "------------------------------------"
echo "Launching kitti 01 with Monocular sensor"
./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI00-02.yaml "$pathDatasetKITTI"/01  2sh_raw_kitti_mono_01.txt
echo "------------------------------------"
echo "Launching kitti 02 with Monocular sensor"
./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI00-02.yaml "$pathDatasetKITTI"/02 2sh_raw_kitti_mono_02.txt


echo "Launching kiiti 03 with Monocular sensor"
./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI03.yaml "$pathDatasetKITTI"/03 2sh_raw_kitti_mono_03.txt
echo "------------------------------------"

echo "Launching kitti 04 with Monocular sensor"
./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI04-12.yaml "$pathDatasetKITTI"/04  2sh_raw_kitti_mono_04.txt
echo "------------------------------------"

echo "Launching kitti 05 with Monocular sensor"
./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI04-12.yaml "$pathDatasetKITTI"/05  2sh_raw_kitti_mono_05.txt
echo "------------------------------------"
echo "Launching kitti 06 with Monocular sensor"
./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI04-12.yaml "$pathDatasetKITTI"/06 2sh_raw_kitti_mono_06.txt

echo "Launching kitti 07 with Monocular sensor"
./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI04-12.yaml "$pathDatasetKITTI"/07 2sh_raw_kitti_mono_07.txt

echo "Launching kiiti 08 with Monocular sensor"
./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI04-12.yaml "$pathDatasetKITTI"/08 2sh_raw_kitti_mono_08.txt
echo "------------------------------------"
echo "Launching kitti 09 with Monocular sensor"
./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI04-12.yaml "$pathDatasetKITTI"/09  2sh_raw_kitti_mono_09.txt
echo "------------------------------------"
echo "Launching kitti 10 with Monocular sensor"
./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI04-12.yaml "$pathDatasetKITTI"/10 2sh_raw_kitti_mono_10.txt
echo "------------------------------------"
echo "Raw kitti finished"
#python evaluation/evaluate_ate_scale.py "$pathDatasetTUM_VI"/magistrale1_512_16/mav0/mocap0/data.csv f_dataset-magistrale1_512_stereoi.txt --plot magistrale1_512_stereoi.pdf
