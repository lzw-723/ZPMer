#ifndef __ZMPER_H 
#define __ZMPER_H

FILE *open(const char *f_name, const char *mode);
int merge(FILE *f_pic, FILE *f_file, FILE *f_finish);

#endif