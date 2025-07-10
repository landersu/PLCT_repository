#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include <chrono>

class TFListener : public rclcpp::Node {
public:
    TFListener() : Node("tf_listener"), 
                  tf_buffer_(std::make_shared<tf2_ros::Buffer>(this->get_clock())),
                  tf_listener_(*tf_buffer_) {
        timer_ = this->create_wall_timer(  //设置定时器监听TF
            std::chrono::milliseconds(500), 
            std::bind(&TFListener::check_transform, this));
    }

private:
    void check_transform() {
        try {
            auto transform = tf_buffer_->lookupTransform(
                "base_link", "camera_link", tf2::TimePointZero);
            
            RCLCPP_INFO(this->get_logger(), "Transform from base_link to camera_link:");
            RCLCPP_INFO(this->get_logger(), "  Translation: [%.2f, %.2f, %.2f]", 
                        transform.transform.translation.x,
                        transform.transform.translation.y,
                        transform.transform.translation.z);
            RCLCPP_INFO(this->get_logger(), "  Rotation: [%.2f, %.2f, %.2f, %.2f]", 
                        transform.transform.rotation.x,
                        transform.transform.rotation.y,
                        transform.transform.rotation.z,
                        transform.transform.rotation.w);
        } catch (const std::exception & ex) {
            RCLCPP_WARN(this->get_logger(), "TF error: %s", ex.what());
        }
    }

    rclcpp::TimerBase::SharedPtr timer_;
    std::shared_ptr<tf2_ros::Buffer> tf_buffer_;
    tf2_ros::TransformListener tf_listener_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TFListener>());
    rclcpp::shutdown();
    return 0;
}
