#include <gmock/gmock.h>
#include <admin_service.hpp>
#include <fstream>

bool spy_admin_login(AdminService *in_AS)
{
    return in_AS->m_authorized;
}

class TestAdminService : public ::testing::Test
{
protected:
    AdminService *as;

    void SetUp() override
    {
        RTC timer;
        Terminal terminal;
        UserDatabase userdb;
        EntryLog entrylog;

        AdminService temp(timer, terminal, userdb, entrylog);
        as = &temp;

        fstream file;
        file.open("data/input.txt");
        file << "admin\nadmin";
        file.close();
        as->set_entrylog_db_path("data/EntryLogDB.csv");
        as->set_user_db_path("data/UserDB.csv");
    }

    void TearDown() override
    {
    }
};

TEST_F(TestAdminService, admin_login)
{
    as->login();
    ASSERT_TRUE(spy_admin_login(as));
}

TEST_F(TestAdminService, show_menu)
{
    as->show_menu();
    ifstream file;
    file.open("data/output.txt");
    string line, val;
    string result;
    while (getline(file, val))
    {
        stringstream ss(val);
        line = ss.str();
        result += line + "\n";
    }

    string answer = "\nAdmin Menu:\n";
    answer += "  1. View registered users.\n";
    answer += "  2. Register new user.\n";
    answer += "  3. Delete registered user.\n";
    answer += "  4. Show last 10 entry logs.\n";
    answer += "  5. Exit.\n\n";

    ASSERT_EQ(answer, result);
}

TEST_F(TestAdminService, admin_logout)
{
    as->logout();
    ASSERT_FALSE(spy_admin_login(as));
}