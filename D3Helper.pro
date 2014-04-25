#-------------------------------------------------
#
# Project created by QtCreator 2014-04-24T14:25:41
#
#-------------------------------------------------

QT       += core gui
CONFIG += C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = D3Helper
TEMPLATE = app

include(controller/controller.pri)
include(model/model.pri)
include(view/view.pri)

SOURCES += main.cpp
