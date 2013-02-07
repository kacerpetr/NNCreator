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
    NeuralNetwork/Neuron.cpp \
    Test/NeuronTest.cpp \
    Util/function.cpp \
    Project/Project.cpp \
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
    Application/OutputGraphWidget.cpp \
    Application/DatasetTestWidget.cpp \
    Project/BaseModel.cpp \
    Project/DatasetEditModel.cpp \
    Project/TopologyEditModel.cpp \
    Project/DatasetTestModel.cpp \
    Project/GraphTestModel.cpp \
    Application/DatasetEditWidget.cpp \
    Test/DatasetTest.cpp \
    NeuralNetwork/BpAlgSt.cpp \
    Test/BpAlgStTest.cpp \
    NeuralNetwork/LrnEngine.cpp \
    Test/LrnEngineTest.cpp \
    NeuralNetwork/MlnNetSt.cpp \
    Test/MlnNetStTest.cpp \
    NeuralNetwork/Dataset.cpp

HEADERS  +=\
            Util/Exception.h\
            Application/MainWindow.h \
    NeuralNetwork/Neuron.h \
    Util/Array.h \
    Test/NeuronTest.h \
    Util/function.h \
    Project/Project.h \
    Dialog/AboutDialog.h \
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
    Application/OutputGraphWidget.h \
    Application/DatasetTestWidget.h \
    Project/BaseModel.h \
    Project/DatasetEditModel.h \
    Project/TopologyEditModel.h \
    Project/DatasetTestModel.h \
    Project/GraphTestModel.h \
    Application/DatasetEditWidget.h \
    Test/DatasetTest.h \
    NeuralNetwork/BpAlgSt.h \
    NeuralNetwork/AbstractLrnAlg.h \
    Test/BpAlgStTest.h \
    NeuralNetwork/LrnEngine.h \
    Test/LrnEngineTest.h \
    NeuralNetwork/AbstractMlnNet.h \
    NeuralNetwork/MlnNetSt.h \
    Test/MlnNetStTest.h \
    NeuralNetwork/Dataset.h

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
    ApplicationUi/OutputGraphWidget.ui \
    ApplicationUi/DatasetTestWidget.ui \
    ApplicationUi/DatasetEditWidget.ui

RESOURCES = styles.qrc
