void clear_stdin()
{
	char current_char;

	current_char = 0;
	while (1)
	{
		current_char = getchar();
		if (current_char == '\n' || current_char == EOF)
			break ;
	}
}

int get_unum()
{
	unsigned int unum;
	
	unum = 0;
	fflush(stdout);
	scanf("%u", &unum);
	clear_stdin();
	return unum;
}

int read_number(char *data)
{
	unsigned int index;
	
	printf(" Index: ");
	index = get_unum();
	printf(" Number at data[%u] is %u\n", index, (unsigned int *)data[index * sizeof(int)]);
	return 0;
}

int store_number(char *data)
{
	unsigned int number;
	unsigned int index;
	
	printf(" Number: ");
	number = get_unum();
	printf(" Index: ");
	index = get_unum();
	if ((index % 3 == 0) || (number >> 0x18 == 0xb7)) //verifies index is not a multiple of 3 and that the number to store does not look like 0xb7000000
	{
	    puts(" *** ERROR! ***");
	    puts("   This index is reserved for wil!");
	    puts(" *** ERROR! ***");
	    return 1;
	}
	else
	{
	    (uint32_t *)data[index * sizeof(int)] = number;
	    return 0
	}
}

int main(int argc, char *argv[], char *envp[]) //stackframe size == 488
{
	char input_command[20]; //@esp+0x1b8
	int return_val; //@esp+0x1b4
	char data[400]; //@esp+0x24 --> 100 * sizeof(int)
	char **argv_copy; //@esp+0x1c
	char **envp_copy; //@esp+0x18

	argv_copy = argv;
	envp_copy = envp; 
	return_val = 0;
	memset(input_command, 0, sizeof(int) * 5);
	memset(data, 0, sizeof(int) * 100);
	while (*argv_copy)			//null all program arguments
	{
		memset(*argv_copy, 0, strlen(*argv_copy));
		argv_copy++;
	}
	while (*envp_copy)			//null all environment variables
	{
		memset(*envp_copy, 0, strlen(*envp_copy));
		envp_copy++;
	}
	puts("----------------------------------------------------\n  Welcome to wil\'s crappy number storage service!   \n----------------------------------------------------\n Commands:                                          \n    store - store a number into the data storage    \n    read  - read a number from the data storage     \n    quit  - exit the program                        \n----------------------------------------------------\n   wil has reserved some storage :>                 \n----------------------------------------------------\n");
	while (1)
	{
		printf("Input command: ");
		return_val = 1;
		fgets(input_command, 20, STDIN);
		input_command[strlen(input_command)] = '\0';
		if (strncmp(input_command, "store", 5) == 0)
			return_val = store_number(data);
		else if (strncmp(input_command, "read", 4))
			return_val = read_number(data);
		else if (strncmp(input_command, "quit", 4))
			break ;
		if (return_val == 0)
			printf(" Completed %s command successfully\n", input_command);
		else
			printf(" Failed to do %s command\n", input_command);
		memset(input_command, 0, sizeof(int) * 5);
	}
	return 0;
}
