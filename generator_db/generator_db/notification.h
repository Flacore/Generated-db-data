#pragma once
#include "generator.h"
class notification
{
public:
	notification(long long int _users) {
		generator generator;
		users_id = generator.generate_number(1, _users);
		notification_text = generator.generate_notification(generator.generate_number(1, 18));
	};
	~notification() {};
	std::string to_string() {
		std::string text = "INSERT INTO notification VALUES(\"";
		text.append(std::to_string(users_id));
		text.append("\",\"");
		text.append(notification_text);
		text.append("\");\n");
		return text;
	};
private:
	long long int users_id;
	std::string notification_text;
};

