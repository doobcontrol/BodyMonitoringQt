#!/bin/sh

# Author : dooacontrol

echo "dpkg deb make start:"

mkdir -p BodyMonitoringQt-dpkg/usr/local/bin
cp ../bin/BodyMonitoringQt BodyMonitoringQt-dpkg/usr/local/bin
mkdir -p BodyMonitoringQt-dpkg/usr/local/share/BodyMonitoring
cp ../BodyMonitoringQt.png BodyMonitoringQt-dpkg/usr/local/share/BodyMonitoring

echo "work fold created and application files copyed!"

mkdir -p BodyMonitoringQt-dpkg/usr/share/applications
cp ./BodyMonitoringQt.desktop BodyMonitoringQt-dpkg/usr/share/applications

echo "desktop file copyed!"

mkdir -p BodyMonitoringQt-dpkg/DEBIAN

cp ./control BodyMonitoringQt-dpkg/DEBIAN/control

echo "control file copyed!"

cp ./postinst BodyMonitoringQt-dpkg/DEBIAN/postinst
chmod 0755 BodyMonitoringQt-dpkg/DEBIAN/postinst

echo "postinst file copyed!"

dpkg-deb -b BodyMonitoringQt-dpkg

rm -r BodyMonitoringQt-dpkg
echo "dpkg file created!"


