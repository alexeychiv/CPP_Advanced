#pragma once


class IRepository
{
    virtual void Open(const char * file) = 0; // бинарная десериализация в файл
    virtual void Save(const char * file) = 0; // бинарная сериализация в файл
};
