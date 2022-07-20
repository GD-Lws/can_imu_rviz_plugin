# IMU_TO_JointState_pub_panel

## Author
* Lws

## 环境
* ros melodic 

## 主要实现功能
* 添加两种方式得到IMU数据：（1）通过订阅外部话题；（2）通过自身can数据处理；
* 实现各关节的imu的can id绑定
* 可以初始化关节，和imu角度

## 未完成功能
* 运动质心的计算

## 效果展示
* 2022/7/13
![微信图片_20220713183842.png](https://s2.loli.net/2022/07/13/FkNXBgSY3HIZlAG.png)

* 2022/7/14
![微信截图_20220714155145.png](https://s2.loli.net/2022/07/14/sojVtRMAdDONr9k.png)

## Pub And Sub
### Pub
|   Topic    | 功能  |  最新更新时间  |
|:-----------|--------:|:------:|
|    joint_states     | 用于rviz的关节显示   | 2022/7/20 |
|    origin_Imu_pub_     | 腰部imu数据      | 2022/7/20 |
|    r_shank_Imu_pub_     | 右大腿imu数据     | 2022/7/20 |
|    l_shank_Imu_pub_     | 左大腿imu数据度   | 2022/7/20 |
|    r_thingh_Imu_pub_     | 右小腿imu数据   | 2022/7/20 |
|    l_thingh_Imu_pub_     | 左小腿imu数据      | 2022/7/20 |
|    x_position_pub_     | 质心x的位置      | 2022/7/20 |
|    x_acc_pub_     | 质心x的加速度      | 2022/7/20 |

### Sub
|   Topic    | 功能  |  回调函数  |
|:-----------|--------:|:------:|
|   sub_imu_msg_   | 用于订阅imu发布的角度数据（方式1）| euler_callback |
