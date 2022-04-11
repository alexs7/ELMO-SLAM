#!/bin/bash
pathDatasetKITTI='/media/ziwen/T7/kitti_data_odometry_gray/sequences/' #Example, it is necesary to change it by the dataset path
# Single Session Example

echo "Launching kiiti 08 with Monocular sensor"
./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI04-12.yaml "$pathDatasetKITTI"/08 "$pathDatasetKITTI"/08 sh_kitti_mono_08.txt
echo "------------------------------------"
echo "Launching kitti 09 with Monocular sensor"
./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI04-12.yaml "$pathDatasetKITTI"/09 "$pathDatasetKITTI"/09 sh_kitti_mono_09.txt
echo "------------------------------------"
echo "Launching kitti 10 with Monocular sensor"
./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI04-12.yaml "$pathDatasetKITTI"/10 "$pathDatasetKITTI"/10 sh_kitti_mono_10.txt
echo "------------------------------------"
echo "Evaluation of Magistrale 1 trajectory with Stereo-Inertial sensor"
#python evaluation/evaluate_ate_scale.py "$pathDatasetTUM_VI"/magistrale1_512_16/mav0/mocap0/data.csv f_dataset-magistrale1_512_stereoi.txt --plot magistrale1_512_stereoi.pdf
