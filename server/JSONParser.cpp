
#include "JSONParser.h"
#include <cstring>

#include <iostream>

void JSONParser::load(char *txt){
	json_str = txt;
	json_it = txt;
}

void JSONParser::reset_json_iterator(){
	json_it = json_str;
}

/*
 * This can't parse objeects or arrays. It'll provide the length of the first element found
 * in the array or the object and ignore the remaining ones.
 */
void JSONParser::parse_valuePtr(JSONData_t *jd)
{
	jd->value.size = 0;
	while(*json_it){
		if (memcmp(jd->property.name, json_it, jd->property.size) == 0){
			json_it += jd->property.size + 1; // skips the whole '"<property>":'
			jd->value.name = json_it;
			//std::cout << jd->property.name << '-' << jd->value.name << "END" << std::endl;

			while(*json_it != ',' && *json_it != '}'){
				json_it++;
				jd->value.size++;
			}
			return;
		}
		json_it++;
	}
}

/*
 * Provides only the address where the key's value is stored. Useful for
 * JSON array and object.
 */
void JSONParser::parse_valuePtr_fast(JSONData_t *jd){
        while(*json_it){
                if (memcmp(jd->property.name, json_it, jd->property.size) == 0){
			json_it++;	// skip ':'
			jd->value.name = json_it;
			return;
                }
        	json_it++;
        }
}
