#ifndef DETECTION_MERGER_DETECTION_MERGER_H_INCLUDED
#define DETECTION_MERGER_DETECTION_MERGER_H_INCLUDED

// Headers in ROS
#include <ros/ros.h>
#include <nodelet/loader.h>
#include <nodelet/nodelet.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <vision_msgs/Detection3DArray.h>

// Headers in STL
#include <memory>
#include <array>

namespace detection_merger
{
    typedef message_filters::sync_policies::ApproximateTime
        <vision_msgs::Detection3DArray,vision_msgs::Detection3DArray,
        vision_msgs::Detection3DArray,vision_msgs::Detection3DArray,
        vision_msgs::Detection3DArray,vision_msgs::Detection3DArray,
        vision_msgs::Detection3DArray,vision_msgs::Detection3DArray> SyncPolicy;
    class DetectionMerger : public nodelet::Nodelet
    {
    protected:
        void onInit();
    private:
        void callback(const vision_msgs::Detection3DArray::ConstPtr detection0,
            const vision_msgs::Detection3DArray::ConstPtr detection1,
            const vision_msgs::Detection3DArray::ConstPtr detection2,
            const vision_msgs::Detection3DArray::ConstPtr detection3,
            const vision_msgs::Detection3DArray::ConstPtr detection4,
            const vision_msgs::Detection3DArray::ConstPtr detection5,
            const vision_msgs::Detection3DArray::ConstPtr detection6,
            const vision_msgs::Detection3DArray::ConstPtr detection7);
        ros::NodeHandle nh_,pnh_;
        std::shared_ptr<message_filters::Synchronizer<SyncPolicy> > sync_ptr_;
        std::shared_ptr<message_filters::Subscriber<vision_msgs::Detection3DArray> > detection_sub_ptrs_[8];
        int num_detections_;
        std::string output_frame_;
        std::array<vision_msgs::Detection3DArray,8> detections_;
        ros::Publisher detection_pub_;
    };
}

#endif  //DETECTION_MERGER_DETECTION_MERGER_H_INCLUDED