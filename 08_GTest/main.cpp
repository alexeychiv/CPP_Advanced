#include <stdio.h>
#include <iostream>

#include <gtest/gtest.h>

#include "../01_SupportClassesForConvenience/PhoneBook/PhoneBook.h"

//=================================================================================================
//TASK 1

TEST(Task1Test, TrueTest)
{
    ASSERT_TRUE(true);
}

TEST(Task1Test, FalseTest)
{
    ASSERT_TRUE(false);
}

//=================================================================================================
// TASK 2

class Task2Test: public testing::Test
{
    protected:
        PhoneBook* phoneBook;
        
        void SetUp() override
        {
            phoneBook = new PhoneBook("PhoneBook.txt");
        }
        void TearDown() override
        {
            delete phoneBook;
        }
};

TEST_F(Task2Test, GetPhoneNumber)
{
    std::cout << *phoneBook;
    
    ASSERT_TRUE(std::get<0>(phoneBook->GetPhoneNumber("Egorova")) == "not found");
    ASSERT_TRUE(std::get<1>(phoneBook->GetPhoneNumber("Egorov")) == "+77(4521)8880876 99");
    ASSERT_TRUE(std::get<0>(phoneBook->GetPhoneNumber("Ilin")) == "found more than 1");
}


//=================================================================================================

int main()
{
    testing::InitGoogleTest();
    
    //  1.  Установить фреймворк Google Test.
    {
        printf("====================\nTASK 1:\n\n");
        
        ::testing::GTEST_FLAG(filter) = "Task1*";
        RUN_ALL_TESTS();
        
        printf("\n");
    }
    
    //  2.  Добавить unit-тесты в проект домашнего задания из первого урока.
    {
        printf("====================\nTASK 2:\n\n");
        
        ::testing::GTEST_FLAG(filter) = "Task2*";
        RUN_ALL_TESTS();
        
        printf("\n");
    }
        
    return 0;
}



