project(javalibrary-shashlik)

set(shashlik-jar_SRCS
    com/google/ads/AdActivity.java
)

set(CMAKE_JAVA_COMPILE_FLAGS -J-Xmx2048M -target 1.5 -source 1.5 -encoding UTF-8 -Xmaxwarns 9999999 -g -bootclasspath ${CMAKE_BINARY_DIR}/src/deps/javalibrary-core/core.jar -extdirs \"\")
add_jar(shashlik SOURCES ${shashlik-jar_SRCS} INCLUDE_JARS core framework)
# install_jar(shashlik ${ANDROID_JAR_DIR})
