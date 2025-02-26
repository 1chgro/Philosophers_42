#include "philo.h"



int main(int ac, char **av)
{
    int num_of_philosophers = 0;
    int time_to_die= 0;
    int time_to_eat= 0;
    int time_to_sleep= 0;
    int num_of_time_phil_must_eat= 0;
    if (ac != 6)
    {
        printf("Error in args\n");
        return (1);
    }

    num_of_philosophers = atoi(av[1]);
    time_to_die = atoi(av[2]);
    time_to_eat = atoi(av[3]);
    time_to_sleep = atoi(av[4]);
    num_of_time_phil_must_eat = atoi(av[5]);

}