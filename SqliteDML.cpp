/*
 * SqliteDML.cpp
 *
 *  Created on: Feb 10, 2018
 *      Author: khubaib
 */

#include "SqliteDML.h"

using namespace std;

SqliteDML::SqliteDML() {
	// TODO Auto-generated constructor stub
	m_db_handle = NULL;
	m_ret_val = -2;
	m_zErrMsg = 0;
	m_db_name.clear();
	m_sql_cmd.clear();
}

SqliteDML::~SqliteDML() {
	// TODO Auto-generated destructor stub
	sqlite3_close(m_db_handle);
}

int sql_handler(void*, int entry_count, char** args, char** cols) {
	for (int i = 0; i < entry_count; i++) {
		cout << cols[i] << ":\t" << args[i] << endl;
	}
	return 0;
}

void SqliteDML::dropTable(std::string table_name) {

	m_sql_cmd.clear();
	m_sql_cmd += "drop table if exists ";
	m_sql_cmd += table_name;
	m_sql_cmd += ";";

	m_ret_val = sqlite3_exec(m_db_handle, m_sql_cmd.c_str(), NULL, NULL,
			&m_zErrMsg);

	if (m_ret_val)
		exit(0), perror("Cannot read Database");

}

bool SqliteDML::performQuery(std::string query_text){

		m_sql_cmd.clear();
		m_sql_cmd += query_text;

		m_ret_val = sqlite3_exec(m_db_handle, m_sql_cmd.c_str(), sql_handler, NULL,
				&m_zErrMsg);

		if (m_ret_val)
			return(perror("Cannot read Database"), false);
		return true;

}

bool SqliteDML::updateTable(std::string table_name, std::string new_attribs,
		std::string condition) {

	m_sql_cmd.clear();
	m_sql_cmd += "update ";
	m_sql_cmd += table_name;
	m_sql_cmd += " set ";
	m_sql_cmd += new_attribs;
	m_sql_cmd += " where(";
	m_sql_cmd += condition;
	m_sql_cmd += ");";

	m_ret_val = sqlite3_exec(m_db_handle, m_sql_cmd.c_str(), NULL, NULL,
			&m_zErrMsg);

	if (m_ret_val)
		return(perror("Cannot read Database"), false);
	return true;

}

void SqliteDML::conditionalDisplayTable(std::string attrib_name,
		std::string table_name, std::string condition) {

	m_sql_cmd.clear();
	m_sql_cmd += "select ";
	m_sql_cmd += attrib_name;
	m_sql_cmd += " from ";
	m_sql_cmd += table_name;
	m_sql_cmd += " where(";
	m_sql_cmd += condition;
	m_sql_cmd += ");";

	m_ret_val = sqlite3_exec(m_db_handle, m_sql_cmd.c_str(), sql_handler, NULL,
			&m_zErrMsg);

	if (m_ret_val)
		exit(0), perror("Cannot read Database");

}

void SqliteDML::displayTable(std::string attrib_name, std::string table_name) {

	m_sql_cmd.clear();
	m_sql_cmd += "select ";
	m_sql_cmd += attrib_name;
	m_sql_cmd += " from ";
	m_sql_cmd += table_name;
	m_sql_cmd += ";";

	m_ret_val = sqlite3_exec(m_db_handle, m_sql_cmd.c_str(), sql_handler, NULL,
			&m_zErrMsg);

	if (m_ret_val)
		exit(0), perror("Cannot read Database");
}

bool SqliteDML::createTable(string tbl_name, const char* fmt, ...) {

	va_list args;
	va_start(args, fmt);

	string type_holder;
	string text;

	while (*fmt != '\0') {
		type_holder.clear();
		if (*fmt == 'P') {
			++fmt;
			if (*fmt == 'a') {
				text += va_arg(args, const char*);
				type_holder += " INTEGER PRIMARY KEY AUTOINCREMENT";
				text += type_holder;
				type_holder += " {\\} ";
				++fmt;
			} else if (*fmt == 'i') {
				text += va_arg(args, const char*);
				type_holder += " INTEGER PRIMARY KEY";
				text += type_holder;
				type_holder += " {\\} ";
				++fmt;
			} else if (*fmt == 'v') {
				text += va_arg(args, const char*);
				type_holder += " varchar(30) PRIMARY KEY";
				text += type_holder;
				type_holder += " {\\} ";
				++fmt;
			} else if (*fmt == 's') {
				text += va_arg(args, const char*);
				type_holder += " varchar(80) PRIMARY KEY";
				text += type_holder;
				type_holder += " {\\} ";
				++fmt;
			}
		} else if (*fmt == 'I') {
			text += va_arg(args, const char*);
			type_holder += " INTEGER";
			text += type_holder;
			type_holder += " {\\} ";
			++fmt;
		} else if (*fmt == 'V') {
			text += va_arg(args, const char*);
			type_holder += " varchar(30)";
			text += type_holder;
			type_holder += " {\\} ";
			++fmt;
		} else if (*fmt == 'S') {
			text += va_arg(args, const char*);
			type_holder += " varchar(80)";
			text += type_holder;
			type_holder += " {\\} ";
			++fmt;
		} else if (*fmt == '_') {
			text += ", ";
			++fmt;
			continue;
		} else if (*fmt == ',') {
			type_holder += " {\\EOL} ";
			break;
		}
	}

	m_sql_cmd.clear();
	m_sql_cmd += "create table if not exists ";
	m_sql_cmd += tbl_name;
	m_sql_cmd += "(";
	m_sql_cmd += text;
	m_sql_cmd += ");";

	sqlite3_exec(m_db_handle, m_sql_cmd.c_str(), NULL, NULL, &m_zErrMsg);

	if (m_zErrMsg != NULL)
		return (perror(m_zErrMsg), sqlite3_free(m_zErrMsg), false);
	sqlite3_free(m_zErrMsg);
	return true;
}

bool SqliteDML::InitDB(string db_name) {
	m_db_name = db_name;

	m_ret_val = sqlite3_open(m_db_name.c_str(), &m_db_handle);
	if (m_ret_val || m_ret_val == -2)
		return (perror("Cannot open database"), false);
	return true;

}
