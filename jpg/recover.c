/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

typedef uint8_t  BYTE;

int main(int argc, char* argv[])
{
    char *infile = "card.raw";
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        char* infile = "card.raw";
        printf("Could not open %s.\n", infile);
        return 2;
    }
    
    char outfile[8] = "000.jpg";
    
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    bool foundJPG = false;
    BYTE *buff = malloc(sizeof(BYTE)*512);
    int counter = 0;
    
    while(fread(buff, sizeof(BYTE), 512, inptr) == 512 )
    {
        if(!foundJPG)
        {
            if(buff[0] == 0xff && buff[1] == 0xd8 && buff[2] == 0xff)
            {
                foundJPG = true;
                fwrite(buff, sizeof(BYTE), 512, outptr);
                counter++;
            }
        }
        else
        {
            if(buff[0] == 0xff && buff[1] == 0xd8 && buff[2] == 0xff)
            {
                fclose(outptr);
                sprintf(outfile, "%.3i.jpg", counter++);
                outptr = fopen(outfile, "w");
                if (outptr == NULL)
                {
                    fclose(inptr);
                    free(buff);
                    fprintf(stderr, "Could not create %s.\n", outfile);
                    return 3;
                }
            }    
            fwrite(buff, sizeof(BYTE), 512, outptr);
        }
    }
    
    free(buff);
    fclose(inptr);
    fclose(outptr);
}
