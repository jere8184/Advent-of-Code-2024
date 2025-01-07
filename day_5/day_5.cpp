

#include <iostream>
#include <sstream>
#include <fstream>
#include <ranges>
#include <map>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream ifs;
    ifs.open("input.txt");

    std::string line;
    std::map<int, std::vector<int>> sorted;
    std::map<int, int> orderings;

    while (std::getline(ifs, line))
    {
        size_t delim = line.find('|');
        if(delim == std::string::npos)
            break;

        int key = stoi(line.substr(delim + 1));
        int value = stoi(line.substr(0, delim));
        sorted[key].push_back(value);
        orderings[value] = key;
    }

    int ans = 0;
    while (std::getline(ifs, line))
    {
        std::vector<int> pages;
        std::stringstream ss(line);
        std::string page;
        while(std::getline(ss, page, ','))
        {
            pages.push_back(stoi(page));
        }

        auto sort_pages = [&sorted](int page_a, int page_b)
        {
            std::vector<int> cant_be_after = sorted[page_a];

            for(int page : cant_be_after)
            {
                if(page == page_b)
                {
                    return false;
                }
            }
            return true;
        };

        bool correctly_ordered = true;
        for(int i = 0; i < pages.size(); i++)
        {
            for(int j = i; j < pages.size(); j++)
            {
                if(!sort_pages(pages[i], pages[j]))
                    correctly_ordered = false;
            }
        }
        if(correctly_ordered)
            //ans += pages[(pages.size() - 1) / 2];
            continue;
        else
        {
            std::sort(pages.begin(), pages.end(), sort_pages);
            ans += pages[(pages.size() - 1) / 2];
        }
    }
    std::cout << ans;
    return ans;
}