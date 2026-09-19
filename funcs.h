#ifndef FUNCS_H
#define FUNCS_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>
#include "leptonica/allheaders.h"

// Function prototypes
double calculateMean(const std::vector<double>& data);
double calculateMedian(std::vector<double> data);
double calculateMode(const std::vector<double>& data);
double calculateVariance(const std::vector<double>& data, double mean);
double calculateStandardDeviation(double variance);

std::vector<double> inputDataManually();
std::vector<double> readDataFromCSV(const std::string& filename);
std::vector<double> readDataFromImage(const std::string& filename);
void plotDataWithGnuplot(const std::vector<double>& data, const std::string& title);
void compareData(const std::vector<double>& data1, const std::vector<double>& data2);

char getValidCharInput(const std::string& prompt, const std::string& validInputs);

#endif // FUNCS_H

