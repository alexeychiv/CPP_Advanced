#include "StudentsGroup.h"

#include <fstream>
#include <sstream>


StudentsGroup::StudentsGroup()
{
    
}

StudentsGroup::~StudentsGroup()
{
    
}

bool StudentsGroup::fullNameEqualsFullName(const Students::FullName& name1, const Students::FullName& name2)
{
    if (name1.surname() == name2.surname())
        if (name1.name() == name2.name())
        {
            std::string mid1 = name1.has_middlename() ? name1.middlename() : "";
            std::string mid2 = name2.has_middlename() ? name2.middlename() : "";
            if (mid1 == mid2)
                return true;
        }
    return false;
}

const Students::Student* StudentsGroup::findStudent(const Students::FullName& name)
{
    for (int i = 0; i < group.students_size(); ++i)
        if (fullNameEqualsFullName(group.students(i).name(), name))
            return &group.students(i);
    return nullptr;
}

std::string StudentsGroup::studentToString(const Students::Student& student)
{
    std::stringstream ss;
    
    ss << student.name().surname() << ' ' << student.name().name();
    if (student.name().has_middlename())
        ss << ' ' << student.name().middlename();
    
    ss << " marks: ";
    if (student.marks_size())
        for (int i = 0; i < student.marks_size(); ++i)
            ss << student.marks(i) << ' ';
    
    ss << " average mark: " << student.averagemark();
    
    return ss.str();
}

void StudentsGroup::Open(const char * file)
{
    std::ifstream in(file, std::ios_base::binary);
    group.ParseFromIstream(&in);
    in.close();
}

void StudentsGroup::Save(const char * file)
{
    std::ofstream out(file, std::ios_base::binary);
    group.SerializeToOstream(&out);
    out.close();
}

double StudentsGroup::GetAverageScore(const Students::FullName& name)
{
    const Students::Student* pFoundStudent = findStudent(name);
    if (!pFoundStudent)
    {
        printf("ERROR: Cant find student %s %s %s!\n", name.surname().c_str(), name.name().c_str(), name.middlename().c_str());
        return 0;
    }
    
    return pFoundStudent->averagemark();
}

std::string StudentsGroup::GetAllInfo(const Students::FullName& name)
{
    const Students::Student* pFoundStudent = findStudent(name);
    if (!pFoundStudent)
    {
        printf("ERROR: Cant find student %s %s %s!\n", name.surname().c_str(), name.name().c_str(), name.middlename().c_str());
        return "";
    }
    
    return studentToString(*pFoundStudent);
}

std::string StudentsGroup::GetAllInfo()
{
    std::stringstream ss;
    for (int i = 0; i < group.students_size(); ++i)
        ss << studentToString(group.students(i)) << std::endl;
    return ss.str();
}


