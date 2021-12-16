#pragma once


#include "generator.h"

class person
{
public:
	person(long long int id,long long int max): id(id),max(max) {};
	~person() {};

	std::string to_string() {
		generator generator;
		std::string text = "";
		int pohlavie = generator.generate_number(0, 1);
		std::string name = generator.generate_name(pohlavie,generator.generate_number(1, 1000));
		std::string surname = generator.generate_surname(generator.generate_number(1, 1000));

		name = name.substr(1, name.size() - 1);

		surname[0] = tolower(surname[0]);
		name[0] = tolower(name[0]);

		text.append("INSERT INTO user VALUES(\"");
		text.append(std::to_string(id));
		text.append("\",\"");
		text.append(name);
		text.append(surname);
		text.append("\",\"");
		text.append(name);
		text.append(surname);
		text.append("\");\n");

		surname[0] = toupper(surname[0]);
		name[0] = toupper(name[0]);

		text.append("INSERT INTO user_bio(user_id,city_id) VALUES(\"");
		text.append(std::to_string(id));
		text.append("\",\"");
		text.append(std::to_string(generator.generate_city(generator.generate_number(1,5))));
		text.append("\");\n");

		if (generator.generate_number(1, 100) <= 80) {
			text.append("UPDATE user_bio SET work=\"");
			text.append(generator.generate_work(generator.generate_number(1, 118)));
			text.append("\" WHERE user_id=\"");
			text.append(std::to_string(id));
			text.append("\";\n");
		}

		if (generator.generate_number(1, 100) <= 80) {
			text.append("UPDATE user_bio SET highschool=\"");
			text.append(generator.generate_high_school(generator.generate_number(1, 301)));
			text.append("\" WHERE user_id=\"");
			text.append(std::to_string(id));
			text.append("\";\n");
		}

		if (generator.generate_number(1, 100) <= 80) {
			text.append("UPDATE user_bio SET university=\"");
			text.append(generator.generate_university(generator.generate_number(1, 169)));
			text.append("\" WHERE user_id=\"");
			text.append(std::to_string(id));
			text.append("\";\n");
		}

		text.append("INSERT INTO user_data(user_id,name,surname,email,tel_number,born_date,gender) VALUES(\"");
		text.append(std::to_string(id));
		text.append("\",\"");
		text.append(name);
		text.append("\",\"");
		text.append(surname);
		text.append("\",\"");
		text.append(surname);
		text.append(std::to_string(id));
		text.append("@gmail.com");
		text.append("\",\"");
		text.append(tel_number());
		text.append("\",");
		text.append(borndate());
		text.append(",\"");
		text.append(std::to_string(pohlavie));
		text.append("\");\n");

		return text;
	};

	std::string borndate();
	std::string tel_number();
private:
	long long int id;
	long long int max;
};

std::string person::borndate()
{
	std::string text = "";
	generator gen;
	text.append("STR_TO_DATE(\"");
	text.append(std::to_string(gen.generate_number(1940, 2003)));
	text.append("-");
	text.append(std::to_string(gen.generate_number(1, 12)));
	text.append("-");
	text.append(std::to_string(gen.generate_number(1, 31)));
	text.append("\", '%Y-%m-%d') ");
	return text;
}

inline std::string person::tel_number()
{
	std::string text = "";
	generator gen;
	text.append("09");
	for (int i = 0; i < 8; i++) {
		text.append(std::to_string(gen.generate_number(1,9)));
	}
	return text;
}