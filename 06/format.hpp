#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

void parseArgs(std::stringstream& argbuf,const char separator);

template<typename T>
void parseArgs(std::stringstream& argbuf,const char separator,T&& first)
{
    argbuf << first;
}

template<typename T,typename... Args>
void parseArgs(std::stringstream& argbuf,const char separator,T&& first,Args&& ...args)
{
    argbuf << first << separator;
    parseArgs(argbuf,separator,std::forward<Args>(args)...);
}

std::vector<std::string> split(const std::string& inpString,const char& separator);

std::string parseFormatString(const std::string& format,const std::vector<std::string>& arguments);

template<typename... Args> 
std::string format(const std::string& format,Args&& ...args)
{
    const char separator = ' ';

    std::vector<std::string> arguments;
    std::string result;

    std::stringstream argbuf;
    parseArgs(argbuf,separator,std::forward<Args>(args)...);
    arguments = split(argbuf.str(),separator);

    return parseFormatString(format,arguments);
}