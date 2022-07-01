#include <cstdio>

#include <ros/console.h>

#include <fstream>
#include <sstream>

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
        QPushButton *button_init = new QPushButton("IMU_msg_init");
        layout_root->addWidget(button_init);
        setLayout(layout_root);
         // set a Qtimer to start a spin for subscriptions
        QTimer *output_timer = new QTimer(this);
        output_timer->start(200);
        connect(output_timer, SIGNAL(timeout()), this, SLOT(startSpin()));
    }


    void ImuToJointPanel::euler_callback(const can_imu_lws::IMU_Euler_msg::ConstPtr &euler_msg){

        ROS_INFO("can_id: %d", euler_msg->imu_can_id);
        ROS_INFO("Roll: %d", euler_msg->Roll);
        ROS_INFO("Pitch: %d", euler_msg->Pitch);
        ROS_INFO("Yaw: %d", euler_msg->Yaw);
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

