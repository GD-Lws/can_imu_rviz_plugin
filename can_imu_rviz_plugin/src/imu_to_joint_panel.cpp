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
     static void* thread_channel_1_receive(void* param){
        ImuToJointPanel *imutojont = (ImuToJointPanel*)param;
        int i,j;
        int ind = 0, reclen = 0, count = 0;
        ROS_INFO("imutojont->flag_thread_1_status : %d", flag_thread_1_status);
        VCI_CAN_OBJ rec[3000];
        while (flag_thread_1_status == 1)
        {
            // ROS_INFO("Start_listen");
            if((reclen=VCI_Receive(VCI_USBCAN2,0,1,rec,3000,100))>0)//调用接收函数，如果有数据，进行数据处理显示。
            {
                for(j=0;j<reclen;j++)
                {
                    imutojont->vci_obj_process(rec[j]);
                }
            }
        }
        ROS_INFO("run thread exit\n");//退出接收线程	
	    pthread_exit(NULL);
   
    }

    void* thread_channel_2_receive(void* param){

    }

    ImuToJointPanel::ImuToJointPanel(QWidget *parent)
            : rviz::Panel(parent),nh_(){
        pub_joint_state_ = nh_.advertise<sensor_msgs::JointState>("joint_states",1);
        sub_imu_msg_ = nh_.subscribe<can_imu_lws::IMU_Euler_msg>("imu_euler_pub",100,
                                    boost::bind(&ImuToJointPanel::euler_callback, this,_1));

        pub_joint_origin_imu = nh_.advertise<sensor_msgs::Imu>("origin_Imu_pub",1);
        pub_joint_r_shank_imu = nh_.advertise<sensor_msgs::Imu>("r_shank_Imu_pub",1);
        pub_joint_l_shank_imu = nh_.advertise<sensor_msgs::Imu>("l_shank_Imu_pub",1);
        pub_joint_r_thigh_imu = nh_.advertise<sensor_msgs::Imu>("r_thingh_Imu_pub",1);
        pub_joint_l_thigh_imu = nh_.advertise<sensor_msgs::Imu>("l_thingh_Imu_pub",1);
        pub_euler_imu = nh_.advertise<can_imu_lws::IMU_Euler_msg>("imu_euler_test",1);

                                    
        QVBoxLayout *layout_root = new QVBoxLayout;
        layout_root->addWidget(new QLabel("imu_msg_to_joint_state"));

        QHBoxLayout *layout_can_device_init = new QHBoxLayout;
        button_can_device_open = new QPushButton("Can Device Open");
        button_can_device_close = new QPushButton("Can Device Close");
    
        layout_can_device_init->addWidget(button_can_device_open);
        layout_can_device_init->addWidget(button_can_device_close);
        layout_root->addLayout(layout_can_device_init);

        QHBoxLayout *layout_can_device_control = new QHBoxLayout;
        button_can_start_listen = new QPushButton("Can Start_listen");
        button_can_stop_listen = new QPushButton("Can Stop_listen");
    
        layout_can_device_control->addWidget(button_can_start_listen);
        layout_can_device_control->addWidget(button_can_stop_listen);
        layout_root->addLayout(layout_can_device_control);

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

        QHBoxLayout *layout_checkBox = new QHBoxLayout;
        checkbox_test = new QCheckBox("Just Test euler");
        layout_checkBox->addWidget(checkbox_test);
        checkbox_sub_or_load = new QCheckBox("Sub_or_Load");
        layout_checkBox->addWidget(checkbox_sub_or_load);
        layout_root->addLayout(layout_checkBox);
        
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
        connect(button_can_start_listen, SIGNAL(clicked()), this, SLOT(can_start_listen()));
        connect(button_can_stop_listen, SIGNAL(clicked()), this, SLOT(can_stop_listen()));

        connect(button_imu_start_listen, SIGNAL(clicked()), this, SLOT(imu_start_listen()));
        // 单个imu接收测试
        connect(checkbox_test, SIGNAL(clicked(bool)), this, SLOT(checkTest()));

      /*  int pthread_create(
                 pthread_t *restrict tidp,   //新创建的线程ID指向的内存单元。
                 const pthread_attr_t *restrict attr,  //线程属性，默认为NULL
                 void *(*start_rtn)(void *), //新创建的线程从start_rtn函数的地址开始运行
                 void *restrict arg //默认为NULL。若上述函数需要参数，将参数放入结构中并将地址作为arg传入。
                  );*/
        // int status_thread_2 = pthread_create(&threadid_2, NULL, (thread_channel_2_receive), this);
        flag_thread_1_status = 0;
        flag_thread_2_status = 0;
    }

    // can_receive to msg
    void ImuToJointPanel::vci_obj_process(VCI_CAN_OBJ vci_can_obj){
        int rec_can_id = vci_can_obj.ID;//ID
        // ROS_INFO("rec_can_id: %d", rec_can_id);
        int rec_can_id_index = rec_can_id - 80;
        if (vector_joint_imu[rec_can_id_index].empty())
        {
            sensor_msgs::Imu temp_Imu;
            temp_Imu.header.seq = 0;
            temp_Imu.header.frame_id = std::to_string(rec_can_id);
            vector_joint_imu[rec_can_id_index].push_back(temp_Imu);
        }
        std::vector<sensor_msgs::Imu>::iterator sensor_iterator = vector_joint_imu[rec_can_id_index].begin();
        if ((int)vci_can_obj.Data[0] == 85)
        {
            //    ROS_INFO("IMU_MSG");
            if((int)vci_can_obj.Data[1] == 82){
                // 角速度输出
                float Wx = (float)byte_to_short(vci_can_obj.Data[3], vci_can_obj.Data[2])  / 32768 * 2000 * M_1_PI / 180;
                float Wy = (float)byte_to_short(vci_can_obj.Data[5], vci_can_obj.Data[4])  / 32768 * 2000 * M_1_PI / 180;
                float Wz = (float)byte_to_short(vci_can_obj.Data[7], vci_can_obj.Data[6])  / 32768 * 2000 * M_1_PI / 180;
                // ROS_INFO("Wx:%f,Wy:%f,Wz:%f", Wx, Wy, Wz);
                if (sensor_iterator->header.seq == 0)
                {
                    sensor_iterator->angular_velocity.x = Wx;
                    sensor_iterator->angular_velocity.y = Wy;
                    sensor_iterator->angular_velocity.z = Wz;
                    sensor_iterator->header.seq = 1;
                }
            }else if ((int)vci_can_obj.Data[1] == 81)
            {
                // 加速度输出
                float Ax = (float)byte_to_short(vci_can_obj.Data[3], vci_can_obj.Data[2]) / 32768.0 * 16 * 9.8;
                float Ay = (float)byte_to_short(vci_can_obj.Data[5], vci_can_obj.Data[4]) / 32768.0 * 16 * 9.8;
                float Az = (float)byte_to_short(vci_can_obj.Data[7], vci_can_obj.Data[6]) / 32768.0 * 16 * 9.8;
                if (sensor_iterator->header.seq == 1)
                {
                    sensor_iterator->linear_acceleration.x = Ax;
                    sensor_iterator->linear_acceleration.y = Ay;
                    sensor_iterator->linear_acceleration.z = Az;
                    sensor_iterator->header.seq = 2;
                }
            }else if ((int)vci_can_obj.Data[1] == 83)
            {
                // ROS_INFO("%f", imu_data);
                // 角度输出
                float imu_roll = (float)byte_to_short(vci_can_obj.Data[3], vci_can_obj.Data[2]) /32768*180;
                float imu_pitch = (float)byte_to_short(vci_can_obj.Data[5], vci_can_obj.Data[4]) /32768*180;
                float imu_yaw = (float)byte_to_short(vci_can_obj.Data[7], vci_can_obj.Data[6]) /32768*180;
                
                can_imu_lws::IMU_Euler_msg imu_euler_msg;
                imu_euler_msg.imu_can_id = rec_can_id;
                imu_euler_msg.Pitch = imu_pitch;
                imu_euler_msg.Yaw = imu_yaw;
                euler_msg_process(imu_euler_msg);
                ROS_INFO("roll: %f, pitch: %f, yaw: %f", imu_roll, imu_pitch, imu_yaw);
                 if (sensor_iterator->header.seq == 2){
                    geometry_msgs::Quaternion quat = tf::createQuaternionMsgFromRollPitchYaw(imu_roll, imu_pitch, imu_yaw);
                    sensor_iterator->orientation = quat;
                    sensor_iterator->header.stamp = ros::Time::now();
                    if (rec_can_id == origin_imu_id){pub_joint_origin_imu.publish(*sensor_iterator);}
                    else if (rec_can_id == right_thigh_id){pub_joint_r_thigh_imu.publish(*sensor_iterator);}
                    else if (rec_can_id == right_shank_id){pub_joint_r_shank_imu.publish(*sensor_iterator);}
                    else if (rec_can_id == left_shank_id){pub_joint_l_shank_imu.publish(*sensor_iterator);}
                    else if (rec_can_id == left_thigh_id){pub_joint_l_thigh_imu.publish(*sensor_iterator);}
                    vector_joint_imu[rec_can_id_index].pop_back();
                }
            }
        }
        // ROS_INFO("\n");
    }

    int ImuToJointPanel::byte_to_short(BYTE H_data, BYTE L_data){
         short temp = 0;
         temp = temp |H_data;
         temp = temp << 8;
         temp = temp | L_data;
        //  ROS_INFO("temp: %d", temp);
         return (int)temp;
    }

    // 用于话题接收处理数据
    void ImuToJointPanel::euler_callback(const can_imu_lws::IMU_Euler_msg::ConstPtr &euler_msg){
         if(flag_sub_or_load == true){
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
            // pub_euler_imu.publish(imu_euler_msg);
            if (flag_start_listen == true)
            {
                joint_state_pub();
            }
         }
    }

    // 用于处理自身读取到的角度
    void ImuToJointPanel::euler_msg_process(can_imu_lws::IMU_Euler_msg euler_msg){
        if(flag_sub_or_load == false){
            int can_id_index = euler_msg.imu_can_id - 80;
            if (can_id_index < 10){can_id_array[can_id_index] = 1;}
            int start_index = 0;
            if (euler_msg.imu_can_id == origin_imu_id){start_index = 0;}
            else if (euler_msg.imu_can_id == right_thigh_id){start_index = 3;}
            else if (euler_msg.imu_can_id == left_thigh_id){start_index = 6;}
            else if (euler_msg.imu_can_id == right_shank_id){start_index = 9;}
            else if (euler_msg.imu_can_id == left_shank_id){start_index = 12;}
            else {
                // ROS_WARN("%d is undefined ID was received", euler_msg->imu_can_id);
                }
            if(flag_just_test == true){start_index = 0;}
            imu_current_list[start_index] = euler_msg.Yaw;
            imu_current_list[start_index + 1] = euler_msg.Roll;
            imu_current_list[start_index + 2] = euler_msg.Pitch;
            if (flag_start_listen == true)
            {
                joint_state_pub();
            }
        }
    }

    void ImuToJointPanel::can_start_listen(){
        if(flag_channel_1_open == 1){flag_thread_1_status = 1;
            int status_thread_1 = pthread_create(&threadid_1, NULL, thread_channel_1_receive, (void*)this);
            ROS_INFO("status_thread_1 : %d", status_thread_1);
        }
        else {ROS_ERROR("Channel 1 is not open yet!!");}
        if(flag_channel_2_open == 1){flag_thread_2_status = 1;}
        else{ROS_ERROR("Channel 2 is not open yet!!");}
        if(flag_channel_2_open == 1 && flag_channel_1_open == 1)
        ROS_WARN("Can Receive On");
    }

    void ImuToJointPanel::can_stop_listen(){
        flag_thread_1_status = 0;
        flag_thread_2_status = 0;
        // pthread_join(threadid_2,NULL);//等待线程关闭。
        ROS_WARN("Can Receive Off");
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
                flag_channel_1_start = VCI_StartCAN(VCI_USBCAN2, 0, 0);
            }else{
                ROS_ERROR("Channel_1_open_failed");
            }
            if(flag_channel_2_open == 1){
                ROS_WARN("Channel_2_open_sucess!!");
                flag_channel_2_start = VCI_StartCAN(VCI_USBCAN2, 0, 1);
            }else{
                ROS_ERROR("Channel_2_open_failed");
            }
            if(flag_channel_1_start == 1){
                ROS_WARN("Channel_1_start_sucess!!");
            }else{
                ROS_ERROR("Channel_1_start_failed");
            }
            if(flag_channel_2_start == 1){
                ROS_WARN("Channel_2_start_sucess!!");
            }else{
                ROS_ERROR("Channel_2_start_failed");
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

    void ImuToJointPanel::checkSubLoad(){
        flag_sub_or_load = checkbox_sub_or_load->isChecked();
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
        if (imu_joint_status_array[0] == 1 && imu_joint_status_array [1] == 1)
        {
            joint_position_euler_array[0] = imu_current_list[3] - imu_current_list[0] - joint_position_offset_array[0];
            joint_position_euler_array[2] = imu_current_list[4] - imu_current_list[1] - joint_position_offset_array[1]; 
            joint_position_euler_array[1] = imu_current_list[5] - imu_current_list[2] - joint_position_offset_array[2];
            ROS_INFO("r_hip euler:%f , %f, %f ",joint_position_euler_array[0], joint_position_euler_array[1], joint_position_euler_array[2]);
        }
        // origin and left_thigh -> l_hip
        if (imu_joint_status_array[0] == 1 && imu_joint_status_array[2] == 1)
        {
            joint_position_euler_array[6] = imu_current_list[6] - imu_current_list[0] - joint_position_offset_array[3];
            joint_position_euler_array[8] = imu_current_list[7] - imu_current_list[1] - joint_position_offset_array[4]; 
            joint_position_euler_array[7] = imu_current_list[8] - imu_current_list[2] - joint_position_offset_array[5];
            ROS_INFO("l_hip euler:%f , %f, %f ",joint_position_euler_array[6], joint_position_euler_array[7], joint_position_euler_array[8]);
        }
        // right_thigh and right_shank -> r_knee
        if (imu_joint_status_array[1] == 1 && imu_joint_status_array[3] == 1)
        {
            joint_position_euler_array[3] = imu_current_list[9] - imu_current_list[3] - joint_position_offset_array[6];
            joint_position_euler_array[4] = imu_current_list[10] - imu_current_list[4] - joint_position_offset_array[7]; 
            joint_position_euler_array[5] = imu_current_list[11] - imu_current_list[5] - joint_position_offset_array[8];
            ROS_INFO("r_knee euler:%f , %f, %f ",joint_position_euler_array[3], joint_position_euler_array[4], joint_position_euler_array[5]);
        }
        // left_thigh and left_shank -> l_knee
        if (imu_joint_status_array[2] == 1 && imu_joint_status_array[4] == 1)
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
            if (imu_joint_status_array[i] == 1)
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
                origin_imu_id = set_origin_imu_id;imu_joint_status_array[0] = 1;
                ROS_INFO("Set origin imu id ");
                flag_have_text = true;
            }
            else {ROS_ERROR("Set_origin_id Error!");imu_joint_status_array[0] = 0;}         
        }
        if (editor_right_thigh_imu->text() != "")
        {
            int set_right_thigh_imu_id = editor_right_thigh_imu->text().toInt();
            if (set_right_thigh_imu_id - 80 >= 0 && can_id_array[set_right_thigh_imu_id - 80] != 0){
                right_thigh_id = set_right_thigh_imu_id;
                imu_joint_status_array[1] = 1;
                flag_have_text = true;
                }
            else {ROS_ERROR("Set_right_thigh_id Error!");imu_joint_status_array[1] = 0;}
        }
        if (editor_left_thigh_imu->text() != "")
        {
            int set_left_thigh_imu_id = editor_left_thigh_imu->text().toInt();
            if (set_left_thigh_imu_id - 80 >= 0 && can_id_array[set_left_thigh_imu_id - 80] != 0){
                left_thigh_id = set_left_thigh_imu_id;
                imu_joint_status_array[2] = 1;
                flag_have_text = true;
                }
            else {ROS_ERROR("Set_left_thigh_id Error!");imu_joint_status_array[2] = 0;}
        }
        if (editor_right_shank_imu->text() != "")
        {
            int set_right_shank_imu_id = editor_right_shank_imu->text().toInt();
            if (set_right_shank_imu_id - 80 >= 0 && can_id_array[set_right_shank_imu_id - 80] != 0){
                right_shank_id = set_right_shank_imu_id;
                imu_joint_status_array[3] = 1;
                flag_have_text = true;
                }
            else {ROS_ERROR("Set_right_shank_id Error!");imu_joint_status_array[3] = 0;}
        }
        if (editor_left_shank_imu->text() != "")
        {
            int set_left_shank_imu_id = editor_left_shank_imu->text().toInt();
            if (set_left_shank_imu_id - 80 >= 0 && can_id_array[set_left_shank_imu_id - 80] != 0){left_shank_id = set_left_shank_imu_id;imu_joint_status_array[4] = 1;}
            else {ROS_ERROR("Set_left_shank_id Error!");imu_joint_status_array[4] = 0;}
        }
        if(flag_have_text == false){
            ROS_ERROR("IMU_ID_SET_EDITOR_IS_NULL");
        }else{
            ROS_WARN("Set_origin_id: %d, Set_Right_thingh_id: %d, Set_left_thingh_id: %d",origin_imu_id,right_thigh_id,left_thigh_id);
            ROS_WARN("Set_right_shank_id: %d, Set_left_shank_id: %d \n",right_shank_id,left_shank_id);
            ROS_WARN("Status_origin_id: %d, Status_Right_thingh_id: %d, Status_left_thingh_id: %d",imu_joint_status_array[0],imu_joint_status_array[1],imu_joint_status_array[2]);
            ROS_WARN("Status_right_shank_id: %d, Status_left_shank_id: %d",imu_joint_status_array[3],imu_joint_status_array[4]);
        }
    }

    void ImuToJointPanel::set_joint_offset(){
        // origin and right_thigh -> r_hip
        if (imu_joint_status_array[0] == 1 && imu_joint_status_array [1] == 1)
        {
            joint_position_offset_array[0] = imu_current_list[3] - imu_current_list[0];
            joint_position_offset_array[1] = imu_current_list[4] - imu_current_list[1]; 
            joint_position_offset_array[2] = imu_current_list[5] - imu_current_list[2];
            ROS_WARN("r_hip offset:%f , %f, %f ",joint_position_offset_array[0], joint_position_offset_array[1], joint_position_offset_array[2]);
        }
        // origin and left_thigh -> l_hip
        if (imu_joint_status_array[0] == 1 && imu_joint_status_array[2] == 1)
        {
            joint_position_offset_array[3] = imu_current_list[6] - imu_current_list[0];
            joint_position_offset_array[4] = imu_current_list[7] - imu_current_list[1]; 
            joint_position_offset_array[5] = imu_current_list[8] - imu_current_list[2];
            ROS_WARN("l_hip offset:%f , %f, %f ",joint_position_offset_array[3], joint_position_offset_array[4], joint_position_offset_array[5]);
        }
        // right_thigh and right_shank -> r_knee
        if (imu_joint_status_array[1] == 1 && imu_joint_status_array[3] == 1)
        {
            joint_position_offset_array[6] = imu_current_list[9] - imu_current_list[3];
            joint_position_offset_array[7] = imu_current_list[10] - imu_current_list[4]; 
            joint_position_offset_array[8] = imu_current_list[11] - imu_current_list[5];
            ROS_WARN("r_knee offset:%f , %f, %f ",joint_position_offset_array[6], joint_position_offset_array[7], joint_position_offset_array[8]);

        }
        // left_thigh and left_shank -> l_knee
        if (imu_joint_status_array[2] == 1 && imu_joint_status_array[4] == 1)
        {
            joint_position_offset_array[9] = imu_current_list[12] - imu_current_list[6];
            joint_position_offset_array[10] = imu_current_list[13] - imu_current_list[7]; 
            joint_position_offset_array[11] = imu_current_list[14] - imu_current_list[8];
            ROS_WARN("l_knee offset:%f , %f, %f ",joint_position_offset_array[9], joint_position_offset_array[10], joint_position_offset_array[11]);
        }
    }

    // 角度转弧度
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

