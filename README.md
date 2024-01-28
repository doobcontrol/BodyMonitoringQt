生命体征监测程序Qt版  
  
从生物雷达读取数据实时展示人的呼吸，心跳等基本生命体征  
  
Linux版  
编译：
如果有新增文件：  
qmake -project  
手动编辑：BodyMonitoringQt.pro 文件，加 QT += widgets serialport 行
make

提交
git status -s 看是否有需要提交的内容  
git add .  
git commit -m"提交"  
git push origin master  
  
github登陆配置：  
ssh-keygen 生成ssh key pair  
拷贝id_rsa.pub内容在github内生成SSH key  
git remote add origin git@github.com:doobcontrol/BodyMonitoringQt.git

备忘：  
1，在Mint上安装后运行出错：  
./BodyMonitoringQt: error while loading shared libraries: libQt5Charts.so.5: cannot open shared object file: No such file or directory  
手动安装libQt5Charts：  
sudo apt install libqt5charts5  （在开发机上应安装  sudo apt install libqt5charts5-dev）  
应在安装程序中实现检查此包是否存在，不存在则安装的功能？？  
