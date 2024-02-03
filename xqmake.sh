#!/bin/sh

# Author : dooacontrol

rm -f tmp/qrc_resource.cpp

echo "reQmake project:"
qmake -project
echo "reQmake project done "

echo "add: DESTDIR = bin"
echo "DESTDIR = bin" >> BodyMonitoringQt.pro

echo "add: MOC_DIR = tmp"
echo "MOC_DIR = tmp" >> BodyMonitoringQt.pro

echo "add: OBJECTS_DIR  = tmp"
echo "OBJECTS_DIR  = tmp" >> BodyMonitoringQt.pro

echo "add: RCC_DIR = tmp"
echo "RCC_DIR = tmp" >> BodyMonitoringQt.pro

echo "add the QT module:
QT += widgets 
QT += serialport 
QT += charts
QT += sql
QT += multimedia "
echo "
QT += widgets 
QT += serialport 
QT += charts
QT += sql
QT += multimedia" >> BodyMonitoringQt.pro

qmake
