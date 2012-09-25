#-------------------------------------------------
#
# Project created by QtCreator 2012-05-28T01:28:17
#
#-------------------------------------------------

QT       += core gui widgets webkit
CONFIG   += qtestlib

TARGET    = main
TEMPLATE  = app

SOURCES  += main.cpp\
            NeuralNetwork/Neuron.cpp\
            NeuralNetwork/Layer.cpp\
            NeuralNetwork/Test.cpp\
            NeuralNetwork/Network.cpp \
            Application/MainWindow.cpp \
            Application/Welcome.cpp \
    Application/Edit.cpp \
    Application/Topology.cpp \
    Application/Help.cpp \
    Application/TrainingPatterns.cpp \
    Application/Learning.cpp \
    Application/Testing.cpp \
    Application/Graphs.cpp \
    Dialog/TextViewBox.cpp \
    NeuralNetwork/BasicNetwork.cpp \
    NeuralNetwork/INeuralNetwork.cpp

HEADERS  += NeuralNetwork/Neuron.h\
            NeuralNetwork/Layer.h\
            NeuralNetwork/Test.h\
            NeuralNetwork/Network.h\
            NeuralNetwork/Exception.h\
            Application/MainWindow.h \
            Application/Welcome.h \
    Application/Edit.h \
    Application/Topology.h \
    Application/Help.h \
    Application/TrainingPatterns.h \
    Application/Learning.h \
    Application/Testing.h \
    Application/Graphs.h \
    Dialog/TextViewBox.h \
    NeuralNetwork/INeuralNetwork.h \
    NeuralNetwork/BasicNetwork.h

FORMS    += ApplicationUi/MainWindow.ui\
            ApplicationUi/Welcome.ui \
    ApplicationUi/Edit.ui \
    ApplicationUi/Topology.ui \
    ApplicationUi/Help.ui \
    ApplicationUi/TrainingPatterns.ui \
    ApplicationUi/Learning.ui \
    ApplicationUi/Testing.ui \
    ApplicationUi/Graphs.ui \
    DialogUi/TextViewBox.ui

RESOURCES = styles.qrc
