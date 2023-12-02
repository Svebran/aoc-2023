#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define SANITY_CHECK fprintf(stdout, "TEST\n");fflush(stdout);

int main()
{
    uint64_t sum = 0;
    uint64_t game = 0;

    uint64_t tmp;
    uint64_t red;
    uint64_t green;
    uint64_t blue;
    char* it;
    char failure;

    char buffer[1024];
    while(fgets(buffer, 1024, stdin) != NULL && buffer[0] != '\n')
    {
        failure = 0;
        it = buffer;
        game++;
        while(*it != ':') it++; it++;
        do
        {
            red = 0; green = 0; blue = 0;
            do
            {
                sscanf(it, "%*[, ]%"SCNu64, &tmp);
                while(*it != 'r' && *it != 'g' && *it != 'b') it++;
                switch(*it)
                {
                    case 'r':
                        red = tmp;
                        it += 3;
                        break;
                    case 'g':
                        green = tmp;
                        it += 5;
                        break;
                    case 'b':
                        blue = tmp;
                        it += 4;
                        break;
                }
            } while(*it != ';' && *it != '\n');
            if(red > 12 || green > 13 || blue > 14) failure = 1;
        } while(*it++ != '\n');
        if(!failure)
            sum += game;
    }
    printf("%"PRIu64"\n", sum);

    return 0;
}
