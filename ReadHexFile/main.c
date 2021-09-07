/*******************************************************************************
 * Include
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define uint8_t unsigned char




typedef enum
{
	START_CODE  = 0U, /* Start code */
	BYTE_COUNT  = 1U, /*  Byte count */
	ADDRESS     = 2U, /*  Address */
	RECORD_TYPE = 3U, /* Record type */
	DATA        = 4U, /* Data */
	CHECKSUM    = 5U, /* Checksum */
	DONE        = 6U  /* work is done */
} FieldHexFiles;



typedef enum
{
	READ_SUCCESSFULLY = 0U,
	READ_FAILED
} StatusReadHexFile;



typedef struct{
    uint8_t u8ByteCount;
    uint8_t u8Addr[2];
    uint8_t u8RecordType;
    uint8_t u8Data[16];
    uint8_t u8CheckSum;
}HexFormData;



char Readline(FILE *fp, char *buffer);
void ConvertStringToHex(char *buff, int u32length);
StatusReadHexFile ReadAllLine(FILE *fp, char *pBufferData);
char cBufferData[50];
int cInternalBufferData[50];

HexFormData hexStruct;
FILE *fp;

int main(int argc, char *argv[])
{
    fp = fopen ("C:\\Users\\tiennh3\\Desktop\\ReadHexFile\\ReadHexFile\\GPIO.hex", "r+");
    if (fp == NULL)
    {
        printf ("FAIL TO OPEN FILE\n");
    }
    else
    {
       if (READ_SUCCESSFULLY == ReadAllLine(fp, cBufferData))
       {
             printf ("DONE");
       }
       else
       {
            printf ("FALSE");
       }
    }
    fclose(fp);
}



StatusReadHexFile ReadAllLine(FILE *fp, char *pBufferData)
{
    uint8_t u8CaculChecksum;
    FieldHexFiles State;
    int u32Count = 0U;
    int u32DataCount = 0U;
    int cntLine = 0;
    while((Readline(fp, pBufferData)) != 0U)
    {
        for (u32DataCount = 0; u32DataCount < 16U; u32DataCount++)
        {
            hexStruct.u8Data[u32DataCount] = 0U;
        }
        cntLine++;
        State = START_CODE;
        for (u32Count = 0; u32Count < strlen(cBufferData); u32Count++)
        {
            switch(State)
            {
                case START_CODE:
                {
                    if(cBufferData[u32Count] != ':')
                    {
                       return READ_FAILED;
                    }
                    else
                    {
                       State = BYTE_COUNT;
                    }
                    break;
                }
                case BYTE_COUNT:
                {
                    ConvertStringToHex(&cBufferData[u32Count], 2U);
                    hexStruct.u8ByteCount = cInternalBufferData[0];
                    u32Count = 2U;
                    State = ADDRESS;
                    break;
                }
                case ADDRESS:
                {
                    ConvertStringToHex(&cBufferData[u32Count], 4U);
                    hexStruct.u8Addr[0] = cInternalBufferData[0];
                    hexStruct.u8Addr[1] = cInternalBufferData[1];
                    u32Count = 6U;
                    State = RECORD_TYPE;
                    break;
                }
                case RECORD_TYPE:
                {
                    ConvertStringToHex(&cBufferData[u32Count], 2U);
                    hexStruct.u8RecordType = cInternalBufferData[0];
                    u32Count = 8U;
                    State = DATA;
                    break;
                }
                case DATA:
                {
                    ConvertStringToHex(&cBufferData[u32Count], (hexStruct.u8ByteCount*2U));
                    for (u32DataCount = 0; u32DataCount < hexStruct.u8ByteCount; u32DataCount++)
                    {
                        hexStruct.u8Data[u32DataCount] = cInternalBufferData[u32DataCount];
                        if(hexStruct.u8RecordType == 0x00U)
                        {
                           printf("-%x",hexStruct.u8Data[u32DataCount] );
                        }
                    }
                    printf("\n");
                    u32Count = 8U + (hexStruct.u8ByteCount*2U);
                    State = CHECKSUM;
                    break;
                }
                case CHECKSUM:
                {
                    ConvertStringToHex(&cBufferData[u32Count], 2U);
                    hexStruct.u8CheckSum = cInternalBufferData[0];
                    State = DONE;
                    break;
                }
                case DONE:
                {
                    u8CaculChecksum = hexStruct.u8ByteCount + hexStruct.u8Addr[0] + hexStruct.u8Addr[1] + hexStruct.u8RecordType;

                    for (u32DataCount = 0; u32DataCount < hexStruct.u8ByteCount; u32DataCount++)
                    {
                        u8CaculChecksum = u8CaculChecksum + hexStruct.u8Data[u32DataCount];
                    }

                    u8CaculChecksum = ~u8CaculChecksum + 1U;
                    cntLine = u8CaculChecksum;
                    if (u8CaculChecksum == hexStruct.u8CheckSum )
                    {
                        /* Work successfully*/
                        if(hexStruct.u8RecordType == 0x01)
                        {
                           /* End Of File */
                           return READ_SUCCESSFULLY;
                        }
                    }
                    else
                    {
                        return READ_FAILED;
                    }
                    break;
                }
                default:
                {
                     return READ_FAILED;
                     break;
                }
           }
       }
    }

    return READ_SUCCESSFULLY;
}
char Readline(FILE *fp, char *pBufferData)
{
    int u32Count = 0U;
    char cDataLine;

    while((cDataLine = fgetc(fp)) != '\n')
    {
        pBufferData[u32Count] = cDataLine;
        u32Count++;
    }
    if (cDataLine == NULL)
    {
        return 0;
    }

    return 1;
}
void ConvertStringToHex(char *buff, int u32length)
{
    int u32Count = 0U;
    int u32Count1 = 0U;
    int tempBuffer[100];

    for(u32Count = 0U; u32Count < u32length; u32Count++)
    {
        if(buff[u32Count] >= '0' && buff[u32Count] <= '9')
        {
            tempBuffer[u32Count] = buff[u32Count] - 48;
        }
        else if(buff[u32Count] >= 'A' && buff[u32Count] <= 'F')
        {
            tempBuffer[u32Count] = buff[u32Count] - 65 + 10;
        }
        else
        {
           return;
        }

        if(u32Count %2 != 0)
        {
            cInternalBufferData[u32Count1] = ((tempBuffer[u32Count - 1] << 4) | (tempBuffer[u32Count]));
            u32Count1++;
        }
    }
}
