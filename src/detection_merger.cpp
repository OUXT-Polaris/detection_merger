#include <detection_merger/detection_merger.h>

namespace detection_merger
{
    void DetectionMerger::onInit()
    {

    }
}

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(detection_merger::DetectionMerger,nodelet::Nodelet);