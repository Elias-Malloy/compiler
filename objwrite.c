#include "objwrite.h"

typedef struct ObjectSymbol {
	// imported, exported, local
	// constant, initialized, uninitialized
	uint32 empty;
} ObjectSymbol;

uint32 writeElf64(ObjectFile *obj) {
	uint32 numSections = 2 + (obj->codeSize && obj->code) + 
		(obj->initializedDataSize && obj->initializedData) + 
		(!!obj->uninitializedDataSize) + 
		(obj->readonlyDataSize && obj->readonlyData); 
		
	// set all fields in header to zero by default
	Elf64_Ehdr header = { 0 };
	// magic number 0x7f E L F
	header.e_ident[EI_MAG0] = ELFMAG0;
	header.e_ident[EI_MAG1] = ELFMAG1;
	header.e_ident[EI_MAG2] = ELFMAG2;
	header.e_ident[EI_MAG3] = ELFMAG3;
	header.e_ident[EI_CLASS] = ELFCLASS64; // use 64 bit 
	header.e_ident[EI_DATA] = ELFDATA2LSB; // use two's complement, little-endian	
	header.e_ident[EI_VERSION] = EV_CURRENT; // use current version of elf
	header.e_ident[EI_OSABI] = ELFOSABI_SYSV; // use system V
	header.e_type = ET_REL; // relocatable object file	
	header.e_machine = EM_X86_64; // target AMD 64 machines
	header.e_version = EV_CURRENT; // current version again for some reason
	header.e_shoff = sizeof(Elf64_Ehdr); // section headers immedietly follow this one
	header.e_ehsize = sizeof(Elf64_Ehdr); // size of this header
	header.e_shentsize = sizeof(Elf64_Shdr); // size of each section header
	header.e_shnum = numSections; // this depends on the details of the submitted object data

	uint8 sectionNames[128]; // excess could be 64 really
	sectionNames[0] = '\0';
	uint32 sectionNamesLen = 1;

	Elf64_Shdr *sectionHeaders = calloc(numSections, sizeof(Elf64_Shdr));
	if (sectionHeaders == NULL) {
		printf("Error out of memory\n");
		return 1;
	}
	uint32 i = 1; // sectionHeaders[0] is left empty
	uint64 offset = sizeof(Elf64_Ehdr) + numSections * sizeof(Elf64_Shdr);
	if (obj->codeSize != 0 && obj->code != NULL) {
		sectionHeaders[i].sh_name = sectionNamesLen;
		sectionHeaders[i].sh_type = SHT_PROGBITS;
		sectionHeaders[i].sh_flags = SHF_ALLOC | SHF_EXECINSTR;
		sectionHeaders[i].sh_offset = offset;
		sectionHeaders[i].sh_size = obj->codeSize;
		sectionHeaders[i].sh_addralign = 1;
		strcpy(sectionNames + sectionNamesLen, ".text");
		sectionNamesLen += 6;
		offset += obj->codeSize;
		i++;
	}

	if (obj->initializedDataSize != 0 && obj->initializedData != NULL) {
		sectionHeaders[i].sh_name = sectionNamesLen;
		sectionHeaders[i].sh_type = SHT_PROGBITS;
		sectionHeaders[i].sh_flags = SHF_ALLOC | SHF_WRITE;
		sectionHeaders[i].sh_offset = offset;
		sectionHeaders[i].sh_size = obj->initializedDataSize;
		sectionHeaders[i].sh_addralign = 1;
		strcpy(sectionNames + sectionNamesLen, ".data");
		sectionNamesLen += 6;
		offset += obj->initializedDataSize;
		i++;
	}

	if (obj->uninitializedDataSize != 0) {
		sectionHeaders[i].sh_name = sectionNamesLen;
		sectionHeaders[i].sh_type = SHT_NOBITS;
		sectionHeaders[i].sh_size = obj->uninitializedDataSize;
		sectionHeaders[i].sh_addralign = 1;
		strcpy(sectionNames + sectionNamesLen, ".bss");
		sectionNamesLen += 5;
		i++;
	}

	if (obj->readonlyDataSize != 0 && obj->readonlyData != NULL) {
		sectionHeaders[i].sh_name = sectionNamesLen;
		sectionHeaders[i].sh_type = SHT_PROGBITS;
		sectionHeaders[i].sh_flags = SHF_ALLOC;
		sectionHeaders[i].sh_offset = offset;
		sectionHeaders[i].sh_size = obj->readonlyDataSize;
		sectionHeaders[i].sh_addralign = 1;
		strcpy(sectionNames + sectionNamesLen, ".rodata");
		sectionNamesLen += 8;
		offset += obj->readonlyDataSize;
		i++;
	}

	if (0) {
		sectionHeaders[i].sh_name = sectionNamesLen;
		sectionHeaders[i].sh_type = SHT_SYMTAB;
		sectionHeaders[i].sh_offset = offset;
		sectionHeaders[i].sh_size = 0; // TODO symbol table size
		sectionHeaders[i].sh_addralign = 1;
		strcpy(sectionNames + sectionNamesLen, ".symtab");
		sectionNamesLen += 8;
		i++;
	}

	if (0) {
		sectionHeaders[i].sh_name = sectionNamesLen;
		sectionHeaders[i].sh_type = SHT_STRTAB;
		sectionHeaders[i].sh_offset = offset;
		sectionHeaders[i].sh_size = 0; // TODO string table size
		sectionHeaders[i].sh_addralign = 1;
		strcpy(sectionNames + sectionNamesLen, ".strtab");
		sectionNamesLen += 8;
		i++;
	}

	// always gotta have the section header string table	
	sectionHeaders[i].sh_name = sectionNamesLen;
	sectionHeaders[i].sh_type = SHT_STRTAB;
	sectionHeaders[i].sh_offset = offset;
	strcpy(sectionNames + sectionNamesLen, ".shstrtab");
	sectionNamesLen += 10;
	sectionHeaders[i].sh_size = sectionNamesLen;
	sectionHeaders[i].sh_addralign = 1;

	header.e_shstrndx = i; // set section header string table index

	FILE *fp = fopen(obj->filename, "wb");
	if (fp == NULL) {
		printf("File open failed for %s\n", obj->filename);
		free(sectionHeaders);
		return 1;
	}
	// this is filled with 64 bytes of zeros (I'm gonna use these to pad for alignment eventually)
	//uint8 *zero = &sectionHeaders[0]; // its a good place to get zeros
	fwrite(&header, 1, sizeof(Elf64_Ehdr), fp);
	fwrite(sectionHeaders, sizeof(Elf64_Shdr), numSections, fp);
	if (obj->codeSize != 0 && obj->code != NULL) {
		fwrite(obj->code, 1, obj->codeSize, fp);	
	}
	if (obj->initializedDataSize != 0 && obj->initializedData != NULL) {
		fwrite(obj->initializedData, 1, obj->initializedDataSize, fp);
	}
	if (obj->readonlyDataSize != 0 && obj->readonlyData != NULL) {
		fwrite(obj->readonlyData, 1, obj->readonlyDataSize, fp);
	}
	fwrite(sectionNames, 1, sectionNamesLen, fp);

	free(sectionHeaders);
	fclose(fp);
	return 0;
}
