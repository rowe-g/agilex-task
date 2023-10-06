# Task2
## 标定过程
适用于小车的雷达标定可参考[此代码](https://github.com/XidianLemon/calibration_camera_lidar.git)，小车的相机标定可利用[autoware](https://blog.csdn.net/qq_41545537/article/details/109312868)来进行[标定](https://blog.csdn.net/qq_38222947/article/details/125146447)。

## 标定结果分析
## 程序效果展示
## 总结和分析
## 参考文献 

## 生成融合图
生成方法参考[CSDN博客](https://blog.csdn.net/qq_38222947/article/details/125146447)

### 思路
读取相机图像+读取激光雷达图像+分别转换为`opencv`和`pcl`可用数据类型+在`opencv`中融合+发布话题。

### 程序设计
函数：

读取相机图像，并转化为`opencv`可用类型

读取激光雷达图像，并转化为`pcl`可用类型

将点云投影到图像上，并发布融合图像话题

变量：

需要存储相机和激光雷达信息的共享变量