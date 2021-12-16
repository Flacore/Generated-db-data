#pragma once
#include "generator.h"
class post
{
public:
	post(long long int id, long long int max) :id(id), max(max) {};
	~post() {};
	std::string to_string() {
		generator generator;
		std::string text = "";

		text.append("INSERT INTO post(post_id,user_id,post_date,text,public) VALUES(\"");
		text.append(std::to_string(id));
		text.append("\",\"");
		text.append(std::to_string(generator.generate_number(1,max)));
		text.append("\",");
		text.append(date());
		text.append(",\"");
		text.append(generator.getParagraph(generator.generate_number(1, 150)));
		text.append("\",\"");
		text.append(std::to_string(generator.generate_number(0, 1)));
		text.append("\");\n");

		text.append("INSERT INTO reaction VALUES(\"");
		text.append(std::to_string(id));
		text.append("\",\"");
		text.append(std::to_string(generator.generate_number(1, max)));
		text.append("\",\"");
		text.append(std::to_string(generator.generate_number(0,1)));
		text.append("\");\n");

		text.append("INSERT INTO comment VALUES(\"");
		text.append(std::to_string(id));
		text.append("\",\"");
		text.append(std::to_string(generator.generate_number(1, max)));
		text.append("\",\"");
		text.append(generator.getLine(generator.generate_number(1,573)));
		text.append("\");\n");

		return text;
	};

	std::string date()
	{
		std::string text = "";
		generator gen;
		text.append("STR_TO_DATE(\"");
		text.append(std::to_string(gen.generate_number(2020, 2021)));
		text.append("-");
		text.append(std::to_string(gen.generate_number(1, 12)));
		text.append("-");
		text.append(std::to_string(gen.generate_number(1, 31)));
		text.append("\", '%Y-%m-%d') ");
		return text;
	}

private:
	long long int id;
	long long int max;
};

