
int main() //stackframe size 288 (0x120)
{
	FILE *flag_filepointer;//@rbp-0x8
	int bytes_read; //@rbp-0xc
	char username_buf[100]//@rbp-0x70 --> nullified 12 * 8 + 4 (100)
	char flag_buf[41]//@rbp-0xa0 --> nullified 5 * 8 + 1 (41)
	char password_buf[100]//@rbp-0x110 --> nullified 12 * 8 + 4 (100)

	flag_filepointer = fopen("/home/users/level03/.pass", "r");
	if (flag_filepointer == NULL)
	{
		fwrite("ERROR: failed to open password file\n", 1, 36, STDERR);
		exit(1);
	}
	//<main+210>
	bytes_read = fread(flag_buf, 1, 41, flag_filepointer);
	flag_buf[strcspn(flag_buf, "\n")] = '\0'; //"\n" @ 0x400bf5 in .rodata
	if (bytes_read != 41)
	{
		fwrite("ERROR: failed to read password file\n", 1, 36, STDERR);
		fwrite("ERROR: failed to read password file\n", 1, 36, STDERR);
		exit(1);
	}
	//0x40097d <main+361>
	fclose(flag_filepointer);
	puts("===== [ Secure Access System v1.0 ] =====");
	puts("/***************************************\\");
	puts("| You must login to access this system. |");
	puts("\\**************************************/");
	printf("--[ Username: ");
	fgets(username_buf, 100, STDIN);
	username_buf[strcspn(username_buf, "\n")] = '\0'; //"\n" @ 0x400bf5 in .rodata
	printf("--[ Password: ");
	fgets(password_buf, 100, STDIN);
	password_buf[strcspn(password_buf, "\n")] = '\0'; //"\n" @ 0x400bf5 in .rodata
	puts("*****************************************");
	if (strncmp(flag_buf, password_buf, 41) == 0)
	{
		printf("Greetings, %s!\n", username_buf);
		system("/bin/sh");
		return(0);
	}
	//0x400a96 <main+642>
	printf(username_buf);
	puts(" does not have access!");
	exit(1);
}
