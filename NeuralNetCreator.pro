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
    Dialog/TextViewBox.cpp \
    NeuralNetwork/BasicNetwork.cpp \
    NeuralNetwork/Neuron.cpp \
    Test/NeuronTest.cpp \
    Util/function.cpp \
    Test/BasicNetworkTest.cpp \
    NeuralNetwork/TrainingPattern.cpp \
    NeuralNetwork/BackPropagation.cpp \
    Test/BackPropagationTest.cpp \
    Project/Project.cpp \
    Test/ProjectItemModelTest.cpp \
    Dialog/AboutDialog.cpp \
    Project/TrainingPatternModel.cpp \
    NeuralNetwork/AbstractLearningMachine.cpp \
    NeuralNetwork/AbstractNeuralNetwork.cpp \
    NeuralNetwork/AbstractTrainingPattern.cpp \
    Project/Workspace.cpp \
    Dialog/NewProjectDialog.cpp \
    Project/LearningConfigModel.cpp \
    Project/TestingScenarioModel.cpp \
    Project/NeuralNetworkModel.cpp

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
    Dialog/TextViewBox.h \
    NeuralNetwork/BasicNetwork.h \
    NeuralNetwork/Neuron.h \
    Util/Array.h \
    Test/NeuronTest.h \
    Util/function.h \
    Test/BasicNetworkTest.h \
    NeuralNetwork/TrainingPattern.h \
    NeuralNetwork/BackPropagation.h \
    Test/BackPropagationTest.h \
    Project/Project.h \
    Test/ProjectItemModelTest.h \
    Dialog/AboutDialog.h \
    Project/TrainingPatternModel.h \
    NeuralNetwork/AbstractLearningMachine.h \
    NeuralNetwork/AbstractNeuralNetwork.h \
    NeuralNetwork/AbstractTrainingPattern.h \
    Project/Workspace.h \
    Dialog/NewProjectDialog.h \
    Project/NeuralNetworkModel.h \
    Project/LearningConfigModel.h \
    Project/TestingScenarioModel.h

FORMS    += ApplicationUi/MainWindow.ui\
            ApplicationUi/Welcome.ui \
    ApplicationUi/Edit.ui \
    ApplicationUi/Topology.ui \
    ApplicationUi/Help.ui \
    ApplicationUi/TrainingPatterns.ui \
    ApplicationUi/Learning.ui \
    ApplicationUi/Testing.ui \
    DialogUi/TextViewBox.ui \
    DialogUi/AboutDialog.ui \
    DialogUi/NewProjectDialog.ui

RESOURCES = styles.qrc
