//~ A very tiny Hex Dump utility by Dan Feerst
//~ It is quite sparce and featureless at it is
//~ only a few dozen lines of code. Use regex 
//~ expressions if you need more specific info
 
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
typedef unsigned char BYTE;
long getFileSize(FILE *file)
{
    long lCurPos, lEndPos;
    lCurPos = ftell(file);
    fseek(file, 0, SEEK_END);
    lEndPos = ftell(file);
    fseek(file, lCurPos, 0);
    return lEndPos;
}
 
int main( int argc, char** argv )
{
    if (argv[1] == 0)
        printf( "Specify a binary file.\n");
    else
    {
        const char *filePath = argv[1]; 
        BYTE *fileBuf;         
        FILE *file = NULL; 
        if ((file = fopen(filePath, "rb")) == NULL)
            printf( "Could not open specified file, %s.\n", filePath);
        else
            printf("%s opened successfully.",filePath);
        size_t fileSize = getFileSize(file);
        fileBuf = new BYTE[fileSize];
        fread(fileBuf, fileSize, 1, file);
        unsigned int offset = 0;
        while( offset < fileSize  )
        {         
            printf( "%.8X | ",offset );                                // Offset
            for (size_t i = offset; i < offset + 0x08; i++)
            {  
                printf("%.2X ", fileBuf[i]);                           // byte 1
            }
            printf(" ");
            for (size_t i = offset + 0x08 ; i < offset + 0x10; i++)
                printf("%.2X ", fileBuf[i]);                            // byte 2
            printf("| ");
            for (size_t i = offset; i < offset + 0x10; i++)  
                if( fileBuf[i] >= 0x20 && fileBuf[i] <= 0x7E)
                    printf("%c", fileBuf[i]);                          // char
                else
                    printf(".");
            printf("|\n");
            offset+=0x10;
        }
            std::cin.get();
            delete[]fileBuf;
            fclose(file);
            return 0;
        }
    return 1;
}
