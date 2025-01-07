

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <ranges>
#include <algorithm>

int main()
{
    std::fstream fs("input.txt");

    std::string line;
    //int line_num = 0;
    long long final_result = 0;

    while(std::getline(fs, line))
    {
        //line_num++;
        long long target = std::stoll(line.substr(0, line.find(':')));
        std::stringstream equation(line.substr(line.find(':')+2));

        std::string val;
        std::vector<int> vals;
        while (std::getline(equation, val, ' '))
        {
            vals.push_back(std::stoi(val));
        }
        
        std::vector<std::vector<int>> combibnations;

        std::vector<int> operators = {0,1,2};


        combibnations.push_back({});

        for(int i = 0; i < vals.size() - 1; i++)
        {
            std::vector<std::vector<int>> extensions;
            for(auto it = combibnations.begin();  it != combibnations.end(); it++)
            {
                for(int op : operators)
                {
                    std::vector<int> extension = *it;
                    extension.push_back(op);
                    extensions.push_back(extension);
                }

            }
            combibnations.clear();
            combibnations.append_range(extensions);
        }

        //std::ranges::sort(combibnations);
        int i = 0;
        for(auto combination : combibnations)
        {
            long long res = vals[i++];
            for(int op : combination)
            {
                if(op == 0)
                {
                    res += vals[i++];
                }
                else if(op == 1)
                {
                    res *= vals[i++];
                }
                else if(op == 2)
                {
                    res = std::stoll(std::to_string(res) + std::to_string(vals[i++]));
                }
            }
            if(res == target)
            {
                //std::cout << line_num << '\n';
                final_result += res;
                break;
            }

            else
            {
                i = 0;
            }
        }

    }
    std::cout << final_result;
    return 0;
}