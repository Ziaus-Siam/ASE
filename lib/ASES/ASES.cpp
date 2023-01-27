/**
 * @file ASES.cpp
 * @author Muhammad Ziaus Siam (ziaus.siam@bjitgroup.com)
 * @brief
 * @version 1.0
 * @date 2023-01-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <ASES.hpp>

int ASES::run()
{
    AdminService m_admin_service(m_timer, m_terminal, m_userdb, m_entrylog);
    // m_admin_service.set_entrylog_db_path("data/EntryLogDB.csv");
    // m_admin_service.set_user_db_path("data/UserDB.csv");
    m_admin_service.set_entrylog_db_path("G:/ASE/ASES_TDD/data/EntryLogDB.csv");
    m_admin_service.set_user_db_path("G:/ASE/ASES_TDD/data/UserDB.csv");

    m_admin_service.load_database();
    while (true)
    {
        m_admin_service.run();
    }

    return 0;
}