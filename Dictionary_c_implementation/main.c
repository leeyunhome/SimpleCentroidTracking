#include <stdio.h>
#include "dictionary.h"

int main()
{
	dictionary dic;
	init_dictionary(&dic);

	add_data_to_dictionary(&dic, "key1", "value2");
	add_data_to_dictionary(&dic, "key2", "value1");

	print_dictionary(dic);

	printf("%s\n", (char*)(dic.head->value));

	return 0;
}


