#include <stdio.h>
#include <iostream>
#include <fstream>

#include "test.pb.h"
#include "Students.pb.h"
#include "StudentsGroup.h"

//=================================================================================================

int main()
{
    //  1.  Установить библиотеку protobuf.
    {
        printf("====================\nTASK 1:\n\n");
        
        TestProtoMessage msg;
        msg.set_str("BLAH");
        
        printf ("msg.str = %s\n", msg.str().c_str());
        //msg.SerializeToOstream(&std::cout);
        
        std::ofstream out("test.bin", std::ios_base::binary);
        msg.SerializeToOstream(&out);
        out.close();
        
        std::ifstream in("test.bin", std::ios_base::binary);
        
        TestProtoMessage msgIn;
        
        if (msgIn.ParseFromIstream(&in))
            printf ("msgIn.str = %s\n", msg.str().c_str());
        
        
        
        printf("\n");
    }
    
    
    //  2.  С помощью компилятора protobuf в отдельном
    //      пространстве имен сгенерировать классы 
    //          - FullName с полями имя, фамилия, отчество (отчество опционально).
    //          - Student с полями полное имя, массив оценок, средний балл.
    //          - StudentsGroup с полем массив студентов.
    {
        printf("====================\nTASK 2:\n\n");
        
        Students::FullName name1;
        name1.set_surname("Ivanov");
        name1.set_name("Ivan");
        name1.set_middlename("Ivanovich");
        
        Students::Student student1;
        student1.unsafe_arena_set_allocated_name(&name1);
        student1.add_marks(4);
        student1.add_marks(4);
        student1.add_marks(5);
        student1.set_averagemark(4.33);
        
        printf("Student1: %s\n", student1.DebugString().c_str());
        
        
        Students::FullName name2;
        name2.set_surname("Petrov");
        name2.set_name("Petr");
        name2.set_middlename("Petrovich");
        
        Students::Student student2;
        student2.unsafe_arena_set_allocated_name(&name2);
        student2.add_marks(3);
        student2.add_marks(5);
        student2.add_marks(4);
        student2.set_averagemark(4);
        
        printf("Student2: %s\n", student2.DebugString().c_str());
        
        
        Students::FullName name3;
        name3.set_surname("Sidorov");
        name3.set_name("Sidr");
        name3.set_middlename("Sidorovich");
        
        Students::Student student3;
        student3.unsafe_arena_set_allocated_name(&name3);
        student3.add_marks(3);
        student3.add_marks(3);
        student3.add_marks(5);
        student3.set_averagemark(3.66);
        
        printf("Student3: %s\n", student3.DebugString().c_str());
        
        
        Students::StudentsGroup group;
        (group.add_students())->CopyFrom(student1);
        (group.add_students())->CopyFrom(student2);
        (group.add_students())->CopyFrom(student3);
        
        std::ofstream out("group.bin", std::ios_base::binary);
        group.SerializeToOstream(&out);
        out.close();
        
        printf("\n");
    }
    
    
    //  3.  Создать класс StudentsGroup, который реализует интерфейсы:
    //          - IRepository
    //          - IMethods.
    {
        printf("====================\nTASK 3:\n\n");
        
        StudentsGroup group;
        
        group.Open("group.bin");
        
        printf("GetAllInfo():\n");
        printf("%s", group.GetAllInfo().c_str());
        printf("\n");
        
        Students::FullName name2;
        name2.set_surname("Petrov");
        name2.set_name("Petr");
        name2.set_middlename("Petrovich");
        
        printf("GetAverageScore of %s %s %s: %.2f\n",
            name2.surname().c_str(),
            name2.name().c_str(),
            (name2.has_middlename() ? name2.middlename().c_str() : ""),
            group.GetAverageScore(name2)
        );
        
        printf("\n");
        
        printf("GetAllInfo(%s %s %s): %s\n",
            name2.surname().c_str(),
            name2.name().c_str(),
            (name2.has_middlename() ? name2.middlename().c_str() : ""),
            group.GetAllInfo(name2).c_str()
        );
        
        printf("\n");
    }
    
    return 0;
}



