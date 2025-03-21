#include "hash_table.h"

ht* ht_create(){
    ht* table = malloc(sizeof(ht));
    if(table == NULL){
        return NULL;
    }

    table->capacity = INITIAL_CAPACITY;
    table->length = 0;
    table->items = calloc(table->capacity, sizeof(ht_item));

    if(table->items == NULL){
        free(table);
        return NULL;
    }

    return table;
}

void ht_delete(ht* table){
    for (size_t i = 0; i < table->capacity; i++) {
        free(table->items[i].key);
        free(table->items[i].value);
    }

    free(table->items);
    free(table);
}

unsigned int get_hash(char* input){
    unsigned int hash = 0;
    unsigned int weight = 31;
    for(size_t i = 0; input[i] != '\0'; i++){
        hash += (input[i] * (weight ^ i));
    }

    return hash;
}

int ht_expand(ht** table) {
    ht* old_table = *table;
    size_t old_capacity = old_table->capacity;

    ht* new_table = malloc(sizeof(ht));
    if (!new_table) {
        return -1;
    }

    new_table->capacity = old_capacity * 2;
    new_table->length = 0;
    new_table->items = calloc(new_table->capacity, sizeof(ht_item));

    if (!new_table->items) {
        free(new_table);
        return -1;
    }

    for (size_t i = 0; i < old_capacity; i++) {
        if (old_table->items[i].key != NULL) {
            ht_insert(&new_table, old_table->items[i].key, old_table->items[i].value);
            free(old_table->items[i].key);
            free(old_table->items[i].value);
        }
    }

    free(old_table->items);
    free(old_table);
    *table = new_table;

    return 0;
}


int ht_insert(ht** table, char* key, char* value){
    if((*table)->length == (*table)->capacity){
        if(ht_expand(table)!=0){
            return -1;
        }
    }

    unsigned int hash_of_key = get_hash(key);
    size_t index = hash_of_key % (*table)->capacity;

    while ((*table)->items[index].key != NULL) { 
        index = (index + 1) % (*table)->capacity;
    }

    (*table)->items[index].key = strdup(key);
    (*table)->items[index].value = strdup(value);

    (*table)->length++;
    return 0;
}

char* ht_get_value(ht* table, char* key){
    unsigned int hash_of_key = get_hash(key);
    size_t index = hash_of_key % table->capacity;

    while (table->items[index].key != NULL) {
        if (strcmp(table->items[index].key, key) == 0) {
            return table->items[index].value;
        }
        index = (index + 1) % table->capacity; 
    }

    return NULL;
}

int ht_get_int_value(ht* table,char* key){
    char* data = NULL;
    unsigned int hash_of_key = get_hash(key);
    size_t index = hash_of_key%(table->capacity);
    
    while(table->items[index].key!=NULL){
        if(strcmp(table->items[index].key,key)==0){
            data = table->items[index].value;
            break;
        }
        index= (index+1) % table->capacity;
    }

    if(data==NULL){
        return -1;
    }

    int data_int = strtol(data,NULL,2);
    free(data);
    return data_int;
}

int ht_entry_kvlist(ht** table,ht_item kvitems[],size_t num_items){
    for(size_t i = 0;i < num_items;i++){
        if(ht_insert(table,kvitems[i].key,kvitems[i].value)!=0){
            return -1;
        };
    }
    return 0;
}