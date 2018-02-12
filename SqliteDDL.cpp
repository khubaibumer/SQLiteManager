/*
 * SqliteDDL.cpp
 *
 *  Created on: Feb 10, 2018
 *      Author: khubaib
 */

#include "SqliteDDL.h"

using namespace std;

SqliteDDL::SqliteDDL() {
	// TODO Auto-generated constructor stub

	m_db_handle = NULL;
	m_ret_val = -2;
	m_zErrMsg = 0;
	m_db_name.clear();
	m_sql_cmd.clear();

}

SqliteDDL::~SqliteDDL() {
	// TODO Auto-generated destructor stub
	sqlite3_close(m_db_handle);
}

bool SqliteDDL::deleteData(std::string table_name, std::string condition) {

	m_sql_cmd.clear();
	m_sql_cmd += "delete from ";
	m_sql_cmd += table_name;
	m_sql_cmd += " where (";
	m_sql_cmd += condition;
	m_sql_cmd += " );";

	if (sqlite3_exec(m_db_handle, m_sql_cmd.c_str(), NULL, NULL, &m_zErrMsg))
		return (perror(m_zErrMsg), false);
	return true;

}

bool SqliteDDL::insertData(string table_name, string col_proto,
		string query_text) {

	m_sql_cmd.clear();

	m_sql_cmd += "insert into ";
	m_sql_cmd += table_name;
	m_sql_cmd += "";
	if (!col_proto.empty()) {
		m_sql_cmd += col_proto;
		m_sql_cmd += " ";
	}
	m_sql_cmd += " values";
	m_sql_cmd += query_text;
	m_sql_cmd += ";";

	if (sqlite3_exec(m_db_handle, m_sql_cmd.c_str(), NULL, NULL, &m_zErrMsg))
		return (perror(m_zErrMsg), false);
	return true;

}

bool SqliteDDL::InitDB(string db_name) {
	m_db_name = db_name;

	m_ret_val = sqlite3_open(m_db_name.c_str(), &m_db_handle);
	if (m_ret_val || m_ret_val == -2)
		return (perror("Cannot open database"), false);
	return true;

}

