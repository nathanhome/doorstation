packer {
}

//  file_urls             = ["https://downloads.raspberrypi.com/raspios_lite_arm64/images/raspios_lite_arm64-2023-05-03/2023-05-03-raspios-bullseye-arm64-lite.img.xz"]
//  file_checksum_url     = "https://downloads.raspberrypi.com/raspios_lite_arm64/images/raspios_lite_arm64-2023-05-03/2023-05-03-raspios-bullseye-arm64-lite.img.xz.sha256"


source "arm" "doorstation" {
  file_urls             = ["https://downloads.raspberrypi.com/raspios_lite_arm64/images/raspios_lite_arm64-2023-12-11/2023-12-11-raspios-bookworm-arm64-lite.img.xz"]
  file_checksum_url     = "https://downloads.raspberrypi.com/raspios_lite_arm64/images/raspios_lite_arm64-2023-12-11/2023-12-11-raspios-bookworm-arm64-lite.img.xz.sha256"
  file_checksum_type    = "sha256"
  file_target_extension = "xz"
  file_unarchive_cmd    = ["xz", "--decompress", "$ARCHIVE_PATH"]
  image_build_method    = "reuse"
  image_type            = "dos"
  image_partitions {
    filesystem = "fat"
    # mountpoint has changed for bookworm !
    mountpoint   = "/boot/firmware"
    name         = "boot"
    size         = "256M"
    start_sector = "2048"
    type         = "c"
  }
  image_partitions {
    filesystem   = "ext4"
    mountpoint   = "/"
    name         = "root"
    size         = "0"
    start_sector = "526336"
    type         = "83"
  }
  image_path       = "doorstation-pi-arm64.img"
  image_size       = "4G"
  image_chroot_env = ["PATH=/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin"]

  # for MAC M1 build
  qemu_binary_destination_path = "/usr/bin/qemu-arm-static"
  qemu_binary_source_path      = "/usr/bin/qemu-arm-static"

  # for Intel build
  # qemu_binary_source_path      = "/usr/bin/qemu-aarch64-static"
  # qemu_binary_destination_path = "/usr/bin/qemu-aarch64-static"
}

build {
  sources = ["source.arm.doorstation"]

  // General raspberry pi image modifications and hardenings
  provisioner "shell" {
    inline = ["apt-get -yq update"]
  }

  provisioner "shell" {
    env = {
      HOSTNAME = "${var.hostname}"
      TZ       = "${var.timezone}"
      LOCALE   = "${var.locale}"
      ENCODING = "${var.encoding}"
      KEYMAP   = "${var.keymap}"
    }
    script = "raspi/core_setup.sh"
  }

  provisioner "shell" {
    env = {
      WIFI_SSID    = "${var.wifi_ssid}"
      WIFI_PASS    = "${var.wifi_passphrase}"
      WIFI_COUNTRY = "${var.wifi_country}"
    }
    script = "raspi/wifi_setup.sh"
  }

  provisioner "shell" {
    env = {
      LOCALE   = "${var.locale}"
      ENCODING = "${var.encoding}"
      BOOTTIME = "${var.boottime}"
    }
    script = "raspi/auto_updates.sh"
  }

  provisioner "file" {
    source      = "raspi/sshd_config"
    destination = "/etc/ssh/sshd_config"
  }

  # an empty file is copy by default
  # to activate password authentication
  provisioner "file" {
    source      = "${var.authorized_keyfile}"
    destination = "/tmp/authorized_keys"
  }

  provisioner "shell" {
    env = {
      LOCALE   = "${var.locale}"
      ENCODING = "${var.encoding}"
      USER     = "${var.user}"
      PASS     = "${var.password}"
    }
    script = "raspi/user_ssh_setup.sh"
  }

  provisioner "shell" {
    env = {
      LOCALE   = "${var.locale}"
      ENCODING = "${var.encoding}"
    }
    script = "raspi/sdcard_saver.sh"
  }

  // doorstation specific setup
  provisioner "shell" {
    env = {
      LOCALE   = "${var.locale}"
      ENCODING = "${var.encoding}"
      USER     = "${var.user}"
    }
    script = "doorstation/doorstation_settings.sh"
  }

  provisioner "shell" {
    env = {
      LOCALE      = "${var.locale}"
      ENCODING    = "${var.encoding}"
      GPUMEM      = "${var.gpumem}"
      SOUNDCARDID = "${var.soundcardid}"
      USER        = "${var.user}"
    }
    script = "doorstation/webrtc_host_setup.sh"
  }

  # post-processors {
  #  post-processor "flasher" {
  #    device      = "${var.sdcard_device}"
  #    block_size  = 4096
  #    interactive = true
  #  }
  #}

}