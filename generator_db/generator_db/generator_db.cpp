#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "generator.h"
#include "conversation.h"
#include "group.h"
#include "notification.h"
#include "person.h"
#include "post.h"

#define FILE_CESTA "script/"
#define FILE_NAZOV "generated_script.sql"

#define POCET_OSOB 100
#define POCET_SKUPIN 10
#define POCET_KONVERZACII 50
#define POCET_NOTIFIKACII 700
#define POCET_POSTOV 450

std::string script = "";

void create_person(long long int id) {
	person* object = new person(id, POCET_OSOB);
	script.append(object->to_string());
	script.append("\n");
	//delete object;
}

void create_group(long long int id, long long int pocet_postov, long long int post_id) {
	group* object = new group(id, POCET_OSOB, pocet_postov, post_id);
	script.append(object->to_string());
	script.append("\n");
	//delete object;
}

void create_conversation(long long int id, int m_pocet) {
	generator generator;
	conversation* object = new conversation(id, POCET_OSOB, m_pocet);
	script.append(object->to_string());
	script.append("\n");
	//delete object;
}

void create_notification() {
	notification* object = new notification(POCET_OSOB);
	script.append(object->to_string());
	script.append("\n");
	//delete object;
}

/*
* <summary>V pripade ak nieje post pre skupinu tak id_skupina -1</summary>
*/
void create_post(long long int id, long long int id_skupina) {
	post* object = new post(id, POCET_OSOB);
	script.append(object->to_string());
	script.append("\n");
	//delete object;
}

void save_to_file(std::string text) {
	std::string file_;
	file_.append(FILE_CESTA);
	file_.append(FILE_NAZOV);
	std::ofstream out(file_);
	out << text;
	out.close();
}

int main()
{
	generator generator;

	std::cout << "Vytvaram osoby" << std::endl;
	//script.append("\*Osob*\ \n");
	for (long long int i = 0; i < POCET_OSOB; ++i) {
		create_person(i + 1);
	}

	std::cout << "Vytvaram priatelstva" << std::endl;
	//script.append("\*Priatelstva*\ \n");
	for (long long int i = 0; i < generator.generate_number(1, POCET_OSOB); ++i) {
		script.append("INSERT INTO friends VALUES(\"");
		script.append(std::to_string(generator.generate_number(1, POCET_OSOB)));
		script.append("\",\"");
		script.append(std::to_string(generator.generate_number(1, POCET_OSOB)));
		script.append("\");\n");
	}
	script.append("\n");

	std::cout << "Vytvaram konverzacie" << std::endl;
	//script.append("\*Konverzacie*\ \n");
	for (long long int i = 0; i < POCET_KONVERZACII; ++i) {
		int tmp = generator.generate_number(1, 10);
		create_conversation(i + 1,tmp);
	}

	std::cout << "Vytvaram posty" << std::endl;
	//script.append("\*Posty*\ \n");
	for (long long int i = 0; i < POCET_POSTOV; ++i) {
		create_post(i + 1, -1);
	}

	std::cout << "Vytvaram skupiny" << std::endl;
	int post_id = POCET_POSTOV;
	//script.append("\*Skupiny*\ \n");
	for (long long int i = 0; i < POCET_SKUPIN; ++i) {
		int tmp = generator.generate_number(1, 10);
		create_group(i + 1,tmp,post_id);
		post_id += tmp;
	}

	std::cout << "Vytvaram notifikacie" << std::endl;
	//script.append("\*Notifikacie*\ \n");
	for (long long int i = 0; i < POCET_NOTIFIKACII; ++i) {
		create_notification();
	}

	save_to_file(script);

	return 0;
}

