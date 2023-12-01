#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

uint32_t recognize_digit(char* str, uint32_t i)
{
    switch(str[i])
    {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return str[i] - '0';
        case 'o':
            if(strncmp(str+i, "one", 3) == 0)
                return 1;
        case 't':
            if(strncmp(str+i, "two", 3) == 0)
                return 2;
            if(strncmp(str+i, "three", 5) == 0)
                return 3;
        case 'f':
            if(strncmp(str+i, "four", 4) == 0)
                return 4;
            if(strncmp(str+i, "five", 4) == 0)
                return 5;
        case 's':
            if(strncmp(str+i, "six", 3) == 0)
                return 6;
            if(strncmp(str+i, "seven", 5) == 0)
                return 7;
        case 'e':
            if(strncmp(str+i, "eight", 5) == 0)
                return 8;
        case 'n':
            if(strncmp(str+i, "nine", 4) == 0)
                return 9;
    }

    return 10;
}

int main()
{
    uint64_t sum = 0;
    uint64_t mn = 0;
    uint64_t mx = 0;

    char first;
    uint32_t digit;
    
    char buffer[1024];
    while(fgets(buffer, 1024, stdin) != NULL && buffer[0] != '\n')
    {
        first = 0;
        for(uint32_t i = 0; buffer[i] != '\n' && i < 1024; i++)
        {
            if((digit = recognize_digit(buffer, i)) < 10)
            {
                if(!first)
                {
                    first = 1;
                    mn = digit;
                }
                mx = digit;
            }
        }
        sum += mn*10 + mx;
    }
    printf("%"PRIu64"\n", sum);

    return 0;
}
