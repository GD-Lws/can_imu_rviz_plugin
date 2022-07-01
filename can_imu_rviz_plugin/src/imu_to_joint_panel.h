#ifndef IMU_TO_JOINT_PANEL_H
#define IMU_TO_JOINT_PANEL_H


#include <string>

#include <ros/ros.h>
#include <ros/console.h>

#include <rviz/panel.h>

#include <QPushButton>
#include <QTableWidget>
#include <QCheckBox>

#include <visualization_msgs/Marker.h>
#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/String.h>
#include <actionlib_msgs/GoalStatus.h>
#include <actionlib_msgs/GoalStatusArray.h>
#include <tf/transform_datatypes.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/JointState.h>
#include <can_imu_lws/IMU_Euler_msg.h>


namespace imu_to_joint_rviz_plugin {
    class ImuToJointPanel : public rviz::Panel {
    Q_OBJECT
    public:
        explicit ImuToJointPanel(QWidget *parent = 0);

    public Q_SLOTS:

    protected Q_SLOTS:
        void euler_callback(const can_imu_lws::IMU_Euler_msg::ConstPtr &euler_msg);
        void imu_id_set();
        static void startSpin(); // spin for sub
        void set_joint_offset();
        void set_joint_state(sensor_msgs::JointState &joint_state_msg);
        void test_joint_state(sensor_msgs::JointState &joint_state_msg);
        void imu_start_listen();
        void joint_state_pub();
        float euler_to_radian(float euler);
        void checkTest();
       
    protected:
        QLineEdit *editor_origin_imu,*editor_right_thigh_imu,*editor_left_thigh_imu,*editor_right_shank_imu,*editor_left_shank_imu;
        QPushButton *button_imu_id_set, *button_imu_start_listen;
        QCheckBox *checkbox_test;
        ros::NodeHandle nh_;
        ros::Publisher pub_joint_state_;
        ros::Subscriber sub_imu_msg_;
        // Y R P r_hip,l_hip,r_knee,l_knee
        float joint_position_euler_array[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        float joint_position_offset_array[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int origin_imu_id = 0x50, right_thigh_id = 0x50, left_thigh_id = 0x50, right_shank_id = 0x50, left_shank_id = 0x50;
        std::string joint_name_array[12] = {"r_hip_yaw_joint", "r_hip_roll_joint", "r_hip_pitch_joint",
                            "r_knee_pitch_joint",
                            "r_ankle_pitch_joint", "r_ankle_roll_joint",
                            "l_hip_yaw_joint", "l_hip_roll_joint", "l_hip_pitch_joint",
                            "l_knee_pitch_joint",
                            "l_ankle_pitch_joint", "l_ankle_roll_joint"};
        int can_id_array[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int imu_status_array[5] = {0, 0, 0, 0, 0};
        // Y R P origin,right_thigh,left_thigh,right_shank,left_shank
        float imu_current_list[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        bool flag_start_listen = false;
        bool flag_just_test = false;
    };
} // end namespace navi-multi-goals-pub-rviz-plugin

#endif // MULTI_NAVI_GOAL_PANEL_H
