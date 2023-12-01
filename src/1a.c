#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main()
{
    uint64_t sum = 0;
    uint64_t mn = 0;
    uint64_t mx = 0;

    char first;
    
    char buffer[1024];
    while(fgets(buffer, 1024, stdin) != NULL && buffer[0] != '\n')
    {
        first = 0;
        for(uint32_t i = 0; buffer[i] != '\n' && i < 1024; i++)
        {
            if(buffer[i] >= '0' && buffer[i] <= '9')
            {
                if(!first)
                {
                    first = 1;
                    mn = buffer[i] - '0';
                }
                mx = buffer[i] - '0';
            }
        }
        sum += mn*10 + mx;
    }
    printf("%"PRIu64"\n", sum);

    return 0;
}
