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
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/testaFaceDetector.o \
	${OBJECTDIR}/FileProcessor.o \
	${OBJECTDIR}/BlobDetector.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/Eye.o \
	${OBJECTDIR}/testaModeloFace.o \
	${OBJECTDIR}/USTimer.o \
	${OBJECTDIR}/testaWebCam.o \
	${OBJECTDIR}/_ext/1508022067/ExperimentRunner.o \
	${OBJECTDIR}/Mouth.o \
	${OBJECTDIR}/FaceDetector.o \
	${OBJECTDIR}/EyeBlobDetector.o \
	${OBJECTDIR}/MouthDetector.o \
	${OBJECTDIR}/IrisFinder.o \
	${OBJECTDIR}/EyeDetector.o \
	${OBJECTDIR}/NoseDetector.o \
	${OBJECTDIR}/MouthFinder.o \
	${OBJECTDIR}/GenericDetector.o \
	${OBJECTDIR}/WebCam.o \
	${OBJECTDIR}/FeatureFinder.o \
	${OBJECTDIR}/VideoFile.o \
	${OBJECTDIR}/_ext/1508022067/testaOlhos.o \
	${OBJECTDIR}/_ext/1508022067/realTimeTracker.o \
	${OBJECTDIR}/Face.o \
	${OBJECTDIR}/_ext/1508022067/testeSolvePoly.o \
	${OBJECTDIR}/_ext/1508022067/EyeProcessor.o \
	${OBJECTDIR}/NoseTipFinder.o \
	${OBJECTDIR}/_ext/1508022067/PointRunningAverageStream.o \
	${OBJECTDIR}/testaToGray.o \
	${OBJECTDIR}/ImageUtils.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f3 \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f1

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-L/usr/local/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann -lcppunit
CXXFLAGS=-L/usr/local/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann -lcppunit

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/vlgt

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/vlgt: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/vlgt ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/testaFaceDetector.o: testaFaceDetector.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/testaFaceDetector.o testaFaceDetector.cpp

${OBJECTDIR}/FileProcessor.o: FileProcessor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/FileProcessor.o FileProcessor.cpp

${OBJECTDIR}/BlobDetector.o: BlobDetector.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/BlobDetector.o BlobDetector.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/Eye.o: Eye.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Eye.o Eye.cpp

${OBJECTDIR}/testaModeloFace.o: testaModeloFace.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/testaModeloFace.o testaModeloFace.cpp

${OBJECTDIR}/USTimer.o: USTimer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/USTimer.o USTimer.cpp

${OBJECTDIR}/testaWebCam.o: testaWebCam.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/testaWebCam.o testaWebCam.cpp

${OBJECTDIR}/_ext/1508022067/ExperimentRunner.o: /home/andrey/NetBeansProjects/vlgt/ExperimentRunner.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1508022067
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1508022067/ExperimentRunner.o /home/andrey/NetBeansProjects/vlgt/ExperimentRunner.cpp

${OBJECTDIR}/Mouth.o: Mouth.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Mouth.o Mouth.cpp

${OBJECTDIR}/FaceDetector.o: FaceDetector.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/FaceDetector.o FaceDetector.cpp

${OBJECTDIR}/EyeBlobDetector.o: EyeBlobDetector.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/EyeBlobDetector.o EyeBlobDetector.cpp

${OBJECTDIR}/MouthDetector.o: MouthDetector.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/MouthDetector.o MouthDetector.cpp

${OBJECTDIR}/IrisFinder.o: IrisFinder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/IrisFinder.o IrisFinder.cpp

${OBJECTDIR}/EyeDetector.o: EyeDetector.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/EyeDetector.o EyeDetector.cpp

${OBJECTDIR}/NoseDetector.o: NoseDetector.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/NoseDetector.o NoseDetector.cpp

${OBJECTDIR}/MouthFinder.o: MouthFinder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/MouthFinder.o MouthFinder.cpp

${OBJECTDIR}/GenericDetector.o: GenericDetector.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/GenericDetector.o GenericDetector.cpp

${OBJECTDIR}/WebCam.o: WebCam.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/WebCam.o WebCam.cpp

${OBJECTDIR}/FeatureFinder.o: FeatureFinder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/FeatureFinder.o FeatureFinder.cpp

${OBJECTDIR}/VideoFile.o: VideoFile.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/VideoFile.o VideoFile.cpp

${OBJECTDIR}/_ext/1508022067/testaOlhos.o: /home/andrey/NetBeansProjects/vlgt/testaOlhos.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1508022067
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1508022067/testaOlhos.o /home/andrey/NetBeansProjects/vlgt/testaOlhos.cpp

${OBJECTDIR}/_ext/1508022067/realTimeTracker.o: /home/andrey/NetBeansProjects/vlgt/realTimeTracker.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1508022067
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1508022067/realTimeTracker.o /home/andrey/NetBeansProjects/vlgt/realTimeTracker.cpp

${OBJECTDIR}/Face.o: Face.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Face.o Face.cpp

${OBJECTDIR}/_ext/1508022067/testeSolvePoly.o: /home/andrey/NetBeansProjects/vlgt/testeSolvePoly.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1508022067
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1508022067/testeSolvePoly.o /home/andrey/NetBeansProjects/vlgt/testeSolvePoly.cpp

${OBJECTDIR}/_ext/1508022067/EyeProcessor.o: /home/andrey/NetBeansProjects/vlgt/EyeProcessor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1508022067
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1508022067/EyeProcessor.o /home/andrey/NetBeansProjects/vlgt/EyeProcessor.cpp

${OBJECTDIR}/NoseTipFinder.o: NoseTipFinder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/NoseTipFinder.o NoseTipFinder.cpp

${OBJECTDIR}/_ext/1508022067/PointRunningAverageStream.o: /home/andrey/NetBeansProjects/vlgt/PointRunningAverageStream.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1508022067
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1508022067/PointRunningAverageStream.o /home/andrey/NetBeansProjects/vlgt/PointRunningAverageStream.cpp

${OBJECTDIR}/testaToGray.o: testaToGray.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/testaToGray.o testaToGray.cpp

${OBJECTDIR}/ImageUtils.o: ImageUtils.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ImageUtils.o ImageUtils.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f3: ${TESTDIR}/tests/GenericDetectorTest1.o ${TESTDIR}/tests/GenericDetectorTestRunner1.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS} -lcppunit 

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/ImageUtilstestclass1.o ${TESTDIR}/tests/ImageUtilstestrunner1.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} -lcppunit 

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/newtestclass.o ${TESTDIR}/tests/newtestrunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} -lcppunit 


${TESTDIR}/tests/GenericDetectorTest1.o: tests/GenericDetectorTest1.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/GenericDetectorTest1.o tests/GenericDetectorTest1.cpp


${TESTDIR}/tests/GenericDetectorTestRunner1.o: tests/GenericDetectorTestRunner1.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/GenericDetectorTestRunner1.o tests/GenericDetectorTestRunner1.cpp


${TESTDIR}/tests/ImageUtilstestclass1.o: tests/ImageUtilstestclass1.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/ImageUtilstestclass1.o tests/ImageUtilstestclass1.cpp


${TESTDIR}/tests/ImageUtilstestrunner1.o: tests/ImageUtilstestrunner1.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/ImageUtilstestrunner1.o tests/ImageUtilstestrunner1.cpp


${TESTDIR}/tests/newtestclass.o: tests/newtestclass.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/newtestclass.o tests/newtestclass.cpp


${TESTDIR}/tests/newtestrunner.o: tests/newtestrunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I. -I/usr/src/OpenCV-2.3.0/include/opencv2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/newtestrunner.o tests/newtestrunner.cpp


${OBJECTDIR}/testaFaceDetector_nomain.o: ${OBJECTDIR}/testaFaceDetector.o testaFaceDetector.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/testaFaceDetector.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/testaFaceDetector_nomain.o testaFaceDetector.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/testaFaceDetector.o ${OBJECTDIR}/testaFaceDetector_nomain.o;\
	fi

${OBJECTDIR}/FileProcessor_nomain.o: ${OBJECTDIR}/FileProcessor.o FileProcessor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/FileProcessor.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/FileProcessor_nomain.o FileProcessor.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/FileProcessor.o ${OBJECTDIR}/FileProcessor_nomain.o;\
	fi

${OBJECTDIR}/BlobDetector_nomain.o: ${OBJECTDIR}/BlobDetector.o BlobDetector.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/BlobDetector.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/BlobDetector_nomain.o BlobDetector.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/BlobDetector.o ${OBJECTDIR}/BlobDetector_nomain.o;\
	fi

${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/main_nomain.o main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

${OBJECTDIR}/Eye_nomain.o: ${OBJECTDIR}/Eye.o Eye.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Eye.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Eye_nomain.o Eye.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Eye.o ${OBJECTDIR}/Eye_nomain.o;\
	fi

${OBJECTDIR}/testaModeloFace_nomain.o: ${OBJECTDIR}/testaModeloFace.o testaModeloFace.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/testaModeloFace.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/testaModeloFace_nomain.o testaModeloFace.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/testaModeloFace.o ${OBJECTDIR}/testaModeloFace_nomain.o;\
	fi

${OBJECTDIR}/USTimer_nomain.o: ${OBJECTDIR}/USTimer.o USTimer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/USTimer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/USTimer_nomain.o USTimer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/USTimer.o ${OBJECTDIR}/USTimer_nomain.o;\
	fi

${OBJECTDIR}/testaWebCam_nomain.o: ${OBJECTDIR}/testaWebCam.o testaWebCam.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/testaWebCam.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/testaWebCam_nomain.o testaWebCam.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/testaWebCam.o ${OBJECTDIR}/testaWebCam_nomain.o;\
	fi

${OBJECTDIR}/_ext/1508022067/ExperimentRunner_nomain.o: ${OBJECTDIR}/_ext/1508022067/ExperimentRunner.o /home/andrey/NetBeansProjects/vlgt/ExperimentRunner.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1508022067
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1508022067/ExperimentRunner.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1508022067/ExperimentRunner_nomain.o /home/andrey/NetBeansProjects/vlgt/ExperimentRunner.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1508022067/ExperimentRunner.o ${OBJECTDIR}/_ext/1508022067/ExperimentRunner_nomain.o;\
	fi

${OBJECTDIR}/Mouth_nomain.o: ${OBJECTDIR}/Mouth.o Mouth.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Mouth.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Mouth_nomain.o Mouth.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Mouth.o ${OBJECTDIR}/Mouth_nomain.o;\
	fi

${OBJECTDIR}/FaceDetector_nomain.o: ${OBJECTDIR}/FaceDetector.o FaceDetector.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/FaceDetector.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/FaceDetector_nomain.o FaceDetector.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/FaceDetector.o ${OBJECTDIR}/FaceDetector_nomain.o;\
	fi

${OBJECTDIR}/EyeBlobDetector_nomain.o: ${OBJECTDIR}/EyeBlobDetector.o EyeBlobDetector.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/EyeBlobDetector.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/EyeBlobDetector_nomain.o EyeBlobDetector.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/EyeBlobDetector.o ${OBJECTDIR}/EyeBlobDetector_nomain.o;\
	fi

${OBJECTDIR}/MouthDetector_nomain.o: ${OBJECTDIR}/MouthDetector.o MouthDetector.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/MouthDetector.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/MouthDetector_nomain.o MouthDetector.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/MouthDetector.o ${OBJECTDIR}/MouthDetector_nomain.o;\
	fi

${OBJECTDIR}/IrisFinder_nomain.o: ${OBJECTDIR}/IrisFinder.o IrisFinder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/IrisFinder.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/IrisFinder_nomain.o IrisFinder.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/IrisFinder.o ${OBJECTDIR}/IrisFinder_nomain.o;\
	fi

${OBJECTDIR}/EyeDetector_nomain.o: ${OBJECTDIR}/EyeDetector.o EyeDetector.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/EyeDetector.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/EyeDetector_nomain.o EyeDetector.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/EyeDetector.o ${OBJECTDIR}/EyeDetector_nomain.o;\
	fi

${OBJECTDIR}/NoseDetector_nomain.o: ${OBJECTDIR}/NoseDetector.o NoseDetector.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/NoseDetector.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/NoseDetector_nomain.o NoseDetector.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/NoseDetector.o ${OBJECTDIR}/NoseDetector_nomain.o;\
	fi

${OBJECTDIR}/MouthFinder_nomain.o: ${OBJECTDIR}/MouthFinder.o MouthFinder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/MouthFinder.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/MouthFinder_nomain.o MouthFinder.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/MouthFinder.o ${OBJECTDIR}/MouthFinder_nomain.o;\
	fi

${OBJECTDIR}/GenericDetector_nomain.o: ${OBJECTDIR}/GenericDetector.o GenericDetector.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/GenericDetector.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/GenericDetector_nomain.o GenericDetector.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/GenericDetector.o ${OBJECTDIR}/GenericDetector_nomain.o;\
	fi

${OBJECTDIR}/WebCam_nomain.o: ${OBJECTDIR}/WebCam.o WebCam.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/WebCam.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/WebCam_nomain.o WebCam.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/WebCam.o ${OBJECTDIR}/WebCam_nomain.o;\
	fi

${OBJECTDIR}/FeatureFinder_nomain.o: ${OBJECTDIR}/FeatureFinder.o FeatureFinder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/FeatureFinder.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/FeatureFinder_nomain.o FeatureFinder.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/FeatureFinder.o ${OBJECTDIR}/FeatureFinder_nomain.o;\
	fi

${OBJECTDIR}/VideoFile_nomain.o: ${OBJECTDIR}/VideoFile.o VideoFile.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/VideoFile.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/VideoFile_nomain.o VideoFile.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/VideoFile.o ${OBJECTDIR}/VideoFile_nomain.o;\
	fi

${OBJECTDIR}/_ext/1508022067/testaOlhos_nomain.o: ${OBJECTDIR}/_ext/1508022067/testaOlhos.o /home/andrey/NetBeansProjects/vlgt/testaOlhos.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1508022067
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1508022067/testaOlhos.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1508022067/testaOlhos_nomain.o /home/andrey/NetBeansProjects/vlgt/testaOlhos.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1508022067/testaOlhos.o ${OBJECTDIR}/_ext/1508022067/testaOlhos_nomain.o;\
	fi

${OBJECTDIR}/_ext/1508022067/realTimeTracker_nomain.o: ${OBJECTDIR}/_ext/1508022067/realTimeTracker.o /home/andrey/NetBeansProjects/vlgt/realTimeTracker.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1508022067
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1508022067/realTimeTracker.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1508022067/realTimeTracker_nomain.o /home/andrey/NetBeansProjects/vlgt/realTimeTracker.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1508022067/realTimeTracker.o ${OBJECTDIR}/_ext/1508022067/realTimeTracker_nomain.o;\
	fi

${OBJECTDIR}/Face_nomain.o: ${OBJECTDIR}/Face.o Face.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Face.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Face_nomain.o Face.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Face.o ${OBJECTDIR}/Face_nomain.o;\
	fi

${OBJECTDIR}/_ext/1508022067/testeSolvePoly_nomain.o: ${OBJECTDIR}/_ext/1508022067/testeSolvePoly.o /home/andrey/NetBeansProjects/vlgt/testeSolvePoly.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1508022067
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1508022067/testeSolvePoly.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1508022067/testeSolvePoly_nomain.o /home/andrey/NetBeansProjects/vlgt/testeSolvePoly.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1508022067/testeSolvePoly.o ${OBJECTDIR}/_ext/1508022067/testeSolvePoly_nomain.o;\
	fi

${OBJECTDIR}/_ext/1508022067/EyeProcessor_nomain.o: ${OBJECTDIR}/_ext/1508022067/EyeProcessor.o /home/andrey/NetBeansProjects/vlgt/EyeProcessor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1508022067
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1508022067/EyeProcessor.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1508022067/EyeProcessor_nomain.o /home/andrey/NetBeansProjects/vlgt/EyeProcessor.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1508022067/EyeProcessor.o ${OBJECTDIR}/_ext/1508022067/EyeProcessor_nomain.o;\
	fi

${OBJECTDIR}/NoseTipFinder_nomain.o: ${OBJECTDIR}/NoseTipFinder.o NoseTipFinder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/NoseTipFinder.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/NoseTipFinder_nomain.o NoseTipFinder.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/NoseTipFinder.o ${OBJECTDIR}/NoseTipFinder_nomain.o;\
	fi

${OBJECTDIR}/_ext/1508022067/PointRunningAverageStream_nomain.o: ${OBJECTDIR}/_ext/1508022067/PointRunningAverageStream.o /home/andrey/NetBeansProjects/vlgt/PointRunningAverageStream.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1508022067
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1508022067/PointRunningAverageStream.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1508022067/PointRunningAverageStream_nomain.o /home/andrey/NetBeansProjects/vlgt/PointRunningAverageStream.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1508022067/PointRunningAverageStream.o ${OBJECTDIR}/_ext/1508022067/PointRunningAverageStream_nomain.o;\
	fi

${OBJECTDIR}/testaToGray_nomain.o: ${OBJECTDIR}/testaToGray.o testaToGray.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/testaToGray.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/testaToGray_nomain.o testaToGray.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/testaToGray.o ${OBJECTDIR}/testaToGray_nomain.o;\
	fi

${OBJECTDIR}/ImageUtils_nomain.o: ${OBJECTDIR}/ImageUtils.o ImageUtils.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ImageUtils.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I/usr/src/OpenCV-2.3.0/include/opencv2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/ImageUtils_nomain.o ImageUtils.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ImageUtils.o ${OBJECTDIR}/ImageUtils_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f3 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/vlgt

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
