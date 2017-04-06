PROJECT(FPGA_Interface_Cell_Analysis1.0)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

cmake_policy(SET CMP0043 OLD)
cmake_policy(SET CMP0020 OLD)

#where to find local cmake modules
#Siso__
FILE(TO_CMAKE_PATH "$ENV{SISODIR5}" SISODIR5)
SET(CMAKE_MODULE_PATH ${SISODIR5} "C:/Program Files/SiliconSoftware/Runtime5.4.1.2/cmake/modules")
SET(SiSo_Runtime_Header "C:/Program Files/SiliconSoftware/Runtime5.4.1.2/include")
SET(LIBS_PATH "C:/Program Files/SiliconSoftware/Runtime5.4.1.2/lib/visualc")

#___________________________________________________________
SET(OpenCV_DIR "C:/opencv-3.0.1/sources/build/install")
SET(CMAKE_PREFIX_PATH "C:/Qt5.6/5.6/msvc2013_64/")

#List of environment variables that have to be set with examples:

#add qt path to env path variable  		C:\Qt5.6\5.6\msvc2013_64\bin (old: C:\QT4_7_2\bin)  !!This has to be the first entry in the path variables!
#add opencv dll to env path variable  	C:\opencv-3.0.1\sources\build\install\x64\vc12\bin
#add SISO dll path to env path  		C:\Program Files\SiliconSoftware\Runtime5.4.1.2\bin  
#set "QTDIR" 					to  	C:\Qt5.6\5.6\msvc2013_64  (old: C:\QT4_7_2)
#set "XILINX" variable  		to  	C:\Xilinx92i
#set "SISOAPPLETIMAGESOURCE" 	to 		C:\Program Files\SiliconSoftware\Runtime5.2.2\Images
#set "SISODIR5" 				to 		C:\Program Files\SiliconSoftware\Runtime5.2.2
#set "SISODIR5_64" 				to 		C:\Program Files\SiliconSoftware\Runtime5.2.2

MESSAGE(STATUS  "SISODIR5: " ${SISODIR5} )
MESSAGE(STATUS  "Current CMake Directory: " ${CMAKE_CURRENT_SOURCE_DIR} )
MESSAGE(STATUS  "CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH} )
MESSAGE(STATUS  "LIB_PATH: " ${LIBS_PATH} )

#Siso
INCLUDE(SisoPlatform)
FIND_PACKAGE(FgLib5 REQUIRED)
FIND_PACKAGE(ClSerSis REQUIRED)
FIND_PACKAGE(SisoDisplayLib REQUIRED)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# Widgets finds its own dependencies.
FIND_PACKAGE(Qt5Widgets REQUIRED)

FIND_PACKAGE(OpenCV REQUIRED)

include_directories(${Qt5Widgets_INCLUDES})

ADD_DEFINITIONS(${SISOPLATFORM_DEFINITIONS})

INCLUDE_DIRECTORIES(${SiSo_Runtime_Header})
INCLUDE_DIRECTORIES(
	${SISODIR5}/include
	${SISODIR5}/include/msinttypes
	${FgLib5_INCLUDE_DIR}
	${SISODISPLAYLIB_INCLUDE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/include #is needed
)

#QT Stuff goes here
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

SET(FPGA_Interface_SRCs

		#core Functionality
		include/ui_FPGA_Interfacemainwindow.h
		include/ui_FPGA_Interfaceiniselectionwindow.h
		include/defines.h
		include/point.h
		include/FPGA_Interface_Core.h
		include/FPGA_Interfaceiniselectionwindow.h
		include/FPGA_Interfacemainwindow.h
		include/Types.h
		include/Point_case_conflict.h
		include/FPGA_InterfaceIni.h
		include/Project.h
		include/ROIManager.h
		include/RB_Plot.h
		include/ROIAnalysis.h
		src/RB_Plot.cpp
		src/ROIAnalysis.cpp
		src/ROIManager.cpp
		src/Project.cpp
		src/FPGA_Interface.cpp
		src/FPGA_Interface_Core.cpp
		src/FPGA_Interfaceiniselectionwindow.cpp
		src/FPGA_Interfacemainwindow.cpp
		src/FPGA_InterfaceIni.cpp
		
		#Framegrabber specific files
		include/Ringbuffer.h
		include/RingbufferItem.h
		include/SiSo_AppletIF.h
		include/SiSo_Applet_min.h
		src/Ringbuffer.cpp
		src/RingbufferItem.cpp
		src/SiSo_AppletIF.cpp
		src/SiSo_Applet_min.cpp
		
		#Camera Related Files
		include/CL.h
		include/CoaXPress.h
		include/Kamera_Dummy.h
		include/Kamera_I.h
		include/Kamera_JAI_Pulnix_AccuPixel.h
		include/Kamera_Mikrotron_MC258x.h
		src/CL.cpp
		src/CoaXPress.cpp
		src/Kamera_Dummy.cpp
		src/Kamera_I.cpp
		src/Kamera_JAI_Pulnix_AccuPixel.cpp
		src/Kamera_Mikrotron_MC258x.cpp
		
		#Inifile Functionality
		include/tree.h
		include/FPGA_InterfaceIniDefines.h
		include/any.h
		include/inifile.h
		include/infotag.h
		src/inifile.cpp
		src/infotag.cpp
		
		#utils
		include/stdutils.h
		include/stringutils.h
		src/stringutils.cpp
		src/stdutils.cpp
		)
		
ADD_EXECUTABLE(	FPGA_Interface
				${FPGA_Interface_SRCs}
				)

TARGET_LINK_LIBRARIES(FPGA_Interface
	${QT_LIBRARIES}
	${FgLib5_LIBRARIES}
	${SISODISPLAYLIB_LIBRARIES}
	${LIBS_PATH}/clsersis.lib
	${OpenCV_LIBS}
	${LIBS_PATH}/siso_genicam.lib
)

qt5_use_modules(FPGA_Interface Widgets)

 INSTALL(	TARGETS
			 FPGA_Interface
			 DESTINATION bin)