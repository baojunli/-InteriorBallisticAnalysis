TEMPLATE	=   app
CONFIG		+=  debug  c++11 
CONFIG		+=  qt
TARGET		=   InteriorBallisticAnalysis
QT          +=  core xml

include(./main.pri)
include(./vtk.pri)

win32{

  INCLUDEPATH	+=  ./ \
					../ \

  Release:DESTDIR         = ../../output/bin 
  Release:MOC_DIR         = ../../output/release/moc 
  Release:RCC_DIR         = ../../output/release/rcc
  Release:UI_DIR          = ../../output/release/qui
  Release:OBJECTS_DIR     = ../../output/release/obj
  Release:LIBS +=  \
	 
 
  Debug:CONFIG	    	+=  console
  Debug:DESTDIR         = ../../output/bin_d 
  Debug:MOC_DIR         = ../../output/debug/moc 
  Debug:RCC_DIR         = ../../output/debug/rcc 
  Debug:UI_DIR          = ../../output/debug/qui 
  Debug:OBJECTS_DIR     = ../../output/debug/obj 
  Debug:LIBS +=  \

	
  message("Windows main build")
}

unix{

  include(../python.pri)

  INCLUDEPATH	+=   ./ \
		     ../ \

  CONFIG       	+=  console
  CONFIG          += plugin
  DESTDIR         = ../../output/bin
  MOC_DIR         = ./release/moc
  UI_DIR          = ./release/qui
  RCC_DIR         = ./release/rcc
  OBJECTS_DIR     = ./release/obj
  LIBS += \
	-L../../output/bin -lPythonModule \
	-L../../output/bin -lSettings \
        -L../../output/bin -lMeshData \
        -L../../output/bin -lMaterial\
        -L../../output/bin -lConfigOptions \
        -L../../output/bin -lHeuDataSrcIO \
        -L../../output/bin -lGeometry \
        -L../../output/bin -lModelData \
        -L../../output/bin -lCurveAnalyse \
        -L../../output/bin -lModuleBase \
        -L../../output/bin -lGraphicsAnalyse \
	-L../../output/bin -lPostWidgets \
	-L../../output/bin -lIO \
	-L../../output/bin -lProjectTree \
	-L../../output/bin -lSolverControl \
	-L../../output/bin -lProjectTreeExtend \
	-L../../output/bin -lMainWidgets \
	-L../../output/bin -lMainWindow \        
	
  message("Linux main build")
}

