#pragma once
#include "generator.h"
class conversation
{
public:
	conversation(long long int id, long long int n_pocet, int m_pocet) :id(id), n_pocet(n_pocet), m_pocet(m_pocet) {};
	~conversation() { delete id_users; };
	std::string to_string() {
		generator generator;
		long long int pocet_ludi = generator.generate_number(2,(n_pocet<10 ? n_pocet : 10));

		id_users = new long long int[pocet_ludi];

		std::string text = "";
		
		if (generator.generate_number(1, 100) <= 70) {
			text.append("INSERT INTO conversation  VALUES(\"");
			text.append(std::to_string(id));
			text.append("\",\"");
			text.append(generator.conversation_name(generator.generate_number(1,793)));
			text.append("\");\n");
		}
		else {
			text.append("INSERT INTO conversation(id_conversation) VALUES(\"");
			text.append(std::to_string(id));
			text.append("\");\n");
		}

		for (int i = 0; i < pocet_ludi; ++i) {
			id_users[i] = generator.generate_number(1, n_pocet);
		}

		for (int i = 0; i < pocet_ludi; ++i) {
			text.append("INSERT INTO messege_group VALUES(\"");
			text.append(std::to_string(id_users[i]));
			text.append("\",\"");
			text.append(std::to_string(id));
			text.append("\");\n");
		}

		for (int i = 0; i < m_pocet; ++i) {
			text.append("INSERT INTO message(sender_id,id_conversation,text) VALUES(\"");
			text.append(std::to_string(id_users[generator.generate_number(0, pocet_ludi - 1)]));
			text.append("\",\"");
			text.append(std::to_string(id));
			text.append("\",\"");
			text.append(generator.getLine(generator.generate_number(1,573)));
			text.append("\");\n");
		}

		return text;
	};

private:
	long long int id;
	long long int n_pocet;
	int m_pocet;
	long long int* id_users;
};

