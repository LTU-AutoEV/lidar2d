#include <ros/ros.h>
#include <geometry_msgs/Point.h>
#include <sensor_msgs/LaserScan.h>

#include <dynamic_reconfigure/server.h>
#include <lidar2d/DetectConfig.h>

#include <limits>
#include <cmath>


// The maximum number of points a lidar could return
#define LIDAR_OBSTACLE_MAX_RANGE_SIZE 2048

class Detect
{
public:
    Detect();

    // Callback functions
    void scanCallback(const sensor_msgs::LaserScan& scan);
    void configCB(lidar2d::DetectConfig &config, uint32_t level);

private:
    // Dynamic reconfigure server
    dynamic_reconfigure::Server<lidar2d::DetectConfig> server_;
    lidar2d::DetectConfig config_;

    // ROS objects
    ros::NodeHandle nh_;
    ros::Publisher  scan_pub_;
    ros::Subscriber scan_sub_;

};

void Detect::configCB(lidar2d::DetectConfig &config, uint32_t level)
{
    config_ = config;
}


// Constructor
//   Set up publisher and subscriber
Detect::Detect()
{
    nh_ = ros::NodeHandle("~");

    // Dynamic Reconfigure
    server_.setCallback(boost::bind(&Detect::configCB, this, _1, _2));
    server_.getConfigDefault(config_);

    // Raw scan subscriber
    scan_sub_ = nh_.subscribe("/lidar2d/scan", 100, &Detect::scanCallback, this);

    // Detectd Scan Publisher
    scan_pub_ = nh_.advertise<sensor_msgs::LaserScan>("scan", 100);
}


// Callback function for the points
void Detect::scanCallback(const sensor_msgs::LaserScan& scan)
{
    sensor_msgs::LaserScan masked_scan = scan;

    //Copy into masked_scan
    for (int i = 0; i < masked_scan.ranges.size(); i++)
    {
        if (masked_scan.ranges[i] > config_.max_dist)
        {
            masked_scan.ranges[i] = INFINITY;
        }
        else if (masked_scan.ranges[i] < config_.min_dist)
        {
            // Guarenteed to be less than range_min
            masked_scan.ranges[i] = scan.range_min - 1.0;
        }

    }

    scan_pub_.publish(masked_scan);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "detect");
  Detect detect;

  ros::spin();
}
