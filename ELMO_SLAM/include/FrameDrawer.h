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

#ifndef FRAMEDRAWER_H
#define FRAMEDRAWER_H

#include "Tracking.h"
#include "MapPoint.h"
#include "Map.h"

#include<opencv2/core/core.hpp>
#include<opencv2/features2d/features2d.hpp>

#include<mutex>


namespace ORB_SLAM2
{

class Tracking;
class Viewer;

class FrameDrawer
{
public:
    FrameDrawer(Map* pMap);

    // Update info from the last processed frame.
    void Update(Tracking *pTracker);

    // Draw last processed frame.
    cv::Mat DrawFrame();

protected:

    void DrawTextInfo(cv::Mat &im, int nState, cv::Mat &imText);

    // Info of the frame to be drawn
    cv::Mat mIm;
    int N;
    vector<KeyPointLabeled> mvCurrentKeys;
    vector<bool> mvbMap, mvbVO;
    bool mbOnlyTracking;
    int mnTracked, mnTrackedVO;
    vector<KeyPointLabeled> mvIniKeys;
    vector<int> mvIniMatches;
    int mState;

    Map* mpMap;
    
    const int mnLabelColour[35][3] = {  {0, 0, 0},          //unlabelled
                                        {0, 0, 0},          //ego vehicle
                                        {0, 0, 0},          //rectification border
                                        {0, 0, 0},          //out of roi
                                        {0, 0, 0},          //static
                                        {111, 74, 0},       //dynamic
                                        {81, 0, 81},        //ground
                                        {128, 64, 128},     //road
                                        {244, 35, 232},     //sidewalk
                                        {250, 170, 160},    //parking
                                        {230, 150, 140},    //rail track
                                        {70, 70, 70},       //building
                                        {102, 102, 156},    //wall
                                        {190, 153, 153},    //fence
                                        {180, 165, 180},    //guard rail
                                        {150, 100, 100},    //bridge
                                        {150, 120, 90},     //tunnel
                                        {153, 153, 153},    //pole
                                        {153, 153, 153},    //polegroup
                                        {250, 170, 30},     //traffic light
                                        {220, 220, 0},      //traffic sign
                                        {107, 142, 35},     //vegetation
                                        {152, 251, 152},    //terrain
                                        {70, 130, 180},     //sky
                                        {220, 20, 60},      //person
                                        {255, 0, 0},        //rider
                                        {0, 0, 142},        //car
                                        {0, 0, 70},         //truck
                                        {0, 60, 100},       //bus
                                        {0, 0, 90},         //caravan
                                        {0, 0, 110},        //trailer
                                        {0, 80, 100},       //train
                                        {0, 0, 230},        //motorcycle
                                        {119, 11, 32},      //bicycle
                                        {0, 0, 142}};       //liscense plate, ID -1

    std::mutex mMutex;
};

} //namespace ORB_SLAM

#endif // FRAMEDRAWER_H
