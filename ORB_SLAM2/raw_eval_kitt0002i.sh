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

