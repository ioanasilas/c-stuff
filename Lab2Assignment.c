#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char **argv)
{
    // pointers to hold strings that correspond to each arg
    char *avalue = NULL, *bvalue = NULL, *cvalue = NULL;
    // store conversion from str to int in these
    int a_int = 0, b_int = 0, c_int = 0;
    opterr = 0;
    // get flags from input
    int option_char;
    // count digits of input values
    int digit_count = 0;

    // if not all arguments are provided
    if (argc < 7)
    {
        printf("Usage: program -a <value> -b <value> -c <value>\n");
        return 1;
    }

    while((option_char = getopt(argc, argv, "a:b:c:")) != -1)
    switch(option_char)
    {
        case 'a':
        {
            digit_count = 0;
            avalue = optarg;
            for (int i = 0; i < strlen(avalue); i++)
            {
                // make sure that the sum of the 3 values does not overflow
                if (digit_count > 8)
                {
                    fprintf(stderr, "Value for -a is too long, provide a shorter one.");
                    return 1;
                }
                // check each char, make sure it's a digit
                // then construct the integer
                if (avalue[i] - '0' >= 0 && avalue[i] - '0' <= 9)
                {
                    digit_count++;
                    a_int = a_int * 10 + (avalue[i] - '0');
                }
                else
                {
                    fprintf(stderr, "Option for -a contains non-digit character %c", avalue[i]);
                    return 1;
                }
            }
            break;
        }
        case 'b':
        {
            digit_count = 0;
            bvalue = optarg;
            for (int i = 0; i < strlen(bvalue); i++)
            {
                if (digit_count >= 9)
                {
                    fprintf(stderr, "Value for -b is too long, provide a shorter one.");
                    return 1;
                }
                // check each char, make sure it's a digit
                // then construct the integer
                if (bvalue[i] - '0' >= 0 && bvalue[i] - '0' <= 9)
                {
                    digit_count++;
                    b_int = b_int * 10 + (bvalue[i] - '0');
                }
                else
                {
                    fprintf(stderr, "Option for -b contains non-digit character %c", bvalue[i]);
                    return 1;
                }
            }
            break;
        }
        case 'c':
        {
            digit_count = 0;
            cvalue = optarg;
            for (int i = 0; i < strlen(cvalue); i++)
            {
                if (digit_count >= 9)
                {
                    fprintf(stderr, "Value for -c is too long, provide a shorter one.");
                    return 1;
                }
                // check each char, make sure it's a digit
                // then construct the integer
                if (cvalue[i] - '0' >= 0 && cvalue[i] - '0' <= 9)
                {
                    digit_count++;
                    c_int = c_int * 10 + (cvalue[i] - '0');
                    
                }
                else
                {
                    fprintf(stderr, "Option for -c contains non-digit character %c", cvalue[i]);
                    return 1;
                }
            }
            break;
        }
        // if getopt() returns an error
        case '?':
        {
            if (optopt == 'a' || optopt == 'b' || optopt == 'c')
            {
                fprintf(stderr, "Option -%c requires an argument.", optopt);
            }
            else
            {
                fprintf(stderr, "Unknown option '-%c'.", optopt);
            }
            printf("Usage: program -a <value> -b <value> -c <value>\n");
            return 1;
        }
        // handle any other case
        default:
        {
            printf("Usage: program -a <value> -b <value> -c <value>\n");
            return 1;
        }
        
    }
    printf("Value for a = %d\n", a_int);
    printf("Value for b = %d\n", b_int);
    printf("Value for c = %d\n", c_int);
    
    //print the actual sum of the values
    printf("The sum of the values provided for the 3 arguments is:%d\n", a_int + b_int + c_int);
    return 0;

}