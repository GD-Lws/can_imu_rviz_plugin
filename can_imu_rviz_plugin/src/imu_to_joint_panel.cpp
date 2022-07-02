#include <cstdio>

#include <ros/console.h>

#include <fstream>
#include <sstream>
#include <math.h>
#include <QPainter>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QDebug>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/qheaderview.h>


#include "imu_to_joint_panel.h"

namespace imu_to_joint_rviz_plugin {
    ImuToJointPanel::ImuToJointPanel(QWidget *parent)
            : rviz::Panel(parent),nh_(){
        pub_joint_state_ = nh_.advertise<sensor_msgs::JointState>("joint_states",1);
        sub_imu_msg_ = nh_.subscribe<can_imu_lws::IMU_Euler_msg>("imu_euler_pub",100,
                                    boost::bind(&ImuToJointPanel::euler_callback, this,_1));
                                    
        QVBoxLayout *layout_root = new QVBoxLayout;
        layout_root->addWidget(new QLabel("imu_msg_to_joint_state"));

        QHBoxLayout *layout_origin_imu = new QHBoxLayout;
        layout_origin_imu->addWidget(new QLabel("Origin_imu_id:"));
        editor_origin_imu = new QLineEdit;
        layout_origin_imu->addWidget(editor_origin_imu);
        layout_root->addLayout(layout_origin_imu);

        QHBoxLayout *layout_right_thigh_imu = new QHBoxLayout;
        layout_right_thigh_imu->addWidget(new QLabel("right_thigh_imu_id:"));
        editor_right_thigh_imu = new QLineEdit;
        layout_right_thigh_imu->addWidget(editor_right_thigh_imu);
        layout_root->addLayout(layout_right_thigh_imu);

        QHBoxLayout *layout_left_thigh_imu = new QHBoxLayout;
        layout_left_thigh_imu->addWidget(new QLabel("left_thigh_imu_id:"));
        editor_left_thigh_imu = new QLineEdit;
        layout_left_thigh_imu->addWidget(editor_left_thigh_imu);
        layout_root->addLayout(layout_left_thigh_imu);

        QHBoxLayout *layout_right_shank_imu = new QHBoxLayout;
        layout_right_shank_imu->addWidget(new QLabel("right_shank_imu_id:"));
        editor_right_shank_imu = new QLineEdit;
        layout_right_shank_imu->addWidget(editor_right_shank_imu);
        layout_root->addLayout(layout_right_shank_imu);

        QHBoxLayout *layout_left_shank_imu = new QHBoxLayout;
        layout_left_shank_imu->addWidget(new QLabel("left_shank_imu_id:"));
        editor_left_shank_imu = new QLineEdit;
        layout_left_shank_imu->addWidget(editor_left_shank_imu);
        layout_root->addLayout(layout_left_shank_imu);

        checkbox_test = new QCheckBox("Just Test euler");
        layout_root->addWidget(checkbox_test);
        
        button_imu_id_set = new QPushButton("Imu_ID_Set");
        layout_root->addWidget(button_imu_id_set);

        button_imu_start_listen = new QPushButton("Imu_Start_Listen");
        layout_root->addWidget(button_imu_start_listen);

        setLayout(layout_root);
         // set a Qtimer to start a spin for subscriptions
        QTimer *output_timer = new QTimer(this);
        output_timer->start(200);
        connect(output_timer, SIGNAL(timeout()), this, SLOT(startSpin()));
        connect(button_imu_id_set, SIGNAL(clicked()), this, SLOT(imu_id_set()));
        connect(button_imu_start_listen, SIGNAL(clicked()), this, SLOT(imu_start_listen()));
        connect(checkbox_test, SIGNAL(clicked(bool)), this, SLOT(checkTest()));
    }


    void ImuToJointPanel::euler_callback(const can_imu_lws::IMU_Euler_msg::ConstPtr &euler_msg){
        int can_id_index = euler_msg->imu_can_id - 80;
        if (can_id_index < 10){can_id_array[can_id_index] = 1;}
        int start_index = 0;
        if (euler_msg->imu_can_id == origin_imu_id){start_index = 0;}
        else if (euler_msg->imu_can_id == right_thigh_id){start_index = 3;}
        else if (euler_msg->imu_can_id == left_thigh_id){start_index = 6;}
        else if (euler_msg->imu_can_id == right_shank_id){start_index = 9;}
        else if (euler_msg->imu_can_id == left_shank_id){start_index = 12;}
        else {
            // ROS_WARN("%d is undefined ID was received", euler_msg->imu_can_id);
            }
        if(flag_just_test == true){start_index = 0;}
        imu_current_list[start_index] = euler_msg->Yaw;
        imu_current_list[start_index + 1] = euler_msg->Roll;
        imu_current_list[start_index + 2] = euler_msg->Pitch;
        if (flag_start_listen == true)
        {
            joint_state_pub();
        }
    }

    void ImuToJointPanel::checkTest(){
        flag_just_test = checkbox_test->isChecked();
    }

    void ImuToJointPanel::joint_state_pub()
    {
        sensor_msgs::JointState joint_state_msg;
        joint_state_msg.header.stamp = ros::Time::now();
        joint_state_msg.header.frame_id = "test";
        joint_state_msg.name = {"r_hip_yaw_joint", "r_hip_roll_joint", "r_hip_pitch_joint",
                            "r_knee_pitch_joint",
                            "r_ankle_pitch_joint", "r_ankle_roll_joint",
                            "l_hip_yaw_joint", "l_hip_roll_joint", "l_hip_pitch_joint",
                            "l_knee_pitch_joint",
                            "l_ankle_pitch_joint", "l_ankle_roll_joint"};
        joint_state_msg.position = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        if(flag_just_test == false){set_joint_state(joint_state_msg);}
        else{test_joint_state(joint_state_msg);}
        pub_joint_state_.publish(joint_state_msg);
    }

    void ImuToJointPanel::test_joint_state(sensor_msgs::JointState &joint_state_msg){
        joint_state_msg.position[0] = euler_to_radian(imu_current_list[0]);
        joint_state_msg.position[1] = euler_to_radian(imu_current_list[1]);
        joint_state_msg.position[2] = euler_to_radian(imu_current_list[2]);
        for(int i = 3; i < 12; i++){joint_state_msg.position[i] = 0;}

    }

    void ImuToJointPanel::set_joint_state(sensor_msgs::JointState &joint_state_msg){
        if (imu_status_array[0] == 1 && imu_status_array [1] == 1)
        {
            joint_position_euler_array[0] = imu_current_list[3] - imu_current_list[0] - joint_position_offset_array[0];
            joint_position_euler_array[1] = imu_current_list[4] - imu_current_list[1] - joint_position_offset_array[1]; 
            joint_position_euler_array[2] = imu_current_list[5] - imu_current_list[2] - joint_position_offset_array[2];
            ROS_INFO("r_hip euler:%d , %d, %d ",joint_position_euler_array[0], joint_position_euler_array[1], joint_position_euler_array[2]);
        }
        // origin and left_thigh -> l_hip
        else if (imu_status_array[0] == 1 && imu_status_array[2] == 1)
        {
            joint_position_euler_array[6] = imu_current_list[6] - imu_current_list[0] - joint_position_offset_array[3];
            joint_position_euler_array[7] = imu_current_list[7] - imu_current_list[1] - joint_position_offset_array[4]; 
            joint_position_euler_array[8] = imu_current_list[8] - imu_current_list[2] - joint_position_offset_array[5];
            ROS_INFO("l_hip offset:%d , %d, %d ",joint_position_euler_array[6], joint_position_euler_array[7], joint_position_euler_array[8]);
        }
        // right_thigh and right_shank -> r_knee
        else if (imu_status_array[1] == 1 && imu_status_array[3] == 1)
        {
            joint_position_euler_array[3] = imu_current_list[9] - imu_current_list[3] - joint_position_offset_array[6];
            joint_position_euler_array[4] = imu_current_list[10] - imu_current_list[4] - joint_position_offset_array[7]; 
            joint_position_euler_array[5] = imu_current_list[11] - imu_current_list[5] - joint_position_offset_array[8];
            ROS_INFO("r_knee offset:%d , %d, %d ",joint_position_euler_array[3], joint_position_euler_array[4], joint_position_euler_array[5]);

        }
        // left_thigh and left_shank -> l_knee
        else if (imu_status_array[2] == 1 && imu_status_array[4] == 1)
        {
            joint_position_euler_array[9] = imu_current_list[12] - imu_current_list[6] - joint_position_offset_array[9] ;
            joint_position_euler_array[10] = imu_current_list[13] - imu_current_list[7] - joint_position_offset_array[10]; 
            joint_position_euler_array[11] = imu_current_list[14] - imu_current_list[8] - joint_position_offset_array[11];
            ROS_INFO("l_knee offset:%d , %d, %d ",joint_position_euler_array[9], joint_position_euler_array[10], joint_position_euler_array[11]);
        }
        for(int i = 0; i < 12; i++){
            joint_state_msg.position[i] = euler_to_radian(joint_position_euler_array[i]);
        }
        joint_state_msg.position[4] = 0;
        joint_state_msg.position[5] = 0;
        joint_state_msg.position[10] = 0;
        joint_state_msg.position[11] = 0;
    }

    void ImuToJointPanel::imu_start_listen(){
        ROS_INFO("imu_start_listen");
        if(flag_just_test == false){
            set_joint_offset();
        }
        int flag_have_imu = 0;
        for(int i = 0; i < 5; i++)
        {
            if (imu_status_array[i] == 1)
            {
                flag_have_imu++;
            }
        }
        if (flag_have_imu > 0)
        {
            flag_start_listen = true;
        }else{
            flag_start_listen = false;
            ROS_ERROR("Start listening failed!!");
        }
    }

    void ImuToJointPanel::imu_id_set()
    {
         ROS_INFO("imu_id_set");
        if (editor_origin_imu->text() != "")
        {
            int set_origin_imu_id = editor_origin_imu->text().toInt();
            if (set_origin_imu_id - 80 >= 0 && can_id_array[set_origin_imu_id - 80] != 0){origin_imu_id = set_origin_imu_id;imu_status_array[0] = 1;
            ROS_INFO("Set origin imu id ");
            }
            else {ROS_ERROR("Set_origin_id Error!");imu_status_array[0] = 0;}         
        }
        else if (editor_right_thigh_imu->text() != "")
        {
            int set_right_thigh_imu_id = editor_right_thigh_imu->text().toInt();
            if (set_right_thigh_imu_id - 80 >= 0 && can_id_array[set_right_thigh_imu_id - 80] != 0){right_thigh_id = set_right_thigh_imu_id;imu_status_array[1] = 1;}
            else {ROS_ERROR("Set_right_thigh_id Error!");imu_status_array[1] = 0;}
        }
        else if (editor_left_thigh_imu->text() != "")
        {
            int set_left_thigh_imu_id = editor_left_thigh_imu->text().toInt();
            if (set_left_thigh_imu_id - 80 >= 0 && can_id_array[set_left_thigh_imu_id - 80] != 0){left_thigh_id = set_left_thigh_imu_id;imu_status_array[2] = 1;}
            else {ROS_ERROR("Set_left_thigh_id Error!");imu_status_array[2] = 0;}
        }
        else if (editor_right_shank_imu->text() != "")
        {
            int set_right_shank_imu_id = editor_right_shank_imu->text().toInt();
            if (set_right_shank_imu_id - 80 >= 0 && can_id_array[set_right_shank_imu_id - 80] != 0){right_shank_id = set_right_shank_imu_id;imu_status_array[3] = 1;}
            else {ROS_ERROR("Set_right_shank_id Error!");imu_status_array[3] = 0;}
        }
        else if (editor_left_shank_imu->text() != "")
        {
            int set_left_shank_imu_id = editor_left_shank_imu->text().toInt();
            if (set_left_shank_imu_id - 80 >= 0 && can_id_array[set_left_shank_imu_id - 80] != 0){left_shank_id = set_left_shank_imu_id;imu_status_array[4] = 1;}
            else {ROS_ERROR("Set_left_shank_id Error!");imu_status_array[4] = 0;}
        }
        else{
            ROS_WARN("IMU_ID_SET_EDITOR_IS_NULL");
        }
        ROS_INFO("Set_origin_id: %d, Set_Right_thingh_id: %d, Set_left_thingh_id: %d",origin_imu_id,right_thigh_id,left_thigh_id);
        ROS_INFO("Set_right_shank_id: %d, Set_left_shank_id: %d \n",right_shank_id,left_shank_id);
        ROS_INFO("Status_origin_id: %d, Status_Right_thingh_id: %d, Status_left_thingh_id: %d",imu_status_array[0],imu_status_array[1],imu_status_array[2]);
        ROS_INFO("Status_right_shank_id: %d, Status_left_shank_id: %d",imu_status_array[3],imu_status_array[4]);
    }

    void ImuToJointPanel::set_joint_offset(){
        // origin and right_thigh -> r_hip
        if (imu_status_array[0] == 1 && imu_status_array [1] == 1)
        {
            joint_position_offset_array[0] = imu_current_list[3] - imu_current_list[0];
            joint_position_offset_array[1] = imu_current_list[4] - imu_current_list[1]; 
            joint_position_offset_array[2] = imu_current_list[5] - imu_current_list[2];
            ROS_INFO("r_hip offset:%d , %d, %d ",joint_position_offset_array[0], joint_position_offset_array[1], joint_position_offset_array[2]);
        }
        // origin and left_thigh -> l_hip
        else if (imu_status_array[0] == 1 && imu_status_array[2] == 1)
        {
            joint_position_offset_array[3] = imu_current_list[6] - imu_current_list[0];
            joint_position_offset_array[4] = imu_current_list[7] - imu_current_list[1]; 
            joint_position_offset_array[5] = imu_current_list[8] - imu_current_list[2];
            ROS_INFO("l_hip offset:%d , %d, %d ",joint_position_offset_array[3], joint_position_offset_array[4], joint_position_offset_array[5]);
        }
        // right_thigh and right_shank -> r_knee
        else if (imu_status_array[1] == 1 && imu_status_array[3] == 1)
        {
            joint_position_offset_array[6] = imu_current_list[9] - imu_current_list[3];
            joint_position_offset_array[7] = imu_current_list[10] - imu_current_list[4]; 
            joint_position_offset_array[8] = imu_current_list[11] - imu_current_list[5];
            ROS_INFO("r_knee offset:%d , %d, %d ",joint_position_offset_array[6], joint_position_offset_array[7], joint_position_offset_array[8]);

        }
        // left_thigh and left_shank -> l_knee
        else if (imu_status_array[2] == 1 && imu_status_array[4] == 1)
        {
            joint_position_offset_array[9] = imu_current_list[12] - imu_current_list[6];
            joint_position_offset_array[10] = imu_current_list[13] - imu_current_list[7]; 
            joint_position_offset_array[11] = imu_current_list[14] - imu_current_list[8];
            ROS_INFO("l_knee offset:%d , %d, %d ",joint_position_offset_array[9], joint_position_offset_array[10], joint_position_offset_array[11]);
        }
        
        
    }

    float ImuToJointPanel::euler_to_radian(float euler){
        float radians = M_PI / 180 * euler;
        return radians;
    }

    // spin for subscribing
    void ImuToJointPanel::startSpin() {
        if (ros::ok()) {
            ros::spinOnce();
        }
    }

} // end namespace navi-multi-goals-pub-rviz-plugin

// 声明此类是一个rviz的插件

#include <pluginlib/class_list_macros.h>

PLUGINLIB_EXPORT_CLASS(imu_to_joint_rviz_plugin::ImuToJointPanel, rviz::Panel)

