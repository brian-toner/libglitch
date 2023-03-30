#-------------------------------------------------
#
# Project created by QtCreator 2018-07-04T22:13:29
#
#-------------------------------------------------

QT       -= core gui

TARGET = libglitch
TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ArgParser.cpp \
    AString.cpp \
    AStringFunctions.cpp \
    Boundary.cpp \
    Cluster.cpp \
    DirectoryFunctions.cpp \
    fft.cpp \
    FileLoad.cpp \
    FileStrings.cpp \
    GeneBuilder.cpp \
    ImgClusters.cpp \
    LinearModel.cpp \
    MatTFunctions.cpp \
    miscfunctions.cpp \
    NDArray.cpp \
    NDPoint.cpp \
    Parser.cpp \
    random.cpp \
    SRAL.cpp \
    StatsF.cpp \
    StringAddress.cpp \
    stringconversion.cpp \
    TopNeighbor.cpp

HEADERS += \
        libglitch.h \
    ArgParser.h \
    AString.h \
    AStringFunctions.h \
    Boundary.h \
    Cluster.h \
    defines.h \
    DirectoryFunctions.h \
    fft.h \
    FileLoad.h \
    FileStrings.h \
    GeneBuilder.h \
    GridFunctions.h \
    ImgClusters.h \
    inprogress.h \
    libglitch.h \
    LinearModel.h \
    MatT.h \
    MatTFunctions.h \
    miscfunctions.h \
    Moments.h \
    NDArray.h \
    NDPoint.h \
    PairT.h \
    Parser.h \
    PointT.h \
    PolygonFunctions.h \
    PolyT.h \
    random.h \
    RectListT.h \
    RectT.h \
    RuntimeErrorReport.h \
    ScalarT.h \
    ShapeProperties.h \
    SRAL.h \
    StatsF.h \
    StringAddress.h \
    stringconversion.h \
    TemplateMath.h \
    TopNeighbor.h \
    VectorFunctions.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
