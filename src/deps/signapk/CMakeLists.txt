project(signapk)

set(REPO_PATH ${GENERAL_SOURCE_PATH}/android-build/tools/signapk)

set(signapk_SRCS
    ${REPO_PATH}/SignApk.java
)
set(CMAKE_JAVA_COMPILE_FLAGS -J-Xmx2048M -target 1.5 -source 1.5 -encoding UTF-8 -Xmaxwarns 9999999 -g -bootclasspath ${CMAKE_BINARY_DIR}/src/deps/javalibrary-core/core.jar -extdirs \"\")
add_jar(signapk SOURCES ${signapk_SRCS} MANIFEST ${REPO_PATH}/SignApk.mf INCLUDE_JARS ${CMAKE_BINARY_DIR}/src/deps/javalibrary-bouncycastle/bouncycastle-bcprov.jar bouncycastle-bcpkix)
