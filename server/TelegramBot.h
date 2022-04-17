#ifndef TELEGRAM_BOT_H
#define TELEGRAM_BOT_H

#include "JSONParser.h"

/* JSON PROPERTIES */
#define TBOT_UPDATE_ID_STR 	"\"update_id\""
#define TBOT_UPDATE_ID_LEN 	11

#define TBOT_MESSAGE_STR  	"\"message\""
#define TBOT_MESSAGE_LEN  	9

#define TBOT_MESSAGE_ID_STR 	"\"message_id\""
#define TBOT_MESSAGE_ID_LEN 	12

#define TBOT_CHAT_STR 		"\"chat\""
#define TBOT_CHAT_LEN 		6

#define TBOT_CHAT_ID_STR 	"\"id\""
#define TBOT_CHAT_ID_LEN 	4

#define TBOT_TEXT_STR 		"\"text\""
#define TBOT_TEXT_LEN 		6


class TelegramBot : public JSONParser
{
public:
	// Contructors
	TelegramBot();
	~TelegramBot();
	// Methods
	char parse();

	// Properties
	JSONData_t *update_id;
	JSONData_t *message_id;
	JSONData_t *chat_id;
	JSONData_t *text;
private:
	// Properties
	JSONData_t *message;
	JSONData_t *chat;
	// Methods
};
#endif
