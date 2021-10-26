int main()
{
	pid_t pid;
	char buf[128]; //32 * 4 @esp+0x20
	int wstatus;

	pid = fork();
	memset(buf, 0, 128); //fill buffer with '\0'

	if (pid != 0) //parent process, pid == pid of the child process
	{
		do {
			wait(&wstatus);
			if (__WIFEXITED(wstatus) || __WIFSIGNALED(wstatus)) //equivalent of ((wstatus & 0x7f == 0) || (((wstatus & 0x7f) + 1) >> 1 > 0)) --> check if child was terminated normally or by a signal (see https://sites.uclouvain.be/SystInfo/usr/include/bits/waitstatus.h.html)
			{
				puts("child is exiting..."); //child exited, so the parent exits too
				return 0;
			}
		} while (ptrace(PTRACE_PEEKUSER, pid, 0x2c, 0) != 0xb); //checks if the EAX register of the child holds syscall execve() --> the shellcode should NOT contain it !
		puts("no exec() for you");
		kill(pid, 9); //send SIGKILL to child
	}
	else //child process, pid == 0
	{
		prctl(PR_SET_PDEATHSIG, SIGHUP); //== prctl(1, 1) --> make child process die when parent process dies (https://stackoverflow.com/questions/284325/how-to-make-child-process-die-after-parent-exits/284443)
		ptrace(PTRACE_TRACEME, 0, NULL, NULL); // == ptrace(0, 0, 0, 0) --> Indicates that this child process is to be traced by its parent
		puts("Give me some shellcode, k");
		gets(buf); //buffer overflowwwww
	}
	return 0;
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
