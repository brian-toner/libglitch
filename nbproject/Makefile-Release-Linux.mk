#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release-Linux
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/AString.o \
	${OBJECTDIR}/AStringFunctions.o \
	${OBJECTDIR}/ArgParser.o \
	${OBJECTDIR}/Boundary.o \
	${OBJECTDIR}/Cluster.o \
	${OBJECTDIR}/DirectoryFunctions.o \
	${OBJECTDIR}/FileLoad.o \
	${OBJECTDIR}/FileStrings.o \
	${OBJECTDIR}/Gene.o \
	${OBJECTDIR}/GeneBuilder.o \
	${OBJECTDIR}/GeneList.o \
	${OBJECTDIR}/ImgClusters.o \
	${OBJECTDIR}/LinearModel.o \
	${OBJECTDIR}/MatTFunctions.o \
	${OBJECTDIR}/NDArray.o \
	${OBJECTDIR}/NDPoint.o \
	${OBJECTDIR}/Parser.o \
	${OBJECTDIR}/SRAL.o \
	${OBJECTDIR}/StatsF.o \
	${OBJECTDIR}/StringAddress.o \
	${OBJECTDIR}/TopNeighbor.o \
	${OBJECTDIR}/fft.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/miscfunctions.o \
	${OBJECTDIR}/random.o \
	${OBJECTDIR}/stringconversion.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/validator.o

# C Compiler Flags
CFLAGS=-pedantic -Wextra

# CC Compiler Flags
CCFLAGS=-pedantic -Wextra
CXXFLAGS=-pedantic -Wextra

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libglitch.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libglitch.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libglitch.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/AString.o: AString.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AString.o AString.cpp

${OBJECTDIR}/AStringFunctions.o: AStringFunctions.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AStringFunctions.o AStringFunctions.cpp

${OBJECTDIR}/ArgParser.o: ArgParser.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ArgParser.o ArgParser.cpp

${OBJECTDIR}/Boundary.o: Boundary.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Boundary.o Boundary.cpp

${OBJECTDIR}/Cluster.o: Cluster.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cluster.o Cluster.cpp

${OBJECTDIR}/DirectoryFunctions.o: DirectoryFunctions.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DirectoryFunctions.o DirectoryFunctions.cpp

${OBJECTDIR}/FileLoad.o: FileLoad.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FileLoad.o FileLoad.cpp

${OBJECTDIR}/FileStrings.o: FileStrings.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FileStrings.o FileStrings.cpp

${OBJECTDIR}/Gene.o: Gene.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Gene.o Gene.cpp

${OBJECTDIR}/GeneBuilder.o: GeneBuilder.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GeneBuilder.o GeneBuilder.cpp

${OBJECTDIR}/GeneList.o: GeneList.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GeneList.o GeneList.cpp

${OBJECTDIR}/ImgClusters.o: ImgClusters.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ImgClusters.o ImgClusters.cpp

${OBJECTDIR}/LinearModel.o: LinearModel.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LinearModel.o LinearModel.cpp

${OBJECTDIR}/MatTFunctions.o: MatTFunctions.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MatTFunctions.o MatTFunctions.cpp

${OBJECTDIR}/NDArray.o: NDArray.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/NDArray.o NDArray.cpp

${OBJECTDIR}/NDPoint.o: NDPoint.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/NDPoint.o NDPoint.cpp

${OBJECTDIR}/Parser.o: Parser.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Parser.o Parser.cpp

${OBJECTDIR}/SRAL.o: SRAL.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SRAL.o SRAL.cpp

${OBJECTDIR}/StatsF.o: StatsF.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/StatsF.o StatsF.cpp

${OBJECTDIR}/StringAddress.o: StringAddress.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/StringAddress.o StringAddress.cpp

${OBJECTDIR}/TopNeighbor.o: TopNeighbor.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TopNeighbor.o TopNeighbor.cpp

${OBJECTDIR}/fft.o: fft.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fft.o fft.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/miscfunctions.o: miscfunctions.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/miscfunctions.o miscfunctions.cpp

${OBJECTDIR}/random.o: random.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/random.o random.cpp

${OBJECTDIR}/stringconversion.o: stringconversion.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/stringconversion.o stringconversion.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/validator.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   


${TESTDIR}/tests/validator.o: tests/validator.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/validator.o tests/validator.cpp


${OBJECTDIR}/AString_nomain.o: ${OBJECTDIR}/AString.o AString.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/AString.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AString_nomain.o AString.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/AString.o ${OBJECTDIR}/AString_nomain.o;\
	fi

${OBJECTDIR}/AStringFunctions_nomain.o: ${OBJECTDIR}/AStringFunctions.o AStringFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/AStringFunctions.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AStringFunctions_nomain.o AStringFunctions.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/AStringFunctions.o ${OBJECTDIR}/AStringFunctions_nomain.o;\
	fi

${OBJECTDIR}/ArgParser_nomain.o: ${OBJECTDIR}/ArgParser.o ArgParser.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ArgParser.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ArgParser_nomain.o ArgParser.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ArgParser.o ${OBJECTDIR}/ArgParser_nomain.o;\
	fi

${OBJECTDIR}/Boundary_nomain.o: ${OBJECTDIR}/Boundary.o Boundary.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Boundary.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Boundary_nomain.o Boundary.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Boundary.o ${OBJECTDIR}/Boundary_nomain.o;\
	fi

${OBJECTDIR}/Cluster_nomain.o: ${OBJECTDIR}/Cluster.o Cluster.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Cluster.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cluster_nomain.o Cluster.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Cluster.o ${OBJECTDIR}/Cluster_nomain.o;\
	fi

${OBJECTDIR}/DirectoryFunctions_nomain.o: ${OBJECTDIR}/DirectoryFunctions.o DirectoryFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/DirectoryFunctions.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DirectoryFunctions_nomain.o DirectoryFunctions.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/DirectoryFunctions.o ${OBJECTDIR}/DirectoryFunctions_nomain.o;\
	fi

${OBJECTDIR}/FileLoad_nomain.o: ${OBJECTDIR}/FileLoad.o FileLoad.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/FileLoad.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FileLoad_nomain.o FileLoad.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/FileLoad.o ${OBJECTDIR}/FileLoad_nomain.o;\
	fi

${OBJECTDIR}/FileStrings_nomain.o: ${OBJECTDIR}/FileStrings.o FileStrings.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/FileStrings.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FileStrings_nomain.o FileStrings.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/FileStrings.o ${OBJECTDIR}/FileStrings_nomain.o;\
	fi

${OBJECTDIR}/Gene_nomain.o: ${OBJECTDIR}/Gene.o Gene.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Gene.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Gene_nomain.o Gene.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Gene.o ${OBJECTDIR}/Gene_nomain.o;\
	fi

${OBJECTDIR}/GeneBuilder_nomain.o: ${OBJECTDIR}/GeneBuilder.o GeneBuilder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/GeneBuilder.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GeneBuilder_nomain.o GeneBuilder.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/GeneBuilder.o ${OBJECTDIR}/GeneBuilder_nomain.o;\
	fi

${OBJECTDIR}/GeneList_nomain.o: ${OBJECTDIR}/GeneList.o GeneList.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/GeneList.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GeneList_nomain.o GeneList.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/GeneList.o ${OBJECTDIR}/GeneList_nomain.o;\
	fi

${OBJECTDIR}/ImgClusters_nomain.o: ${OBJECTDIR}/ImgClusters.o ImgClusters.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ImgClusters.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ImgClusters_nomain.o ImgClusters.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ImgClusters.o ${OBJECTDIR}/ImgClusters_nomain.o;\
	fi

${OBJECTDIR}/LinearModel_nomain.o: ${OBJECTDIR}/LinearModel.o LinearModel.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/LinearModel.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LinearModel_nomain.o LinearModel.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/LinearModel.o ${OBJECTDIR}/LinearModel_nomain.o;\
	fi

${OBJECTDIR}/MatTFunctions_nomain.o: ${OBJECTDIR}/MatTFunctions.o MatTFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/MatTFunctions.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MatTFunctions_nomain.o MatTFunctions.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/MatTFunctions.o ${OBJECTDIR}/MatTFunctions_nomain.o;\
	fi

${OBJECTDIR}/NDArray_nomain.o: ${OBJECTDIR}/NDArray.o NDArray.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/NDArray.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/NDArray_nomain.o NDArray.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/NDArray.o ${OBJECTDIR}/NDArray_nomain.o;\
	fi

${OBJECTDIR}/NDPoint_nomain.o: ${OBJECTDIR}/NDPoint.o NDPoint.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/NDPoint.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/NDPoint_nomain.o NDPoint.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/NDPoint.o ${OBJECTDIR}/NDPoint_nomain.o;\
	fi

${OBJECTDIR}/Parser_nomain.o: ${OBJECTDIR}/Parser.o Parser.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Parser.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Parser_nomain.o Parser.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Parser.o ${OBJECTDIR}/Parser_nomain.o;\
	fi

${OBJECTDIR}/SRAL_nomain.o: ${OBJECTDIR}/SRAL.o SRAL.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/SRAL.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SRAL_nomain.o SRAL.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/SRAL.o ${OBJECTDIR}/SRAL_nomain.o;\
	fi

${OBJECTDIR}/StatsF_nomain.o: ${OBJECTDIR}/StatsF.o StatsF.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/StatsF.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/StatsF_nomain.o StatsF.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/StatsF.o ${OBJECTDIR}/StatsF_nomain.o;\
	fi

${OBJECTDIR}/StringAddress_nomain.o: ${OBJECTDIR}/StringAddress.o StringAddress.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/StringAddress.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/StringAddress_nomain.o StringAddress.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/StringAddress.o ${OBJECTDIR}/StringAddress_nomain.o;\
	fi

${OBJECTDIR}/TopNeighbor_nomain.o: ${OBJECTDIR}/TopNeighbor.o TopNeighbor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/TopNeighbor.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TopNeighbor_nomain.o TopNeighbor.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/TopNeighbor.o ${OBJECTDIR}/TopNeighbor_nomain.o;\
	fi

${OBJECTDIR}/fft_nomain.o: ${OBJECTDIR}/fft.o fft.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/fft.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fft_nomain.o fft.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/fft.o ${OBJECTDIR}/fft_nomain.o;\
	fi

${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_nomain.o main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

${OBJECTDIR}/miscfunctions_nomain.o: ${OBJECTDIR}/miscfunctions.o miscfunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/miscfunctions.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/miscfunctions_nomain.o miscfunctions.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/miscfunctions.o ${OBJECTDIR}/miscfunctions_nomain.o;\
	fi

${OBJECTDIR}/random_nomain.o: ${OBJECTDIR}/random.o random.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/random.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/random_nomain.o random.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/random.o ${OBJECTDIR}/random_nomain.o;\
	fi

${OBJECTDIR}/stringconversion_nomain.o: ${OBJECTDIR}/stringconversion.o stringconversion.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/stringconversion.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/stringconversion_nomain.o stringconversion.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/stringconversion.o ${OBJECTDIR}/stringconversion_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
