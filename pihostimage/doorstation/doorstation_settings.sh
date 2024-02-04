#!/bin/bash

###
# ENable some required hardware features
# Disable some unused/unwanted features that harden the system a little more

BOOTDIR=$(/usr/lib/raspberrypi-sys-mods/get_fw_loc)

# Set or add config param: $1=name $2=value $3=file
function setConfig {
    name=${1//\//\\/}
    value=${2//\//\\/}
    sed -i \
        -e '/^#\?\(\s*'"${name}"'\s*=\s*\).*/{s//\1'"${value}"'/;:a;n;ba;q}' \
        -e '$a'"${name}"'='"${value}" $3
}

# no screen on boot
#setConfig hdmi_ignore_cec_init 1 ${BOOTDIR}/config.txt

# diable hardware UART completely to disable peephole
setConfig enable_uart 0 ${BOOTDIR}/config.txt

# disable bluetooth
echo "dtoverlay=disable-bt" >> ${BOOTDIR}/config.txt
echo "blacklist bluetooth" >> /etc/modprobe.d/raspi-blacklist.conf

# enable SPI
setConfig "dtparam=spi" on ${BOOTDIR}/config.txt

