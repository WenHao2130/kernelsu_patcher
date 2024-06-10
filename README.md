## This is a simple KernelSU LKM patch program

## Usage
```
Patch boot or init_boot images to apply KernelSU
Usage: boot-patch [OPTIONS]
Options:
    -b <BOOT>            boot image path, default value is "boot.img" in the working directory
    -i <KSUINIT>         ksuinit path, default value is "ksuinit" in the working directory
    -m <MODULE>          LKM module path, default value is "kernelsu.ko" in the working directory
    -t <MAGISKBOOT>      magiskboot path, default value is "magiskboot" in the working directory
    -h                   Print this menu
Please use " " to enclose the path
Example:
    boot-patch -b "workdir/init_boot.img" -i "workdir/ksuinit" -m "workdir/android13-5.15_kernelsu.ko" -t "workdir/magiskboot"
```

## Build
```
gcc boot-patch.c -o boot-patch
```

## Other
My code level is very low, I can only achieve usability.
