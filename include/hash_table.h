#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INITIAL_CAPACITY 10

//ITEM WITH KEY VALUE PAIR
typedef struct {
    char *key;
    char* value;
} ht_item;

//HASH TABLE 
typedef struct {
    ht_item *items;
    size_t capacity;
    size_t length;    
} ht;


//TO CREATE A HASH TABLE
ht* ht_create();

//TO DELETE A HASH TABLE
void ht_delete(ht* table);

//TO INSERT A KEY VALUE PAIR
// Key: str , Value:str
//PASS THE TABLE BY REFERENCE TO INSERT
//RETURNS 0 (SUCCESS)
//RETURNS -1 (FAILURE)
int ht_insert(ht** table, char* key, char* value);

//TO GET THE VALUE USING A KEY
//RETURNS NULL IF KEY IS NOT THERE
//Returns the value on success and NULL on failure
char* ht_get_value(ht* table, char* key);

//TO GET THE INT VALUE OF BINARY STR USING A KEY
//RETURNS -1 IF KEY IS NOT THERE
//Returns the value on success and -1 on failure
int ht_get_int_value(ht* table,char* key);

//TO INSERT A LIST OF HASH TABLE ITEMS IN THE TABLE
// PASS TABLE BY REFERENCE
//NEED TO PASS THE ht_items array and the size of that array
int ht_entry_kvlist(ht** table,ht_item kvitems[],size_t num_items);

#endif 
