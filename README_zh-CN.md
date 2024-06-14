## 这是一个简易的KernelSU LKM模式修补工具

[English](./README.md) | **简体中文**

## 使用方法

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

## 如何构建

```
gcc boot-patch.c -o boot-patch
```

## 提示

`ksuinit`二进制文件位于KernelSU仓库中，它通常位于`/userspace/ksud/bin/<arch>/ksuinit`

你也可以[点击此处](https://raw.githubusercontent.com/tiann/KernelSU/main/userspace/ksud/bin/aarch64/ksuinit)来下载`ksuinit`的二进制文件

## 其他

本人的代码水平很低，程序仅仅可以做到可用级别，请各位大佬轻喷
