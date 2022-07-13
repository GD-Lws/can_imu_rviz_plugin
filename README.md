# IMU_TO_JointState_pub_panel

## Author
* Lws

## 环境
* ros melodic 

## 主要实现功能
* * 将msg_receive取消，直接通过rviz开启can device，提高了数据读取效率
* 初始化各关节的can Id
* 加入初始化角度抵消

## 未完成功能
* 运动质心的计算

## 效果展示
![微信图片_20220713183842.png](https://s2.loli.net/2022/07/13/FkNXBgSY3HIZlAG.png)