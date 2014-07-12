cmake_minimum_required(VERSION 2.8)

# Other requirements
find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

include(FeatureSummary)
include(GenerateExportHeader)
include(ECMGenerateHeaders)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
include(ECMPackageConfigHelpers)
include(ECMSetupVersion)
include(KDEFrameworkCompilerSettings)

set(KF5_VERSION "5.0.0") # handled by release scripts
set(KF5_DEP_VERSION "5.0.0") # handled by release scripts

find_package(Qt5Core ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE)
#find_package(Qt COMPONENTS QtCore REQUIRED)

add_subdirectory(src)
