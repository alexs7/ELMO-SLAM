#!/bin/bash
pathDatasetKITTI='/media/ziwen/T7/kitti_data_odometry_gray/sequences/'


for i in {00..10}
do
   python kitti_to_tum.py ${i}.txt /media/ziwen/T7/kitti_data_odometry_gray/sequences/${i}/times.txt kitt_${i}_tum.txt
done

#python kitti_to_tum.py 00.txt /media/ziwen/T7/kitti_data_odometry_gray/sequences/00/times.txt kitt_00_tum.txt
