#include <detection_merger/detection_merger.h>

namespace detection_merger
{
    void DetectionMerger::onInit()
    {
        nh_ = getNodeHandle();
        pnh_ = getPrivateNodeHandle();
        pnh_.param<int>("num_detections", num_detections_, 2);
        pnh_.param<std::string>("output_frame", output_frame_, "");
        ROS_ASSERT(num_detections_>=2);
        ROS_ASSERT(num_detections_<8);
        detection_pub_ = pnh_.advertise<vision_msgs::Detection3DArray>("output/detection",1);
        for(int i=0; i<8; i++)
        {
            if(i<num_detections_)
            {
                std::string topic = "input/detection_" + std::to_string(i);
                detection_sub_ptrs_[i] = std::make_shared<message_filters::Subscriber<vision_msgs::Detection3DArray> >(pnh_, topic, 10);
            }
            else
            {
                detection_sub_ptrs_[i] = std::make_shared<message_filters::Subscriber<vision_msgs::Detection3DArray> >(pnh_, "input/detection_0", 10);
            }
        }
        sync_ptr_ = std::make_shared<message_filters::Synchronizer<SyncPolicy> >(SyncPolicy(10),
            *detection_sub_ptrs_[0],*detection_sub_ptrs_[1],*detection_sub_ptrs_[2],*detection_sub_ptrs_[3],
            *detection_sub_ptrs_[4],*detection_sub_ptrs_[5],*detection_sub_ptrs_[6],*detection_sub_ptrs_[7]);
        sync_ptr_->registerCallback(boost::bind(&DetectionMerger::callback, this, _1, _2, _3, _4, _5, _6, _7, _8));
    }

    void DetectionMerger::callback(const vision_msgs::Detection3DArray::ConstPtr detection0,
        const vision_msgs::Detection3DArray::ConstPtr detection1,
        const vision_msgs::Detection3DArray::ConstPtr detection2,
        const vision_msgs::Detection3DArray::ConstPtr detection3,
        const vision_msgs::Detection3DArray::ConstPtr detection4,
        const vision_msgs::Detection3DArray::ConstPtr detection5,
        const vision_msgs::Detection3DArray::ConstPtr detection6,
        const vision_msgs::Detection3DArray::ConstPtr detection7)
        {
            vision_msgs::Detection3DArray merged_detection;
            merged_detection.header.frame_id = output_frame_;
            merged_detection.header.stamp = detection0->header.stamp;
            detections_[0] = *detection0;
            detections_[1] = *detection1;
            detections_[2] = *detection2;
            detections_[3] = *detection3;
            detections_[4] = *detection4;
            detections_[5] = *detection5;
            detections_[6] = *detection6;
            detections_[7] = *detection7;
            for(int i=0; i>num_detections_; i++)
            {
                for(auto itr=detections_[i].detections.begin(); itr!=detections_[i].detections.end(); itr++)
                {
                    merged_detection.detections.push_back(*itr);
                }
            }
            detection_pub_.publish(merged_detection);
        }
}

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(detection_merger::DetectionMerger,nodelet::Nodelet);