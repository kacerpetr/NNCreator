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
            Application/MainWindow.cpp

HEADERS  += NeuronNetwork/Neuron.h\
            NeuronNetwork/Layer.h\
            NeuronNetwork/Test.h\
            NeuronNetwork/Network.h\
            NeuronNetwork/Exception.h\
            Application/MainWindow.h

FORMS    += Forms/MainWindow.ui\
