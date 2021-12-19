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

TEST(Task2Test1, PersonTest)
{
    Person p("Aa", "Bb", "Cc");
    
    ASSERT_EQ(p.surname, "Aa");
    ASSERT_EQ(p.name, "Bb");
    ASSERT_EQ(p.middleName, "Cc");
    
    ASSERT_TRUE(p == Person("Aa", "Bb", "Cc"));
    
    ASSERT_TRUE(p < Person("Bb", "Cc", "Dd"));
}

TEST(Task2Test2, PhoneNumberTest)
{
    PhoneNumber pn1("1", "2", "3", "4");
    ASSERT_EQ(pn1.toString(), "+1(2)3 4");
    
    PhoneNumber pn2(1, 2, "3", 4);
    ASSERT_EQ(pn2.toString(), "+1(2)3 4");
    
    ASSERT_TRUE(pn1 == pn2);
    ASSERT_FALSE(pn1 < pn2);
}

TEST(Task2Test3, PhoneBookConstructor)
{
    ASSERT_THROW(PhoneBook("blah.blah"), std::runtime_error);
}


class Task2Test4: public testing::Test
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

TEST_F(Task2Test4, GetPhoneNumber)
{
    //std::cout << *phoneBook;
    
    ASSERT_EQ(std::get<0>(phoneBook->GetPhoneNumber("Egorova")), "not found");
    ASSERT_EQ(std::get<1>(phoneBook->GetPhoneNumber("Egorov")), "+77(4521)8880876 99");
    ASSERT_EQ(std::get<0>(phoneBook->GetPhoneNumber("Ilin")), "found more than 1");
}

TEST_F(Task2Test4, ChangePhoneNumber)
{
    Person p("Egorov", "Savelii", "Stanislavovich");
    PhoneNumber n("55", "66", "77", "88");
    
    phoneBook->ChangePhoneNumber(p, n);
    
    ASSERT_EQ(std::get<1>(phoneBook->GetPhoneNumber("Egorov")), "+55(66)77 88");
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



