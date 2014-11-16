#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "symbol.h"

/** @file symbol.c
 *  @brief You will modify this file and implement nine functions
 *  @details Your implementation of the functions defined in symbol.h.
 *  You may add other functions if you find it helpful. Added functions
 *  should be declared <b>static</b> to indicate they are only used
 *  within this file. The reference implementation added approximately
 *  90 lines of code to this file. This count includes lines containing
 *  only a single closing bracket (}).
 * <p>
 * @author <b>Your name</b> goes here
 */

/** size of LC3 memory */
#define LC3_MEMORY_SIZE  65536

/** Provide prototype for strdup() */
char *strdup(const char *s);

/** defines data structure used to store nodes in hash table */
typedef struct node {
  symbol_t     symbol;   /**< the data the user is interested in   */
  int          hash;     /**< hash value - makes searching faster  */
  struct node* next;     /**< linked list of symbols at same index */
} node_t;

/** defines the data structure for the hash table */
struct sym_table {
  node_t*  hash_table[SYMBOL_SIZE]; /**< head of linked list for this index */
  char**   addr_table;              /**< look up symbols by addr            */
};

/** djb hash - found at http://www.cse.yorku.ca/~oz/hash.html
 * tolower() call to make case insensitive.
 */

static int symbol_hash (const char* name) {
  unsigned char* str  = (unsigned char*) name;
  unsigned long  hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + tolower(c); /* hash * 33 + c */

  c = hash & 0x7FFFFFFF; /* keep 31 bits - avoid negative values */

  return c;
}

/** @todo implement this function */
sym_table_t* symbol_init (int lookup_by_addr) {
  struct sym_table *new_sym_table = malloc(sizeof(struct sym_table));
  for(int j = 0 ; j < SYMBOL_SIZE; j++) {
    struct node *newNode = malloc(sizeof(struct node));
    newNode = NULL;
    new_sym_table->hash_table[j] = newNode;
  }
  //  sym_table new_sym_table = {NULL,NULL};
  if (lookup_by_addr != 0) {
    new_sym_table->addr_table = malloc(sizeof(char*) * SYMBOL_SIZE);
    for(int j = 0; j < SYMBOL_SIZE; j++) {
      new_sym_table->addr_table[j] = malloc(sizeof(char*));
    }
    //allocate and initialize an array of char * (addr_table)
  }  
  return new_sym_table;
}

/** @todo implement this function */
void symbol_term (sym_table_t* symTab) {
  symbol_reset(symTab);
  free(symTab->addr_table);
  free(symTab);
}

/** @todo implement this function */
void symbol_reset(sym_table_t* symTab) {

 for(int j = 0; j < SYMBOL_SIZE;j++) {
    while(symTab->hash_table[j] != NULL) {
      int addr = symTab->hash_table[j]->symbol.addr;
      if(addr < SYMBOL_SIZE) {
        free(symTab->addr_table[addr]);
      }
      free(symTab->hash_table[j]->symbol.name);
      symTab->hash_table[j] = symTab->hash_table[j]->next;
    }
  }
}

/** @todo implement this function */
int symbol_add (sym_table_t* symTab, const char* name, int addr) {
  int hash;
  int index;
  char* cpyName = (char *) name;
  if(symbol_search(symTab, name, &hash, &index) == NULL) {
    node_t *newNode = malloc(sizeof(struct node));
    struct symbol *newSymbol = malloc(sizeof(struct symbol));
    newSymbol->name = malloc(sizeof(char *));
    strcpy(newSymbol->name, cpyName);
    newSymbol->addr = addr;
    newNode->symbol = *newSymbol;
    newNode->hash = symbol_hash(cpyName);
    int newIndex = symbol_hash(cpyName) % SYMBOL_SIZE;
    newNode->next = symTab->hash_table[newIndex];
    symTab->hash_table[newIndex] = newNode;
    if(addr < SYMBOL_SIZE) {
      strcpy(symTab->addr_table[addr], cpyName);
    }
    return 1;
  } else {
    return 0;
  }
}

/** @todo implement this function */
struct node* symbol_search (sym_table_t* symTab, const char* name, int* hash, int* index) {
  *hash = symbol_hash(name);
  *index = *hash % SYMBOL_SIZE;
 // printf("%d\n",*index);

  if(symTab->hash_table[*index] == NULL) {
    return NULL;
  } else {
   // printf("symTab->hash_table[index]->symbol.name = %s \n",symTab->hash_table[*index]->symbol.name);
    node_t *tmpNode = malloc(sizeof(node_t));
    tmpNode = symTab->hash_table[*index];
    while(tmpNode != NULL) {
      symbol_t *tmpSymbol = malloc(sizeof(symbol_t));
      *tmpSymbol = tmpNode->symbol;
      // printf("hash %d \n", *hash);
      // printf("tmpNode->hash %d \n", tmpNode->hash);
      if (tmpNode->hash == *hash) {
        // printf("tmpNode->hash == *hash\n");
        // printf("tmpSymbol->name = %s \n", tmpSymbol->name);
        // printf("tmpSymbol->addr = %d \n", tmpSymbol->addr);
        if (strcasecmp(tmpNode->symbol.name, name) == 0) {
          return tmpNode;
        }
      } 
      free(tmpSymbol);
      tmpNode = tmpNode->next;
    }
    free(tmpNode);
   // printf("not null\n");
  }
  return NULL;
}

/** @todo implement this function */
symbol_t* symbol_find_by_name (sym_table_t* symTab, const char* name) {
  int hash;
  int index;
  node_t *tmpNode = malloc(sizeof(node_t));
  tmpNode = symbol_search(symTab, name, &hash, &index);
  if(tmpNode != NULL) {
    symbol_t *tmpSymbol = malloc(sizeof(symbol_t));
    *tmpSymbol = tmpNode->symbol;
    return tmpSymbol;
  }
  return NULL;
}

/** @todo implement this function */
char* symbol_find_by_addr (sym_table_t* symTab, int addr) {
  if (addr >= SYMBOL_SIZE) {
    return NULL;
  }
  if(strcasecmp(symTab->addr_table[addr], "") != 0) {
    return symTab->addr_table[addr];
  }
  return NULL;
}

/** @todo implement this function */
void symbol_iterate (sym_table_t* symTab, iterate_fnc_t fnc, void* data) {
  for(int j = 0; j < SYMBOL_SIZE;j++) {
    node_t *tmpNode = malloc(sizeof(node_t));
    tmpNode = symTab->hash_table[j];
    while(tmpNode != NULL) {
      symbol_t tmpSymbol = tmpNode->symbol;
      (*fnc)(&tmpSymbol, data);
      tmpNode = tmpNode->next;
    }
    free(tmpNode);
  }
}

