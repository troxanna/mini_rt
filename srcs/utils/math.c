#include "../../includes/minirt.h"

float     solve_quadratic(float a, float b, float c)
{
    float discr;
    float t1;
    float t2;
    float q;
    float tmp;
    
    discr = b * b - 4 * a * c; 
    if (discr < 0)
        return (-1);
    else if (discr == 0)
        t1 = -0.5 * b / a;
    else
    {
        q = (b > 0) ? -0.5 * (b + sqrt(discr)) : -0.5 * (b - sqrt(discr));
        t1 = q / a; 
        t2 = c / q;
        // printf("%f\n", t1);
        // printf("%f\n", t2);
        if (t1 > t2)
        {
            //исправить swap и перенести туда
            tmp = t1;
            t1 = t2;
            t2 = tmp;
        }
        if (t1 < 0)
        {
            t1 = t2;
            if (t1 < 0)
                return (-1);
        }   
    }
    return (t1);
}
