project(javalibrary-okhttp)

set(REPO_PATH ${GENERAL_SOURCE_PATH}/okhttp)

# find -L okhttp/src/main/java  -name "*.java"
# filter out /Platform.java
set(okhttp_common_SRCS
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/Address.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/Connection.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/ConnectionPool.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/Failure.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/HttpResponseCache.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/MediaType.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/OkAuthenticator.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/OkHttpClient.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/OkResponseCache.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/Request.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/Response.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/ResponseSource.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/Route.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/RouteDatabase.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/TunnelRequest.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/AbstractOutputStream.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/Base64.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/DiskLruCache.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/Dns.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/FaultRecoveringOutputStream.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/NamedRunnable.java
#     ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/Platform.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/StrictLineReader.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/Util.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/http/AbstractHttpInputStream.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/http/Dispatcher.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/http/HeaderParser.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/http/HttpAuthenticator.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/http/HttpDate.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/http/HttpEngine.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/http/HttpTransport.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/http/HttpURLConnectionImpl.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/http/HttpsEngine.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/http/HttpsURLConnectionImpl.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/http/Job.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/http/OkResponseCacheAdapter.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/http/Policy.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/http/RawHeaders.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/http/RequestHeaders.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/http/ResponseHeaders.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/http/RetryableOutputStream.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/http/RouteSelector.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/http/SpdyTransport.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/http/Transport.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/http/UnknownLengthHttpInputStream.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/spdy/IncomingStreamHandler.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/spdy/Ping.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/spdy/Settings.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/spdy/SpdyConnection.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/spdy/SpdyReader.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/spdy/SpdyStream.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/spdy/SpdyWriter.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/tls/DistinguishedNameParser.java
    ${REPO_PATH}/src/main/java/com/squareup/okhttp/internal/tls/OkHostnameVerifier.java
)

# find -L okhttp/android/main/java/  -name "*.java"
set(okhttp_other_SRCS
    ${REPO_PATH}/android/main/java/com/squareup/okhttp/internal/Platform.java
    ${REPO_PATH}/android/main/java/com/squareup/okhttp/HttpHandler.java
    ${REPO_PATH}/android/main/java/com/squareup/okhttp/HttpsHandler.java
)

set(CMAKE_JAVA_COMPILE_FLAGS -J-Xmx2048M -target 1.5 -source 1.5 -encoding UTF-8 -Xmaxwarns 9999999 -g -bootclasspath ${CMAKE_BINARY_DIR}/src/deps/javalibrary/core.jar -extdirs \"\")
add_jar(okhttp-prejarjar ${okhttp_common_SRCS} ${okhttp_other_SRCS} INCLUDE_JARS core ${CMAKE_BINARY_DIR}/src/deps/javalibrary-conscrypt/conscrypt.jar)
jarjar_process(okhttp-prejarjar "${REPO_PATH}/jarjar-rules.txt" "${CMAKE_CURRENT_BINARY_DIR}/okhttp-prejarjar.jar" "${CMAKE_CURRENT_BINARY_DIR}/okhttp.jar" "${CMAKE_CURRENT_BINARY_DIR}/okhttp-nojarjar.jar")
# install_jar(okhttp ${ANDROID_JAR_DIR})
