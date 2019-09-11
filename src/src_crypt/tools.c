#include "ft_ssl_crypt.h"

char *xor_functon(char *a, char *b)
{
    int     i;
    char    *ans;

    if (!(ans = malloc(ft_strlen(a) + 1)))
        return (NULL);
    i = -1;
    while (++i < ft_strlen(a))
    {
        if(a[i] == b[i]) 
            ans[i] = "0"; 
        else 
            ans[i] = "1";
    }
    ans[i] = '\0';
    return ans;
}

char *permute(char *key, int* arr, int n)
{ 
    char    *per;
    int     i;

    if (!(per = (char*)malloc(n + 1)))
        return (NULL);
    i = -1;
    while(++i < n)
        per[i] = key[arr[i] - 1];
    return per; 
} 