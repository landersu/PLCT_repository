#include <chrono>
#include <functional>
#include <memory>
#include <cmath>
#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/msg/transform_stamped.hpp"

using namespace std::chrono_literals;

class TFBroadcaster : public rclcpp::Node {
public:
    TFBroadcaster() : Node("tf_broadcaster") {
        tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);
        //设置定时器同时发布静态和动态TF
        timer_ = this->create_wall_timer(
            100ms, std::bind(&TFBroadcaster::broadcast_tf, this));
        
        RCLCPP_INFO(this->get_logger(), "TF Broadcaster started");
    }

private:
    void broadcast_tf() {
        publish_static_tf();//发布静态TFworld_link给base_link
        publish_dynamic_tf();//发布动态TFbase_link给camera_link
    }

    void publish_static_tf() {
        geometry_msgs::msg::TransformStamped tf;
        tf.header.stamp = this->now();
        tf.header.frame_id = "world_link";
        tf.child_frame_id = "base_link";
        tf.transform.translation.x = 0.0;
        tf.transform.translation.y = 0.0;
        tf.transform.translation.z = 0.5;
        tf.transform.rotation.w = 1.0;
        tf_broadcaster_->sendTransform(tf);
    }

    void publish_dynamic_tf() {
        geometry_msgs::msg::TransformStamped tf;
        tf.header.stamp = this->now();
        tf.header.frame_id = "base_link";
        tf.child_frame_id = "camera_link";
        angle_ += 0.05;
        tf.transform.translation.x = 0.1;
        tf.transform.translation.y = 0.0;
        tf.transform.translation.z = 0.2;
        tf.transform.rotation.z = sin(angle_/2);
        tf.transform.rotation.w = cos(angle_/2);
        tf_broadcaster_->sendTransform(tf);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
    double angle_ = 0.0;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TFBroadcaster>());
    rclcpp::shutdown();
    return 0;
}
