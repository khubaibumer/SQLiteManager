/*
 * SqliteDDL.h
 *
 *  Created on: Feb 8, 2018
 *      Author: khubaib
 */

#ifndef SQLITEDDL_H_
#define SQLITEDDL_H_

#include <iostream>
#include <sqlite3.h>
#include <stdio.h>

class SqliteDDL {
public:
	SqliteDDL();
	virtual ~SqliteDDL();

	/*
	 * This function inserts data to a table.
	 * prototype is: insertData(string table_name, string table_columns_prototype (optional),
	 * 							string values_to_be_inserted "(value1,...)"
	 * return true on success or returns false on failure with error msg
	 * */
	bool	insertData(std::string table_name, std::string col_proto , std::string query_text);

	/*
	 * This function deletes data from a table
	 * prototype is: deleteData(string table_name, string condition);
	 * condition should be like "Name=='John' AND Age==22" || "(Name=='John' AND Age==22) OR Name=='Doe'"
	 * */
	bool	deleteData(std::string table_name, std::string condition);

	/*
	 * Initialization funtion for SqliteDDL
	 * opens a connection with mentioned database
	 * prototype is: InitDB(string database_name);
	 * Must be called once before utilizing any functions provided by SqliteDDL
	 * */
	bool	InitDB(std::string db_name);

private:
	sqlite3* m_db_handle;
	char* m_zErrMsg;
	int m_ret_val;
	std::string m_sql_cmd;
	std::string m_db_name;

};

#endif /* SQLITEDDL_H_ */
