#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void)

{
    FILE *raw = fopen("card.raw", "r");
    if (raw == NULL)
    {
        fprintf(stderr, "Could not open card.raw.\n");
        return 1;
    }
    uint8_t buffer[512];
    unsigned int size_block = 512;
    unsigned int number_jpg = 0;
    char new_jpg[8];
    FILE *img = NULL;
    while (fread(buffer, size_block, 1, raw))
    {

        if (buffer[0] == 0xff && 
            buffer[1] == 0xd8 && 
            buffer[2] == 0xff && 
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (img != NULL)
            {
               fclose(img); 
            }
            
            sprintf(new_jpg, "%03i.jpg", number_jpg);
            img = fopen(new_jpg, "w");
            
            
            number_jpg++;
            //printf("Now file");
        }
        if (img != NULL)
        {
            fwrite(buffer, size_block, 1, img);
        }
        
        /*if (fread(buffer, size_block, 2, raw) == 1)
        {
            
            // close img
            fclose(img);
            
            // close raw
            fclose(raw);

            // success
            return 0;
        }*/
    }
    fclose(img);
    fclose(raw);
    
}