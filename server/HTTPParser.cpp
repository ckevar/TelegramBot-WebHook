#include "HTTPParser.h"
#include <cstring>

#include <iostream>

void HTTPParser::load(char *msg){
	http = msg;
	http_it = msg;
}

void HTTPParser::reset_http_iterator(){
	http_it = http;
}

void HTTPParser::lookup_method(){
	RESTMethod = -1;
	if(memcmp(http_it, HTTP_METHOD_GET_STR, HTTP_METHOD_GET_LEN) == 0) {
		http_it += HTTP_METHOD_GET_LEN + 1; 	// +1, to skip the ' ' (space)
                RESTMethod = HTTP_METHOD_GET;
		return;
	}
        else if (memcmp(http_it, HTTP_METHOD_POST_STR, HTTP_METHOD_POST_LEN) == 0){
		http_it += HTTP_METHOD_POST_LEN + 1; 	// +1, to skip the ' ' (space)
		RESTMethod = HTTP_METHOD_POST;
		return;
	}
        else if (memcmp(http_it, HTTP_METHOD_PUT_STR, HTTP_METHOD_PUT_LEN) == 0) {
		http_it += HTTP_METHOD_PUT_LEN + 1; 	// +1, to skip the ' ' (space)
                RESTMethod = HTTP_METHOD_PUT;
		return;
	}
        else if (memcmp(http_it, HTTP_METHOD_DELETE_STR, HTTP_METHOD_DELETE_LEN) == 0) {
		http_it += HTTP_METHOD_DELETE_LEN + 1; 	// +1, to skip the ' ' (space)
		RESTMethod = HTTP_METHOD_DELETE;
		return;
	}
	else if (memcmp(http_it, HTTP_HTTP_1_1_STR, HTTP_HTTP_1_1_LEN) == 0) {
		http_it += HTTP_HTTP_1_1_LEN + 1; 	// +1, to skip the ' ' (space)
		RESTMethod = HTTP_METHOD_NONE;
		return;
	}
}

void HTTPParser::locate_resource_ptr() {
	// catch the resource
	resource.resource = http_it;
	resource.size = 0;
	while(*http_it != ' ') {
		http_it++;
		resource.size++;
	}

	// Finish the first line
	while(*http_it != '\n') http_it++;
}

void HTTPParser::lookup_HeaderFields(){
	ContentLength = 0;
	while(*http_it) {
		// Extract Content Length
		if(memcmp(http_it, HTTP_CONTENT_LENGTH_STR, HTTP_CONTENT_LENGTH_LEN) == 0) {
			http_it += HTTP_CONTENT_LENGTH_LEN;
			while(*http_it != '\r') {
				ContentLength = ContentLength * 10 + *http_it - 48;
				http_it++;
			}
			return;
		}

		// TODO: Extract other header fields
		http_it++;
	}
}

void HTTPParser::locate_Content(){
	while(*http_it){
		if(memcmp(http_it, "\r\n\r\n", 4) == 0){
			http_it += 4;
			Content = http_it;
		}
		http_it++;
	}
}

char HTTPParser::parse(){
	std::cout << "MSG[:" << http << std::endl;
	// Get REST Method
	lookup_method();
	if(RESTMethod < 0) return -1;

	// Locate Resource
	locate_resource_ptr();

	// Lookup and Locate Header Fields
	lookup_HeaderFields();

	// Locate Content
	locate_Content();

	// Reset http iterator
	http_it = http;
	return 0;
}
