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
#include <can_imu_lws/X_Position_Acc_msg.h>
#include "controlcan.h"

namespace imu_to_joint_rviz_plugin {
    struct Angular_Velocity;
    static void* thread_channel_receive(void *param);//接收线程。
    static int flag_thread_status = 0, channel_select = 0;
    static int origin_imu_id = 79, right_thigh_id = 79, left_thigh_id = 79, right_shank_id = 79, left_shank_id = 79;

    class ImuToJointPanel : public rviz::Panel {
    Q_OBJECT
    public:
        explicit ImuToJointPanel(QWidget *parent = 0);

    public Q_SLOTS:
        void vci_obj_process(VCI_CAN_OBJ vci_can_obj);

    protected Q_SLOTS:
        void qt_layout_init();
        void initImuTable();
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
        void checkSubLoad();
        void checkChannel();
        void open_can_device();
        void close_can_device();
        void can_device_config_init(int Baud);
        void can_start_listen();
        void can_stop_listen();
        int byte_to_short(BYTE H_data, BYTE L_data);
        void euler_msg_process(can_imu_lws::IMU_Euler_msg euler_msg);
        void set_imu_euler_offset();
        void av_msg_process(imu_to_joint_rviz_plugin::Angular_Velocity *av_msg);


    protected:
        // QLineEdit *editor_origin_imu,*editor_right_thigh_imu,*editor_left_thigh_imu,*editor_right_shank_imu,*editor_left_shank_imu;
        QPushButton *button_imu_id_set, *button_imu_start_listen, *button_can_device_open, *button_can_device_close, *button_can_start_listen, *button_can_stop_listen;
        QCheckBox *checkbox_test, *checkbox_sub_or_load, *checkbox_channel_select;
        QTableWidget *table_imuarray;
        ros::NodeHandle nh_;
        ros::Publisher pub_x_position_acc;
        ros::Publisher pub_joint_state_;
        ros::Publisher pub_joint_origin_imu, pub_joint_r_shank_imu, pub_joint_l_shank_imu, pub_joint_r_thigh_imu, pub_joint_l_thigh_imu;
        ros::Subscriber sub_imu_msg_;
        // Y R P r_hip,l_hip,r_knee,l_knee
        VCI_INIT_CONFIG can_device_config;
        pthread_t threadid;
        float joint_position_euler_array[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        float joint_position_offset_array[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        float joint_rod_length_length[5];
        float joint_center_mass_length[5];
        float imu_euler_offset_array[15];

        std::string joint_name_array[12] = {"r_hip_yaw_joint", "r_hip_roll_joint", "r_hip_pitch_joint",
                            "r_knee_pitch_joint",
                            "r_ankle_pitch_joint", "r_ankle_roll_joint",
                            "l_hip_yaw_joint", "l_hip_roll_joint", "l_hip_pitch_joint",
                            "l_knee_pitch_joint",
                            "l_ankle_pitch_joint", "l_ankle_roll_joint"};
        int can_id_array[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int imu_joint_status_array[5] = {0, 0, 0, 0, 0};
        int flag_center_people = 0;
        // Y R P origin,right_thigh,left_thigh,right_shank,left_shank
        float imu_current_list[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        float imu_current_av_list[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        int flag_channel_1_open = 0, flag_channel_2_open = 0, flag_channel_1_start = 0, flag_channel_2_start = 0,flag_device_open = 0;
        std::vector<sensor_msgs::Imu> vector_joint_imu[10];
        bool flag_sub_or_load = false;
        bool flag_start_listen = false;
        bool flag_just_test = false;
    };
} // end namespace navi-multi-goals-pub-rviz-plugin

#endif // MULTI_NAVI_GOAL_PANEL_H
