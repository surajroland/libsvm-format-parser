#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <vector>
#include "stat.h"

using namespace std;


void statistics::parseData(const char* _path_to_file){

	ifstream db(_path_to_file);
	string line;

	while(std::getline(db, line))
	{
		istringstream stream(line);
	    string l, pair, k, v;
	    string delimiter(":");

	    int label;
	    vector<unsigned int> keys;
	    vector<double> values;

	    stream >> l;
	    label = std::atoi(l.c_str());

	    while (stream >> pair)
	    {
	    	size_t pos = pair.find(delimiter);

	    	k = pair.substr(0, pos);
	    	v = pair.substr(pos+1, std::string::npos);

	    	keys.push_back((unsigned int)std::atoi(k.c_str()));
	    	values.push_back(std::strtod(v.c_str(),NULL));
	    }

		sample samp(label, keys, values);
		sparseDataset.push_back(samp);

	}
}



void statistics::sparseToDense(void){

	dimFeatures = 0;
	numSamples = sparseDataset.size();

	for (int i=0; i<numSamples; ++i)
	{
		int current_dim = sparseDataset[i].keys.back();

		if (current_dim>dimFeatures)
		{
			dimFeatures = current_dim;
		}
	}

	int totalDenseCols = dimFeatures + 1;
	denseDataset = new double[(size_t)(numSamples * totalDenseCols)];

    for(int i=0; i<numSamples; ++i)
    {
    	for(int j=0; j<totalDenseCols; ++j)
    	{
    		std::vector<unsigned int>::iterator it_key_begin, it_key_end;
            it_key_begin = sparseDataset[i].keys.begin();
            it_key_end = sparseDataset[i].keys.end();
            int act_pos = find(it_key_begin, it_key_end, j)-it_key_begin;

            int pos = i*totalDenseCols+j;

    		if (j == 0)
    		{
    			denseDataset[pos] = sparseDataset[i].label;
    		}
    		else if (act_pos < sparseDataset[i].keys.size())
    		{
    			denseDataset[pos] = sparseDataset[i].values[act_pos];
    		}
    		else
    		{
    			denseDataset[pos] = 0;
    		}
    	}
    }
}



void statistics::writeDenseData(const char* _path_to_file)
{
	std::remove(_path_to_file);
	std::ofstream db(_path_to_file);
	std::ostringstream out;
    string str;

	int totalDenseCols = dimFeatures + 1;
	for (int i=0; i<numSamples; ++i)
	{
		for (int j=0; j<totalDenseCols; ++j)
		{
			out << denseDataset[i*totalDenseCols+j] <<" ";
        }
		out << "\n";
	}

	db << out.str();
	db.close();
}




void statistics::writeStatistics(const char* _path_to_file)
{
	std::remove(_path_to_file);
	std::ofstream db(_path_to_file);
	std::ostringstream out;
    string str;

    // expectation for label -1
    out << -1 <<" ";
	for (int k=0; k<nonZeroEntropyKeys[0].size(); ++k)
	{
		out << nonZeroEntropyKeys[0][k] << ":" << mu[0][nonZeroEntropyKeys[0][k]] << " ";
	}
	out << "\n";

	// variance for label -1
    out << -1 <<" ";
	for (int k=0; k<nonZeroEntropyKeys[0].size(); ++k)
	{
		out << nonZeroEntropyKeys[0][k] << ":" << sigma[0][nonZeroEntropyKeys[0][k]] << " ";
	}
	out << "\n";

	// expectation for label 1
    out << 1 <<" ";
	for (int k=0; k<nonZeroEntropyKeys[1].size(); ++k)
	{
		out << nonZeroEntropyKeys[1][k] << ":" << mu[1][nonZeroEntropyKeys[1][k]] << " ";
	}
	out << "\n";

	// variance for label 1
    out << 1 <<" ";
	for (int k=0; k<nonZeroEntropyKeys[1].size(); ++k)
	{
		out << nonZeroEntropyKeys[1][k] << ":" << sigma[1][nonZeroEntropyKeys[1][k]] << " ";
	}
	out << "\n";

	db << out.str();
	db.close();
}



void statistics::markNonZeroEntropyKeys(void)
{
	  std::vector<double>:: iterator it_mu_0_begin = mu[0].begin(), it_sigma_0_begin = sigma[0].begin();
	  std::vector<double>:: iterator it_mu_0 = it_mu_0_begin, it_sigma_0 = it_sigma_0_begin;
	  std::vector<double>:: iterator it_mu_0_end= mu[0].end();

	  while(it_mu_0 != it_mu_0_end)
	  {
	   	 if (*it_mu_0 != 0 && *it_sigma_0 != 0)
	   	 {
	   		 nonZeroEntropyKeys[0].push_back(it_mu_0-it_mu_0_begin);
	   	 }
	   	 it_mu_0++;
	   	 it_sigma_0++;
	  }

	  std::vector<double>:: iterator it_mu_1_begin = mu[1].begin(), it_sigma_1_begin = sigma[1].begin();
	  std::vector<double>:: iterator it_mu_1 = it_mu_1_begin, it_sigma_1 = it_sigma_1_begin;
      std::vector<double>:: iterator it_mu_1_end= mu[1].end();

	  while(it_mu_1 != it_mu_1_end)
	  {
	   	 if (*it_mu_1 != 0 && *it_sigma_1 != 0)
	     {
	    	nonZeroEntropyKeys[1].push_back(it_mu_1-it_mu_1_begin);
    	 }
	   	 it_mu_1++;
	   	 it_sigma_1++;
	  }
}




void statistics::expectation(void)
{
	int totalDenseCols = dimFeatures + 1;
	for(int j=1; j<totalDenseCols; ++j)
    {
		double expNeg, expPos;
		expNeg = expPos = 0;

	    int numPosSamples, numNegSamples;
	    numPosSamples = numNegSamples = 0;

		for(int i=0; i<numSamples; ++i)
    	{
		    int pos = i*totalDenseCols;

    		if (denseDataset[pos] == -1)
    		{
    			expNeg += denseDataset[pos+j];
    			numNegSamples++;
    		}
    		if (denseDataset[pos] == 1)
    		{
    			expPos += denseDataset[pos+j];
    			numPosSamples++;
    		}
    	}
		mu[0].push_back(expNeg/numNegSamples);
		mu[1].push_back(expPos/numPosSamples);
    }
}


void statistics::variance(void)
{
	int totalDenseCols = dimFeatures + 1;
	for(int j=1; j<totalDenseCols; ++j)
    {
		double varNeg, varPos;
		varNeg = varPos = 0;

	    int numPosSamples, numNegSamples;
	    numPosSamples = numNegSamples = 0;

		for(int i=0; i<numSamples; ++i)
    	{
		    int pos = i*totalDenseCols;

    		if (denseDataset[pos] == -1)
    		{
    			varNeg += denseDataset[pos+j] * denseDataset[pos+j];
    			numNegSamples++;
    		}
    		if (denseDataset[pos] == 1)
    		{
    			varPos += denseDataset[pos+j] * denseDataset[pos+j];
    			numPosSamples++;
    		}
    	}
		sigma[0].push_back(varNeg/numNegSamples);
		sigma[1].push_back(varPos/numPosSamples);
    }

	for (int k=0; k<dimFeatures; k++)
	{
		sigma[0][k] = sigma[0][k]-(mu[0][k]*mu[0][k]);
		sigma[1][k] = sigma[1][k]-(mu[1][k]*mu[1][k]);
	}
}








