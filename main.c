# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>



typedef struct DatabaseRecords
{
	char fieldName[11];		// 0 - 10
	char fieldType;			// 11
	uint8_t reservedf[4];		// 12 - 15
	uint8_t fieldLength;		// 16
	uint8_t fieldDecimal;		// 17
	uint16_t waid;			// 18 - 19
	uint8_t example;		// 20
	uint8_t reserveds[10];		// 21 - 30
	uint8_t mdxflag;		// 31
} dbr;

/* DatabaseRecords (dbr)
 *
 * FIELDNAME: 		field name in ASCII
 *
 * FIELDTYPE: 		allowed:
 * 				C: character
 * 				D: date YYYYMMDD
 * 				F: floating point
 * 				L: logical Y, y, N, n, T, t, F, f, ? (when uninitialized)
 *				M: memo, any ASCII text
 * 				N: numeric
 *
 * FIELDLENGHT: 	in binary max 254 / 0xfe
 *
 * FIELDDECIMAL:	count in binary
 *
 * WAID:		working area id
 *
 * MDXFLAG:		field has an index tag in production MDX file
*/

typedef struct FieldDescriptorArray
{
	uint8_t vdbase;			// 0
	uint8_t date[3];		// 1 - 3
	uint32_t recordsdb;		// 4 - 7
	uint16_t headerb;		// 8 - 9
	uint16_t recordb;		// 10 - 11
	uint8_t reservedf[2];		// 12 - 13	perche` non unit16_t
	uint8_t transaction;		// 14
	uint8_t eflag;			// 15
	uint8_t reserveds[12];		// 16 - 27
	uint8_t mdxflag;		// 28
	uint8_t driverid;		// 29
	uint8_t reservedt[2];		// 30 - 31	perche` non unit16_t
	//dbr fd;				// 32 - n
	//uint8_t end;			// n + 1
} fda;

/* FieldDescriptorArray (fda)
 *
 * VDBASE:
 * 0 - 2: version number
 * 3	: presence of dBASE for DOS memo file
 * 4 - 6: presence of SQL table
 * 7	: presence of memo file
 *
 * DATE: 	YYMMDD since 1900
 *
 * RECORDSDB: 	number of records in db file
 *
 * HEADERB:	number of bites in header
 *
 * RECORDB:	number of bites in record
 *
 * TRANSACTION:	incomplete transaction
 *
 * EFLAG: 	encryption flag
 *
 * MDXFLAG:	production .mdx file flag
 *
 * DRIVERID:	language driver id
 *
 * END:		0x0d
*/


void printchars(char *, uint8_t *, int);
void print_header(fda *);


int main(int argc, char *argv[])
{
	fda mainfda;
	dbr firstdbr;

	if (argc < 2)
	{
		fprintf(stderr, "Missing required argument.\n"
			"Usage: %s bin_file \n\n", argv[0]);
		exit(1);
	}

	FILE *f = fopen(argv[1], "rb");

 	fread(&mainfda, sizeof(fda), 1, f);
	fread(&firstdbr, sizeof(dbr), 1, f);

	fclose(f);

	print_fda(&mainfda);
	print_dbr(&firstdbr);

	return 0;
}

void print_fda(fda *datas)
{
	printf("vdbase:\t%b\n", datas->vdbase);
	printchars("date:\t", datas->date, sizeof(datas->date));
	printf("recordsdb:\t%d\n", datas->recordsdb, sizeof(datas->recordsdb));
	printf("headerb:\t%d\n", datas->headerb);
	printf("recordb:\t%d\n", datas->recordb);
	printchars("reservedf:\t", datas->reservedf, sizeof(datas->reservedf));
	printf("transaction:\t%x\n", datas->transaction);
	printf("eflag:\t%x\n", datas->eflag);
	printchars("reserveds:\t", datas->reserveds, sizeof(datas->reserveds));
	printf("mdxflag:\t%x\n", datas->mdxflag);
	printf("driverid:\t%x\n", datas->driverid);
	printchars("reservedt:\t", datas->reservedt, sizeof(datas->reservedt));
}

void print_dbr(dbr *datas)
{
	printf("fd->fieldName\t%s\n", temp->fieldName);
	printf("fd->fieldType\t%c\n", temp->fieldType);
	printchars("fd->reservedf\t", temp->reservedf, sizeof(temp->reservedf));
	printf("fd->fieldLength\t%x\n", temp->fieldLength);
	printf("fd->fieldDec\t%x\n", temp->fieldDecimal);
	printf("fd->waid\t%x\n", temp->waid);
	printf("fd->example\t%x\n", temp->example);
	printchars("fd->reserveds\t", temp->reserveds, sizeof(temp->reserveds));
	printf("fd->mdxflag\t%x\n", temp->mdxflag);
	printf("end:\t%x\n", datas->end);
}



void printchars(char * text, uint8_t *c, int size)
{
	printf("%s", text);
	for(int i = 0; i < size - 1; i++)
		printf("%x, ", *c++);
	printf("%x\n", *c);
}



