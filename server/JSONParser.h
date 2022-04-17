#ifndef JSON_PARSER_H
#define JSON_PARSER_H

typedef struct JSONPrimitive_str_t{
	char *name;
	unsigned short size;
}JSONPrimitive_str_t;

typedef struct JSONData_t{
	JSONPrimitive_str_t property;
	JSONPrimitive_str_t value;
} JSONData_t;


class JSONParser
{
public:
	JSONParser(){}
	void load(char *txt);
	void reset_json_iterator();
private:
	char *json_str;
	char *json_it;
protected:
	void parse_valuePtr(JSONData_t *jd);
	void parse_valuePtr_fast(JSONData_t *jd);
};

#endif
