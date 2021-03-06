int auth(char *login, int serial)
{
	int len; //@ebp-0xc
	unsigned long key; //@ebp-0x10
	int index; //@ebp-0x14

	login[strcspn(login, "\n")] = '\0'; //replace trailing newline with null byte in login[]
	len = strnlen(login, 32);
	if (len <= 5)
		return 1;
	if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1) //verifies if this process is already being debugged
	{
		puts ("\e[32m.---------------------------.");
		puts ("\e[31m| !! TAMPERING DETECTED !!  |");
		puts ("\e[32m'---------------------------'");
		return 1;
	}
	key = ((int32_t)login[3] ^ 0x1337) + 0x5eeded;
	for (index = 0; index < len; index++)
	{
		if (login[index] < ' ') //verifies that current byte is printable
			return 1;
		key += ((int32_t)login[index] ^ key) % 0x539;
	}
	if (serial == key)
		return 0;
	else
		return 1;
}

int main()
{
	char login[32]; //@esp+0x2c
	unsigned int serial; //@esp+0x28

	puts ("***********************************");
	puts ("*\t\tlevel06\t\t  *");
	puts ("***********************************");

	printf("-> Enter Login: ");
	fgets(login, 32, STDIN);

	puts ("***********************************");
	puts ("***** NEW ACCOUNT DETECTED ********");
	puts ("***********************************");

	printf("-> Enter Serial: ");
	scanf("%u", &serial);
	if (auth(login, serial) == 0)
	{
		puts ("Authenticated!");
		system ("/bin/sh");
		return 0;
	}
	return 1;
}

void prog_timeout(int sig) //do exit(1) with a syscall
{
  asm("mov $1, %eax;"
      "mov $1, %ebx;"
      "int $0x80");
}

__attribute__ ((constructor)) void enable_timeout_cons() // constructor function --> make the program exit(1) after 60sec
{
    signal(SIGALRM, prog_timeout);
    alarm(60);
}

