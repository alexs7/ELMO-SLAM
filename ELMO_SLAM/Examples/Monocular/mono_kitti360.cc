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


#include<iostream>
#include<algorithm>
#include<fstream>
#include<chrono>
#include<iomanip>

#include<opencv2/core/core.hpp>

#include"System.h"
#define KOGMO_TIMESTAMP_TICKSPERSECOND 1000000000.0
using namespace std;

void LoadImages(const string &strPathToSequence, vector<string> &vstrImageFilenames,
                vector<double> &vTimestamps);

void LoadLabels(const string &strPathToLabel, vector<string> &vstrLabel,
                vector<double> &vTimestamps);
double String2Timestamp(const char *time_str);
int main(int argc, char **argv)
{
    if(argc != 5)
    {
        cerr << endl << "Usage: ./mono_kitti path_to_vocabulary path_to_settings path_to_sequence path_to_label" << endl;
        return 1;
    }

    // Retrieve paths to images
    vector<string> vstrImageFilenames;
    vector<double> vTimestamps;
    LoadImages(string(argv[3]), vstrImageFilenames, vTimestamps);
    vector<string> vstrLabel;
    LoadLabels(string(argv[4]), vstrLabel, vTimestamps);

    int nImages = vstrImageFilenames.size();
    int nLabels = vstrLabel.size();
    
    if (nLabels != nImages)
    {
        cerr << endl << "Images and Labels disagree with each other. " << endl;
        return 1;
    }

    // Create SLAM system. It initializes all system threads and gets ready to process frames.
    ORB_SLAM2::System SLAM(argv[1],argv[2],ORB_SLAM2::System::MONOCULAR,true);

    // Vector for tracking time statistics
    vector<float> vTimesTrack;
    vTimesTrack.resize(nImages);

    cout << endl << "-------" << endl;
    cout << "Start processing sequence ..." << endl;
    cout << "Images in the sequence: " << nImages << endl << endl;

    // Main loop
    cv::Mat im;
    cv::Mat label;
    for(int ni=0; ni<nImages; ni++)
    {
        // Read image from file
        im = cv::imread(vstrImageFilenames[ni],CV_LOAD_IMAGE_UNCHANGED);
        // Read left and right labels frome file
        label = cv::imread(vstrLabel[ni],CV_LOAD_IMAGE_UNCHANGED);
        double tframe = vTimestamps[ni];

        if(im.empty())
        {
            cerr << endl << "Failed to load image at: " << vstrImageFilenames[ni] << endl;
            return 1;
        }
        
        if(label.empty())
        {
            cerr << endl << "Failed to load label at: " << string(vstrLabel[ni]) << endl;
            return 1;
        }

#ifdef COMPILEDWITHC11
        std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
#else
        std::chrono::monotonic_clock::time_point t1 = std::chrono::monotonic_clock::now();
#endif

        // Pass the image to the SLAM system
        SLAM.TrackMonocular(im,label,tframe);

#ifdef COMPILEDWITHC11
        std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
#else
        std::chrono::monotonic_clock::time_point t2 = std::chrono::monotonic_clock::now();
#endif

        double ttrack= std::chrono::duration_cast<std::chrono::duration<double> >(t2 - t1).count();

        vTimesTrack[ni]=ttrack;

        // Wait to load the next frame
        double T=0;
        if(ni<nImages-1)
            T = vTimestamps[ni+1]-tframe;
        else if(ni>0)
            T = tframe-vTimestamps[ni-1];

        if(ttrack<T)
            usleep((T-ttrack)*1e6);
    }

    // Stop all threads
    SLAM.Shutdown();

    // Tracking time statistics
    sort(vTimesTrack.begin(),vTimesTrack.end());
    float totaltime = 0;
    for(int ni=0; ni<nImages; ni++)
    {
        totaltime+=vTimesTrack[ni];
    }
    cout << "-------" << endl << endl;
    cout << "median tracking time: " << vTimesTrack[nImages/2] << endl;
    cout << "mean tracking time: " << totaltime/nImages << endl;

    // Save camera trajectory
//    SLAM.SaveKeyFrameTrajectoryTUM("KeyFrameTrajectory.txt");
    SLAM.SaveTrajectoryKITTI("FrameTrajectory.txt");
    return 0;
}

void LoadImages(const string &strPathToSequence, vector<string> &vstrImageFilenames, vector<double> &vTimestamps)
{
    ifstream fTimes;
    string strPathTimeFile = strPathToSequence + "image_00/timestamps.txt";
    fTimes.open(strPathTimeFile.c_str());

    //TODO Swap timestamp loading script fitting the new KITTI-360 timestamp format.
    https://github.com/autonomousvision/kitti360Scripts/blob/b74933bb4d358d4b8f4c371528f036be2092060c/kitti360scripts/devkits/accumuLaser/src/commons.cpp
    while(!fTimes.eof())
    {
        string s;
        getline(fTimes,s);
        if(!s.empty())
        {
            double ts = String2Timestamp(s.c_str());

//            stringstream ss;
//            ss << s;
//            double t;
//            ss >> t;
            cout<<ts<<endl;
            vTimestamps.push_back(ts/1e9); //Kitti timestamp is in ns
        }
    }

    string strPrefixLeft = strPathToSequence + "image_00/data_rect/";

    const int nTimes = vTimestamps.size();
    vstrImageFilenames.resize(nTimes);

    for(int i=0; i<nTimes; i++)
    {
        stringstream ss;
        ss << setfill('0') << setw(10) << i;
        vstrImageFilenames[i] = strPrefixLeft + ss.str() + ".png";
    }
}

void LoadLabels(const string &strPathToLabel, vector<string> &vstrLabel, vector<double> &vTimestamps)
{
    string strPrefixLeft = strPathToLabel;

    const int nTimes = vTimestamps.size();
    vstrLabel.resize(nTimes);

    for(int i=0; i<nTimes; i++)
    {
        stringstream ss;
        ss << setfill('0') << setw(10) << i;
        vstrLabel[i] = strPrefixLeft + ss.str() + ".png";
    }
}
//From  https://github.com/autonomousvision/kitti360Scripts/blob/b74933bb4d358d4b8f4c371528f036be2092060c/kitti360scripts/devkits/accumuLaser/src/commons.cpp#L151
//MIT license
/**
 * @brief String2Timestamp Convert timestamp in string to a double value.
 * @param time_str Timestamp in string format.
 * @return Timestamp in double value.
 */
double String2Timestamp (const char *time_str) {

    struct tm tmx;
    char ns_string[10] = "";
    memset (&tmx,0,sizeof(struct tm));

    // scan string
    int32_t err = sscanf (time_str, "%d-%d-%d%*[ _tT]%d:%d:%d.%9s",
                          &tmx.tm_year, &tmx.tm_mon, &tmx.tm_mday,
                          &tmx.tm_hour, &tmx.tm_min, &tmx.tm_sec,
                          ns_string);

    // we need at least a date (time will be 00:00:00.0 then)
    if (err<3) {
        return 0;
    }

    // the ranges of those value are a horrible confusion, see mktime(3)
    tmx.tm_year  -= +1900;
    tmx.tm_mon   -= +1;
    tmx.tm_isdst  = -1;
    time_t secs   = mktime(&tmx);
    if (secs<0) {
        return 0;
    }
    char *ns_string_end;
    uint64_t ns = strtoul (ns_string,&ns_string_end,10);

    // calculate the correct decimal fraction (9 digits)
    // this is: ns *= pow ( 10, 9 - strlen (ns_string) );
    // but prevent dependency from math-library
    for (int32_t i=ns_string_end-ns_string; i<9; i++)
        ns *= 10;

    double time_num = (double)ns + (double)secs * KOGMO_TIMESTAMP_TICKSPERSECOND;
    return time_num;

}
