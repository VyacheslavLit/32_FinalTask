#pragma once
#include <mysql.h> 
#include "DBConnection.h"


class ClassThatUseDB : public DBConnection
{
private:
    MYSQL mysql;
    MYSQL_RES* res;
    MYSQL_ROW row;

public:
    ClassThatUseDB() {}
    ~ClassThatUseDB() {}

    void open(const char*, const char*, const char*) override;

    void createTable() override;

    bool insertTovar(const string&, const string&, const string&) override;

    void printTovar() override;

    void deleteTable()override;

    void close()override;
};

