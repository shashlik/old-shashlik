project(javalibrary-voip)

set(REPO_PATH ${GENERAL_SOURCE_PATH}/voip)

set(aidl_entries_to_handle
    src/java/android/net/sip/ISipService
    src/java/android/net/sip/ISipSession
    src/java/android/net/sip/ISipSessionListener
#     this aidl file is not an interface and cannot be handled by the tool
#     src/java/android/net/sip/SipProfile
)

set(voip_SRCS
    ${REPO_PATH}/src/java/android/net/rtp/AudioCodec.java
    ${REPO_PATH}/src/java/android/net/rtp/AudioStream.java
    ${REPO_PATH}/src/java/android/net/rtp/RtpStream.java
    ${REPO_PATH}/src/java/android/net/rtp/AudioGroup.java
    ${REPO_PATH}/src/java/android/net/sip/SimpleSessionDescription.java
    ${REPO_PATH}/src/java/android/net/sip/SipAudioCall.java
    ${REPO_PATH}/src/java/android/net/sip/SipErrorCode.java
    ${REPO_PATH}/src/java/android/net/sip/SipException.java
    ${REPO_PATH}/src/java/android/net/sip/SipProfile.java
    ${REPO_PATH}/src/java/android/net/sip/SipRegistrationListener.java
    ${REPO_PATH}/src/java/android/net/sip/SipSession.java
    ${REPO_PATH}/src/java/android/net/sip/SipSessionAdapter.java
    ${REPO_PATH}/src/java/android/net/sip/SipManager.java
    ${REPO_PATH}/src/java/com/android/server/sip/SipHelper.java
    ${REPO_PATH}/src/java/com/android/server/sip/SipService.java
    ${REPO_PATH}/src/java/com/android/server/sip/SipSessionGroup.java
    ${REPO_PATH}/src/java/com/android/server/sip/SipSessionListenerProxy.java
    ${REPO_PATH}/src/java/com/android/server/sip/SipWakeLock.java
    ${REPO_PATH}/src/java/com/android/server/sip/SipWakeupTimer.java
)

foreach(_fileNameAndPathWithoutExtension ${aidl_entries_to_handle})
    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${_fileNameAndPathWithoutExtension}.java
        COMMAND aidl -d${CMAKE_CURRENT_BINARY_DIR}/${_fileNameAndPathWithoutExtension}.P -b -I${REPO_PATH} -I${REPO_PATH}/src -I${REPO_PATH}/src/java -I${ANDROID_FRAMEWORKS_BASE}/core/java ${REPO_PATH}/${_fileNameAndPathWithoutExtension}.aidl  ${CMAKE_CURRENT_BINARY_DIR}/${_fileNameAndPathWithoutExtension}.java
        )
    list(APPEND javalibrary_voip_interface_SRCS "${CMAKE_CURRENT_BINARY_DIR}/${_fileNameAndPathWithoutExtension}.java")
endforeach()


set(CMAKE_JAVA_COMPILE_FLAGS -J-Xmx2048M -target 1.5 -source 1.5 -encoding UTF-8 -Xmaxwarns 9999999 -g -bootclasspath ${CMAKE_BINARY_DIR}/src/deps/javalibrary-core/core.jar -extdirs \"\")
add_jar(voip-common SOURCES ${voip_SRCS} ${javalibrary_voip_interface_SRCS} INCLUDE_JARS core ext framework)
# install_jar(voip-common ${ANDROID_JAR_DIR})
