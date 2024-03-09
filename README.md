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
2，实现声音播放需要加multimedia模块引用，此模块的安装方法：    
sudo apt-get update    
sudo apt-get install qtmultimedia5-dev    
3，20240206 编译过程管理已由qmake改为cmake，同时打包方式改为cmake的cpack  
由于此更改，qt也由5升级到6，打包时可连程序依赖库（qt6相关库）一起打包发布了  
命令备忘：  
cmake -DCMAKE_INSTALL_PREFIX=tmp .. #本机测试安装到此目录，若不做本机测试，直接cpack 则不需此参数  
cmake --build .  
cmake --install .  
cpack -G DEB  
4，开发机环境升级到QT6后程序被自动配置使用wayland，但窗口无边框（安装到目标机没问题），没有搜索到好的解决方案。在开发机上手工进行如下设置可临时解决（每次新开命令窗口均需运行）：  
export QT_QPA_PLATFORM=xcb  
5，使用cpack打包后的安装包没有自动把用户加入dialout组，因此暂需要手动加入  
sudo usermod -aG currUsername aaaabbbbcccc  
加入后需要重启系统才能生效  
