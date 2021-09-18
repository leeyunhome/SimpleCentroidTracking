//#pragma once
#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

typedef struct _DICTIONARY
{
	char* key;
	void* value;
	struct _DICTIONARY* link;
}_dictionary;

typedef struct DICTIONARY
{
	int count;
	struct _DICTIONARY* head;
}dictionary;

void print_dictionary(dictionary dic);
int add_data_to_dictionary(dictionary* head, char* key, void* value);
void init_dictionary(dictionary* dic);
#endif // __DICTIONARY_H__