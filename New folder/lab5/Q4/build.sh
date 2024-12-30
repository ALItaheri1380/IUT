make
sudo insmod iut_audio_device.ko
major=`cat /proc/devices | grep iut_audio_device | cut -d' ' -f1`
mknod /dev/iut_audio_device c $major 0
gcc iut_audio_device_test.c -o main
