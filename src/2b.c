#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define SANITY_CHECK fprintf(stdout, "TEST\n");fflush(stdout);

int main()
{
    uint64_t sum = 0;

    uint64_t tmp;
    uint64_t red;
    uint64_t green;
    uint64_t blue;
    char* it;

    char buffer[1024];
    while(fgets(buffer, 1024, stdin) != NULL && buffer[0] != '\n')
    {
        it = buffer;
        while(*it != ':') it++; it++;
        red = 0; green = 0; blue = 0;
        do
        {
            do
            {
                sscanf(it, "%*[, ]%"SCNu64, &tmp);
                while(*it != 'r' && *it != 'g' && *it != 'b') it++;
                switch(*it)
                {
                    case 'r':
                        red = tmp > red ? tmp : red;
                        it += 3;
                        break;
                    case 'g':
                        green = tmp > green ? tmp : green;
                        it += 5;
                        break;
                    case 'b':
                        blue = tmp > blue ? tmp : blue;
                        it += 4;
                        break;
                }
            } while(*it != ';' && *it != '\n');
        } while(*it++ != '\n');
        sum += red * green * blue;
    }
    printf("%"PRIu64"\n", sum);

    return 0;
}
