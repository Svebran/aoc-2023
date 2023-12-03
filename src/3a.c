#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define SANITY_CHECK fprintf(stdout, "TEST\n");fflush(stdout);

char check_symbol(char* pos)
{
    if((*pos >= '0' && *pos <= '9') || *pos == '.' || *pos == '\n')
        return 0;
    return 1;
}

int main()
{
    uint64_t sum = 0;

    char is_a_part;
    char considering_digit;
    uint32_t start;
    uint64_t val;
    uint32_t i;

    char buffer[3][1024];
    char* prev = buffer[0];
    char* curr = buffer[1];
    char* next = buffer[2];
    char* swapper;
    char last_iteration = 0;
    for(i = 0; i < 1023; i++) prev[i] = '.'; prev[1023] = '\0';
    fgets(curr+1, 1024, stdin); curr[0] = '.'; next[0] = '.';
    while(fgets(next+1, 1024, stdin) != NULL && next[1] != '\n')
    {
        LAST_ITERATION_LABEL:
        i = 0;
        considering_digit = 0;
        while(curr[i] != '\0')
        {
            if(curr[i] >= '0' && curr[i] <= '9')
            {
                if(!considering_digit)
                {
                    considering_digit = 1;
                    is_a_part = 0;
                    start = i;
                    if(check_symbol(prev+(i-1)) || check_symbol(curr+(i-1)) || check_symbol(next+(i-1)))
                        is_a_part = 1;
                }
                if(check_symbol(prev+i) || check_symbol(curr+i) || check_symbol(next+i))
                    is_a_part = 1;
            }
            else if(considering_digit)
            {
                considering_digit = 0;
                if(check_symbol(prev+i) || check_symbol(curr+i) || check_symbol(next+i))
                    is_a_part = 1;
                if(is_a_part)
                {
                    sscanf(curr+start, "%"SCNu64, &val);
                    sum += val;
                }
            }
            i++;
        }
        swapper = prev;
        prev = curr;
        curr = next;
        next = swapper;
    }
    for(i = 0; i < 1023; i++) next[i] = '.'; next[1023] = '\0';
    if(!last_iteration)
    {
        last_iteration = 1;
        goto LAST_ITERATION_LABEL;
    }
    printf("%"PRIu64"\n", sum);

    return 0;
}
