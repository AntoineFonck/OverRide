void secret_backdoor()
{
	char string[128]; //@rbp-0x80

	fgets(string, 128, STDIN);
	system(string);
	return;
}

void set_msg(char *buf)
{
	char msgbuf[1024]; //@rbp-0x400
	char *buf_copy; //@rbp-0x408

	buf_copy = buf;
	memset(msgbuf, 0, 128 * 8);
	puts(">: Msg @Unix-Dude");
	printf(">>: ");
	fgets(msgbuf, 1024, STDIN);
	strncpy(buf, msgbuf, (int)buf[180]);
}

void set_username(char *buf)
{
	int index; //@rbp-0x4
	char userbuf[128]; //@rbp-0x90
	char *buf_copy; //@rbp-0x98
	
	buf_copy = buf;
	memset(userbuf, 0, 16 * 8);
	puts(">: Enter your username");
	printf(">>: ");
	fgets(userbuf, 128, STDIN);

	for (index = 0; index <= 40 && userbuf[index] != '\0'; index++)
		buf_copy[140 + index] = userbuf[index];
	printf(">: Welcome, %s", buf_copy + 140);
}

void handle_msg()
{
	int msg_len; //@rbp-0xc
	char buf[180]; //@rbp-0xc0

	memset(buf + 140, 0, 40);
	msg_len = 140;
	set_username(buf);
	set_msg(buf);
	puts(">: Msg sent!");
}

int main()
{
	puts("--------------------------------------------\n|   ~Welcome to l33t-m$n ~    v1337        |\n--------------------------------------------");
	handle_msg();
	return 0;
}
