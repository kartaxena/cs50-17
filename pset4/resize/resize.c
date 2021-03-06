/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./copy n_size infile outfile\n");
        return 1;
    }
    
    int n_size = atoi(argv[1]);

    if ((n_size < 1) || (n_size > 100))
    {
        fprintf(stderr, "Incorect number!\n");
        return 5;
    }
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    int orig_biHeight = bi.biHeight;
    int orig_biWidth = bi.biWidth;
    int orig_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
     
    bi.biHeight *= n_size;
    bi.biWidth *= n_size;
    
    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biSizeImage = (abs(bi.biHeight) * bi.biWidth) * 3 + (abs(bi.biHeight) * padding);
    bf.bfSize = bi.biSizeImage + bf.bfOffBits;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(orig_biHeight); i < biHeight; i++)
    {
        // resize by vertical
        for (int h = 0; h < n_size; h++)
        {    
            // iterate over pixels in scanline
            for (int j = 0; j < orig_biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                // resize by horizontaly
                for (int add = 0; add < n_size; add++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
                
            
            
            }
            // add padding in output file
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
            
            // Move to the previous position to resize vertically
            long offset = orig_biWidth * sizeof(RGBTRIPLE);
            fseek(inptr, -offset, SEEK_CUR);
            
        }
        
        long offset = orig_biWidth * sizeof(RGBTRIPLE) + orig_padding;
        fseek(inptr, offset, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
