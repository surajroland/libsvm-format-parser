#ifndef STAT
#define STAT

using namespace std;

typedef struct sample{
    int label;
    std::vector<unsigned int>keys;
    std::vector<double>values;
    sample(){}
    sample(int _label): label(_label){}
    sample(int _label,
           std::vector<unsigned int>_keys,
           std::vector<double>_values): label(_label),
                                        keys(_keys),
                                        values(_values){}
    ~sample(){}
}sample;

class statistics{
private:
    int numSamples;
    int dimFeatures;
    std::vector<sample> sparseDataset;
    double* denseDataset;
    std::vector<double> mu[2];
    std::vector<double> sigma[2];
    std::vector<unsigned int>nonZeroEntropyKeys[2];

public:
    statistics(){}
    ~statistics(){}
    void parseData(const char* _path_to_file);
    void writeDenseData(const char* _path_to_file);
    void writeStatistics(const char* _path_to_file);
    void markNonZeroEntropyKeys(void);
    void sparseToDense(void);
    void denseToSparse(void);
    void expectation(void);
    void variance(void);
};

#endif
