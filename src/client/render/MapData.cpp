#include "MapData.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string.h>
#include <thread>
#include <pthread.h>
#include <vector>
#include <sstream>
#include <iterator>

using namespace std;

std::vector<int> getDataFromFile(std::string path){
    std::string text;
    ifstream myfile (path);
    if (myfile.is_open())
    {
        while ( getline (myfile, text) ) {
            // cout << text << '\n';
        }
      myfile.close();

    vector<int> numbers;

    stringstream text_stream(text);
    string item;
    while (std::getline(text_stream, item, ',')) {
        numbers.push_back(stoi(item));
    }

    /*for (auto &n : numbers) {
        printf("%d,", n);
    }*/

      return numbers;
  }
  else cout << "Unable to open file"; 
}