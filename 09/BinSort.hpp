#include <algorithm>
#include <thread>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include <stdexcept>
#include <queue>
#include <iterator>
#include <cstdio>

//merge sorting,using temporary files(swappers)
namespace swapsort
{
    using data_type = uint64_t;
    using iter = std::istream_iterator<data_type>;
    using dup_iter = std::pair<iter,iter>;

    constexpr size_t availiable_mem = 8 * 1024 * 1024;//bytes
    constexpr size_t chunk_size =  1.5 * 1024 * 1024;//chunks sizes

    constexpr size_t data_type_size = sizeof(data_type);
    
    void writeBuffer(const std::shared_ptr<data_type>& buffer, size_t from, size_t to, std::string& fileName)
    {
        std::ofstream output(fileName);

        if(!output)
        {
            throw std::runtime_error(fileName);
        }
        
        for(size_t i = from; i < to;++i)
        {
            output << buffer.get()[i] << " ";
        }
        
        output.close();
    }

    void mergeChunks(const std::vector<std::string>& fileNames,const std::string& outPutFilename)
    {
        //let's use priority queue with Compare == less_firts. dup_iter is tuple of local and global iterators(chunk and chunks iterators)
        auto compare_less = [](const dup_iter& queueIter, const dup_iter& queueIterAnother) {
            return *(queueIter.first) > *(queueIterAnother.first);
        };
        //adding elems to priority queue and sorting it immediately
        std::priority_queue<dup_iter, std::vector<dup_iter>, decltype(compare_less)> pr_queue(compare_less);

        

        size_t left = fileNames.size();
        std::fstream sortedChunks[left];

        for(size_t i = left; i > 0;--i)
        {
            sortedChunks[i - 1].open(fileNames[i - 1]);
            pr_queue.emplace(iter(sortedChunks[i - 1]), iter());
        }

        std::ofstream out(outPutFilename);
        if (!out)
        {
            throw std::runtime_error(outPutFilename);
        }
        while (!pr_queue.empty())
         {
            dup_iter pair = pr_queue.top();
            pr_queue.pop();
            out << *pair.first << ' ';
            pair.first++;
           

            if (pair.first != pair.second)
            {
                pr_queue.emplace(pair);//next 
            }
        }
        out.close();
    }

    void fileSort(const std::string& fileName,const std::string& outPutFilename)
    {
        std::ifstream input(fileName);
        
        if(!input)
        {
            throw std::runtime_error(fileName);
        }

        std::shared_ptr<data_type> buffer(new data_type[chunk_size],std::default_delete<data_type[]>());
        
        size_t chunks = 0;
        std::vector<std::string> sortedChunkFilenames;//files with sorted chunks

        while(!input.eof())
        {
            input.read(reinterpret_cast<char*>(buffer.get()),chunk_size);
            size_t justRead = input.gcount() / data_type_size;//previously read
            size_t middleChunk = justRead / 2;
            
            sortedChunkFilenames.push_back("chunk_" + std::to_string(chunks) + ".txt");
            sortedChunkFilenames.push_back("chunk_" + std::to_string(chunks + 1) + ".txt");

            //now reading and sorting chunks
            //think that sort uses in avarage 2 * size of buffer: total size less than 8mb 
            if (justRead > 0)
            {
                std::thread chunk_1([buffer,middleChunk,justRead]()
                                    {
                                        std::sort(buffer.get(),buffer.get() + middleChunk,std::less<data_type>());
                                    }
                                );
                std::thread chunk_2([buffer,middleChunk,justRead]()
                                    {
                                        std::sort(buffer.get() + middleChunk,buffer.get() + justRead,std::less<data_type>());
                                    }
                                );

                chunk_1.join();
                chunk_2.join();
                
                writeBuffer(buffer,0,middleChunk,sortedChunkFilenames[chunks]);
                writeBuffer(buffer,middleChunk,justRead,sortedChunkFilenames[chunks + 1]);

                chunks += 2;      
            }   
        }
        input.close();
        mergeChunks(sortedChunkFilenames,outPutFilename);


        //remove chunk_ files
        for(size_t i = 0; i < sortedChunkFilenames.size();++i)
        {
            std::remove(sortedChunkFilenames[i].c_str());
        }

    }

    void generateRandom(const std::string& target,size_t number)
    {
        std::ofstream out(target);
        if (!out)
        {
            throw std::runtime_error(target);
        }
        for(size_t i = 0; i < number;++i)
        {
            data_type randGenerated = std::rand() % number;
            out.write(reinterpret_cast<char*>(&randGenerated), data_type_size);
        }
        out.close();
    }
};





