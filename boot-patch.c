#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void system_plus(const char *command);
void checkfile(char *filename);

int main(int argc, char *argv[]) {
    char *origin_boot_path;
    char *kernelmodule_path;
    char *magiskboot_path;
    char *ksuinit_path;
    char *option;
    char command[260];

#ifdef _WIN32
    origin_boot_path = ".\\boot.img";
    kernelmodule_path = ".\\kernelsu.ko";
    magiskboot_path = ".\\magiskboot.exe";
    ksuinit_path = ".\\ksuinit";
#else
    origin_boot_path = "./boot.img";
    kernelmodule_path = "./kernelsu.ko";
    magiskboot_path = "./magiskboot";
    ksuinit_path = "./ksuinit";
#endif

    // Read Option
    for (int i = 1; i < argc; i++) {

        if (i + 1 < argc)
            option = strtok(argv[i + 1], " ");

        if (strcmp(argv[i], "-b") == 0) {
            if (i + 1 < argc) {
                i++;
                origin_boot_path = option;
            } else {
                printf("[x] Missing argument for \"-b\"\n");
                return 1;
            }
        } else if (strcmp(argv[i], "-i") == 0) {
            if (i + 1 < argc) {
                i++;
                ksuinit_path = option;
            } else {
                printf("[x] Missing argument for \"-i\"\n");
                return 1;
            }
        } else if (strcmp(argv[i], "-m") == 0) {
            if (i + 1 < argc) {
                i++;
                kernelmodule_path = option;
            } else {
                printf("[x] Missing argument for \"-m\"\n");
                return 1;
            }
        } else if (strcmp(argv[i], "-t") == 0) {
            if (i + 1 < argc) {
                i++;
                magiskboot_path = option;
            } else {
                printf("[x] Missing argument for \"-t\"\n");
                return 1;
            }
        } else if (strcmp(argv[i], "-h") == 0) {
            printf("Patch boot or init_boot images to apply KernelSU\n");
            printf("Usage: boot-patch [OPTIONS]\n");
            printf("Options:\n");
            printf("    -b <BOOT>            boot image path, default value is \"boot.img\" in the working directory\n");
            printf("    -i <KSUINIT>         ksuinit path, default value is \"ksuinit\" in the working directory\n");
            printf("    -m <MODULE>          LKM module path, default value is \"kernelsu.ko\" in the working directory\n");
            printf("    -t <MAGISKBOOT>      magiskboot path, default value is \"magiskboot\" in the working directory\n");
            printf("    -h                   Print this menu\n");
            printf("Please use \" \" to enclose the path\n");
            printf("Example:\n");
            printf("    boot-patch -b \"workdir/init_boot.img\" -i \"workdir/ksuinit\" -m \"workdir/android13-5.15_kernelsu.ko\" -t \"workdir/magiskboot\"");

            exit(0);
        } else {
            printf("[x] Unknown option \"%s\"!\n", argv[i]);
            return 0;
        }
    }

    // Print INFO
    printf("[-] Boot Path: \"%s\"\n", origin_boot_path);
    printf("[-] Ksuinit Path: \"%s\"\n", ksuinit_path);
    printf("[-] LKM Path: \"%s\"\n", kernelmodule_path);
    printf("[-] Magiskboot Path: \"%s\"\n", magiskboot_path);

    // Check File
    checkfile(origin_boot_path);
    checkfile(ksuinit_path);
    checkfile(kernelmodule_path);
    checkfile(magiskboot_path);

    printf("[-] File Check Pass!\n");

    // Unpack Boot
    printf("[-] Unpacking boot image\n");

    sprintf(command, "%s unpack %s", magiskboot_path, origin_boot_path);
    system_plus(command);

    // Add KernelSU LKM
    printf("[-] Add KernelSU LKM\n");

    sprintf(command, "%s cpio ramdisk.cpio \'mv init init.real\'", magiskboot_path);
    system_plus(command);

    sprintf(command, "%s cpio ramdisk.cpio \'add 0755 init %s\'", magiskboot_path, ksuinit_path);
    system_plus(command);

    sprintf(command, "%s cpio ramdisk.cpio \"add 0755 kernelsu.ko %s\"", magiskboot_path, kernelmodule_path);
    system_plus(command);

    // Unpack Boot
    printf("[-] Repacking boot image\n");

    sprintf(command, "%s repack %s kernelsu_patched.img", magiskboot_path, origin_boot_path);
    system_plus(command);

    // Clean Workdir
    sprintf(command, "%s cleanup", magiskboot_path);
    system_plus(command);

    // Patch Succeed
    printf("[-] Patch Succeed! See \"kernelsu_patched.img\"");


    return 0;
}
void system_plus(const char *command) {
	if (system(command) != 0){
        printf("[x] Patch Failed!\n");
        exit(1);
	}
}
void checkfile(char *filename){
	FILE *fp;

	fp = fopen(filename, "r");

	if (fp != NULL){
		fclose(fp);
		return;
	} else {
		printf("[x] File \"%s\" not found!\n", filename);
		exit(1);
	}
}