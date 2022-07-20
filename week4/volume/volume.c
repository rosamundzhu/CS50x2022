// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    uint8_t header[HEADER_SIZE];
    fread(header, sizeof(header), 1, input);
    fwrite(header, sizeof(header), 1, output);

    // TODO: Read samples from input file and write updated data to output file
    int16_t buffer; //每次2bytes
    while (fread(&buffer, sizeof(buffer), 1, input)) //只要返回的是true, 就继续循环
        //之前fread后指针已经到了HEADER_SIZE的末尾
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(buffer), 1, output); //调取buffer中的内容
    }

    // Close files
    fclose(input);
    fclose(output);
}