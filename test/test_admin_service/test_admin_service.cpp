#include <gmock/gmock.h>
#include <admin_service.hpp>
#include <fstream>

bool spy_admin_login(AdminService in_AS)
{
    return in_AS.m_authorized;
}

bool helper_compareFiles(const std::string &file1, const std::string &file2)
{
    std::ifstream f1(file1);
    std::ifstream f2(file2);

    if (!f1 || !f2)
    {
        std::cerr << "Error opening one of the files" << std::endl;
        return false;
    }

    std::string line1, line2;
    while (std::getline(f1, line1) && std::getline(f2, line2))
    {
        if (line1 != line2)
        {
            return false;
        }
    }

    return true;
}

class TestAdminService : public ::testing::Test
{
protected:
    RTC timer;
    Terminal terminal;
    UserDatabase userdb;
    EntryLog entrylog;

    void SetUp() override
    {
        fstream file;
        file.open("data/input.txt");
        file << "admin\nadmin";
        file.close();
    }

    void TearDown() override
    {
    }
};

TEST_F(TestAdminService, admin_login)
{
    AdminService as(timer, terminal, userdb, entrylog);
    as.login();
    ASSERT_TRUE(spy_admin_login(as));
}

TEST_F(TestAdminService, show_menu)
{
    AdminService as(timer, terminal, userdb, entrylog);
    as.set_user_db_path("data/UserDB.csv");

    as.show_menu();
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
    AdminService as(timer, terminal, userdb, entrylog);
    as.logout();
    ASSERT_FALSE(spy_admin_login(as));
}

TEST_F(TestAdminService, view_registered_users)
{

    AdminService as(timer, terminal, userdb, entrylog);
    as.set_user_db_path("data/valid_UserDB.csv");
    as.load_database();
    int x = as.view_registered_users();

    ASSERT_TRUE(helper_compareFiles("data/output.txt", "data/valid_output.txt"));
}

TEST_F(TestAdminService, register_new_users)
{
    AdminService as(timer, terminal, userdb, entrylog);
    as.set_user_db_path("data/UserDB.csv");
    ASSERT_EQ(as.register_new_user(), 0);
}

TEST_F(TestAdminService, remove_registered_user)
{
    AdminService as(timer, terminal, userdb, entrylog);
    as.set_user_db_path("data/UserDB.csv");
    as.remove_registered_user();
}