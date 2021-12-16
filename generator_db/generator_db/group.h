#pragma once
#include "generator.h"
class group
{
public:
	group(long long int id, long long int max,long long int postov,long long int post_id) : id(id), max(max),postov(postov),post_id(post_id) {};
	~group() { delete osoby_system; };
	std::string to_string() {
		generator generator;
		std::string text = "";

		long long int group_memebers=generator.generate_number(1,(max<30 ? max : 30));
		long long int admins = generator.generate_number(1, group_memebers);
		long long int join_request = generator.generate_number((max < 10 ? 1 : 5), (max < 30 ? max : 30));

		text.append("INSERT INTO mydb.group(group_id,group_name,description) VALUES(\"");
		text.append(std::to_string(id));
		text.append("\",\"");
		text.append(generator.group_name());
		text.append("\",\"");
		text.append(generator.getParagraph(generator.generate_number(1,150)));
		text.append("\");\n");

		//repair
		osoby_system = new long long int[group_memebers];
		for (int i = 0; i < group_memebers; ++i) {
			osoby_system[i] = generator.generate_number(1, max);
			text.append("INSERT INTO group_members VALUES(\"");
			text.append(std::to_string(id));
			text.append("\",\"");
			text.append(std::to_string(osoby_system[i]));
			text.append("\");\n");
		}

		for (int i = 0; i < admins; ++i) {
			text.append("INSERT INTO admins VALUES(\"");
			text.append(std::to_string(id));
			text.append("\",\"");

			text.append(std::to_string(osoby_system[generator.generate_number(0, group_memebers - 1)]));
			text.append("\");\n");
		}

		for (int i = 0; i < join_request; ++i) {
			text.append("INSERT INTO join_request VALUES(\"");
			text.append(std::to_string(id));
			text.append("\",\"");
			text.append(std::to_string(generator.generate_number(1,max)));
			text.append("\");\n");
		}

		for (int i = 0; i < postov; ++i) {
			post_id ++;
			text.append("INSERT INTO post(post_id,user_id,post_date,text,public,group_id) VALUES(\"");
			text.append(std::to_string(post_id));
			text.append("\",\"");
			text.append(std::to_string(osoby_system[generator.generate_number(0, group_memebers - 1)]));
			text.append("\",");
			text.append(date());
			text.append(",\"");
			text.append(generator.getParagraph(generator.generate_number(1, 150)));
			text.append("\",\"");
			text.append(std::to_string(generator.generate_number(0, 1)));
			text.append("\",\"");
			text.append(std::to_string(id));
			text.append("\");\n");

			text.append("INSERT INTO reaction VALUES(\"");
			text.append(std::to_string(post_id));
			text.append("\",\"");
			text.append(std::to_string(osoby_system[generator.generate_number(0, group_memebers - 1)]));
			text.append("\",\"");
			text.append(std::to_string(generator.generate_number(0, 1)));
			text.append("\");\n");

			text.append("INSERT INTO comment VALUES(\"");
			text.append(std::to_string(post_id));
			text.append("\",\"");
			text.append(std::to_string(osoby_system[generator.generate_number(0, group_memebers - 1)]));
			text.append("\",\"");
			text.append(generator.getLine(generator.generate_number(1, 573)));
			text.append("\");\n");
		}
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
	long long int postov;
	long long int post_id;

	long long int* osoby_system;
};

