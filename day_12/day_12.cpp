
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <utility>
#include <optional>
#include <tuple>
#include <bitset>

using coordinate = std::pair<int, int>;
using region = std::tuple<std::set<coordinate>, size_t, char, int>;

std::vector<std::string> grid = {};

bool inbounds(const coordinate& coord)
{
    auto [y,x] = coord;
    
    if((y > -1 && y < grid.size()) && (x > -1 && x < grid[0].size()))
    {
        return true;
    }
    return false;
}

std::optional<char> get_plant(const coordinate& coord)
{
    const auto [y,x] = coord;
    //std::cout << y << " " << x << std::endl;
    if(inbounds(coord))
        return std::optional<char>(grid[y][x]);
    return std::nullopt; 
}

int find_internal_angles(const coordinate& coord, bool up, bool right, bool down, bool left)
{
    int internal_angles_count = 0;
    char plant = get_plant(coord).value();
    auto [y, x] = coord;

    //std::cout << "find_internal_angles\\" << "plant: " << plant << " y:"<< y << " x:" << x << " up:" << up << " right:" << right << " down:" << down << " left:" << left << std::endl; 

    if(up && right && get_plant({y-1, x+1}) != plant)
        internal_angles_count++;
    if(right && down && get_plant({y+1, x+1}) != plant)
        internal_angles_count++;
    if(down && left && get_plant({y+1, x-1}) != plant)
        internal_angles_count++;
    if(left && up && get_plant({y-1, x-1}) != plant)
        internal_angles_count++;
    return internal_angles_count;
}

void explore_area(region& region, const coordinate& current_coordinate)
{
    auto& [region_coords, perimeter, plant, sides] = region;
    bool up = true;
    bool down = true;
    bool left = true;
    bool right = true;
    //std::cout << "explore area\\ " << "plant:"<< plant << " y:" <<  current_coordinate.first <<  " x:" << current_coordinate.second << " size:" << region_coords.size() << " sides:" << sides << std::endl;
    if(region_coords.insert(current_coordinate).second)
    {
        coordinate new_coordinate = {current_coordinate.first - 1, current_coordinate.second};
        if(auto p = get_plant(new_coordinate); plant == p)
        {
            explore_area(region, new_coordinate);
        }
        else
        {
            perimeter++;
            up = false;
        }
        new_coordinate = {current_coordinate.first + 1, current_coordinate.second};
        if(auto p = get_plant(new_coordinate); plant == p)
        {
            explore_area(region, new_coordinate);
        } 
        else
        {
            perimeter++;
            down = false;
        }  
        new_coordinate = {current_coordinate.first, current_coordinate.second + 1};
        if(auto p = get_plant(new_coordinate); plant == p)
        {
            explore_area(region, new_coordinate);
        }
        else
        {
            perimeter++;
            right = false;
        }  
        new_coordinate = {current_coordinate.first, current_coordinate.second - 1};
        if(auto p = get_plant(new_coordinate); plant == p)
        {
            explore_area(region, new_coordinate);
        } 
        else
        {
            perimeter++;
            left = false;
        }
        int res = up + down + left + right;
        if(res == 4)
        {
            sides += find_internal_angles(current_coordinate, up, right, down, left);
        }
        else if(res == 3)
        {
            sides += find_internal_angles(current_coordinate, up, right, down, left);
        }
        else if(res == 2)
        {
            if(up != down)
            {
                sides += 1;
                sides += find_internal_angles(current_coordinate, up, right, down, left);
            }
        }
        else if(res == 1)
        {
            sides += 2;
        }
        else if(res == 0)
        {
            sides += 4;
        }
    }
}


int main()
{


    std::string line;
    std::fstream fs("input.txt");
    while(std::getline(fs, line))
    {
        grid.push_back(line);
    }


    std::vector<region> regions;
    std::set<coordinate> visited;
    
    int y = 0;
    for(std::string line : grid)
    {
        int x = 0;
        for(char plant : line)
        {
            if(!visited.contains({y, x}))
            {
                region region = {{}, 0, plant, 0};

                explore_area(region, {y, x});
                visited.insert_range(std::get<0>(region));
                regions.push_back(region);
            }
            x++;
        }
        y++;
    }

    unsigned long long total_cost = 0;
    for(auto& [region_coords, perimeter, plant, sides]: regions)
    {
        //std::cout << "plant:" << plant << " perimeter:" << perimeter << " size:" << region_coords.size() << " sides:" << sides << std::endl;
        total_cost += sides * region_coords.size();
    }
    std::cout << total_cost;
};