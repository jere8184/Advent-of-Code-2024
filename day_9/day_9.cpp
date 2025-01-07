

#include <fstream>
#include <string>
#include <ranges>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

int main()
{
    std::fstream fs("input.txt");

    //std::string disk_map;

    //auto chunks = disk_map | std::ranges::views::chunk(2);


    long long id = 0;

    char file_size;
    char space_left;
    int total_free_space = 0;
    std::vector<long long> disk;
    
    while(fs >> file_size)
    {
        int i_file_size = file_size - '0';
        int i_space_left;
        
        if(fs >> space_left)
            i_space_left = space_left - '0';
        else
            i_space_left = 0;

        for(int i = 0; i < i_file_size; i++)
        {
            disk.push_back(id);
        } 

        for(int i = 0; i < i_space_left; i++)
        {
            disk.push_back(-1);
        } 

        total_free_space += i_space_left;

        id++;
    }


    ///PART 1
    /*auto next_empty = std::ranges::find(disk, -1);
    auto rightmost_value = std::find_if(disk.rbegin(), disk.rend(), [](long long ll){return ll != -1;});

    auto stop_postion = disk.rbegin() + (std::ranges::count(disk, -1));
    while(rightmost_value + 1 != stop_postion)
    {
        rightmost_value = std::find_if(disk.rbegin(), disk.rend(), [](long long ll){return ll != -1;});
        *next_empty = *rightmost_value;
        *rightmost_value = -1;
        next_empty = std::ranges::find(disk, -1);

    }*/



   auto get_block_size = [&disk](long long index)
   {
        int val = disk[index];
        int size = 0;
        while(disk[index++] == val)
            size++;
        return size;
   };


   ///PART 2
    std::vector<std::pair<long long, long long>> free_chunks;
    std::vector<std::pair<long long , long long>> occupied_chunks;


    for(int i = 0; i < disk.size();)
    {
        int val = disk[i];
        size_t size = get_block_size(i);

        if(val == -1)
        {
            free_chunks.push_back({i, i+size});
        }
        else
        {
            occupied_chunks.push_back({i, i+size});
        }
        i += size;
    }

    std::cout << disk.size() << std::endl;


    for(int j =  occupied_chunks.size() - 1; j > -1; j--)
    {
        auto chunk =  occupied_chunks[j]; 
        int size = chunk.second - chunk.first;
        int val = disk[chunk.first];
        auto free_chunk_it = std::find_if(free_chunks.begin(), free_chunks.end(), [size](std::pair<long long , long long> p){return (p.second - p.first) >= size;});
        if(free_chunk_it != free_chunks.end() && free_chunk_it->first < chunk.first)
        {
            //std::cout << free_chunk_it->first << " " << free_chunk_it->second << std::endl;
            //std::cout << chunk.first << " " << chunk.second << std::endl;

            for(int i = 0; i < size; i++)
            {
                disk[i + free_chunk_it->first] = val;
                disk[i + chunk.first] =  -1;
            }
            free_chunks[std::distance(free_chunks.begin(), free_chunk_it)].first += size;

            for(int i = 0; i < 30; i++)
            {
                std::cout << disk[i];
            }
            std::cout << std::endl;
        }
    }
    




    
    /*std::cout << std::endl;
    for(long long i : disk)
        std::cout << i;


    std::cout << disk.size() << std::endl;*/
    
    long long checksum = 0;
    size_t i = 0;
    for(int ll : disk)
    {
        if(ll != -1)
        {
            checksum += ll*i;
        }

        i++;
        //std::cout << std::endl << checksum;
    }

    std::cout << checksum  << std::endl;

    return 0;
}