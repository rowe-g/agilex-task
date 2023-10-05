#!/bin/bash
#main refs were listed beblow:
#https://github.com/ROBOTIS-GIT/robotis_tools/blob/master/install_ros_melodic.sh
#https://blog.csdn.net/cnds123/article/details/107427030
#https://stackoverflow.com/questions/9952177/whats-the-meaning-of-the-parameter-e-for-bash-shell-command-line

echo ""
echo "[Note] Target OS version  >>> Ubuntu 18.04.x (Bionic Beaver) or Linux Mint 19.x"
echo "[Note] Target ROS version >>> ROS Melodic Morenia"
echo "[Note] Catkin workspace   >>> $HOME/catkin_ws"
echo ""
echo "PRESS [ENTER] TO CONTINUE THE INSTALLATION"
echo "IF YOU WANT TO CANCEL, PRESS [CTRL] + [C]"
read

echo "[Set the target OS, ROS version and name of catkin workspace]"
name_os_version=${name_os_version:="bionic"}
name_ros_version=${name_ros_version:="melodic"}
name_catkin_workspace=${name_catkin_workspace:="catkin_ws"}

echo "[update&upgrade the package lists]"
sudo apt update -y && sudo apt upgrade

echo "[Install build environment, the chrony, ntpdate and set the ntpdate]"
sudo apt install -y chrony ntpdate curl build-essential aptitude
sudo ntpdate ntp.ubuntu.com

echo "[Add the ROS repository]"
if [ ! -e /etc/apt/sources.list.d/ros-latest.list ]; then
  sudo sh -c "echo \"deb http://packages.ros.org/ros/ubuntu ${name_os_version} main\" > /etc/apt/sources.list.d/ros-latest.list"
fi

echo "[Download the ROS keys]"
roskey=`apt-key list | grep "Open Robotics"`
if [ -z "$roskey" ]; then
  curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
fi

echo "[Setup ROS keys]"
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
#https://unix.stackexchange.com/questions/109625/shell-scripting-z-and-n-options-with-if
#http://wiki.ros.org/melodic/Installation/Ubuntu


echo "[Update the package lists]"
sudo apt update -y

echo "[Install the ros-desktop-full]"
sudo apt install -y ros-$name_ros_version-desktop-full

echo "[Environment setup and getting rosinstall]"
echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
source ~/.bashrc
#echo "source /opt/ros/melodic/setup.zsh" >> ~/.zshrc
#source ~/.zshrc
sudo apt install -y python-rosinstall python-rosinstall-generator python-wstool build-essential git

echo "[Install rosdep]"
sudo apt install python-rosdep rosdepc

echo "[Initialize rosdep and Update]"
#https://github.com/fishros/install
sudo sh -c "rosdepc init"
rosdepc update

echo "[Make the catkin workspace and test the catkin_make]"
mkdir -p $HOME/$name_catkin_workspace/src
cd $HOME/$name_catkin_workspace/src
catkin_init_workspace
cd $HOME/$name_catkin_workspace
catkin_make

echo "[Set the ROS evironment]"
#https://askubuntu.com/questions/831847/what-is-the-sh-c-command
#sh -c "echo \"alias eb='nano ~/.bashrc'\" >> ~/.bashrc"
#sh -c "echo \"alias sb='source ~/.bashrc'\" >> ~/.bashrc"
#sh -c "echo \"alias gs='git status'\" >> ~/.bashrc"
#sh -c "echo \"alias gp='git pull'\" >> ~/.bashrc"
#sh -c "echo \"alias cw='cd ~/$name_catkin_workspace'\" >> ~/.bashrc"
#sh -c "echo \"alias cs='cd ~/$name_catkin_workspace/src'\" >> ~/.bashrc"
#sh -c "echo \"alias cm='cd ~/$name_catkin_workspace && catkin_make'\" >> ~/.bashrc"

sh -c "echo \"source /opt/ros/$name_ros_version/setup.bash\" >> ~/.bashrc"
sh -c "echo \"source ~/$name_catkin_workspace/devel/setup.bash\" >> ~/.bashrc"

#https://blog.csdn.net/qq_43406338/article/details/109637978
sh -c "echo \"export ROS_MASTER_URI=http://localhost:11311\" >> ~/.bashrc"
sh -c "echo \"export ROS_HOSTNAME=localhost\" >> ~/.bashrc"

source $HOME/.bashrc

echo "[DONE]"
exit 0