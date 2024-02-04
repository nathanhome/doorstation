#!/bin/bash

###
# Multimedia settings for webrtc

BOOTDIR=$(/usr/lib/raspberrypi-sys-mods/get_fw_loc)

# Set or add config param: $1=name $2=value $3=file
function setConfig {
    name=${1//\//\\/}
    value=${2//\//\\/}
    sed -i \
        -e '/^#\?\(\s*'"${name}"'\s*=\s*\).*/{s//\1'"${value}"'/;:a;n;ba;q}' \
        -e '$a'"${name}"'='"${value}" $3
}

# enable audio
setConfig "dtparam=audio" on ${BOOTDIR}/config.txt

# enable cam detection
setConfig camera_auto_detect 1 ${BOOTDIR}/config.txt

# enable usb soundcard
sed -i 's/^\s*\(defaults\.ctl\.card\)\s\+[0-9\-]\+/\1 '"${SOUNDCARDID}"'/' /usr/share/alsa/alsa.conf
sed -i 's/^\s*\(defaults\.pcm\.card\)\s\+[0-9\-]\+/\1 '"${SOUNDCARDID}"'/' /usr/share/alsa/alsa.conf