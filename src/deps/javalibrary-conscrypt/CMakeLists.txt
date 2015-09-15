project(javalibrary_conscrypt)

set(REPO_PATH ${ANDROID_LIBCORE_PATH})

set(javalibrary_SRCS
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/AbstractSessionContext.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/AlertException.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/AlertProtocol.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/Appendable.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/ByteArray.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/CertPinManager.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/CertificateMessage.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/CertificateRequest.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/CertificateVerify.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/ChainStrengthAnalyzer.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/CipherSuite.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/ClientHandshakeImpl.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/ClientHello.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/ClientKeyExchange.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/ClientSessionContext.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/ConnectionState.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/ConnectionStateSSLv3.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/ConnectionStateTLS.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/ContentType.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/DHParameters.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/DataStream.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/DefaultSSLContextImpl.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/DelegatedTask.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/DigitalSignature.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/EndOfBufferException.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/EndOfSourceException.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/FileClientSessionCache.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/Finished.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/Handshake.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/HandshakeIODataStream.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/HandshakeProtocol.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/HelloRequest.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/JSSEProvider.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/KeyManagerFactoryImpl.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/KeyManagerImpl.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/Logger.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/Message.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/NativeCrypto.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLBIOInputStream.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLCipher.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLCipherContext.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLCipherRSA.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLContextImpl.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLDSAKeyFactory.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLDSAKeyPairGenerator.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLDSAParams.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLDSAPrivateKey.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLDSAPublicKey.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLDigestContext.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLECDHKeyAgreement.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLECGroupContext.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLECKeyFactory.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLECKeyPairGenerator.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLECPointContext.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLECPrivateKey.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLECPublicKey.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLEngine.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLKey.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLKeyHolder.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLMac.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLMessageDigestJDK.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLProvider.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLRSAKeyFactory.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLRSAKeyPairGenerator.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLRSAPrivateCrtKey.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLRSAPrivateKey.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLRSAPublicKey.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLRandom.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLSecretKey.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLServerSocketFactoryImpl.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLServerSocketImpl.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLSessionImpl.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLSignature.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLSignatureRawRSA.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLSocketFactoryImpl.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLSocketImpl.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLSocketImplWrapper.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLX509CRL.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLX509CRLEntry.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLX509CertPath.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLX509Certificate.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/OpenSSLX509CertificateFactory.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/PRF.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/PinEntryException.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/PinFailureLogger.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/PinListEntry.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/PinManagerException.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/Platform.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/ProtocolVersion.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/SSLBufferedInput.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/SSLClientSessionCache.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/SSLContextImpl.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/SSLEngineAppData.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/SSLEngineDataStream.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/SSLEngineImpl.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/SSLInputStream.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/SSLParametersImpl.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/SSLRecordProtocol.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/SSLServerSessionCache.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/SSLServerSocketFactoryImpl.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/SSLServerSocketImpl.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/SSLSessionImpl.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/SSLSocketFactoryImpl.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/SSLSocketImpl.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/SSLSocketInputStream.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/SSLSocketOutputStream.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/SSLSocketWrapper.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/SSLStreamedInput.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/SSLv3Constants.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/ServerHandshakeImpl.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/ServerHello.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/ServerHelloDone.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/ServerKeyExchange.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/ServerSessionContext.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/TrustManagerFactoryImpl.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/TrustManagerImpl.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/TrustedCertificateIndex.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/TrustedCertificateKeyStoreSpi.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/TrustedCertificateStore.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/X509PublicKey.java
    ${REPO_PATH}/crypto/src/main/java/org/conscrypt/util/EmptyArray.java
)

set(conscrypt_lib_SRCS
    ${REPO_PATH}/crypto/src/main/native/org_conscrypt_NativeCrypto.cpp
)

include_directories(
    ${LIBNATIVEHELPER_INCLUDEDIRS}
    ${LIBANDROIDLIBCORE_INCLUDEDIRS}
    ${ANDROID_LIBCORE_PATH}/luni/src/main/native
    ${LIBCUTILS_INCLUDES}
    ${GENERAL_SOURCE_PATH}/openssl/include
)
add_definitions(-Wall -Wextra -Werror)
add_library(javacrypto SHARED ${conscrypt_lib_SRCS})
target_compile_definitions(javacrypto
    PRIVATE
    -DJNI_JARJAR_PREFIX=com/android/
)
add_custom_command(TARGET javacrypto POST_BUILD
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND rm -f libconscrypt_jni.so
    COMMAND ln -s libjavacrypto.so libconscrypt_jni.so
)
target_link_libraries(javacrypto crypto ssl)
if(FORCE_32BIT_BUILD)
    set_target_properties(javacrypto PROPERTIES COMPILE_FLAGS "-m32 -std=gnu++11" LINK_FLAGS "-m32")
else()
    set_target_properties(javacrypto PROPERTIES COMPILE_FLAGS "-std=gnu++11")
endif(FORCE_32BIT_BUILD)
install(TARGETS javacrypto DESTINATION ${ANDROID_LIB_DIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libconscrypt_jni.so DESTINATION ${ANDROID_LIB_DIR})

set(CMAKE_JAVA_COMPILE_FLAGS -J-Xmx2048M -target 1.5 -source 1.5 -encoding UTF-8 -Xmaxwarns 9999999 -g -bootclasspath ${CMAKE_BINARY_DIR}/src/deps/javalibrary/core.jar -extdirs \"\")
add_jar(conscrypt-prejarjar ${javalibrary_SRCS} INCLUDE_JARS core)
# add_jar(conscrypt-nojarjarthing ${javalibrary_SRCS} INCLUDE_JARS core)
jarjar_process(conscrypt-prejarjar "${REPO_PATH}/crypto/jarjar-rules.txt" "${CMAKE_CURRENT_BINARY_DIR}/conscrypt-prejarjar.jar" "${CMAKE_CURRENT_BINARY_DIR}/conscrypt.jar" "${CMAKE_CURRENT_BINARY_DIR}/conscrypt-nojarjar.jar")
#install_jar(conscrypt ${ANDROID_JAR_DIR})
# install(FILES ${CMAKE_CURRENT_BINARY_DIR}/conscrypt-nojarjarthing.jar DESTINATION ${ANDROID_JAR_DIR} RENAME conscrypt.jar)
