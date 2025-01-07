
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <unordered_set>


struct PairHash
{
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &v) const
    {
        return std::hash<T1>()(v.first) ^ std::hash<T2>()(v.second) << 1;    
    }
};

int main()
{
    std::fstream fs("input.txt");


    std::vector<std::string> grid;
    std::string line;
    while(std::getline(fs, line))
    {
        grid.push_back(line);
    }

    int total_lines = grid.size();
    int total_col = grid[0].size();

    int count = 0;



    std::unordered_map<char, std::vector<std::pair<int,int>>> postions;
    std::unordered_set<std::pair<int,int>, PairHash> unique_locations;

    int line_num = 0;
    for(auto line : grid)
    {
        int offset = 0;
        for(char c : line)
        {
            if(c != '.')
            {
                unique_locations.insert({line_num, offset});
                for(std::pair<int,int> other : postions[c])
                {
                    bool hit = false;
                    bool left = other.second < offset;
                    if(left)
                    {
                        std::pair<int,int> one = {other.first + (other.first - line_num), other.second + (other.second - offset)};
                        int i = 1;
                        while( one.first > -1 && one.second > -1)
                        {
                            unique_locations.insert(one);
                            i++;
                            one = {other.first + (other.first - line_num)*i, other.second + (other.second - offset)*i};
                            hit = true;
                        }

                        std::pair<int,int> two = {line_num + (line_num - other.first), offset + (offset - other.second)};
                        i = 1;
                        while(two.first < total_lines && two.second < total_col)
                        {
                            unique_locations.insert(two);
                            i++;
                            two = {line_num + (line_num - other.first)*i, offset + (offset - other.second)*i};
                            hit = true;
                        }
                    }
                    else
                    {
                        std::pair<int,int> one = {other.first + (other.first - line_num), other.second + (other.second - offset)};
                        int i = 1;
                        while(one.first > -1 && one.second < total_col)
                        {
                            unique_locations.insert(one);
                            i++;
                            one = {other.first + (other.first - line_num)*i, other.second + (other.second - offset)*i};
                            hit = true;
                        }
                        std::pair<int,int> two = {line_num + (line_num - other.first), offset + (offset - other.second)};
                        i = 1;
                        while(two.first < total_lines && two.second > -1)
                        {
                            unique_locations.insert(two);
                            i++;
                            two = {line_num + (line_num - other.first)*i, offset + (offset - other.second)*i};
                            hit = true;
                        }
                    }
                    if(hit)
                    {
                        unique_locations.insert(other);
                    }
                }
                postions[c].push_back({line_num, offset});
            }
            offset++;
        }
        line_num++;
    }


    std::fstream output("output.txt");
    
    for(auto [x, y] : unique_locations)
    {
        grid[x][y] = '#';
    }

    for(std::string line : grid)
        output << line << '\n';

    std::cout << unique_locations.size();
}