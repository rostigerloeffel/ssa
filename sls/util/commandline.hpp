#ifndef __SLS_UTIL_COMMANDLINE_HPP__
#define __SLS_UTIL_COMMANDLINE_HPP__


#include <map>
#include <string>
#include <sstream>


namespace sls
{


namespace util
{


class commandline
{
    std::map<std::string, std::string> commandline_;

public:
    commandline()
    {
    }

    template<typename Iterator>
    commandline(Iterator begin, Iterator end)
    {
        parse(begin, end);
    }

    template<typename Iterator>
    commandline(Iterator begin, size_t count)
    {
        parse(begin, begin + count);
    }

    template<typename Iterator>
    void parse(Iterator begin, Iterator end)
    {
        while(begin != end)
        {
            std::string argstring(*begin);
            size_t pos = argstring.find("=");

            if(pos != std::string::npos)
                commandline_[argstring.substr(0, pos)] = argstring.substr(pos + 1);
            else
                commandline_[argstring] = "";

            ++begin;
        }
    }

    template<typename TargetType>
    TargetType const get(std::string const& identifier, TargetType const& default_value = TargetType()) const
    {
        if(commandline_.find(identifier) == commandline_.end())
            return default_value;

        std::stringstream strstream(commandline_.find(identifier)->second);

        TargetType buffer;
        strstream >> buffer;

        return buffer;
    }
};


} /* util */


} /* sls */


#endif
