//
//  RGenerator.hpp
//  VM_L1
//
//  Created by Aleksandr Borzikh on 06.10.15.
//  Copyright © 2015 Aleksanteri. All rights reserved.
//

#ifndef RGenerator_hpp
#define RGenerator_hpp

#include <vector>
#include <fstream>
using namespace std;

class RGenerator
{
public:
    void CreateFile(const char* filename, int);
    RGenerator();
    ~RGenerator();
private:
    ofstream filestream_;
};

#endif /* RGenerator_hpp */
