#include "../../includes/minirt.h"

float     solve_quadratic(float a, float b, float c, float *t)
{
    float discr;
    float q;
    float tmp;
    
    discr = b * b - 4 * a * c; 
    if (discr < 0)
        return (65536);
    else if (discr == 0)
        t[0] = -0.5 * b / a;
    // else
    // {
    //     t[0] = ((b * (-1)) + sqrt(discr)) / 2 * a;
    //     t[1] = ((b * (-1)) - sqrt(discr)) / 2 * a;
    //     if (t[0] > 0 && t[0] < t[1])
    //         return (t[0]);
    //     else if (t[1] > 0 && t[1] < t[0])
    //         return (t[1]);
    // }
    // return (65536);
    else
    {
        q = (b > 0) ? -0.5 * (b + sqrt(discr)) : -0.5 * (b - sqrt(discr));
        t[0] = q / a; 
        t[1] = c / q;
        // printf("%f\n", t1);
        // printf("%f\n", t2);
        if (t[0] < t[1] && t[0] > 0)
            return (t[0]);
        else if (t[1] < t[0] && t[1] > 0)
            return (t[1]);
        else
            return (65536);
        // if (t[0] < t[1])
        // {
        //     //исправить swap и перенести туда
        //     tmp = t[0];
        //     t[0] = t[1];
        //     t[1] = tmp;
        // }
        // else if (t[0] < 0)
        // {
        //     t[0] = t[1];
        //     if (t[1] < 0)
        //         return (65536);
        // }   
    }
    return (t[0]);
}

int				ft_atoi(char *str, int *i)
{
	int			result;

	result = 0;
	if (str[*i] >= '0' && str[*i] <= '9')
	{
		while (str[*i] >= '0' && str[*i] <= '9')
		{
			result = result * 10 + (str[*i] - '0');
			(*i)++;
		}
		return (result);
	}
	else
		return (-1);
}
