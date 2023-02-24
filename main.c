#include <stdio.h>
#include <stdlib.h>

int	**get_rgb(unsigned int color)
{
    int **array;
    int i;

    array = (int **)malloc(sizeof(int *) * 3);
    i = 0;
    while (i <= 3)
    {
        array[i] = malloc(sizeof(int));
        i++;
    }
	*array[2] = color % 256;
	*array[1] = ((color - *array[1]) / 256) % 256;
	*array[0] = ((color - *array[1]) / 256 / 256) - *array[2] / 256;
    return (array);
}

int main(void)
{
    int **ptr;

    ptr = get_rgb(0xFF0099);

    int i = 0;
    while (i < 3)
    {
        printf("array[%i] = %i\n", i, *ptr[i]);
        i++;
    }
    free(ptr);
       
}