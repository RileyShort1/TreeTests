
#include "Splay_Tree.h"
#include "AVL_Tree.h"

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <chrono>
#include <random>
#include <algorithm>
using namespace std::chrono;

class Benchmark {
private:

    // fill tree with numbers 1 - tree size (shuffled order)
    void build_tree(Splay_Tree<int>& splay_tree, AVL_Tree<int>& avl_tree, const unsigned int seed, const int treeSize)
    {
        // delete everything in tree
        splay_tree.clear();
        avl_tree.clear();

        std::vector<int> rands;

        for (int i = 1; i < treeSize + 1; i++)
        {
            rands.push_back(i);
        }

        auto rng = std::default_random_engine(seed);
        std::shuffle(std::begin(rands), std::end(rands), rng);

        for (size_t j = 0; j < rands.size(); j++)
        {
            splay_tree.insert(rands[j]);
            avl_tree.insert(rands[j]);
        }

        return;
    }

    void get_array_gaussian(std::vector<int>& randNums, const unsigned int randSeed, const double stddev, const int numRands, const int treeSize)
    {
        // Mersenne Twister random engine
        std::mt19937 randEngine(randSeed);
        double mean = treeSize / 2.0;

        std::normal_distribution<double> generator(mean, stddev);

        randNums.clear();

        for (int i = 0; i < numRands; i++)
        {
            randNums.push_back(double(generator(randEngine)));
        }

        return;
    }

public: // ################################# PUBLIC ######################################

    void searchTests(std::string fileName, const double stddev, const int treeSize)
    {
        AVL_Tree<int> avl_tree;
        Splay_Tree<int> splay_tree;

        // Consts for loop values/testing values
        const int num_finds = 50000;
        const int num_seeds_tested = 10;
        const int num_trees_per_seed = 5;

        double total_over_all_avl_trees = 0;
        double total_over_all_splay_trees = 0;

        double avg_time_per_find_avl;
        double avg_time_per_find_splay;

        double time_per_batch_avl = 0;
        double time_per_batch_splay = 0;

        size_t avgTreeSize = 0;
        int programTime = 0;
        std::vector<int> nums_to_find; // vector to store find values

        
        std::fstream find; // output file
        find.open(fileName, std::ios::out | std::ios::app);

        find << "Rand seeds 0-" << num_seeds_tested - 1 << ", " << "Stddev of finds = " << stddev << ", "
            << "Finding " << num_finds << " normal" << ", " << "AVL and Splay Tree with microsecond time containing nums 0 - " << treeSize << "\n"
            << "mean of searched data is half tree size\n";
        find.close();
        

        for (int seed = 0; seed < num_seeds_tested; seed++)
        {
            programTime++; // progress tracker
            std::cout << programTime << " / " << num_seeds_tested << "\n";

            for (int num_trees = 0; num_trees < num_trees_per_seed; num_trees++) // how many trees tested per single seed
            {
                // build both trees
                build_tree(splay_tree, avl_tree, seed, treeSize); 

                get_array_gaussian(nums_to_find, seed, stddev, num_finds, treeSize); // get nums to find
                avgTreeSize += avl_tree.get_size();         

                // reset batch values
                time_per_batch_avl = 0;
                time_per_batch_splay = 0;

                for (int num_find_calls = 0; num_find_calls < num_finds; num_find_calls++)
                {
                    // AVL Time
                    auto start_avl = high_resolution_clock::now();
                    avl_tree.contains(nums_to_find[num_find_calls]);
                    auto stop_avl = high_resolution_clock::now();
                    duration<double, std::micro> single_time_avl = stop_avl - start_avl;

                    // Splay Time
                    auto start_splay = high_resolution_clock::now();
                    avl_tree.contains(nums_to_find[num_find_calls]);
                    auto stop_splay = high_resolution_clock::now();
                    duration<double, std::micro> single_time_splay = stop_splay - start_splay;

                    // add times
                    time_per_batch_avl += single_time_avl.count(); // add single find time to pool of times for avl tree k
                    time_per_batch_splay += single_time_splay.count(); // add single find time to pool of times for splay tree k
                }

                // avg single find time for tree x (total time / num find operations)
                time_per_batch_avl /= num_finds; 
                time_per_batch_splay /= num_finds;

                // adds avg find time of items in tree k 
                total_over_all_avl_trees += time_per_batch_avl; 
                total_over_all_splay_trees += time_per_batch_splay;
            }
        }

        // divide by total trees tested to get avg time across all trees
        avg_time_per_find_avl = total_over_all_avl_trees / (double(num_seeds_tested) * double(num_trees_per_seed));
        avg_time_per_find_splay = total_over_all_splay_trees / (double(num_seeds_tested) * double(num_trees_per_seed));


        avgTreeSize /= (num_seeds_tested * num_trees_per_seed); // get avg tree size

        // output file
        //std::fstream find;
        find.open(fileName, std::ios::out | std::ios::app);

        find << std::fixed << std::setprecision(4) << "AVL avg time: " << avg_time_per_find_avl << ", " << avgTreeSize << "\n" <<
            "Splay avg time: " << avg_time_per_find_splay << ", " << avgTreeSize << "\n\n";

        find.close();

        return;
    }
    /*
    void testImpulseSplay(double stddev, std::string filename)
    {
        SplayTree<int> tree;
        std::vector<double> times(100, 0.0);
        std::vector<int> finds;
        int programTime = 0;

        for (size_t seed = 0; seed < 25; seed++)
        {
            programTime++;
            std::cout << programTime << " / 25\n";

            for (int num_tree = 0; num_tree < 5; num_tree++) // 5 trees of identical nature
            {
                gaussian(finds, seed, stddev, 100, 1000000);
                build_tree(tree, seed, 1000000);

                for (size_t i = 0; i < finds.size(); i++)
                {
                    auto start = high_resolution_clock::now();
                    tree.contains(finds[i]);
                    auto stop = high_resolution_clock::now();
                    duration<double, std::micro> single_time = stop - start;
                    times[i] += single_time.count();
                }
            }
        }

        std::fstream SplayFind1; // output file
        SplayFind1.open(filename, std::ios::out | std::ios::app);
        SplayFind1 << "col_1" << "," << "col_2" << "\n";

        for (size_t j = 0; j < times.size(); j++)
        {
            SplayFind1 << j + 1 << "," << (times[j] / 125) << "\n";
        }

        SplayFind1.close();

        return;
    }
    */

};


int main()
{
    Benchmark testClass;

   // auto start = high_resolution_clock::now();

    for (double i = 1.0; i < 30.0; i++)
    {
        testClass.searchTests("testTimes.csv", i, 1000000);
    }

    //auto stop = high_resolution_clock::now();

   // auto duration = duration_cast<minutes>(stop - start);

   // std::cout << "Time taken by function: "
       // << duration.count() << " minutes" << std::endl;

    return 0;
}


