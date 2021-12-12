#pragma once

#include "IRepository.h"
#include "IMethods.h"


class StudentsGroup : public IRepository, IMethods
{
    private:
        Students::StudentsGroup group;
        
    public:
        StudentsGroup();
        ~StudentsGroup();
        
    private:
        bool fullNameEqualsFullName(const Students::FullName& name1, const Students::FullName& name2);
        const Students::Student* findStudent(const Students::FullName& name);
        std::string studentToString(const Students::Student& student);
        
    public:
        void Open(const char * file) override;
        void Save(const char * file) override;
        
        double GetAverageScore(const Students::FullName& name) override;
        std::string GetAllInfo(const Students::FullName& name) override;
        std::string GetAllInfo() override;
};