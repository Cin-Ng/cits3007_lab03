#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

void fill_buffer(const char *dir, const char *fname, const char *ext,char *path) {

    char dash[] = "/";
    char stop[] = ".";

    strcpy(path, dir);
    strcat(path, dash);
    strcat(path, fname);
    strcat(path, stop);
    strcat(path, ext);

}

bool would_wrap_around(size_t dirlen, size_t filelen, size_t extlen) {

    if((dirlen + filelen) < dirlen || (dirlen + filelen) < filelen ){
        return true;
    }

    size_t eq = dirlen + filelen + extlen;

    if(eq < dirlen || eq < filelen || eq < extlen ){
        return true;
    }

    size_t eq3 = eq + 3;

    if(eq3 < dirlen || eq3 < filelen || eq3 < extlen ){
        return true;
    }

    return false;
}

int main(){

    size_t dirlen = SIZE_MAX - 8; // adding 9 will cause wraparound
    size_t filelen = 3;
    size_t extlen = 3;
    bool res = would_wrap_around(dirlen, filelen, extlen);
    printf("%d\n", res);


    char dir[] = "dddddd";
    size_t dir_len = sizeof(dir);

    char fname[] = "fffffff";
    size_t file_len = sizeof(fname);

    char ext[] = "xxxx";
    size_t ext_len = sizeof(ext);

    //buf = malloc(1<<30);
    size_t size = dir_len + file_len + ext_len + 2 ;

    char *buf = malloc(size);

    fill_buffer(dir,fname,  ext,  buf);

    printf("\n%s\n",buf);

    free(buf);

    return 0;
}