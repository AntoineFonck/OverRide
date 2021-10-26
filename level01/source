char a_user_name[100]; //@0x804a040

verify_user_name()
{
	puts("verifying username....\n");
	return(strncmp(a_user_name, "dat_wil", 7)); //hardcoded "dat_wil" @0x80486a8
}

verify_user_pass(char *password) //password @ebp+0x8
{
	return(strncmp(password, "admin", 5)); //hardcoded "admin" @0x80486b0
}

int main()
{
	int return_value;//@esp+0x5c (right after buf) == 4 bytes nullified
	char buf[64]; //@esp+0x1c (size == 4x16) --> nullified with rep stos

	puts("********* ADMIN LOGIN PROMPT *********"); //@0x80486b8
	printf("Enter Username: "); //@0x80486df

	fgets(a_user_name, 256, STDIN);
	return_value = verify_user_name();
	if (return_value != 0)
	{
		puts("nope, incorrect username...\n");
		return 1;
	}
	printf("Enter Password: "); //@0x804870d
	fgets(buf, 100, STDIN);
	return_value = verify_user_pass(buf);
	if (return_value == 0 || return_value != 0)
	{
		puts("nope, incorrect password...\n");
		return 1;
	}
							//|0x8048589 <main+185>    cmp    DWORD PTR [esp+0x5c],0x0
							//|0x804858e <main+190>    je     0x8048597 <main+199>
							//|0x8048590 <main+192>    cmp    DWORD PTR [esp+0x5c],0x0
							//|0x8048595 <main+197>    je     0x80485aa <main+218>
	else if (return_value == 0)
		return 0;
	return 0;
}
