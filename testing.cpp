#include <gtest/gtest.h>
#include "functions.h"


// Test for SearchUs function
TEST(SearchUsTest, FindsUser) {
    std::vector<user> users = {
        {"Alice", "password1", "Alice Wonderland", "1990-01-01"},
        {"Bob", "password2", "Bob Builder", "1985-05-05"},
        {"Charlie", "password3", "Charlie Brown", "1980-10-10"}
    };
    EXPECT_EQ(SearchUs(users, "Bob"), 1);
    EXPECT_EQ(SearchUs(users, "Alice"), 0);
    EXPECT_EQ(SearchUs(users, "Charlie"), 2);
    EXPECT_EQ(SearchUs(users, "David"), -1);
}

// Test for viewAllLoan function (This will require file handling and mocking as well)
TEST(ViewAllLoanTest, DisplaysLoans) {
    std::string filename = "loans.txt";

    // Create a temporary file with test data
    std::ofstream file(filename);
    file << "1,Book1,Author1,500,Fiction,2020,Text,Desc1,User1\n";
    file << "2,Book2,Author2,300,Non-Fiction,2019,Text,Desc2,User2\n";
    file << "3,Book3,Author3,400,Fiction,2018,Text,Desc3,User3\n";
    file.close();

    testing::internal::CaptureStdout();
    viewAllLoan(filename);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("ID: 1") != std::string::npos);
    EXPECT_TRUE(output.find("ID: 2") != std::string::npos);
    EXPECT_TRUE(output.find("ID: 3") != std::string::npos);

    // Remove the temporary file
    std::remove(filename.c_str());
}

// Test for viewLoan function (This will require file handling and mocking as well)
TEST(ViewLoanTest, DisplaysUserLoans) {
    std::string filename = "loans.txt";
    std::string logged_in_user = "User1";

    // Create a temporary file with test data
    std::ofstream file(filename);
    file << "1,Book1,Author1,500,Fiction,2020,Text,Desc1,User1\n";
    file << "2,Book2,Author2,300,Non-Fiction,2019,Text,Desc2,User2\n";
    file << "3,Book3,Author3,400,Fiction,2018,Text,Desc3,User3\n";
    file.close();

    testing::internal::CaptureStdout();
    viewBorrowedBooks(filename, logged_in_user);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("ID: 1") != std::string::npos);
    EXPECT_FALSE(output.find("ID: 2") != std::string::npos);
    EXPECT_FALSE(output.find("ID: 3") != std::string::npos);

    // Remove the temporary file
    std::remove(filename.c_str());
}

// Test for viewAllLoans function (Mock admin check)
TEST(ViewAllLoansTest, DisplaysAdminLoans) {
    std::string filename = "loans.txt";
    std::string logged_in_user = "admin";
    std::string admin_check_type = "Text";
    std::string admin_file = "admin.txt";

    // Create temporary files with test data
    std::ofstream file(filename);
    file << "1,Book1,Author1,500,Fiction,2020,Text,Desc1,User1\n";
    file << "2,Book2,Author2,300,Non-Fiction,2019,Text,Desc2,User2\n";
    file << "3,Book3,Author3,400,Fiction,2018,Text,Desc3,User3\n";
    file.close();

    std::ofstream adminfile(admin_file);
    adminfile << "admin\n";
    adminfile.close();

    testing::internal::CaptureStdout();
    viewAllLoans(filename, logged_in_user, admin_check_type, admin_file);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("ID: 1") != std::string::npos);
    EXPECT_TRUE(output.find("ID: 2") != std::string::npos);
    EXPECT_TRUE(output.find("ID: 3") != std::string::npos);

    // Remove the temporary files
    std::remove(filename.c_str());
    std::remove(admin_file.c_str());
}