# This file is part of Neural network Creator, backpropagation
# simulator and multilayer neural network IDE.
# Copyright (C) 2013  Petr Kačer <kacerpetr@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.


QT       += core gui webkit opengl
CONFIG   += qtestlib
LIBS += -L/usr/local/lib -lGLU

TARGET    = NeuralNetCreator
TEMPLATE  = app

TRANSLATIONS = Translation/lang_cs.ts

SOURCES +=\
    Application/MainWindow.cpp \
    NeuralNetwork/Neuron.cpp \
    Test/NeuronTest.cpp \
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
    Dialog/SettingsDialog.cpp \
    Dialog/FileNameDialog.cpp \
    Util/Globaldef.cpp \
    NeuralNetCreator.cpp

HEADERS +=\
    Application/MainWindow.h \
    NeuralNetwork/Neuron.h \
    Util/Array.h \
    Test/NeuronTest.h \
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
    Project/DatasetViewModel.h \
    GuiPart/OpenedListItem.h \
    GuiPart/PlotCls.h \
    Dialog/SettingsDialog.h \
    Dialog/FileNameDialog.h \
    Util/Globaldef.h

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
    DialogUi/SettingsDialog.ui \
    DialogUi/FileNameDialog.ui

RESOURCES = styles.qrc
