#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define SANITY_CHECK fprintf(stdout, "TEST\n");fflush(stdout);

int main()
{
    uint64_t sum = 0;

    char* it;
    char nums[100];
    uint32_t val;
    uint64_t score;

    char buffer[1024];
    while(fgets(buffer, 1024, stdin) != NULL && buffer[0] != '\n')
    {
        for(uint32_t i = 0; i < 100; i++) nums[i] = 0;
        it = buffer;
        while(*it != ':') it++; it++;
        while(*it == ' ') it++;
        while(*it != '|')
        {
            sscanf(it, "%"SCNu32, &val);
            nums[val] = 1;
            while(*it != ' ') it++;
            while(*it == ' ') it++;
        } it++;
        score = 0;
        while(*it == ' ') it++;
        while(*it != '\n' && *it != '\0')
        {
            sscanf(it, "%"SCNu32, &val);
            nums[val] == 1 ? score++ : 0;
            while(*it != ' ' && *it != '\n') it++;
            while(*it == ' ' && *it != '\n') it++;
        }
        sum += score != 0 ? 1 << (score - 1) : 0;
    }
    printf("%"PRIu64"\n", sum);

    return 0;
}
