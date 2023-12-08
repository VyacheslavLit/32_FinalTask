#include"ClassThatUseDB.h"

void ClassThatUseDB::open(const char* login, const char* pass, const char* DB_name)
{
    mysql_init(&mysql);
    if (&mysql == nullptr)
    {
        cout << "Ошибка соединения с MySQL." << endl;
        exit(1);
    }
    MYSQL* connect = mysql_real_connect(&mysql, "localhost", login, pass, DB_name, 0, NULL, 0);
    if (connect == nullptr)
    {
        cout << "Ошибка подключения к базе данных: " << mysql_error(&mysql) << endl;
        exit(1);
    }
}

void ClassThatUseDB::createTable()
{
    mysql_query(&mysql, "create table if not exists tovar (id int auto_increment primary key not null, 	\
     nomen varchar(200) not null, ves varchar(20) not null, cost varchar(20) not null)");
}

bool ClassThatUseDB::insertTovar(const string& nomen, const string& ves, const string& cost)
{
    const string str = "insert tovar (nomen, ves, cost) values ('" + nomen + "', '" + ves + "', '" + cost + "')";

    mysql_query(&mysql, str.c_str());
    if (mysql_errno(&mysql))
    {
        cout << "Ошибка ввода товара в базу" << endl;
        return false;
    }
    else
    {
        cout << "Товар внесен" << endl;
        return true;
    }
}

void ClassThatUseDB::printTovar() {
    mysql_query(&mysql, "SELECT * FROM tovar"); 
    if (res = mysql_store_result(&mysql)) 
    {
        cout << "ID Название  Вес  Цена\n----------------------\n";
        while (row = mysql_fetch_row(res)) {
            for (size_t i = 0; i < mysql_num_fields(res); i++) {
                cout << row[i] << "  ";
            }
            cout << endl;
        }
        cout << endl;
    }
    else
        cout << "Ошибка MySql номер " << mysql_error(&mysql);
}

void ClassThatUseDB::deleteTable() {
    mysql_query(&mysql, "drop table tovar");
    cout << "\nТаблица удалена\n";
}

void ClassThatUseDB::close()
{
    mysql_close(&mysql);
}
