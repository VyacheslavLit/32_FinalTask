#pragma once
#include<iostream>

using namespace std;

class DBConnection {
public:
	DBConnection() {}
	virtual ~DBConnection() {}

	virtual void open(const char*, const char*, const char*) = 0;

	virtual void createTable() = 0;

	virtual bool insertTovar(const string&, const string&, const string&) = 0;

	virtual void printTovar() = 0;

	virtual void close() = 0;

	virtual void deleteTable() = 0;
};