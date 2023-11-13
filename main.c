# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>

typedef struct DatabaseRecords
{
	char fieldName[11];		// 0 - 10
	uint8_t fieldType;		// 11
	uint8_t reservedf[4];		// 12 - 15
	uint8_t fieldLength;		// 16
	uint8_t fieldDecimal;		// 17
	uint8_t waid;			// 18 - 19
	uint8_t example;		// 20
	uint8_t reserveds[10];		// 21 - 30
	uint8_t mdxflag;		// 31
} dbr;

typedef struct FieldDescriptorArray
{
	uint8_t vdbase;			// 0
	uint8_t open[3];		// 1 - 3
	uint32_t recordsdb;		// 4 - 7
	uint16_t headerb;		// 8 - 9
	uint16_t recordb;		// 10 - 11
	uint8_t reservedf[2];		// 12 - 13
	uint8_t transaction;		// 14
	uint8_t encryptionflag;		// 15
	uint8_t reserveds[12];		// 16 - 27
	uint8_t mdxflag;		// 28
	uint8_t driverid;		// 29
	uint8_t reservedt[2];		// 30 - 31
	dbr *fd;			// 32 - n
	uint8_t end;			// n + 1
} fda;

void printchars(char *, uint8_t *, int);
void print_header(fda *);


int main(int argc, char *argv[])
{
	fda mainfda;

	if (argc < 2)
	{
		fprintf(stderr, "Missing required argument.\n"
			"Usage: %s bin_file \n\n", argv[0]);
		exit(1);
	}

	FILE *f = fopen(argv[1], "rb");

 	fread(&mainfda, sizeof(fda), 1, f);
	fclose(f);

	print_header(&mainfda);

	return 0;
}

void print_header(fda *datas)
{
	printf("vdbase:\t%x\n", datas->vdbase);
	printchars("open:\t", datas->open, sizeof(datas->open));
	printf("recordsdb:\t%d\n", datas->recordsdb, sizeof(datas->recordsdb));
	printf("headerb:\t%d\n", datas->headerb);
	printf("recordb:\t%d\n", datas->recordb);
	printchars("reservedf:\t", datas->reservedf, sizeof(datas->reservedf));
	printf("transaction:\t%x\n", datas->transaction);
	printf("encryptionflag:\t%x\n", datas->encryptionflag);
	printchars("reserveds:\t", datas->reserveds, sizeof(datas->reserveds));
	printf("mdxflag:\t%x\n", datas->mdxflag);
	printf("driverid:\t%x\n", datas->driverid);
	printchars("reservedt:\t", datas->reservedt, sizeof(datas->reservedt));

	printf("end:\t%x\n", datas->end);
}

void printchars(char * text, uint8_t *c, int size)
{
	printf("%s", text);
	for(int i = 0; i < size - 1; i++)
		printf("%x, ", *c++);
	printf("%x\n", *c);
}



