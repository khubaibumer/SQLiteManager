/*
 * SqliteDML.h
 *
 *  Created on: Feb 10, 2018
 *      Author: khubaib
 */

#ifndef SQLITEDML_H_
#define SQLITEDML_H_

#include <iostream>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

class SqliteDML {
public:
	SqliteDML();
	virtual ~SqliteDML();



	/*
	 * Initialization funtion for SqliteDML
	 * opens a connection with mentioned database
	 * prototype is: InitDB(string database_name);
	 * Must be called once before utilizing any functions provided by SqliteDML
	 *
	 *
	 */
	bool InitDB(std::string db_name);



	/*
	 * format is createTable("Pa_I_V_S_I,","col1","col2","col3","col4","col5");
	 * createTable("Pi_I_V_S_I,","col1","col2","col3","col4","col5");
	 * createTable("Pv_I_V_S_I,","col1","col2","col3","col4","col5");
	 * createTable("Ps_<nexttype>_...,","col1","col2","col3","col4","col5");
	 * all datatypes for columns should be mentioned as 1st argument joined by '_'
	 * column names should be in string format seperated by comma
	 * Table is created If-and-only-If it doesnot exists earlier. Otherwise safe return
	 *
	 */
	bool createTable(std::string table_name, const char* fmt, ...);


	/*
	 * Displays the contents of a table with the following format
	 * Col1:	Value1
	 * ...
	 * prototype is: displayName(string attrib_name, string table_name);
	 * attrib_name has a format of "col1, col2, ..." OR attrib_name can have "*"
	 *
	 *
	 */
	void displayTable(std::string attrib_name, std::string table_name);

	/*
	 * Displays the contents of a table with the following format
	 * Col1:	Value1
	 * ...
	 * prototype is: displayName(string attrib_name, string table_name, string condition);
	 * attrib_name has a format of "col1, col2, ..." OR attrib_name can have "*"
	 * condition can be like "(F_Name=='john' AND L_Name=='Doe') OR Age==27"
	 *
	 */
	void conditionalDisplayTable(std::string attrib_name, std::string table_name, std::string condition);


	/*
	 * Drops an existing table
	 * prototype is: dropTable(string table_name);
	 * termination safe. Safely Returns if no table by the specified name is present
	 *
	 *
	 */
	void dropTable(std::string table_name);


	/*
	 * Perform any other userdefined query.
	 * Returns true on success or false at failure
	 *
	 *
	 */
	bool performQuery(std::string query_text);

	/*
	 * updates attributes of a table
	 * prototype is: updateTable(string table_name, string new_attributes, string condition);
	 * attribs format is "old_val=new_val, old_val_2=new_val_2,..."
	 * condition can be like "(F_Name=='john' AND L_Name=='Doe') OR Age==27"
	 * */
	bool updateTable(std::string table_name, std::string new_attribs, std::string condition);

private:
	sqlite3* m_db_handle;
	char* m_zErrMsg;
	int m_ret_val;
	std::string m_sql_cmd;
	std::string m_db_name;

};

#endif /* SQLITEDML_H_ */
