#!/bin/bash

echo "||||||||||||||||||||||||"
echo "*----------------------*"
echo "     Welcome `users`    "
echo "*----------------------*"
echo "||||||||||||||||||||||||"
echo "                              "
echo "© MaLd0n InsanelyMac / Olarila"
echo "                              "
sudo /usr/libexec/PlistBuddy -c "Set :IOKitPersonalities:NVDAStartup:NVDARequiredOS "$(sw_vers -buildVersion) /Library/Extensions/NVDAStartupWeb.kext/Contents/Info.plist
sudo /usr/libexec/PlistBuddy -c "Set :IOKitPersonalities:NVDAStartup:NVDARequiredOS "$(sw_vers -buildVersion) /System/Library/Extensions/NVDAStartupWeb.kext/Contents/Info.plist
sudo nvram -c
sudo rm -f /System/Library/Caches/com.apple.kext.caches/Startup/kernelcache && sudo touch /Library/Extensions && sudo kextcache -i /
sudo chown -R root:wheel /System/Library/Extensions/
sudo chmod -R 755 /System/Library/Extensions/
sudo touch /System/Library/Extensions/
sudo chown -R root:wheel /Library/Extensions/
sudo chmod -R 755 /Library/Extensions/
sudo touch /Library/Extensions/
osascript -e 'tell app "loginwindow" to «event aevtrrst»'