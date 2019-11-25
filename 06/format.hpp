#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

void parseArgs(std::stringstream& argbuf,const char separator)
{
}

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

std::vector<std::string> split(const std::string& inpString,const char& separator)
{
    std::string buf;
    std::vector<std::string> res;

    for(size_t i = 0;i < inpString.size();++i)
    {
        if (inpString.at(i) == separator)
        {
            res.push_back(std::move(buf));
            buf.clear();
        }
        else
        {
            buf += inpString.at(i);
        }
    }
    if (!buf.empty())
    {
        res.push_back(std::move(buf));
        buf.clear();
    }
    return res;
}

std::string parseFormatString(const std::string& format,const std::vector<std::string>& arguments)
{
    std::string buf,result = "";
    bool insideBrackets = false;
    size_t curArgPos;

    for(size_t i = 0;i < format.size();++i)
    {
        char cur_symbol = format.at(i);
        if (cur_symbol == '}')
        {
            try
            {
                curArgPos = std::stoi(buf);
                if (curArgPos >= arguments.size())
                {
                    throw std::runtime_error("Wrong argument position in format string!");
                }
                else if (insideBrackets == false)
                {
                    throw std::runtime_error("Wrong number of formatting brackets!");
                }
            }
            catch(std::invalid_argument& invArgExc)
            {
                throw std::runtime_error("Wrong format of formatting string!");
            }

            insideBrackets = false;
            result.append(arguments[curArgPos]);//"{}" expression
            buf.clear();
        }
        else if (cur_symbol == '{')
        {
            if (insideBrackets == true)
            {
                throw std::runtime_error("Wrong number of formatting brackets!");
            }
            result.append(buf);//not "{}" expression
            buf.clear();
            insideBrackets = true;
        }
        else
        {
            buf += cur_symbol;
        }
    }
    if (insideBrackets == true)
    {
        throw std::runtime_error("Wrong number of formatting brackets!");
    }
    else if (!buf.empty())
    {
        result.append(buf);
        buf.clear();
    }
    return result;
}

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