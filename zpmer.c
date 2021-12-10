#include <stdio.h>
#include <stdlib.h>
#include "zmper.h"

/**
 * 参考
 * https://juejin.cn/post/7016491615023792159
 */

int merge(FILE *f_pic, FILE *f_file, FILE *f_finish) {

	char ch;
	
	while(!(feof(f_pic))) {
		ch = fgetc(f_pic);
		fputc(ch,f_finish);
	}

	fclose(f_pic);

	while(!(feof(f_file))) {
		ch = fgetc(f_file);
		fputc(ch,f_finish);
	}

	fclose(f_file);
	fclose(f_finish);
}

FILE *open(const char *f_name, const char *mode) {
	return fopen(f_name, mode);
}
