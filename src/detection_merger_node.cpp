// Headers in this package
#include <detection_merger/detection_merger.h>

// Headers in ROS
#include <ros/ros.h>
#include <nodelet/loader.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "detection_merger", ros::init_options::AnonymousName);
    ros::param::set("~num_worker_threads", 1); // need to call   Loader(bool provide_ros_api = true);
    nodelet::Loader manager(true);
    nodelet::M_string remappings;
    nodelet::V_string my_argv(argv + 1, argv + argc);
    my_argv.push_back("--shutdown-on-close"); // Internal

    manager.load(ros::this_node::getName(), "detection_merger/DetectionMerger", remappings, my_argv);

    ros::spin();
    return 0;
}