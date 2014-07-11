cmake_minimum_required(VERSION 2.8)

# Other requirements
set(DESIRED_QT_VERSION 5)
set(REQUIRED_QT_VERSION 5.3)

find_package(Qt5Core ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE)
#find_package(Qt COMPONENTS QtCore REQUIRED)

add_subdirectory(src)
