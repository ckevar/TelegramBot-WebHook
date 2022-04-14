
#include "JSONParser.h"


/*
 * This can't parse objeects or arrays. It'll provide the length of the first element found
 * in the array or the object and ignore the remaining ones.
 */
short json_parse_valuePtr(char *json, char *key, unsigned short key_len, char **val)
{
	short val_len;
	while(*json){
		if (memcmp(*key, *json, key_len) == 0){
			json++; // skips ':'
			*val = json;
			val_len = 0;
			while(*json != ','){
				json++;
				val_len++;
			}
			return val_len;
		}
		json++;
	}
	return -1;
}

/*
 * Provides only the address where the key's value is stored. Useful for
 * JSON array and object.
 */
char *json_parse_valuePtr_fast(char *json, char *key, unsigned short key_len){
        while(*json){
                if (memcmp(*key, *json, key_len) == 0){
			json++;	// skip ':'
			return json;
                }
        	json++;
        }
        return -1;
}
