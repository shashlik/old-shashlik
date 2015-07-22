project(am)

set(REPO_PATH ${ANDROID_FRAMEWORKS_BASE}/cmds/am)

set(am_SRCS
    ${REPO_PATH}/src/com/android/commands/am/Am.java
)

set(CMAKE_JAVA_COMPILE_FLAGS -J-Xmx2048M -target 1.5 -source 1.5 -encoding UTF-8 -Xmaxwarns 9999999 -g -bootclasspath ${CMAKE_BINARY_DIR}/src/deps/javalibrary-core/core.jar -extdirs \"\")
add_jar(am SOURCES ${am_SRCS} INCLUDE_JARS core framework)
# install_jar(am ${ANDROID_JAR_DIR})
install(PROGRAMS ${REPO_PATH}/am DESTINATION ${ANDROID_BIN_DIR})
