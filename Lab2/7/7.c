/*
C-implementation of the following forsyde model

-- | The graySDF actor, which transforms a every RGB image from a stream
-- into a grayscale one. In this case it is assumed that the X dimension holds the additional information.
graySDF :: Int -- ^ dimension X for input images
        -> Int -- ^ dimension Y for input images
        -> Signal Int -- ^ stream of pixels from the RGB image
        -> Signal Double -- ^ stream of resulting grayscale pixels
graySDF dimX dimY = actor11SDF (3 * dimX * dimY) (dimX * dimY) (wrapImageF (3 * dimX) dimY grayscale)
*/

#include <stdio.h>
#include "circular_buffer.h"
#include "actors.h"
#include "ppm_io.c"

char asciiLevels[] = {' ', '.', ':', '-', '=', '+', '/', 't', 'z', 'U', 'w', '*', '0', '#', '%', '@'};

double convert(unsigned int r, unsigned int g, unsigned int b)
{
    double rr = (double)r;
    double gg = (double)g;
    double bb = (double)b;
    return (rr * 0.3125) + (gg * 0.5625) + (bb * 0.125);
}

void graySDF(int dimX, int dimY, unsigned int *data, double *out)
{
    for (int i = 0; i < dimX * dimY * 3; i += 3)
    {
        // printf("%d ", i);
        out[i / 3] = convert(data[i], data[i + 1], data[i + 2]);
        // printf("%f ", out[i/3]);
    }
}

void asciiSDF(int dimX, int dimY, double *data, char *out)
{
    for (int i = 0; i < dimX * dimY; i++)
    {
        double index = 15.0 * (data[i] / 255.0);
        // printf("%d ", (int)index);
        out[i] = asciiLevels[(int)index];
    }
}

// actor_b = actor11SDF 1 2 f_2 where
// f_2 [x] = [x, x + 1]

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Please provide the input file name\n");
        return 1;
    }
    ppmTy ppm = ppm_read(argv[1]);

    int dimX = ppm.w;
    int dimY = ppm.h;

    /* Buffer out: Size: width * height */
    double *buffer_out = malloc(dimX * dimY * sizeof(double));

    graySDF(ppm.w, ppm.h, ppm.data, buffer_out);

    char *buffer_out2 = malloc(dimX * dimY * sizeof(char));
    asciiSDF(ppm.w, ppm.h, buffer_out, buffer_out2);

        FILE *ppm_file = fopen("gray.ppm", "w");
        fputs("P2\n", ppm_file);
        fprintf(ppm_file, "%d %d\n", dimX, dimY);
        fprintf(ppm_file, "%d\n", ppm.max_val);
        for (int i = 0; i < dimX * dimY; i++)
        {
            fprintf(ppm_file, "%d\n", (int)buffer_out[i]);
        }
        fclose(ppm_file);

    // printf("P2\n%d %d\n%d\n", dimX, dimY, ppm.max_val);
    // for (int i = 0; i < dimX * dimY; i++)
    // {
    //     printf("%d\n", (int)buffer_out[i]);
    // }
    // for(int i = 0; i < dimY; i++) {
    //     for(int j = 0; j < dimX; j++) {
    //         printf("%c", buffer_out2[i * dimY + j]);
    //     }
    //     printf("\n");
    // }

    FILE *ascii_file = fopen("ascii.txt", "w");
        for (int i = 0; i < dimY; i++)
        {
            for(int j = 0; j < dimX; j++) {
                fprintf(ascii_file, "%c", buffer_out2[i * dimX + j]);
            }
            fprintf(ascii_file, "\n");
        }
        fclose(ascii_file);

    return 0;
}