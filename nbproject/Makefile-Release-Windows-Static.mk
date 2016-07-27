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
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Release-Windows-Static
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
	${OBJECTDIR}/Boundary.o \
	${OBJECTDIR}/DirectoryFunctions.o \
	${OBJECTDIR}/FileLoad.o \
	${OBJECTDIR}/FileStrings.o \
	${OBJECTDIR}/LinearModel.o \
	${OBJECTDIR}/SRAL.o \
	${OBJECTDIR}/StatsF.o \
	${OBJECTDIR}/StringAddress.o \
	${OBJECTDIR}/TopNeighbor.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/miscfunctions.o \
	${OBJECTDIR}/random.o \
	${OBJECTDIR}/stringconversion.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libglitch.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libglitch.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libglitch.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libglitch.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libglitch.a

${OBJECTDIR}/AString.o: AString.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AString.o AString.cpp

${OBJECTDIR}/AStringFunctions.o: AStringFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AStringFunctions.o AStringFunctions.cpp

${OBJECTDIR}/Boundary.o: Boundary.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Boundary.o Boundary.cpp

${OBJECTDIR}/DirectoryFunctions.o: DirectoryFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DirectoryFunctions.o DirectoryFunctions.cpp

${OBJECTDIR}/FileLoad.o: FileLoad.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FileLoad.o FileLoad.cpp

${OBJECTDIR}/FileStrings.o: FileStrings.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FileStrings.o FileStrings.cpp

${OBJECTDIR}/LinearModel.o: LinearModel.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LinearModel.o LinearModel.cpp

${OBJECTDIR}/SRAL.o: SRAL.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SRAL.o SRAL.cpp

${OBJECTDIR}/StatsF.o: StatsF.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/StatsF.o StatsF.cpp

${OBJECTDIR}/StringAddress.o: StringAddress.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/StringAddress.o StringAddress.cpp

${OBJECTDIR}/TopNeighbor.o: TopNeighbor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TopNeighbor.o TopNeighbor.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/miscfunctions.o: miscfunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/miscfunctions.o miscfunctions.cpp

${OBJECTDIR}/random.o: random.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/random.o random.cpp

${OBJECTDIR}/stringconversion.o: stringconversion.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/stringconversion.o stringconversion.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libglitch.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
