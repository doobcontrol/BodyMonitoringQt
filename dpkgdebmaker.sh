#!/bin/sh

# Author : dooacontrol

echo "dpkg deb make start:"

mkdir -p BodyMonitoringQt-dpkg/usr/local/bin
cp ./BodyMonitoringQt BodyMonitoringQt-dpkg/usr/local/bin
cp ./BodyMonitoringQt.png BodyMonitoringQt-dpkg/usr/local/bin

echo "work fold created and files copyed!"

mkdir -p BodyMonitoringQt-dpkg/usr/share/applications
cp ./BodyMonitoringQt.desktop BodyMonitoringQt-dpkg/usr/share/applications

echo "desktop file copyed!"

mkdir -p BodyMonitoringQt-dpkg/DEBIAN

echo "Package: BodyMonitoringQt \nVersion: 0.1 \nMaintainer: dooacontrol \nArchitecture: all \nDescription: BodyMonitoringQt" >> BodyMonitoringQt-dpkg/DEBIAN/control

echo "control file created!"
usertext='$SUDO_USER'
echo "tDeskTopPath=/home/$usertext/桌面 \ncp /usr/share/applications/BodyMonitoringQt.desktop \$tDeskTopPath/ \nchmod a+x \$tDeskTopPath/BodyMonitoringQt.desktop
" >> BodyMonitoringQt-dpkg/DEBIAN/postinst
chmod 0755 BodyMonitoringQt-dpkg/DEBIAN/postinst

echo "postinst file created!"

dpkg-deb -b BodyMonitoringQt-dpkg

rm -r BodyMonitoringQt-dpkg
echo "dpkg file created!"


