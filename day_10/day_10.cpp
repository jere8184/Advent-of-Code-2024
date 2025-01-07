

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <set>




bool in_bounds(std::vector<std::string>& map, int x, int y)
{
    if(x > -1 && x < map.size() && y > -1 && y < map[0].size())
        return true;
    return false;
};

std::vector<std::pair<size_t, size_t>> get_neigbours(std::vector<std::string>& map, int x, int y)
{
    std::vector<std::pair<size_t, size_t>> neigbours;
    if(in_bounds(map, x + 1, y))
    {
        neigbours.push_back({x+1, y});
    }

    if(in_bounds(map, x, y+1))
    {
        neigbours.push_back({x, y+1});
    }
    
    if(in_bounds(map, x - 1, y))
    {
        neigbours.push_back({x-1, y});
    }

    if(in_bounds(map, x, y-1))
    {
        neigbours.push_back({x, y-1});
    }

    return neigbours;
};


std::vector<std::pair<size_t, size_t>> explore(std::vector<std::string>& map, int x, int y)
{
    std::vector<std::pair<size_t, size_t>> peaks;
    for(auto neigbour : get_neigbours(map,x,y))
    {
        if(map[x][y] + 1 == map[neigbour.first][neigbour.second])
        {
            if ('9' == map[neigbour.first][neigbour.second])
            {
                peaks.push_back(neigbour);
                continue;
            }

            for(auto peak : explore(map, neigbour.first, neigbour.second))
            {
                peaks.push_back(peak);
            }
        }     
    }
    return peaks;
}


int main()
{
    std::fstream fs("example.txt");

    std::vector<std::string> map;
    std::string line;
    while(std::getline(fs, line))
    {
        map.push_back(line);
    }




    int x = 0;
   
    std::vector<std::pair<size_t, size_t>> trial_heads;
    for(auto line : map)
    {
        int y = 0;
        while(y != std::string::npos)
        {
            y = line.find('0', y);

            if(y != std::string::npos)
                trial_heads.push_back({x,y++});
                
        }
        x++;
    }
    std::cout << trial_heads.size() << std::endl;


    long long score = 0;
    for(auto [x,y] : trial_heads)
    {
        auto peaks = explore(map,x,y);
        std::cout << peaks.size() << std::endl;

        score += peaks.size();
    }
    std::cout << score << std::endl;

}