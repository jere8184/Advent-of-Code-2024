

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>




/*unsigned long long expand(std::string val, int expansions_left = 75)
{
    unsigned long long splits = 0;
    if(!expansions_left)
    {
        return splits;
    }

    if(val == "0")
    {
        splits += expand("1", --expansions_left);
    }
    else if(val.length() % 2 == 0)
    {
        std::string one(val.begin(), val.begin() + (val.length()/2));
        std::string two(val.begin() + (val.length()/2), val.end());
        
        splits++;
        splits += expand(std::to_string(std::stoull(one)), expansions_left - 1);
        splits += expand(std::to_string(std::stoull(two)), expansions_left - 1);
    }
    else
    {
        unsigned long long value = std::stoull(val);
        value *= 2024;
        splits += expand(std::to_string(value),  --expansions_left);
    }
    return splits;
}*/


std::unordered_map<int, std::unordered_map<int, unsigned long long>>  cache;

unsigned long long expand(unsigned long long val, int expansions_left = 75)
{
    unsigned long long splits = 0;
    //std::cout << val << " " << expansions_left << std::endl;
    if(!expansions_left)
    {
        return splits;
    }

    if(cache.contains(val) && cache[val].contains(expansions_left))
    {
        splits = cache[val][expansions_left];
    }
    else if(val == 0)
    {
        splits = expand(1, expansions_left - 1);
    }
    else if(unsigned int digits = (unsigned long long)std::floor(std::log10(val) + 1); digits % 2 == 0)
    {
        unsigned long long value = val;
        unsigned long long one = 0;
        unsigned long long two = 0;
        //std::cout << digits << " " << value << " ";
        for(int i = 0; i < digits / 2; i++)
        {
            int digit =  value % 10;
            one += digit * std::pow(10, i);
            value /= 10; 
        }

        for(int i = 0; i < digits / 2; i++)
        {
            int digit =  value % 10;
            two += digit * std::pow(10, i);
            value /= 10; 
        }
        //std::cout << one << " " << two << std::endl;
        splits++;
        splits += expand(one, expansions_left - 1);
        splits += expand(two, expansions_left - 1);
    }
    else
    {
        unsigned long long value = val;
        value *= 2024;
        splits += expand(value,  expansions_left - 1);
    }
    cache[val][expansions_left] = splits;
    return splits;
}


int main()
{
    std::vector<unsigned long long> input;
    std::fstream fs("example.txt");
    unsigned long long val;
    while(fs >> val)
    {
        input.push_back(val);
    }

    unsigned long long splits = 0;
    
    for(unsigned long long val : input)
    {
        std::cout << "processing: " << val << std::endl;
        splits += expand(val, 75);
    }
    std::cout << splits + input.size();





    return 0;
}