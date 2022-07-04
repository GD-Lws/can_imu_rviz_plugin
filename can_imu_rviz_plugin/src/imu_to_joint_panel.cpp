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
     void* thread_channel_1_receive(void* param){
        ImuToJointPanel *imutojont = (ImuToJointPanel*)param;
        int flag_run = imutojont->flag_thread_1_status;
        VCI_CAN_OBJ rec[3000];
        while (flag_run == 1)
        {
            if((reclen=VCI_Receive(VCI_USBCAN2,0,1,rec,3000,100))>0)//调用接收函数，如果有数据，进行数据处理显示。
            {
                for(j=0;j<reclen;j++)
                {
                    printf("Index:%04d  ",count);count++;//序号递增
                    printf("CAN%d RX ID:0x%08X", ind+1, rec[j].ID);//ID
                    if(rec[j].ExternFlag==0) printf(" Standard ");//帧格式：标准帧
                    if(rec[j].ExternFlag==1) printf(" Extend   ");//帧格式：扩展帧
                    if(rec[j].RemoteFlag==0) printf(" Data   ");//帧类型：数据帧
                    if(rec[j].RemoteFlag==1) printf(" Remote ");//帧类型：远程帧
                    printf("DLC:0x%02X",rec[j].DataLen);//帧长度
                    printf(" data:0x");	//数据
                    for(i = 0; i < rec[j].DataLen; i++)
                    {
                        printf(" %02X", rec[j].Data[i]);
                    }
                    printf(" TimeStamp:0x%08X",rec[j].TimeStamp);//时间标识。
                    printf("\n");
                }
            }
        }
    }

    void* thread_channel_2_receive(void* param){

    }

    ImuToJointPanel::ImuToJointPanel(QWidget *parent)
            : rviz::Panel(parent),nh_(){
        pub_joint_state_ = nh_.advertise<sensor_msgs::JointState>("joint_states",1);
        sub_imu_msg_ = nh_.subscribe<can_imu_lws::IMU_Euler_msg>("imu_euler_pub",100,
                                    boost::bind(&ImuToJointPanel::euler_callback, this,_1));
                                    
        QVBoxLayout *layout_root = new QVBoxLayout;
        layout_root->addWidget(new QLabel("imu_msg_to_joint_state"));

        QHBoxLayout *layout_can_device = new QHBoxLayout;
        button_can_device_open = new QPushButton("Can Device Open");
        button_can_device_close = new QPushButton("Can Device Close");
        button_can_msg_receive = new QPushButton("Can Msg Rec");
    
        layout_can_device->addWidget(button_can_device_open);
        layout_can_device->addWidget(button_can_device_close);
        layout_root->addLayout(layout_can_device);

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
        output_timer->start(100);
        connect(output_timer, SIGNAL(timeout()), this, SLOT(startSpin()));
        connect(button_imu_id_set, SIGNAL(clicked()), this, SLOT(imu_id_set()));
       
        connect(button_can_device_open, SIGNAL(clicked()), this, SLOT(open_can_device()));
        connect(button_can_device_close, SIGNAL(clicked()), this, SLOT(close_can_device()));
        connect(button_can_msg_receive, SIGNAL(clicked()), this, SLOT(close_can_device()));
        
        connect(button_imu_start_listen, SIGNAL(clicked()), this, SLOT(imu_start_listen()));
        connect(checkbox_test, SIGNAL(clicked(bool)), this, SLOT(checkTest()));

      /*  int pthread_create(
                 pthread_t *restrict tidp,   //新创建的线程ID指向的内存单元。
                 const pthread_attr_t *restrict attr,  //线程属性，默认为NULL
                 void *(*start_rtn)(void *), //新创建的线程从start_rtn函数的地址开始运行
                 void *restrict arg //默认为NULL。若上述函数需要参数，将参数放入结构中并将地址作为arg传入。
                  );*/
        pthread_t threadid_1;
        pthread_t threadid_2;
        int status_thread_1 = pthread_create(&threadid_1, NULL, (thread_channel_1_receive), this);
        int status_thread_2 = pthread_create(&threadid_2, NULL, (thread_channel_2_receive), this);
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

    void ImuToJointPanel::can_msg_receive(){
        flag_thread_1_status = 1;
        flag_thread_2_status = 1;
    }

    

    void ImuToJointPanel::can_device_config_init(int Baud){
        can_device_config.AccCode = 0;
        can_device_config.AccMask=0xFFFFFFFF;
        can_device_config.Filter=1;//接收所有帧
        if (Baud == 500){
            // 500K
            can_device_config.Timing0=0x00;/*波特率500 Kbps*/
            can_device_config.Timing1=0x1C;
        }else if(Baud == 100)
        {
            // 100K
            can_device_config.Timing0=0x04;/*波特率100 Kbps*/
            can_device_config.Timing1=0x1C;
        }else{
            // 1M
            can_device_config.Timing0=0x00;/*波特率1 Mbps*/
            can_device_config.Timing1=0x14;
        }
       
        can_device_config.Mode=0;//正常模式
    }

    void ImuToJointPanel::open_can_device(){
        flag_device_open = VCI_OpenDevice(VCI_USBCAN2, 0, 0);
        if (flag_device_open == 1)
        {
            ROS_WARN("Device open sucess!!");
            can_device_config_init(1000);
            flag_channel_1_open = VCI_InitCAN(VCI_USBCAN2, 0, 0, &can_device_config);
            flag_channel_2_open = VCI_InitCAN(VCI_USBCAN2, 0, 1, &can_device_config);
            if(flag_channel_1_open == 1){
                ROS_WARN("Channel_1_open_sucess!!");
            }else{
                ROS_ERROR("Channel_1_open_failed");
            }
            if(flag_channel_2_open == 1){
                ROS_WARN("Channel_2_open_sucess!!");
            }else{
                ROS_ERROR("Channel_2_open_failed");
            }
        }else{
            ROS_ERROR("Device open failed!!");
        }
    };
    void ImuToJointPanel::close_can_device(){
        if (flag_device_open == 1)
        {
            VCI_ResetCAN(VCI_USBCAN2, 0, 0);//复位CAN1通道。
	        usleep(100000);//延时100ms。
            VCI_ResetCAN(VCI_USBCAN2, 0, 1);//复位CAN2通道。
            VCI_CloseDevice(VCI_USBCAN2,0);
            ROS_WARN("The device has been shut down.");
        }else{
            ROS_WARN("The device is not started.");
        }
    };

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
            joint_position_euler_array[2] = imu_current_list[4] - imu_current_list[1] - joint_position_offset_array[1]; 
            joint_position_euler_array[1] = imu_current_list[5] - imu_current_list[2] - joint_position_offset_array[2];
            ROS_INFO("r_hip euler:%f , %f, %f ",joint_position_euler_array[0], joint_position_euler_array[1], joint_position_euler_array[2]);
        }
        // origin and left_thigh -> l_hip
        if (imu_status_array[0] == 1 && imu_status_array[2] == 1)
        {
            joint_position_euler_array[6] = imu_current_list[6] - imu_current_list[0] - joint_position_offset_array[3];
            joint_position_euler_array[8] = imu_current_list[7] - imu_current_list[1] - joint_position_offset_array[4]; 
            joint_position_euler_array[7] = imu_current_list[8] - imu_current_list[2] - joint_position_offset_array[5];
            ROS_INFO("l_hip euler:%f , %f, %f ",joint_position_euler_array[6], joint_position_euler_array[7], joint_position_euler_array[8]);
        }
        // right_thigh and right_shank -> r_knee
        if (imu_status_array[1] == 1 && imu_status_array[3] == 1)
        {
            joint_position_euler_array[3] = imu_current_list[9] - imu_current_list[3] - joint_position_offset_array[6];
            joint_position_euler_array[4] = imu_current_list[10] - imu_current_list[4] - joint_position_offset_array[7]; 
            joint_position_euler_array[5] = imu_current_list[11] - imu_current_list[5] - joint_position_offset_array[8];
            ROS_INFO("r_knee euler:%f , %f, %f ",joint_position_euler_array[3], joint_position_euler_array[4], joint_position_euler_array[5]);
        }
        // left_thigh and left_shank -> l_knee
        if (imu_status_array[2] == 1 && imu_status_array[4] == 1)
        {
            joint_position_euler_array[9] = imu_current_list[12] - imu_current_list[6] - joint_position_offset_array[9] ;
            joint_position_euler_array[10] = imu_current_list[13] - imu_current_list[7] - joint_position_offset_array[10]; 
            joint_position_euler_array[11] = imu_current_list[14] - imu_current_list[8] - joint_position_offset_array[11];
            ROS_INFO("l_knee euler:%f , %f, %f ",joint_position_euler_array[9], joint_position_euler_array[10], joint_position_euler_array[11]);
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
         bool flag_have_text = false;
        if (editor_origin_imu->text() != "")
        {
            int set_origin_imu_id = editor_origin_imu->text().toInt();
            if (set_origin_imu_id - 80 >= 0 && can_id_array[set_origin_imu_id - 80] != 0){
                origin_imu_id = set_origin_imu_id;imu_status_array[0] = 1;
                ROS_INFO("Set origin imu id ");
                flag_have_text = true;
            }
            else {ROS_ERROR("Set_origin_id Error!");imu_status_array[0] = 0;}         
        }
        if (editor_right_thigh_imu->text() != "")
        {
            int set_right_thigh_imu_id = editor_right_thigh_imu->text().toInt();
            if (set_right_thigh_imu_id - 80 >= 0 && can_id_array[set_right_thigh_imu_id - 80] != 0){
                right_thigh_id = set_right_thigh_imu_id;
                imu_status_array[1] = 1;
                flag_have_text = true;
                }
            else {ROS_ERROR("Set_right_thigh_id Error!");imu_status_array[1] = 0;}
        }
        if (editor_left_thigh_imu->text() != "")
        {
            int set_left_thigh_imu_id = editor_left_thigh_imu->text().toInt();
            if (set_left_thigh_imu_id - 80 >= 0 && can_id_array[set_left_thigh_imu_id - 80] != 0){
                left_thigh_id = set_left_thigh_imu_id;
                imu_status_array[2] = 1;
                flag_have_text = true;
                }
            else {ROS_ERROR("Set_left_thigh_id Error!");imu_status_array[2] = 0;}
        }
        if (editor_right_shank_imu->text() != "")
        {
            int set_right_shank_imu_id = editor_right_shank_imu->text().toInt();
            if (set_right_shank_imu_id - 80 >= 0 && can_id_array[set_right_shank_imu_id - 80] != 0){
                right_shank_id = set_right_shank_imu_id;
                imu_status_array[3] = 1;
                flag_have_text = true;
                }
            else {ROS_ERROR("Set_right_shank_id Error!");imu_status_array[3] = 0;}
        }
        if (editor_left_shank_imu->text() != "")
        {
            int set_left_shank_imu_id = editor_left_shank_imu->text().toInt();
            if (set_left_shank_imu_id - 80 >= 0 && can_id_array[set_left_shank_imu_id - 80] != 0){left_shank_id = set_left_shank_imu_id;imu_status_array[4] = 1;}
            else {ROS_ERROR("Set_left_shank_id Error!");imu_status_array[4] = 0;}
        }
        if(flag_have_text == false){
            ROS_ERROR("IMU_ID_SET_EDITOR_IS_NULL");
        }else{
            ROS_WARN("Set_origin_id: %d, Set_Right_thingh_id: %d, Set_left_thingh_id: %d",origin_imu_id,right_thigh_id,left_thigh_id);
            ROS_WARN("Set_right_shank_id: %d, Set_left_shank_id: %d \n",right_shank_id,left_shank_id);
            ROS_WARN("Status_origin_id: %d, Status_Right_thingh_id: %d, Status_left_thingh_id: %d",imu_status_array[0],imu_status_array[1],imu_status_array[2]);
            ROS_WARN("Status_right_shank_id: %d, Status_left_shank_id: %d",imu_status_array[3],imu_status_array[4]);
        }
    }

    void ImuToJointPanel::set_joint_offset(){
        // origin and right_thigh -> r_hip
        if (imu_status_array[0] == 1 && imu_status_array [1] == 1)
        {
            joint_position_offset_array[0] = imu_current_list[3] - imu_current_list[0];
            joint_position_offset_array[1] = imu_current_list[4] - imu_current_list[1]; 
            joint_position_offset_array[2] = imu_current_list[5] - imu_current_list[2];
            ROS_WARN("r_hip offset:%f , %f, %f ",joint_position_offset_array[0], joint_position_offset_array[1], joint_position_offset_array[2]);
        }
        // origin and left_thigh -> l_hip
        if (imu_status_array[0] == 1 && imu_status_array[2] == 1)
        {
            joint_position_offset_array[3] = imu_current_list[6] - imu_current_list[0];
            joint_position_offset_array[4] = imu_current_list[7] - imu_current_list[1]; 
            joint_position_offset_array[5] = imu_current_list[8] - imu_current_list[2];
            ROS_WARN("l_hip offset:%f , %f, %f ",joint_position_offset_array[3], joint_position_offset_array[4], joint_position_offset_array[5]);
        }
        // right_thigh and right_shank -> r_knee
        if (imu_status_array[1] == 1 && imu_status_array[3] == 1)
        {
            joint_position_offset_array[6] = imu_current_list[9] - imu_current_list[3];
            joint_position_offset_array[7] = imu_current_list[10] - imu_current_list[4]; 
            joint_position_offset_array[8] = imu_current_list[11] - imu_current_list[5];
            ROS_WARN("r_knee offset:%f , %f, %f ",joint_position_offset_array[6], joint_position_offset_array[7], joint_position_offset_array[8]);

        }
        // left_thigh and left_shank -> l_knee
        if (imu_status_array[2] == 1 && imu_status_array[4] == 1)
        {
            joint_position_offset_array[9] = imu_current_list[12] - imu_current_list[6];
            joint_position_offset_array[10] = imu_current_list[13] - imu_current_list[7]; 
            joint_position_offset_array[11] = imu_current_list[14] - imu_current_list[8];
            ROS_WARN("l_knee offset:%f , %f, %f ",joint_position_offset_array[9], joint_position_offset_array[10], joint_position_offset_array[11]);
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

