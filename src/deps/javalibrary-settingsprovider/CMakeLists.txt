project(javalibrary_settingsprovider)

set(REPO_PATH ${ANDROID_FRAMEWORKS_BASE}/packages/SettingsProvider)

set(settingsprovider_SRCS
    ${REPO_PATH}/src/com/android/providers/settings/DatabaseHelper.java
    ${REPO_PATH}/src/com/android/providers/settings/SettingsBackupAgent.java
    ${REPO_PATH}/src/com/android/providers/settings/SettingsHelper.java
    ${REPO_PATH}/src/com/android/providers/settings/SettingsProvider.java
    ${CMAKE_CURRENT_BINARY_DIR}/com/android/providers/settings/R.java
)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/com/android/providers/settings/R.java
    # build resources
    COMMAND touch ${CMAKE_CURRENT_BINARY_DIR}/dummy
    COMMAND jar cf package-export.apk dummy
    COMMAND zip -qd ${CMAKE_CURRENT_BINARY_DIR}/package-export.apk dummy
    COMMAND rm ${CMAKE_CURRENT_BINARY_DIR}/dummy
#     COMMAND aapt package -u -z -c en_US,normal,ldpi,mdpi,hdpi,xhdpi,xxhdpi,nodpi --preferred-configurations hdpi -M ${REPO_PATH}/AndroidManifest.xml -S ${REPO_PATH}/res  -I ${CMAKE_BINARY_DIR}/src/deps/javalibrary-frameworks/package-export.apk  --min-sdk-version 19 --target-sdk-version 19 --product default --version-code 19 --version-name 4.4.4-eng.leinir.20150212.133909   -F ${CMAKE_CURRENT_BINARY_DIR}/package-export.apk
    COMMAND aapt package -u -z -c en_US,en_US,cs_CZ,da_DK,de_AT,de_CH,de_DE,de_LI,el_GR,en_AU,en_CA,en_GB,en_NZ,en_SG,eo_EU,es_ES,fr_CA,fr_CH,fr_BE,fr_FR,it_CH,it_IT,ja_JP,ko_KR,nb_NO,nl_BE,nl_NL,pl_PL,pt_PT,ru_RU,sv_SE,tr_TR,zh_CN,zh_HK,zh_TW,am_ET,hi_IN,en_US,fr_FR,it_IT,es_ES,de_DE,nl_NL,cs_CZ,pl_PL,ja_JP,zh_TW,zh_CN,ru_RU,ko_KR,nb_NO,es_US,da_DK,el_GR,tr_TR,pt_PT,pt_BR,rm_CH,sv_SE,bg_BG,ca_ES,en_GB,fi_FI,hi_IN,hr_HR,hu_HU,in_ID,iw_IL,lt_LT,lv_LV,ro_RO,sk_SK,sl_SI,sr_RS,uk_UA,vi_VN,tl_PH,ar_EG,fa_IR,th_TH,sw_TZ,ms_MY,af_ZA,zu_ZA,am_ET,hi_IN,mdpi,nodpi  -M ${REPO_PATH}/AndroidManifest.xml -S ${REPO_PATH}/res  -I ${CMAKE_BINARY_DIR}/src/deps/javalibrary-frameworks/package-export.apk --min-sdk-version 19 --target-sdk-version 19 --product tablet,nosdcard --version-code 19 --version-name 4.4.4-eng.leinir.20150212.133909   -F ${CMAKE_CURRENT_BINARY_DIR}/package-export.apk
#     COMMAND aapt package -x -z -m  -J ${CMAKE_CURRENT_BINARY_DIR} -M ${REPO_PATH}/AndroidManifest.xml -P ${CMAKE_CURRENT_BINARY_DIR}/public_resources.xml -S ${REPO_PATH}/res  -I ${CMAKE_BINARY_DIR}/src/deps/javalibrary-frameworks/package-export.apk -G ${CMAKE_CURRENT_BINARY_DIR}/proguard_options --min-sdk-version 19 --target-sdk-version 19 --version-code 19 --version-name 4.4.4-eng.leinir.20150212.133909
    COMMAND aapt package -z -m  -J ${CMAKE_CURRENT_BINARY_DIR} -M ${REPO_PATH}/AndroidManifest.xml -P ${CMAKE_CURRENT_BINARY_DIR}/public_resources.xml -S ${REPO_PATH}/res  -I ${CMAKE_BINARY_DIR}/src/deps/javalibrary-frameworks/package-export.apk -G ${CMAKE_CURRENT_BINARY_DIR}/proguard_options --min-sdk-version 19 --target-sdk-version 19 --version-code 19 --version-name 4.4.4-eng.leinir.20150212.133909  
)

set(CMAKE_JAVA_COMPILE_FLAGS -J-Xmx2048M -target 1.5 -source 1.5 -encoding UTF-8 -Xmaxwarns 9999999 -g -bootclasspath ${CMAKE_BINARY_DIR}/src/deps/javalibrary-core/core.jar -extdirs \"\")
add_jar(SettingsProvider SOURCES ${settingsprovider_SRCS} INCLUDE_JARS core ext framework telephony-common)

# target Java: SettingsProvider (out/target/common/obj/APPS/SettingsProvider_intermediates/classes)
# rm -f out/target/common/obj/APPS/SettingsProvider_intermediates/classes-full-debug.jar
# rm -rf out/target/common/obj/APPS/SettingsProvider_intermediates/classes
# mkdir -p out/target/common/obj/APPS/SettingsProvider_intermediates/
# mkdir -p out/target/common/obj/APPS/SettingsProvider_intermediates/classes
# for f in ; do if [ ! -f $f ]; then echo Missing file $f; exit 1; fi; unzip -qo $f -d out/target/common/obj/APPS/SettingsProvider_intermediates/classes; done ;rm -rf out/target/common/obj/APPS/SettingsProvider_intermediates/classes/META-INF
# if [ -d "out/target/common/obj/APPS/SettingsProvider_intermediates/src" ]; then find out/target/common/obj/APPS/SettingsProvider_intermediates/src -name '*.java' >> out/target/common/obj/APPS/SettingsProvider_intermediates/classes/java-source-list; fi
# tr ' ' '\n' < out/target/common/obj/APPS/SettingsProvider_intermediates/classes/java-source-list | sort -u > out/target/common/obj/APPS/SettingsProvider_intermediates/classes/java-source-list-uniq
# if [ -s out/target/common/obj/APPS/SettingsProvider_intermediates/classes/java-source-list-uniq ] ; then javac -J-Xmx512M -target 1.5 -Xmaxerrs 9999999 -encoding UTF-8 -g  -bootclasspath out/target/common/obj/JAVA_LIBRARIES/core_intermediates/classes.jar -classpath out/target/common/obj/JAVA_LIBRARIES/core_intermediates/classes.jar:out/target/common/obj/JAVA_LIBRARIES/core-junit_intermediates/classes.jar:out/target/common/obj/JAVA_LIBRARIES/ext_intermediates/classes.jar:out/target/common/obj/JAVA_LIBRARIES/framework_intermediates/classes.jar:out/target/common/obj/JAVA_LIBRARIES/telephony-common_intermediates/classes.jar  -extdirs "" -d out/target/common/obj/APPS/SettingsProvider_intermediates/classes  \@out/target/common/obj/APPS/SettingsProvider_intermediates/classes/java-source-list-uniq || ( rm -rf out/target/common/obj/APPS/SettingsProvider_intermediates/classes ; exit 41 ) fi
# Note: frameworks/base/packages/SettingsProvider/src/com/android/providers/settings/DatabaseHelper.java uses or overrides a deprecated API.
# Note: Recompile with -Xlint:deprecation for details.
# rm -f out/target/common/obj/APPS/SettingsProvider_intermediates/classes/java-source-list
# rm -f out/target/common/obj/APPS/SettingsProvider_intermediates/classes/java-source-list-uniq
# jar -cf out/target/common/obj/APPS/SettingsProvider_intermediates/classes-full-debug.jar  -C out/target/common/obj/APPS/SettingsProvider_intermediates/classes .
# Copying: out/target/common/obj/APPS/SettingsProvider_intermediates/classes-jarjar.jar
# out/host/linux-x86/bin/acp -fp out/target/common/obj/APPS/SettingsProvider_intermediates/classes-full-debug.jar out/target/common/obj/APPS/SettingsProvider_intermediates/classes-jarjar.jar
# Copying: out/target/common/obj/APPS/SettingsProvider_intermediates/emma_out/lib/classes-jarjar.jar
# out/host/linux-x86/bin/acp -fp out/target/common/obj/APPS/SettingsProvider_intermediates/classes-jarjar.jar out/target/common/obj/APPS/SettingsProvider_intermediates/emma_out/lib/classes-jarjar.jar
# Copying: out/target/common/obj/APPS/SettingsProvider_intermediates/classes.jar
# out/host/linux-x86/bin/acp -fp out/target/common/obj/APPS/SettingsProvider_intermediates/emma_out/lib/classes-jarjar.jar out/target/common/obj/APPS/SettingsProvider_intermediates/classes.jar
# Copying: out/target/common/obj/APPS/SettingsProvider_intermediates/noproguard.classes.jar
# out/host/linux-x86/bin/acp -fp out/target/common/obj/APPS/SettingsProvider_intermediates/classes.jar out/target/common/obj/APPS/SettingsProvider_intermediates/noproguard.classes.jar
# target Dex: SettingsProvider
# out/host/linux-x86/bin/dx -JXms16M -JXmx2048M --dex --output=out/target/common/obj/APPS/SettingsProvider_intermediates/noproguard.classes-with-local.dex     out/target/common/obj/APPS/SettingsProvider_intermediates/noproguard.classes.jar
# Copying: out/target/common/obj/APPS/SettingsProvider_intermediates/noproguard.classes.dex
# out/host/linux-x86/bin/acp -fp out/target/common/obj/APPS/SettingsProvider_intermediates/noproguard.classes-with-local.dex out/target/common/obj/APPS/SettingsProvider_intermediates/noproguard.classes.dex
# target Package: SettingsProvider (out/target/product/vexpress/obj/APPS/SettingsProvider_intermediates/package.apk)
# touch out/target/product/vexpress/obj/APPS/SettingsProvider_intermediates//dummy
# (cd out/target/product/vexpress/obj/APPS/SettingsProvider_intermediates/ && jar cf package.apk dummy)
# zip -qd out/target/product/vexpress/obj/APPS/SettingsProvider_intermediates/package.apk dummy
# rm out/target/product/vexpress/obj/APPS/SettingsProvider_intermediates//dummy
# out/host/linux-x86/bin/aapt package -u -z -c en_US,normal,ldpi,mdpi,hdpi,xhdpi,xxhdpi,nodpi --preferred-configurations hdpi -M frameworks/base/packages/SettingsProvider/AndroidManifest.xml -S frameworks/base/packages/SettingsProvider/res  -I out/target/common/obj/APPS/framework-res_intermediates/package-export.apk --min-sdk-version 17 --target-sdk-version 17 --product tablet,nosdcard --version-code 17 --version-name 4.2.1-68   -F out/target/product/vexpress/obj/APPS/SettingsProvider_intermediates/package.apk
# _adtp_classes_dex=out/target/common/obj/APPS/SettingsProvider_intermediates/classes.dex; cp out/target/common/obj/APPS/SettingsProvider_intermediates/noproguard.classes.dex $_adtp_classes_dex && out/host/linux-x86/bin/aapt add -k out/target/product/vexpress/obj/APPS/SettingsProvider_intermediates/package.apk $_adtp_classes_dex && rm -f $_adtp_classes_dex
#  'out/target/common/obj/APPS/SettingsProvider_intermediates/classes.dex' as 'classes.dex'...
# if [ -d out/target/common/obj/APPS/SettingsProvider_intermediates/classes ] ; then java_res_jar_flags=$(find out/target/common/obj/APPS/SettingsProvider_intermediates/classes -type f -a -not -name "*.class" | sed -e "s?^out/target/common/obj/APPS/SettingsProvider_intermediates/classes/? -C out/target/common/obj/APPS/SettingsProvider_intermediates/classes ?"); if [ -n "$java_res_jar_flags" ] ; then echo $java_res_jar_flags >out/target/product/vexpress/obj/APPS/SettingsProvider_intermediates/java_res_jar_flags; jar uf out/target/product/vexpress/obj/APPS/SettingsProvider_intermediates/package.apk $java_res_jar_flags; fi; fi
# mv out/target/product/vexpress/obj/APPS/SettingsProvider_intermediates/package.apk out/target/product/vexpress/obj/APPS/SettingsProvider_intermediates/package.apk.unsigned
# java -jar out/host/linux-x86/framework/signapk.jar build/target/product/security/platform.x509.pem build/target/product/security/platform.pk8 out/target/product/vexpress/obj/APPS/SettingsProvider_intermediates/package.apk.unsigned out/target/product/vexpress/obj/APPS/SettingsProvider_intermediates/package.apk.signed
# mv out/target/product/vexpress/obj/APPS/SettingsProvider_intermediates/package.apk.signed out/target/product/vexpress/obj/APPS/SettingsProvider_intermediates/package.apk
# mv out/target/product/vexpress/obj/APPS/SettingsProvider_intermediates/package.apk out/target/product/vexpress/obj/APPS/SettingsProvider_intermediates/package.apk.unaligned
# out/host/linux-x86/bin/zipalign -f 4 out/target/product/vexpress/obj/APPS/SettingsProvider_intermediates/package.apk.unaligned out/target/product/vexpress/obj/APPS/SettingsProvider_intermediates/package.apk.aligned
# mv out/target/product/vexpress/obj/APPS/SettingsProvider_intermediates/package.apk.aligned out/target/product/vexpress/obj/APPS/SettingsProvider_intermediates/package.apk
# Install: out/target/product/vexpress/system/app/SettingsProvider.apk
# out/host/linux-x86/bin/acp -fp out/target/product/vexpress/obj/APPS/SettingsProvider_intermediates/package.apk out/target/product/vexpress/system/app/SettingsProvider.apk
