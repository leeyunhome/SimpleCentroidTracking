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
		// ��尡 ����� ��
		if (head->count == 0)
		{
			temp = (_dictionary*)malloc(sizeof(_dictionary));
			temp->key = key;
			temp->link = NULL;
			head->head = temp;
			break;
		}

		// ���� ����� Ű�� ���� �߰��Ϸ��� Ű�� ���� ��
		else if (0 == strcmp(temp->key, key))
		{
			return false;
		}

		// ���(���� ���)�� ������ �� ��
		else if (NULL == temp->link)
		{
			temp->link = (_dictionary*)malloc(sizeof(_dictionary));
			temp->link->key = key;
			//printf("%s\n", value);
			temp->link->value = value;
			temp->link->link = NULL;
			break;
		}
		
		// ���� ��尡 ������ ��
		else
		{
			temp = temp->link;
		}
	}
	head->count++;
	return true;
}