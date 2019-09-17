#ifndef DETECTION_MERGER_DETECTION_MERGER_H_INCLUDED
#define DETECTION_MERGER_DETECTION_MERGER_H_INCLUDED

// Headers in ROS
#include <ros/ros.h>
#include <nodelet/loader.h>
#include <nodelet/nodelet.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

namespace detection_merger
{
    class DetectionMerger : public nodelet::Nodelet
    {
    protected:
        void onInit();
    };
}

#endif  //DETECTION_MERGER_DETECTION_MERGER_H_INCLUDED