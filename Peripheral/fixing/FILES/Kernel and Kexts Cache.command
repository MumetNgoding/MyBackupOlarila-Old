#!/bin/bash
#
sudo rm -f /System/Library/Caches/com.apple.kext.caches/Startup/kernelcache && sudo kextcache -i / && sudo touch /System/Library/Extensions && sudo update_dyld_shared_cache -force && sudo nvram -c && sudo purge