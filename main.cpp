#include "TestDBConnection.h"
#include <Windows.h>

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    ClassThatUseDB dbconnect;
    dbconnect.open("root", "1111", "test");
    dbconnect.createTable();
    dbconnect.insertTovar("Vodka", "0.5 kg", "450");
    dbconnect.insertTovar("Snikers", "60 gr", "54");
    dbconnect.printTovar();
    dbconnect.deleteTable();
    dbconnect.close();

    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();

    return  0;
}