void log_wrapper(FILE *logfile, char *alert_msg, char *filename)
{
	char    log_msg[264]; //@rbp-0x110

	strcpy(log_msg, alert_msg);
	snprintf(log_msg[strlen(log_msg)], 254 - strlen(log_msg), filename);
	log_msg[strcspn(log_msg, "\n")] = '\0';
	fprintf(logfile, "LOG: %s\n", log_msg);
}

int main(int argc, char *argv[])
{
	char	file_buf[100]; //@rbp-0x70
	char	read_char = EOF; //@rbp-0x71
	int fd = -1; //@rbp-0x78
	FILE *backupfile; //@rbp-0x80
	FILE *logfile; //@rbp-0x88

	if (argc != 2)
		printf("Usage: %s filename\n", argv[0]);
	logfile = fopen("./backups/.log", "w");
	if (logfile == NULL)
	{
		printf("ERROR: Failed to open %s\n", "./backups/.log");
		exit(1);
	}
	log_wrapper(logfile, "Starting back up: ", argv[1]);
	backupfile = fopen(argv[1], "r");
	if (backupfile == NULL)
	{
		printf("ERROR: Failed to open %s\n", argv[1]);
		exit(1);
	}
	strcpy(file_buf, "./backups/");
	strncat(file_buf, argv[1], 99 - strlen(file_buf));
	fd = open(file_buf, O_EXECL | O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP); //flags in octal from https://sites.uclouvain.be/SystInfo/usr/include/asm-generic/fcntl.h.html / mode defined in octal in man 2 open --> file gets created in write mode, and with read/write access
	if (fd < 0)
	{
		printf("ERROR: Failed to open %s%s\n", "./backups/", argv[1]);
		exit(1);
	}
	while (read_char = (char)fgetc(backupfile) != EOF)
		write(fd, &read_char, 1);
	log_wrapper(logfile, "Finished back up ", argv[1]);
	fclose(backupfile);
	close(fd);
	return 0;
}
