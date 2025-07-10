# ROS基础编程测试题目-TF

# 题目-2

- 新建功能包，编写第一个ROS节点实现TF发布功能：发布/world_link到/base_link的静态TF（可自定义）以及/base_link到/camera_link的动态TF（可自定义）
- 编写第二个ROS节点实现TF监听功能：监听/camera_link到/base_link的动态TF并在终端打印输出
- 启动rviz查看TF的实时变化

# 环境配置

虚拟机OS：openEuler-24.03-x86

参考文献：[安装指南 — openEuler ROS 在线文档 0.1 documentation](https://openeuler-ros-docs.readthedocs.io/en/latest/installation/install-guide.html)，[Installation — ROS 2 Documentation: Humble documentation](https://docs.ros.org/en/humble/Installation.html)

# 任务

## 创建工作区

```
mkdir -p TF_ws/src
cd TF_ws/src
ros2 pkg create tf_demo --build-type ament_cmake
```

## 修改CMakeLists.txt文件

添加以下内容：

```
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(geometry_msgs REQUIRED)

add_executable(tf_broadcaster src/tf_broadcaster.cpp)
ament_target_dependencies(tf_broadcaster 
  rclcpp 
  tf2_ros 
  geometry_msgs
)

add_executable(tf_listener src/tf_listener.cpp)
ament_target_dependencies(tf_listener 
  rclcpp 
  tf2_ros 
  geometry_msgs
)

install(TARGETS
  tf_broadcaster
  tf_listener
  DESTINATION lib/${PROJECT_NAME}
)
```

## 修改package.xml2文件

添加以下内容

```
<depend>rclcpp</depend>
<depend>tf2_ros</depend>
<depend>geometry_msgs</depend>
```

## 发布节点tf_broadcaster.cpp主要代码

```
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
```

## 监听节点tf_listener.cpp主要代码

```
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
```

## 运行

执行命令：

```
cd ~/TF_ws
colcon build --packages-select tf_demo
source install/setup.bash
ros2 run tf_demo tf_broadcaster
```

新终端：

```
source ~/TF_ws/install/setup.bash
ros2 run tf_demo tf_listener
```

![image](http://127.0.0.1:49742/assets/image-20250710195346-mdkj289.png)

新终端：

```
rviz2
```

添加TF，变换Fixed Frame，有三个选项，

world_link ：固定坐标系

base_link： 位于 world_link 上方 0.5 米处

camera_link： 位于 base_link 上方 0.2 米，前方 0.1 米，并绕 Z 轴旋转

![image](http://127.0.0.1:49742/assets/image-20250710195903-4kzsyg3.png)

‍

‍