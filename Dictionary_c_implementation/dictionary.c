#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

void init_dictionary(dictionary* dic)
{
	dic->head = NULL;
	dic->count = 0;
}

void print_dictionary(dictionary dic)
{
	_dictionary* temp = dic.head;
	int iter = 0;

	printf("### total count : %d\n", dic.count);

	while (NULL != temp)
	{
		printf("[%d] %s\n", iter, temp->key);
		iter++;
		temp = temp->link;
	}
}

int add_data_to_dictionary(dictionary* head, char* key, void* value)
{
	_dictionary* temp = head->head;

	while (true)
	{
		// 헤드가 비었을 때
		if (head->count == 0)
		{
			temp = (_dictionary*)malloc(sizeof(_dictionary));
			temp->key = key;
			temp->link = NULL;
			head->head = temp;
			break;
		}

		// 현재 노드의 키가 새로 추가하려는 키와 같을 때
		else if (0 == strcmp(temp->key, key))
		{
			return false;
		}

		// 헤드(현재 노드)가 마지막 일 때
		else if (NULL == temp->link)
		{
			temp->link = (_dictionary*)malloc(sizeof(_dictionary));
			temp->link->key = key;
			//printf("%s\n", value);
			temp->link->value = value;
			temp->link->link = NULL;
			break;
		}
		
		// 다음 노드가 존재할 때
		else
		{
			temp = temp->link;
		}
	}
	head->count++;
	return true;
}