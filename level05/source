int main()
{
	char buf[100]; //@esp+0x28
	int counter; //@esp+0x8c

	fgets(buf, 100, STDIN);
	counter = 0;
	do {
		if (buf[counter] > 64 && buf[counter] <= 90) //if current char is between 'A' and 'Z'
		{
			buf[counter] = buf[counter] ^ 32; //make uppercase characters lowercase
		}
		counter++;
	} while (counter < strlen(buf));
	printf(buf);
	exit(0);
}
