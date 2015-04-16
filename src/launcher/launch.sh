# Script to start "launch" on the device, which has a very rudimentary
# shell.
#

export CLASSPATH=/home/leinir/projects/android-player/shashlik/install/lib64/android/system/framework/launch.jar
exec ./shashlik-launcher.bin /home/leinir/projects/android-player/shashlik/install/lib64/android/system/bin com.android.commands.launch.Launch $*

#export CLASSPATH=/data/launch.jar
#exec app_process /data/ com.android.commands.launch.Launch $*
