/**
* This file is part of ORB-SLAM2.
*
* Copyright (C) 2014-2016 Raúl Mur-Artal <raulmur at unizar dot es> (University of Zaragoza)
* For more information see <https://github.com/raulmur/ORB_SLAM2>
*
* ORB-SLAM2 is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ORB-SLAM2 is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with ORB-SLAM2. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ORBEXTRACTOR_H
#define ORBEXTRACTOR_H

#include <vector>
#include <list>
#include <opencv/cv.h>


namespace ORB_SLAM2
{

// More Conservative on Non-Movable Labels
//const int IdxMove[] = {5, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 19, 21, 22};
//const int IdxNon[] = {0, 1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 20, 23};

//// Less Conservative on Non-Movable Labels
//const int IdxMove[] = {5, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33};
//const int IdxNon[] = {0, 1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 20, 23, 19, 21, 22};

//Deeplab model used trainId instead of id for label:
//Cityscape dataset https://github.com/mcordts/cityscapesScripts/blob/master/cityscapesscripts/helpers/labels.py
    // Less Conservative on Non-Movable Labels
    const int IdxMove[] = {11,12, 13,14,15,16,17,18};//sky and vegetation,
    const int IdxNon[] = {0, 1, 2, 3, 4, 6, 7, 9};



class KeyPointLabeled : public cv::KeyPoint
{
public:
    KeyPointLabeled();
    KeyPointLabeled(const KeyPointLabeled &keyPointLabeled);
    KeyPointLabeled(cv::Point2f _pt, float _size, float _angle, float _response, int _octave, int _class_id);
    KeyPointLabeled(float x, float y, float _size, float _angle, float _response, int _octave, int _class_id);
    void SetLabel(int label);
    
    ~KeyPointLabeled();
    int mnLabel;
    bool mbMovable = 1;
    bool mbMoving = 1;
};

class ExtractorNode
{
public:
    ExtractorNode():bNoMore(false){}

    void DivideNode(ExtractorNode &n1, ExtractorNode &n2, ExtractorNode &n3, ExtractorNode &n4);

    std::vector<KeyPointLabeled> vKeys;
    cv::Point2i UL, UR, BL, BR;
    std::list<ExtractorNode>::iterator lit;
    bool bNoMore;
};

class ORBextractor
{
public:
    
    enum {HARRIS_SCORE=0, FAST_SCORE=1 };

    ORBextractor(int nfeatures, float scaleFactor, int nlevels,
                 int iniThFAST, int minThFAST);

    ~ORBextractor(){}

    // Compute the ORB features and descriptors on an image.
    // ORB are dispersed on the image using an octree.
    // Mask is ignored in the current implementation.
    void operator()( cv::InputArray image, cv::InputArray mask,
      std::vector<KeyPointLabeled>& keypoints,
      cv::OutputArray descriptors);

    int inline GetLevels(){
        return nlevels;}

    float inline GetScaleFactor(){
        return scaleFactor;}

    std::vector<float> inline GetScaleFactors(){
        return mvScaleFactor;
    }

    std::vector<float> inline GetInverseScaleFactors(){
        return mvInvScaleFactor;
    }

    std::vector<float> inline GetScaleSigmaSquares(){
        return mvLevelSigma2;
    }

    std::vector<float> inline GetInverseScaleSigmaSquares(){
        return mvInvLevelSigma2;
    }

    std::vector<cv::Mat> mvImagePyramid;

protected:

    void ComputePyramid(cv::Mat image);
    void ComputeKeyPointsOctTree(std::vector<std::vector<KeyPointLabeled> >& allKeypoints);    
    std::vector<KeyPointLabeled> DistributeOctTree(const std::vector<KeyPointLabeled>& vToDistributeKeys, const int &minX,
                                           const int &maxX, const int &minY, const int &maxY, const int &nFeatures, const int &level);

    //void ComputeKeyPointsOld(std::vector<std::vector<KeyPointLabeled> >& allKeypoints);
    std::vector<cv::Point> pattern;

    int nfeatures;
    double scaleFactor;
    int nlevels;
    int iniThFAST;
    int minThFAST;

    std::vector<int> mnFeaturesPerLevel;

    std::vector<int> umax;

    std::vector<float> mvScaleFactor;
    std::vector<float> mvInvScaleFactor;    
    std::vector<float> mvLevelSigma2;
    std::vector<float> mvInvLevelSigma2;
};

} //namespace ORB_SLAM

#endif

