#pragma once

#include <string>
#include "Students.pb.h"


class IMethods
{
    virtual double GetAverageScore(const Students::FullName& name) = 0;
    virtual std::string GetAllInfo(const Students::FullName& name) = 0;
    virtual std::string GetAllInfo() = 0;
};


