#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include <chrono>
#include <fstream>

class ImageSub : public rclcpp::Node {
public:
    ImageSub() : Node("image_subscriber") {
        sub_ = this->create_subscription<sensor_msgs::msg::Image>(
            "/camera/image_raw", 10,
            [this](sensor_msgs::msg::Image::SharedPtr msg) {
                auto now = this->get_clock()->now();
                rclcpp::Time img_time(msg->header.stamp);
                auto latency = now - img_time;
                log_ << msg->header.seq << ","
                     << img_time.seconds() << ","
                     << now.seconds() << ","
                     << latency.seconds() << std::endl;
            });
        log_.open("logs/timestamps.csv");
        log_ << "seq,img_timestamp,recv_timestamp,latency\n";
    }

    ~ImageSub() { log_.close(); }

private:
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr sub_;
    std::ofstream log_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ImageSub>());
    rclcpp::shutdown();
    return 0;
}
