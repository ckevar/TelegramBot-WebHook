#ifndef JSON_PARSER_H
#define JSON_PARSER_H

class JSONParser
{
public:
	
};

short json_parse_valuePtr(char *json, char *key, unsigned short key_len, char **val);
char *json_parse_valuePtr_fast(char *json, char *key, unsigned short key_len);

#endif
