#pragma once
#include<gtest/gtest.h>
#include<gmock/gmock.h>
#include"ClassThatUseDB.h"

void test_DB(DBConnection* dbconnect)
{
    dbconnect->open("root", "1111", "test");
    dbconnect->createTable();
    dbconnect->insertTovar("Vodka", "0.5 kg", "450");
    dbconnect->insertTovar("Snikers", "60 gr", "54");
    dbconnect->printTovar();
    dbconnect->deleteTable();
    dbconnect->close();
}

class Mock_Test_DBConnection : public DBConnection
{
public:

    MOCK_METHOD(void, open, (const char*, const char*, const char*), (override));
    MOCK_METHOD(void, createTable, (), (override));
    MOCK_METHOD(bool, insertTovar, (const string&, const string&, const string&), (override));
    MOCK_METHOD(void, printTovar, (), (override));
    MOCK_METHOD(void, deleteTable, (), (override));
    MOCK_METHOD(void, close, (), (override));

};

TEST(DBConnection, test1) {
    ::testing::NaggyMock<Mock_Test_DBConnection> mconnect;
    EXPECT_CALL(mconnect, open).Times(1);
    EXPECT_CALL(mconnect, createTable).Times(1);
    EXPECT_CALL(mconnect, insertTovar).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(mconnect, printTovar).Times(::testing::AtLeast(1));
    EXPECT_CALL(mconnect, deleteTable).Times(1);
    EXPECT_CALL(mconnect, close).Times(1);

    test_DB(&mconnect);
}


class GTest : public ::testing::Test
{
protected:
    void SetUp() {
        cout << "Установки теста\n" << endl;
        dbconnect.open("root", "1111", "test");
        dbconnect.createTable();
    }
    void TearDown() {
        cout << "Сброс утановок\n" << endl;
        dbconnect.deleteTable();
        dbconnect.close();
    }

protected:
    ClassThatUseDB dbconnect;
};

TEST_F(GTest, test2)
{
    bool b = dbconnect.insertTovar("Vodka", "0.5 kg", "450");
    ASSERT_EQ(b, true);
}

