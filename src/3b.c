#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define SANITY_CHECK fprintf(stdout, "TEST\n");fflush(stdout);

char check_symbol(char* pos)
{
    if(*pos >= '0' && *pos <= '9')
        return 1;
    return 0;
}

uint64_t get_num(char* pos)
{
    uint64_t result;
    while(*pos >= '0' && *pos <= '9')
        pos--;
    pos++;
    int test = sscanf(pos, "%"SCNu64, &result);
    if(test == 0 || test == EOF)
        printf("that should not happen\n");
    return result;
}

int main()
{
    uint64_t sum = 0;

    uint32_t i;
    uint32_t count;
    uint64_t ratio;

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
        while(curr[i] != '\0')
        {
            if(curr[i] == '*')
            {
                count = 0;
                ratio = 1;

#define consider(pos) \
                if(check_symbol(pos)) \
                { \
                    ratio *= get_num(pos); \
                    count++; \
                }

                consider(prev+i)
                else
                {
                    consider(prev+(i-1));
                    consider(prev+(i+1));
                }

                consider(curr+(i-1));
                consider(curr+(i+1));

                consider(next+i)
                else
                {
                    consider(next+(i-1));
                    consider(next+(i+1));
                }
                if(count == 2)
                    sum += ratio;
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
