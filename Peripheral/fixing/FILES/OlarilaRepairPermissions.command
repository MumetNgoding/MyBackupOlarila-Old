#!/bin/bash

echo "||||||||||||||||||||||||"
echo "*----------------------*"
echo "     Welcome `users`    "
echo "*----------------------*"
echo "||||||||||||||||||||||||"
echo "                                                                  "
echo "||| Olarila.com - The Real Vanilla Hackintosh |||"
echo "Please type your password"

sudo spctl --master-disable & sudo mount -uw / & killall Finder
sudo chown -v -R root:wheel /System/Library/Extensions
sudo touch /System/Library/Extensions
sudo chmod -v -R 755 /Library/Extensions
sudo chown -v -R root:wheel /Library/Extensions
sudo touch /Library/Extensions
sudo rm -f /System/Library/Caches/com.apple.kext.caches/Startup/kernelcache && sudo kextcache -i / && sudo touch /System/Library/Extensions && sudo update_dyld_shared_cache -force && sudo nvram -c && sudo purge
sudo pmset -a autopoweroff 0
sudo pmset -a standby 0
sudo pmset -a hibernatemode 0
echo
echo "Hibernatemode, standby, and autopoweroff set to 0..."
sudo rm /private/var/vm/sleepimage
echo
echo "Sleepimage deleted..."
sudo touch /private/var/vm/sleepimage
sudo chflags uchg /private/var/vm/sleepimage
echo
echo "Zero-byte sleepimage created and locked from further writes."
echo "Clearing Your NVRAM:"
echo "--------------------"
sudo nvram -c
sudo purge
sleep 1
echo
echo "Done!!!"
echo "Enjoy!!!"
osascript -e 'tell app "loginwindow" to «event aevtrrst»'