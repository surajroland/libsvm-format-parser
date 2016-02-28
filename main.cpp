#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <vector>
#include "stat.h"

using namespace std;

int main()
{
    statistics* stat = new statistics();

    stat->parseData("example_file");
    stat->sparseToDense();
    stat->writeDenseData("example_file_dense_version");

    stat->expectation();
    stat->variance();

    stat->markNonZeroEntropyKeys();
    stat->writeStatistics("example_file_statistics");

    delete[] stat;

    return 0;
}





