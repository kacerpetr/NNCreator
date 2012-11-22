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
    Project/NeuralNetworkModel.cpp \
    Application/TrainingPatternWidget.cpp \
    Application/WelcomeWidget.cpp \
    Application/TopologyWidget.cpp \
    Application/TestingWidget.cpp \
    Application/LearningWidget.cpp \
    Application/HelpWidget.cpp \
    Application/LayerEditWidget.cpp \
    Application/NoModelWidget.cpp

HEADERS  +=\
            Util/Exception.h\
            Application/MainWindow.h \
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
    Project/TestingScenarioModel.h \
    Application/TrainingPatternWidget.h \
    Application/WelcomeWidget.h \
    Application/TopologyWidget.h \
    Application/TestingWidget.h \
    Application/LearningWidget.h \
    Application/HelpWidget.h \
    Application/LayerEditWidget.h \
    Application/NoModelWidget.h

FORMS    += ApplicationUi/MainWindow.ui\
    DialogUi/TextViewBox.ui \
    DialogUi/AboutDialog.ui \
    DialogUi/NewProjectDialog.ui \
    ApplicationUi/TrainingPatternWidget.ui \
    ApplicationUi/WelcomeWidget.ui \
    ApplicationUi/TopologyWidget.ui \
    ApplicationUi/TestingWidget.ui \
    ApplicationUi/LearningWidget.ui \
    ApplicationUi/HelpWidget.ui \
    ApplicationUi/LayerEditWidget.ui \
    ApplicationUi/NoModelWidget.ui

RESOURCES = styles.qrc
