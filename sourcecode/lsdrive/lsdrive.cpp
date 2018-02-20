// lsdrive.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 1024

int GetDriverInfo(char* pdrive)
{
	unsigned int driver_type = 0;
	unsigned long volume_serial_nb = 0;
	unsigned long maximum_component_length = 0;
	unsigned long file_system_flags = 0;

	char file_system_name_buf[BUF_SIZE];
	char drive_name[MAX_PATH];
	char drive_type_str[MAX_PATH];

	memset(file_system_name_buf, 0, sizeof(file_system_name_buf));
	memset(drive_name, 0, sizeof(drive_name));
	memset(drive_type_str, 0, sizeof(drive_type_str));

	driver_type = GetDriveType(pdrive);

	//printf("driver_type is %d\n", driver_type);

	switch (driver_type)
	{
	case DRIVE_UNKNOWN:
		sprintf(drive_type_str, "UNKNOWN");
		break;
	case DRIVE_NO_ROOT_DIR:
		sprintf(drive_type_str, "NO_ROOT_DIR");
		break;
	case DRIVE_REMOVABLE:
		sprintf(drive_type_str, "REMOVABLE");
		break;
	case DRIVE_FIXED:
		sprintf(drive_type_str, "FIXED");
		break;
	case DRIVE_REMOTE:
		sprintf(drive_type_str, "REMOTE");
		break;
	case DRIVE_CDROM:
		sprintf(drive_type_str, "CDROM");
		break;
	case DRIVE_RAMDISK:
		sprintf(drive_type_str, "RAMDISK");
		break;
	default:
		break;
	}

	if ((driver_type != DRIVE_CDROM) &&
		!(GetVolumeInformation(
			pdrive,
			drive_name,
			MAX_PATH,
			&volume_serial_nb,
			&maximum_component_length,
			&file_system_flags,
			file_system_name_buf,
			BUF_SIZE))) {
		return -1;
	}

	printf("%3s \t %20s \t %10s \t %8s\n", pdrive, drive_name, file_system_name_buf, drive_type_str);

	return 0;
}

int main(void)
{
	char logic_driver_string[BUF_SIZE];
	char *pdrive;
	int ret;

	memset(logic_driver_string, 0, sizeof(logic_driver_string));

	GetLogicalDriveStrings(BUF_SIZE - 1, logic_driver_string);
	pdrive = logic_driver_string;

	//printf("Windows Current DRIVE:\n\n");
	printf("\n  DRIVE    Ten o dia :     FS     TYPE\n\n");
	do {
		if ((ret = GetDriverInfo(pdrive)) != 0)
			printf("\nGet Volume Information Error: %s\n", strerror(ret));

		pdrive += (strlen(pdrive) + 1);
	} while (*pdrive != '\x00');
	system("pause");
	return 0;
}

#if 0
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#define BUF_SIZE 1024
int GetDriverInfo(char* pdrive);
int main(void)
{
	char logic_driver_string[BUF_SIZE];
	char *pdrive;

	memset(logic_driver_string, 0, sizeof(logic_driver_string));

	GetLogicalDriveStrings(BUF_SIZE - 1, logic_driver_string);
	pdrive = logic_driver_string;

	do {
		if (!GetDriverInfo(pdrive))
			printf("\nGet Volume Information Error:%d", GetLastError());

		pdrive += (strlen(pdrive) + 1);
	} while (*pdrive != '\x00');
	return 0;
}

int GetDriverInfo(char* pdrive)
{
	unsigned int driver_type;
	unsigned long volume_serial_nb;
	unsigned long maximum_component_length;
	unsigned long file_system_flags;
	char file_system_name_buf[BUF_SIZE];
	char drive_name[MAX_PATH];

	printf("\n%s\n", pdrive);
	driver_type = GetDriveType(pdrive);

	switch (driver_type)
	{
	case DRIVE_UNKNOWN:
		printf("The driver type cannot be determined!");
		break;
	case DRIVE_NO_ROOT_DIR:
		printf("The root path is invalid,for example,no volume is mounted at the path");
		break;
	case DRIVE_REMOVABLE:
		printf("The drive is a type that has removable media,for example:a floppy drive or removable hard disk");
		break;
	case DRIVE_FIXED:
		printf("The drive is a type that cannot be removed, for example,a fixed hard drive");
		break;
	case DRIVE_REMOTE:
		printf("This drive is a remote(network) drive");
		break;
	case DRIVE_CDROM:
		printf("This drive is a CD-ROM drive.");
		break;
	case DRIVE_RAMDISK:
		printf("This drive is a RAM disk");
		break;
	default:
		break;
	}

	if (!(GetVolumeInformation(
		pdrive,
		drive_name,
		MAX_PATH,
		&volume_serial_nb,
		&maximum_component_length,
		&file_system_flags,
		file_system_name_buf,
		BUF_SIZE)))
	{
		return FALSE;

	}

	if (0 != strlen(drive_name))
	{
		printf("\nDrive Name is %s.\n", drive_name);
	}

	printf("\nVolume Serial is %u.", volume_serial_nb);
	printf("\nMaximum Component Length is %u.", maximum_component_length);
	printf("\nSystem Type is %s.\n", file_system_name_buf);

	if (file_system_flags & FILE_VOLUME_QUOTAS)
	{

		printf("The file system supports disk Quotas.\n");
	}

	if (file_system_flags & FILE_SUPPORTS_REPARSE_POINTS)
	{
		printf("The file system does not support volume mount points.\n");

	}

	if (file_system_flags & FILE_CASE_SENSITIVE_SEARCH)
	{
		printf("The file system supports case-sentitive file name.\n");
	}

	printf("...\n");

	return TRUE;

}
#endif