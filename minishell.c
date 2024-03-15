#include "minishell.h"

int global_sig = 0;

void printIntArray2D(int (*arr)[2]) 
{
    while (arr[0][0] != -1 && arr[0][1] != -1) 
	{
        printf("\n[%d, %d]\n", arr[0][0], arr[0][1]);
        arr++;
    }
}

void unsetEnvVar(char **envp, const char *varname) {
    int i, j;
    int env_count = 0;

    // Count the number of environment variables
    while (envp[env_count] != NULL) {
        env_count++;
    }

    // Find the environment variable to unset
    for (i = 0; i < env_count; i++) {
        if (strncmp(envp[i], varname, strlen(varname)) == 0 && envp[i][strlen(varname)] == '=') {
            // Free memory for the variable
            free(envp[i]);
            // Shift subsequent elements to fill the gap
            for (j = i; j < env_count - 1; j++) {
                envp[j] = envp[j + 1];
            }
            envp[j] = NULL; // Set the last element to NULL
            break;
        }
    }
}

int main(int argc, char *argv[], char *envp[])
{
	t_struct	*stru;
	int			i;
	int			j;
	int			k;
	int			len;

	(void)argc;
	(void)argv;
	stru = ft_calloc(1,sizeof(t_struct));
	stru->ufd_i = 0;
	copy_env(envp, stru);
	signal_handling();
	export("?", ft_itoa(0), stru);
	while (1) 
	{
		stru->input = readline("minishell ## ");
		if (!stru->input)
		{
			printf("exit\n");
			break;
		}
		if (strcmp(stru->input, "") == 0)
			continue; //should be called skip, because it skips the rest of this loop iteration
		if (strcmp(stru->input, "exit") == 0) //
		{
			printf("exit\n");
			break;
		}
		add_history(stru->input);
		stru->input_by_pipes = pipe_split(stru->input);
		i = 0;
		j = 0;
		len = 0;
		while (stru->input_by_pipes[len])
			len++;
		stru->reassembled_commands = ft_calloc((len + 1 + 1),sizeof(char *));
		stru->filefds = ft_calloc((2 * len) + 1, sizeof(int )); //pointer because it will be an array with one potential infile and one potential outile
		stru->pids = ft_calloc( len + 1, sizeof(pid_t));
		while (stru->input_by_pipes[i])			//needs to be parsed for redirection operators
		{
			stru->split_by_space = space_split(stru->input_by_pipes[i]); //needs to reduce to one space, needs to leave quoted spaces intact
			open_files(stru,i);		//opens files and saves fds in struct
			rem_redir(stru->split_by_space); //removes redirection operators and files from split_by_space
			k = 0;
			while (stru->split_by_space[k])
				k++;
			stru->reassembled_commands[j] = line_expansion(concat_strings(stru->split_by_space,k),stru);
			i++;
			j++;
		}
		terminate_filefds(stru, i);
		stru->reassembled_commands[j] = NULL;
		if (strcmp(stru->reassembled_commands[0], "") == 0)
			continue; //should be called skip, because it skips the rest of this loop iteration
		
		global_sig = 1;
		subprocesses(len, stru->reassembled_commands, envp, stru);
		global_sig = 0;
		unset(stru->env_copy,"?"); //unsets previous exit status, should be done every run
		export("?", ft_itoa(stru->exit_status), stru); // adds exit status to env, should be done every run
		//printStringArray(stru->env_copy); // OFT only for testing
	}
	return 0;
}