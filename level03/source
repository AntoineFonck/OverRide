void decrypt(int number)
{
	var_1dh = 0x757c7d51; //'Q}|u' @ebp-0x1d
	var_19h = 0x67667360; //'`sfg'
	var_15h = 0x7b66737e; //'~sf{'
	var_11h = 0x33617c7d; //'}|a3'
	char string[17] = "Q}|u`sfg~sf{}|a3"; // + trailing '\0'. string starts at @ebp-0x1d
	unsigned long len; //@ebp-0x24
	int index; //@ebp-0x28

	string[16] = '\0';
	len = strlen(string); // == 16
	index = 0;
	while (index < len)
	{
		string[index] = string[index] ^ number;
		index++;
	}
	if (strncmp(string, "Congratulations", 17) == 0)
		system("/bin/sh");
	else
		puts("Invalid Password");
}

int test(int user_input, int hardcoded_secret) //stackframe size == 40
{
	int new_value; //@ebp-0xc

	new_value = hardcoded_secret - user_input;
	if (new_value <= 21)			// useless switch(new_value) with always the same instructions :
	{
		return decrypt(new_value);	//     mov eax, dword [ebp - 0xc]
						//     mov dword [esp], eax
						//     call decrypt       ; sym.decrypt
						//     jmp 0x8048858 (leave test() and go back to main())
	}
	return decrypt(rand());
}

int main()
{
	int user_input;

	srand(time(0));
	puts("***********************************"); //@0x08048a48
	puts("*\t\tlevel03\t\t**");
	puts("***********************************"); //@0x08048a48
	printf("Password:");

	scanf("%d", &user_input);
	test(user_input, 0x1337d00d); //xD Leet dude
	return(0);
}
