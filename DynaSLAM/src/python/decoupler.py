from MaskRCNN import Mask
import os
import cv2

print "Creating new Instance"

images_path = "/home/alex/datasets/KITTI/data_odometry_gray/dataset/sequences/03/"
mask = Mask()

# mask and save left ones:
left_images_path = "/home/alex/datasets/KITTI/data_odometry_gray/dataset/sequences/03/" + "image_0"
left_masks_path = "/home/alex/ELMO-SLAM/DynaSLAM/masks_python/imLeft/"

right_images_path = "/home/alex/datasets/KITTI/data_odometry_gray/dataset/sequences/03/" + "image_1"
right_masks_path = "/home/alex/ELMO-SLAM/DynaSLAM/masks_python/imRight/"

print "Running Segmentation on left images 1/2"
for filename in os.listdir(left_images_path):
    f = os.path.join(left_images_path, filename)
    left_img = cv2.imread(f, cv2.CV_LOAD_IMAGE_UNCHANGED)
    left_mask = mask.GetDynSeg(left_img)
    cv2.imwrite(left_masks_path + filename, left_mask)

print "Running Segmentation on right images 2/2"
for filename in os.listdir(right_images_path):
    f = os.path.join(right_images_path, filename)
    right_img = cv2.imread(f, cv2.CV_LOAD_IMAGE_UNCHANGED)
    right_mask = mask.GetDynSeg(right_img)
    cv2.imwrite(right_masks_path + filename, right_mask)
