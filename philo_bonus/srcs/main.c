#include "../includes/philo.h"


#define FILO_COUNT 6
#define FORK_ERROR 2

void	ft_process(int id, sem_t *sem)
{
	sem_wait(sem);
	usleep(1000000);
	printf("Process id == %d\n", id);
	printf("_____________\n");
	sem_post(sem);
	exit(1);
}


int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	
	int		i;
	pid_t	id[FILO_COUNT];
	sem_t	*sem;

	i = 0;
	sem = sem_open("filo_sem", O_CREAT, 0644, 2u);
	sem_unlink("filo_sem");
	while (i < FILO_COUNT)
	{
		id[i] = fork();
		if (id[i] == 0)
			ft_process(i + 1, sem);
		else if (id[i] == -1)
		{
			write(2, "Fork error\n", 12);
			exit(FORK_ERROR);
		}
		i++;
	}
	i = 0;
	while (i < FILO_COUNT)
	{
		waitpid(id[i], NULL, 0);
		i++;
	}
	return (0);
}
