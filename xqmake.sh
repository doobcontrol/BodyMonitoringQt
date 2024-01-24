#!/bin/sh

# Author : dooacontrol

echo "reQmake project:"
qmake -project
echo "reQmake project done "

echo "add the QT module:
QT += widgets 
QT += serialport 
QT += charts
QT += sql "
echo "
QT += widgets 
QT += serialport 
QT += charts
QT += sql" >> BodyMonitoringQt.pro
