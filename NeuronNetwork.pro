#-------------------------------------------------
#
# Project created by QtCreator 2012-05-28T01:28:17
#
#-------------------------------------------------

QT       += core gui widgets
CONFIG   += qtestlib

TARGET    = main
TEMPLATE  = app

SOURCES  += main.cpp\
            NeuronNetwork/Neuron.cpp\
            NeuronNetwork/Layer.cpp\
            NeuronNetwork/Test.cpp\
            NeuronNetwork/Network.cpp \
            Application/MainWindow.cpp \
            Application/Welcome.cpp \
    Application/Edit.cpp \
    Application/Topology.cpp \
    Application/Help.cpp

HEADERS  += NeuronNetwork/Neuron.h\
            NeuronNetwork/Layer.h\
            NeuronNetwork/Test.h\
            NeuronNetwork/Network.h\
            NeuronNetwork/Exception.h\
            Application/MainWindow.h \
            Application/Welcome.h \
    Application/Edit.h \
    Application/Topology.h \
    Application/Help.h

FORMS    += Forms/MainWindow.ui\
            Forms/Welcome.ui \
    Forms/Edit.ui \
    Forms/Topology.ui \
    Forms/Help.ui

RESOURCES = styles.qrc
