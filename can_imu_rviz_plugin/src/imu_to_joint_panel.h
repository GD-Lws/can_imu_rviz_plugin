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


namespace imu_to_joint_rviz_plugin {
    class ImuToJointPanel : public rviz::Panel {
    Q_OBJECT
    public:
        explicit ImuToJointPanel(QWidget *parent = 0);

    public Q_SLOTS:

    protected Q_SLOTS:

       
    protected:
       
    };

} // end namespace navi-multi-goals-pub-rviz-plugin

#endif // MULTI_NAVI_GOAL_PANEL_H
