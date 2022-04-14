#ifndef TELEGRAM_BOT_H
#define TELEGRAM_BOT_H

#include "JSONParser.h"

typedef struct TelegramBot_MsgText_t{
	char *text;
	short len;
} TelegramBot_MsgText_t;

class TelegramBot : public JSONParser
{
public:
	// Default Contructor
	TelegramBot(){}

	// Methods
	char parse();

	// Properties
	int update_id;
	int message_id;
	int chat_id;
	TelegramBot_MsgText_t msg;
private:
	// Methods
	void lookup_update_id();
	void lookup_message_id();
	void lookup_char_id();
	void locate_text();
};
#endif
/*
class HTTPParser
{
public:
	HTTPParser(){} // Default contructor
	void load(char *msg);
	char parse();
	void reset_http_iterator();

	// Properties
	char RESTMethod;
	HTTP_Resource_t resource;
	short ContentLength;
	char *Content;

private:
	// Properties
	char *http;
	char *http_it;

	// Methods
	void lookup_method();
	void locate_resource_ptr();
	void lookup_HeaderFields();
	void locate_Content();
};

*/
