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
#include<iomanip>
#include<chrono>
#include<stdio.h>

#include<opencv2/core/core.hpp>

#include<System.h>

using namespace std;
#define KOGMO_TIMESTAMP_TICKSPERSECOND 1000000000.0

double String2Timestamp(const char *time_str);

void LoadImages(const string &strPathToSequence, vector<string> &vstrImageLeft,
                vector<string> &vstrImageRight, vector<double> &vTimestamps);

void LoadLabels(const string &strPathToLabel, vector<string> &vstrLabelLeft,
                vector<string> &vstrLabelRight, vector<double> &vTimestamps);

int main(int argc, char **argv)
{
    if(argc != 5)
    {
        cerr << endl << "Usage: ./stereo_kitti path_to_vocabulary path_to_settings path_to_sequence path_to_label" << endl;
        return 1;
    }

    // Retrieve paths to images
    vector<string> vstrImageLeft;
    vector<string> vstrImageRight;
    vector<double> vTimestamps;
    LoadImages(string(argv[3]), vstrImageLeft, vstrImageRight, vTimestamps);
    vector<string> vstrLabelLeft;
    vector<string> vstrLabelRight;
    LoadLabels(string(argv[4]), vstrLabelLeft, vstrLabelRight, vTimestamps);

    const int nImages = vstrImageLeft.size();
    const int nLabels = vstrLabelLeft.size();
    
    if (nLabels != nImages)
    {
        cerr << endl << "Images and Labels disagree with each other. " << endl;
        return 1;
    }

    // Create SLAM system. It initializes all system threads and gets ready to process frames.
    ORB_SLAM2::System SLAM(argv[1],argv[2],ORB_SLAM2::System::STEREO,true);

    // Vector for tracking time statistics
    vector<float> vTimesTrack;
    vTimesTrack.resize(nImages);

    cout << endl << "-------" << endl;
    cout << "Start processing sequence ..." << endl;
    cout << "Images in the sequence: " << nImages << endl << endl;   

    // Main loop
    cv::Mat imLeft, imRight;
    cv::Mat labelLeft, labelRight;
    for(int ni=0; ni<nImages; ni++)
    {
        // Read left and right images from file
        imLeft = cv::imread(vstrImageLeft[ni],CV_LOAD_IMAGE_UNCHANGED);
        imRight = cv::imread(vstrImageRight[ni],CV_LOAD_IMAGE_UNCHANGED);
        // Read left and right labels frome file
        labelLeft = cv::imread(vstrLabelLeft[ni],CV_LOAD_IMAGE_UNCHANGED);
        labelRight = cv::imread(vstrLabelRight[ni],CV_LOAD_IMAGE_UNCHANGED);
        //getchar();
        double tframe = vTimestamps[ni];

        if(imLeft.empty())
        {
            cerr << endl << "Failed to load image at: "
                 << string(vstrImageLeft[ni]) << endl;
            return 1;
        }
        
        if(labelLeft.empty())
        {
            cerr << endl << "Failed to load label at: "
                 << string(vstrLabelLeft[ni]) << endl;
            return 1;
        }
        
#ifdef COMPILEDWITHC11
        std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
#else
        std::chrono::monotonic_clock::time_point t1 = std::chrono::monotonic_clock::now();
#endif

        // Pass the images to the SLAM system
        SLAM.TrackStereo(imLeft,imRight,labelLeft,labelRight,tframe);

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
    SLAM.SaveTrajectoryKITTI("CameraTrajectory.txt");

    return 0;
}

void LoadImages(const string &strPathToSequence, vector<string> &vstrImageLeft,
                vector<string> &vstrImageRight, vector<double> &vTimestamps)
{
    ifstream fTimes;
//    string strPathTimeFile = strPathToSequence + "/times.txt";
    //Although Kitti360 have seperate timestamps for individual cameras, we use the image_0 timestamp as the difference is negligible,<1e-4s.
    string strPathTimeFile = strPathToSequence + "image_00/timestamps.txt";
    fTimes.open(strPathTimeFile.c_str());

    while(!fTimes.eof())
    {
        string s;
        getline(fTimes,s);
        if(!s.empty())
        {
//            stringstream ss;
//            ss << s;
//            double t;
//            ss >> t;

            double ts = String2Timestamp(s.c_str());
            cout<<ts<<endl;
            vTimestamps.push_back(ts/1e9); //Kitti timestamp is in ns
//            vTimestamps.push_back(t);
        }
    }

//    string strPrefixLeft = strPathToSequence + "/image_0/";
//    string strPrefixRight = strPathToSequence + "/image_1/";

    string strPrefixLeft = strPathToSequence+ "image_00/data_rect/";
    string strPrefixRight = strPathToSequence + "image_01/data_rect/";

    const int nTimes = vTimestamps.size();
    vstrImageLeft.resize(nTimes);
    vstrImageRight.resize(nTimes);

    for(int i=0; i<nTimes; i++)
    {
        stringstream ss;
//        ss << setfill('0') << setw(6) << i;
        ss << setfill('0') << setw(10) << i;

        vstrImageLeft[i] = strPrefixLeft + ss.str() + ".png";
        vstrImageRight[i] = strPrefixRight + ss.str() + ".png";
    }
}

void LoadLabels(const string &strPathToLabel, vector<string> &vstrLabelLeft,
                vector<string> &vstrLabelRight, vector<double> &vTimestamps)
{
    //for now, we pass the same image folder directory to label path as the label for individual image channel is in its own segmentation folder.
    string strPrefixLeft = strPathToLabel + "image_00/segmentation/";
    string strPrefixRight = strPathToLabel + "image_01/segmentation/";

    const int nTimes = vTimestamps.size();
    vstrLabelLeft.resize(nTimes);
    vstrLabelRight.resize(nTimes);

    for(int i=0; i<nTimes; i++)
    {
        stringstream ss;
//        ss << setfill('0') << setw(6) << i;
        ss << setfill('0') << setw(10) << i;
        vstrLabelLeft[i] = strPrefixLeft + ss.str() + ".png";
        vstrLabelRight[i] = strPrefixRight + ss.str() + ".png";
    }
}


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
