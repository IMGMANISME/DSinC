#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct seller
{
    char *ID;
    int price;
}seller;

typedef struct commodity
{
    char *name;
    seller *owner;
}commodity;

void insert();
void search();
void buy();
void sort();
void report();
