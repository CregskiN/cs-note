#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>

std::vector<cv::Point2f> control_points;

void mouse_handler(int event, int x, int y, int flags, void *userdata) {
    if (event == cv::EVENT_LBUTTONDOWN && control_points.size() < 4) {
        std::cout << "Left button of the mouse is clicked - position (" << x << ", "
                  << y << ")" << '\n';
        control_points.emplace_back(x, y);
    }
}

void naive_bezier(const std::vector<cv::Point2f> &points, cv::Mat &window) {
    auto &p_0 = points[0];
    auto &p_1 = points[1];
    auto &p_2 = points[2];
    auto &p_3 = points[3];

    for (double t = 0.0; t <= 1.0; t += 0.001) {
        auto point = std::pow(1 - t, 3) * p_0 + 3 * t * std::pow(1 - t, 2) * p_1 +
                     3 * std::pow(t, 2) * (1 - t) * p_2 + std::pow(t, 3) * p_3;

        window.at<cv::Vec3b>(point.y, point.x)[2] = 255;
    }
}

cv::Point2f recursive_bezier(const std::vector<cv::Point2f> &control_points, float t) {
    // TODO: Implement de Casteljau's algorithm
    if (control_points.size() == 1) {
        return control_points[0];
    }

    std::vector<cv::Point2f> lerp_points;
    for (size_t i = 0; i < control_points.size() - 1; i++) {
        cv::Point2f new_point = control_points[i] + t * (control_points[i + 1] - control_points[i]);
        lerp_points.push_back(new_point);
    }

    return recursive_bezier(lerp_points, t);
}

void bezier(const std::vector<cv::Point2f> &control_points, cv::Mat &window) {
    // TODO: Iterate through all t = 0 to t = 1 with small steps, and call de Casteljau's
    float t = 0.0f;
    while (t < 1) {
        // recursive Bezier algorithm.
        cv::Point2f point = recursive_bezier(control_points, t);
        window.at<cv::Vec3b>(point.y, point.x)[1] = 255;
        t += 0.001f;
    }
}

void bezier_antialiasing(const std::vector<cv::Point2f> &control_points, cv::Mat &window) {
    // TODO: 通过 point 与周围 2*2 像素中心的关系，决定 这四个像素的颜色深度 // 没有实现反走样
    float t = 0.0f;
    while (t < 1) {
        // recursive Bezier algorithm.
        cv::Point2f point = recursive_bezier(control_points, t);
        int quadrant = -1;  // 记录 point 在 4*4 中所处象限
        cv::Point2f point_center(std::floor(point.x) + 0.5, std::floor(point.y) + 0.5);
        // 1. 判定 point 与所在像素中心的位置关系，右上？左上？左下？右下？
        bool isRight = point.x > point_center.x;
        bool isTop = point.y > point_center.y;
        // 2. 依据 point 在 4*4 的位置，决定每个像素的颜色
        cv::Point2f p1, p2, p3, p4;  // 定义四个像素点
        float d1, d2, d3, d4;        // point 距离4 4*4 各像素中心的距离
        if (isRight && isTop) {      // 在第一象限
            p1 = cv::Point2f(point_center.x - 0.5, point_center.y - 0.5);
            p2 = cv::Point2f(p1.x - 1, p1.y);
            p3 = cv::Point2f(p1.x - 1, p1.y - 1);
            p4 = cv::Point2f(p1.x, p1.y - 1);

            d1 = std::sqrt(std::pow(std::abs(point_center.x - point.x), 2) + std::pow(std::abs(point_center.y - point.y), 2));
            d2 = std::sqrt(std::pow(std::abs(point_center.x - 1 - point.x), 2) + std::pow(std::abs(point_center.y - point.y), 2));
            d3 = std::sqrt(std::pow(std::abs(point_center.x - 1 - point.x), 2) + std::pow(std::abs(point_center.y - 1 - point.y), 2));
            d4 = std::sqrt(std::pow(std::abs(point_center.x - point.x), 2) + std::pow(std::abs(point_center.y - 1 - point.y), 2));

            window.at<cv::Vec3b>(p1.y, p1.x)[1] = 255;
            window.at<cv::Vec3b>(p2.y, p2.x)[1] = 255 * (1 - d2);
            window.at<cv::Vec3b>(p3.y, p3.x)[1] = 255 * (1 - d3);
            window.at<cv::Vec3b>(p4.y, p4.x)[1] = 255 * (1 - d4);
        } else if (!isRight && isTop) {  // 第二象限
            p2 = cv::Point2f(point_center.x - 0.5, point_center.y - 0.5);
            p1 = cv::Point2f(p2.x + 1, p2.y);
            p3 = cv::Point2f(p2.x, p2.y - 1);
            p4 = cv::Point2f(p2.x + 1, p2.y - 1);
            d1 = std::sqrt(std::pow(std::abs(point_center.x + 1 - point.x), 2) + std::pow(std::abs(point_center.y - point.y), 2));
            d2 = std::sqrt(std::pow(std::abs(point_center.x - point.x), 2) + std::pow(std::abs(point_center.y - point.y), 2));
            d3 = std::sqrt(std::pow(std::abs(point_center.x - point.x), 2) + std::pow(std::abs(point_center.y - 1 - point.y), 2));
            d4 = std::sqrt(std::pow(std::abs(point_center.x + 1 - point.x), 2) + std::pow(std::abs(point_center.y - 1 - point.y), 2));
            window.at<cv::Vec3b>(p1.y, p1.x)[1] = 255 * (1 - d1);
            window.at<cv::Vec3b>(p2.y, p2.x)[1] = 255;
            window.at<cv::Vec3b>(p3.y, p3.x)[1] = 255 * (1 - d3);
            window.at<cv::Vec3b>(p4.y, p4.x)[1] = 255 * (1 - d4);
        } else if (!isRight && !isTop) {  // 在第三象限
            p3 = cv::Point2f(point_center.x - 0.5, point_center.y - 0.5);
            p1 = cv::Point2f(p3.x + 1, p3.y + 1);
            p2 = cv::Point2f(p3.x, p3.y + 1);
            p4 = cv::Point2f(p3.x + 1, p3.y);

            d1 = std::sqrt(std::pow(std::abs(point_center.x + 1 - point.x), 2) + std::pow(std::abs(point_center.y + 1 - point.y), 2));
            d2 = std::sqrt(std::pow(std::abs(point_center.x - point.x), 2) + std::pow(std::abs(point_center.y + 1 - point.y), 2));
            d3 = std::sqrt(std::pow(std::abs(point_center.x - point.x), 2) + std::pow(std::abs(point_center.y - point.y), 2));
            d4 = std::sqrt(std::pow(std::abs(point_center.x + 1 - point.x), 2) + std::pow(std::abs(point_center.y - point.y), 2));
            window.at<cv::Vec3b>(p1.y, p1.x)[1] = 255 * (1 - d1);
            window.at<cv::Vec3b>(p2.y, p2.x)[1] = 255 * (1 - d2);
            window.at<cv::Vec3b>(p3.y, p3.x)[1] = 255;
            window.at<cv::Vec3b>(p4.y, p4.x)[1] = 255 * (1 - d4);
        } else {  // 第四象限
            p4 = cv::Point2f(point_center.x - 0.5, point_center.y - 0.5);
            p1 = cv::Point2f(p4.x, p4.y - 1);
            p2 = cv::Point2f(p4.x - 1, p4.y - 1);
            p3 = cv::Point2f(p4.x - 1, p4.y);
            d1 = std::sqrt(std::pow(std::abs(point_center.x - point.x), 2) + std::pow(std::abs(point_center.y + 1 - point.y), 2));
            d2 = std::sqrt(std::pow(std::abs(point_center.x - 1 - point.x), 2) + std::pow(std::abs(point_center.y - 1 - point.y), 2));
            d3 = std::sqrt(std::pow(std::abs(point_center.x - 1 - point.x), 2) + std::pow(std::abs(point_center.y - point.y), 2));
            d4 = std::sqrt(std::pow(std::abs(point_center.x - point.x), 2) + std::pow(std::abs(point_center.y - point.y), 2));
            window.at<cv::Vec3b>(p1.y, p1.x)[1] = 255 * (1 - d1);
            window.at<cv::Vec3b>(p2.y, p2.x)[1] = 255 * (1 - d2);
            window.at<cv::Vec3b>(p3.y, p3.x)[1] = 255 * (1 - d3);
            window.at<cv::Vec3b>(p4.y, p4.x)[1] = 255;
        }

        t += 0.001f;
    }
}

int main() {
    cv::Mat window = cv::Mat(700, 700, CV_8UC3, cv::Scalar(0));
    cv::cvtColor(window, window, cv::COLOR_BGR2RGB);
    cv::namedWindow("Bezier Curve", cv::WINDOW_AUTOSIZE);

    cv::setMouseCallback("Bezier Curve", mouse_handler, nullptr);

    int key = -1;
    while (key != 27) {
        for (auto &point : control_points) {
            cv::circle(window, point, 3, {255, 255, 255}, 3);
        }

        if (control_points.size() == 4) {
            // naive_bezier(control_points, window);
            // bezier(control_points, window);
            bezier_antialiasing(control_points, window);

            cv::imshow("Bezier Curve", window);
            cv::imwrite("my_bezier_curve.png", window);
            key = cv::waitKey(0);

            return 0;
        }

        cv::imshow("Bezier Curve", window);
        key = cv::waitKey(20);
    }

    return 0;
}
