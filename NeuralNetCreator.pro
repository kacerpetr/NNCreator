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
    NeuralNetwork/BasicNetwork.cpp \
    NeuralNetwork/Neuron.cpp \
    Test/NeuronTest.cpp \
    Util/function.cpp \
    Test/BasicNetworkTest.cpp \
    NeuralNetwork/BackPropagation.cpp \
    Test/BackPropagationTest.cpp \
    Project/Project.cpp \
    Test/ProjectItemModelTest.cpp \
    Dialog/AboutDialog.cpp \
    Project/Workspace.cpp \
    Dialog/NewProjectDialog.cpp \
    Project/LearningConfigModel.cpp \
    Application/WelcomeWidget.cpp \
    Application/TopologyWidget.cpp \
    Application/LearningWidget.cpp \
    Application/HelpWidget.cpp \
    Application/LayerEditWidget.cpp \
    Application/NoModelWidget.cpp \
    Dialog/TextViewBoxDialog.cpp \
    Dialog/NewTestScnDialog.cpp \
    Application/OutputGraphWidget.cpp \
    Application/DatasetTestWidget.cpp \
    Project/BaseModel.cpp \
    Project/DatasetEditModel.cpp \
    Project/TopologyEditModel.cpp \
    Project/DatasetTestModel.cpp \
    Project/GraphTestModel.cpp \
    Application/DatasetEditWidget.cpp \
    NeuralNetwork/Dataset.cpp \
    Test/DatasetTest.cpp

HEADERS  +=\
            Util/Exception.h\
            Application/MainWindow.h \
    NeuralNetwork/BasicNetwork.h \
    NeuralNetwork/Neuron.h \
    Util/Array.h \
    Test/NeuronTest.h \
    Util/function.h \
    Test/BasicNetworkTest.h \
    NeuralNetwork/BackPropagation.h \
    Test/BackPropagationTest.h \
    Project/Project.h \
    Test/ProjectItemModelTest.h \
    Dialog/AboutDialog.h \
    NeuralNetwork/AbstractLearningMachine.h \
    NeuralNetwork/AbstractNeuralNetwork.h \
    Project/Workspace.h \
    Dialog/NewProjectDialog.h \
    Project/LearningConfigModel.h \
    Application/WelcomeWidget.h \
    Application/TopologyWidget.h \
    Application/LearningWidget.h \
    Application/HelpWidget.h \
    Application/LayerEditWidget.h \
    Application/NoModelWidget.h \
    Dialog/TextViewBoxDialog.h \
    Dialog/NewTestScnDialog.h \
    Application/OutputGraphWidget.h \
    Application/DatasetTestWidget.h \
    Project/BaseModel.h \
    Project/DatasetEditModel.h \
    Project/TopologyEditModel.h \
    Project/DatasetTestModel.h \
    Project/GraphTestModel.h \
    Application/DatasetEditWidget.h \
    NeuralNetwork/Dataset.h \
    NeuralNetwork/AbstractDataset.h \
    Test/DatasetTest.h

FORMS    += ApplicationUi/MainWindow.ui\
    DialogUi/AboutDialog.ui \
    DialogUi/NewProjectDialog.ui \
    ApplicationUi/WelcomeWidget.ui \
    ApplicationUi/TopologyWidget.ui \
    ApplicationUi/LearningWidget.ui \
    ApplicationUi/HelpWidget.ui \
    ApplicationUi/LayerEditWidget.ui \
    ApplicationUi/NoModelWidget.ui \
    DialogUi/TextViewBoxDialog.ui \
    DialogUi/NewTestScnDialog.ui \
    ApplicationUi/OutputGraphWidget.ui \
    ApplicationUi/DatasetTestWidget.ui \
    ApplicationUi/DatasetEditWidget.ui

RESOURCES = styles.qrc
