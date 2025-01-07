

#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include <iostream>
#include <utility>



using Map = std::vector<std::string>;
using Path = std::vector<std::pair<int, int>>;

struct Gaurd
{
    Map& map;
    size_t line;
    size_t offset;
    int steps = 1;
    Path path;

    bool move(int line_direction = 0, int offset_direction = 0)
    {
        auto& new_postion = this->map.at(this->line + line_direction).at(this->offset + offset_direction);
        if(new_postion != '#')
        {
            this->line += line_direction;
            this->offset +=  offset_direction;
            if(new_postion == '.')
            {
                new_postion = 'X';
                this->steps++;
                this->path.push_back({line, offset});
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    bool patrol()
    {
        path.clear();
        int steps = 0;
        while(steps != this->steps)
        {
            steps = this->steps;
            try
            {
                while(this->move(-1, 0));
                while(this->move(0, 1));
                while(this->move(1, 0));
                while(this->move(0, -1));
            }
            catch(const std::out_of_range& e)
            {
                return true;
            }
        }
        return false;
    }
};



int main()
{

    Map map;

    std::fstream fs("input.txt");
    size_t line_num = 0;
    std::string line;
    size_t gaurd_index = std::string::npos;
    while(std::getline(fs, line))
    {
        if(gaurd_index == std::string::npos)
        {
            gaurd_index = line.find('^');
            line_num++;
        }
        map.push_back(line);
        
    }

    std::cout << line_num << " " << gaurd_index << '\n';
    Gaurd g {map, line_num - 1, gaurd_index};
    
    
    //part_1
    //if(g.patrol())
    //    return g.steps;

    int count = 0;
    auto reset_map = [&map](Path& p)
    {
        for(auto [line, offset] : p)
        {
            map[line][offset] = '.';
        }
    };

    g.patrol();
    Path origional_path = g.path;
    reset_map(origional_path);
    for(auto [line, offset] : origional_path)
    {
        g.line = line_num;
        g.offset = gaurd_index;
        map[line][offset] = '#';
        if(g.patrol() == false)
            count++;
        reset_map(g.path);
        map[line][offset] = '.';
    }

    return count;
}