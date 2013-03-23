#-------------------------------------------------
#
# Project created by QtCreator 2012-05-28T01:28:17
#
#-------------------------------------------------

QT       += core gui widgets webkit opengl
CONFIG   += qtestlib
LIBS += -L/usr/local/lib -lGLU

TARGET    = main
TEMPLATE  = app

SOURCES +=\
    main.cpp\
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
    GuiPart/LayerEditWidget.cpp \
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
    Test/MlnNetStTest.cpp \
    NeuralNetwork/Dataset.cpp \
    Parser/ProjectParser.cpp \
    Parser/DatasetMdlParser.cpp \
    Parser/TopologyMdlParser.cpp \
    Parser/LrnConfMdlParser.cpp \
    Parser/DatasetTestMdlParser.cpp \
    Parser/GraphTestMdlParser.cpp \
    GuiPart/NetParamWidget.cpp \
    GuiPart/LabelButton.cpp \
    Util/Settings.cpp \
    GuiPart/Plot1D.cpp \
    GuiPart/Plot2D.cpp \
    GuiPart/Plot3D.cpp \
    Project/DatasetViewModel.cpp \
    GuiPart/OpenedListItem.cpp \
    NeuralNetwork/MlnNetSt.cpp \
    GuiPart/PlotCls.cpp \
    Dialog/SettingsDialog.cpp

HEADERS +=\
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
    GuiPart/LayerEditWidget.h \
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
    NeuralNetwork/Dataset.h \
    Parser/ProjectParser.h \
    Parser/DatasetMdlParser.h \
    Parser/TopologyMdlParser.h \
    Parser/LrnConfMdlParser.h \
    Parser/DatasetTestMdlParser.h \
    Parser/GraphTestMdlParser.h \
    GuiPart/NetParamWidget.h \
    GuiPart/LabelButton.h \
    Util/Settings.h \
    GuiPart/Plot1D.h \
    GuiPart/Plot2D.h \
    GuiPart/Plot3D.h \
    Util/globaldef.h \
    Project/DatasetViewModel.h \
    GuiPart/OpenedListItem.h \
    GuiPart/PlotCls.h \
    Dialog/SettingsDialog.h

FORMS +=\
    ApplicationUi/MainWindow.ui\
    DialogUi/AboutDialog.ui \
    DialogUi/NewProjectDialog.ui \
    ApplicationUi/WelcomeWidget.ui \
    ApplicationUi/TopologyWidget.ui \
    ApplicationUi/LearningWidget.ui \
    ApplicationUi/HelpWidget.ui \
    GuiPartUi/LayerEditWidget.ui \
    ApplicationUi/NoModelWidget.ui \
    DialogUi/TextViewBoxDialog.ui \
    ApplicationUi/OutputGraphWidget.ui \
    ApplicationUi/DatasetTestWidget.ui \
    ApplicationUi/DatasetEditWidget.ui \
    GuiPartUi/NetParamWidget.ui \
    DialogUi/SettingsDialog.ui

RESOURCES = styles.qrc
