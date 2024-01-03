#include "include/pipex.h"

void check_numargc(int argc)
{
	if (argc != 5)
		return (send_error(ERR_INPUT));
}

char *create_path(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL); // Add return statement to avoid warning
}
static int open_infile_outfile(char *filename, bool is_outfile)
{
	int infile;
	int outfile;

	if (is_outfile)
	{
		outfile = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile < 0)
			send_error(ERR_OUTFILE);
		return (outfile);
	}
	else
	{
		infile = open(filename, O_RDONLY);
		if (infile < 0)
			send_error(ERR_INFILE);
		return (infile);
	}
}
static void create_pipe(int *tube) {
    if (pipe(tube) == -1)
        send_error(ERR_PIPE); 
}

t_pipex init_pipex(int argc, char **argv, char **envp)
{
	t_pipex pipex;
		
	pipex.infile = open_infile_outfile(argv[1], false);
	ft_printf("infile: %d\n", pipex.infile);
	pipex.outfile = open_infile_outfile(argv[argc-1], true);
	ft_printf("outfile: %d\n", pipex.outfile);
	create_pipe(pipex.tube);
	ft_printf("tube: %d\n", pipex.tube);
	pipex.paths = create_path(envp);	
	ft_printf("paths: %s\n", pipex.paths);		  
	pipex.cmd_paths = ft_split(pipex.paths, ':'); 
	ft_printf("cmd_paths: %s\n", pipex.cmd_paths[0]);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_cmd(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		second_cmd(pipex, argv, envp);	
	close_pipes(&pipex);
	wait_for_children(&pipex);
	dad_free(&pipex);
	return (pipex);
}
int main(int argc, char **argv, char **envp)
{
	t_pipex pipex;

	check_numargc(argc);
	pipex = init_pipex(argc, argv, envp);
	return (0);
}