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
    NeuralNetwork/Neuron.cpp \
    Test/NeuronTest.cpp \
    Util/function.cpp \
    Test/BasicNetworkTest.cpp \
    NeuralNetwork/TrainingPattern.cpp

HEADERS  +=\
            Util/Exception.h\
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
    NeuralNetwork/BasicNetwork.h \
    NeuralNetwork/Neuron.h \
    Util/Array.h \
    Test/NeuronTest.h \
    Util/function.h \
    Test/BasicNetworkTest.h \
    NeuralNetwork/TrainingPattern.h

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
