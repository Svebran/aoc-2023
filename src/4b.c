#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define SANITY_CHECK fprintf(stdout, "TEST\n");fflush(stdout);

typedef struct match_list
{
    uint64_t n;
    struct match_list* next;
} match_list;

int main()
{
    uint64_t sum = 0;

    char* it;
    char nums[100];
    uint32_t val;
    uint64_t score;
    match_list matches[128];
    for(uint32_t i = 0; i < 128; i++)
    {
        matches[i].n = 1;
        matches[i].next = matches+i+1;
    }
    matches[127].next = matches;
    match_list* match_it = matches;
    match_list* match_it2;

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
        match_it2 = match_it;
        for(uint64_t i = 0; i < score; i++)
        {
            match_it2 = match_it2->next;
            match_it2->n += match_it->n;
        }
        sum += match_it->n;
        match_it->n = 1;
        match_it = match_it->next;
    }
    printf("%"PRIu64"\n", sum);

    return 0;
}
