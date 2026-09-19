#include "funcs.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <limits>
#include <cctype>

#ifdef _WIN32
#include <stdio.h>
#define popen _popen
#define pclose _pclose
#endif

char getValidCharInput(const std::string& prompt, const std::string& validInputs) {
   char input;
   while (true) {
       std::cout << prompt;
       std::cin >> input;
       input = toupper(input);
       if (validInputs.find(input) != std::string::npos && validInputs.length() > 0) {
           return input; // Valid input
       }
       std::cout << "Invalid input. Please enter one of the following: " << validInputs << "\n";
   }
}


// Function to calculate the mean
double calculateMean(const std::vector<double>& data) {
   double sum = 0;
   for (double num : data) {
       sum += num;
   }
   return sum / data.size();
}

// Function to calculate the median
double calculateMedian(std::vector<double> data) {
   std::sort(data.begin(), data.end());
   size_t size = data.size();
   if (size % 2 == 0) {
       return (data[size / 2 - 1] + data[size / 2]) / 2.0;
   } else {
       return data[size / 2];
   }
}

// Function to calculate the mode
double calculateMode(const std::vector<double>& data) {
   std::unordered_map<double, int> frequency;
   for (double num : data) {
       frequency[num]++;
   }
   int maxCount = 0;
   double mode = data[0];
   for (const auto& [key, count] : frequency) {
       if (count > maxCount) {
           maxCount = count;
           mode = key;
       }
   }
   return mode;
}

// Function to calculate the variance
double calculateVariance(const std::vector<double>& data, double mean) {
   double sum = 0.0;
   for (double num : data) {
       sum += (num - mean) * (num - mean);
   }
   return sum / data.size();
}

// Function to calculate the standard deviation
double calculateStandardDeviation(double variance) {
   return std::sqrt(variance);
}

// Dummy function to input data manually
// Function to input data manually
std::vector<double> inputDataManually() {
   std::vector<double> data;
   int n;

   while (true) {
       std::cout << "Enter the number of elements: ";
       std::cin >> n;

       if (std::cin.fail() || n <= 0) {
           std::cin.clear(); // Clear the error state
           std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
           std::cout << "Invalid input. Please enter a positive integer.\n";
       } else {
           break; // Valid input
       }
   }

   std::cout << "Enter the elements:\n";
   for (int i = 0; i < n; i++) {
       double value;

       while (true) {
           std::cout << "Element " << i + 1 << ": ";
           std::cin >> value;

           if (std::cin.fail()) {
               std::cin.clear(); // Clear the error state
               std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
               std::cout << "Invalid input. Please enter a numeric value.\n";
           } else {
               data.push_back(value);
               break; // Valid input
           }
       }
   }

   return data;
}

// Function to read data from CSV file
std::vector<double> readDataFromCSV(const std::string& filename)
{
    std::vector<double> data;

    // Copy the filename so we can modify it
    std::string path = filename;

    // Remove quotation marks if the user enters the path like:
    // "C:\Users\saras\...\TestBook.csv"
    if (path.length() >= 2 &&
        path.front() == '"' &&
        path.back() == '"')
    {
        path = path.substr(1, path.length() - 2);
    }

    // Open the CSV file
    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cerr << "ERROR: Could not open CSV file:\n";
        std::cerr << path << std::endl;

        return data;
    }

    std::string line;
    bool firstLine = true;

    // Read the file line by line
    while (std::getline(file, line))
    {
        // Remove Windows carriage return if present
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }

        // Remove UTF-8 BOM from the first line
        // Excel can add this when saving as "CSV UTF-8"
        if (firstLine)
        {
            const std::string bom = "\xEF\xBB\xBF";

            if (line.size() >= 3 &&
                line.compare(0, 3, bom) == 0)
            {
                line.erase(0, 3);
            }

            firstLine = false;
        }

        // Skip empty lines
        if (line.empty())
        {
            continue;
        }

        // Split the line using commas
        std::stringstream ss(line);
        std::string value;

        while (std::getline(ss, value, ','))
        {
            // Remove leading and trailing spaces
            size_t start = value.find_first_not_of(" \t\r\n");
            size_t end = value.find_last_not_of(" \t\r\n");

            if (start == std::string::npos)
            {
                continue;
            }

            value = value.substr(start, end - start + 1);

            // Convert the value to a double
            try
            {
                double number = std::stod(value);

                data.push_back(number);
            }
            catch (const std::invalid_argument&)
            {
                std::cerr << "Warning: Could not convert '"
                          << value
                          << "' to a number. Skipping it."
                          << std::endl;
            }
            catch (const std::out_of_range&)
            {
                std::cerr << "Warning: Value '"
                          << value
                          << "' is out of range. Skipping it."
                          << std::endl;
            }
        }
    }

    file.close();

    // Display how many values were loaded
    std::cout << "Successfully loaded "
              << data.size()
              << " values from CSV."
              << std::endl;

    return data;
}





// Function to extract numbers from an image using OCR
std::vector<double> readDataFromImage(const std::string& filename)
{
    std::vector<double> data;

    // Copy the filename so we can modify it
    std::string path = filename;

    // Remove quotation marks if the user enters the path like:
    // "C:\Users\saras\...\image.png"
    if (path.length() >= 2 &&
        path.front() == '"' &&
        path.back() == '"')
    {
        path = path.substr(1, path.length() - 2);
    }

    // Open the image
    cv::Mat image = cv::imread(path, cv::IMREAD_GRAYSCALE);

    if (image.empty())
    {
        std::cout << "Error: Could not open or find the image:\n";
        std::cout << path << std::endl;
        return data;
    }

    // Initialize Tesseract OCR
    tesseract::TessBaseAPI ocr;

    if (ocr.Init(
        "C:/Program Files/Tesseract-OCR/tessdata",
        "eng",
        tesseract::OEM_LSTM_ONLY))
    {
        std::cout << "Error: Could not initialize Tesseract OCR.\n";
        return data;
    }

    // Set image data for OCR
    ocr.SetImage(
        image.data,
        image.cols,
        image.rows,
        1,
        image.step
    );

    // Run OCR
    ocr.Recognize(0);

    // Get OCR result
    char* output = ocr.GetUTF8Text();

    if (output == nullptr)
    {
        std::cout << "Error: Tesseract could not extract text from image.\n";
        ocr.End();
        return data;
    }

    std::string text(output);

    delete[] output;

    // Extract numbers from OCR result
    std::istringstream ss(text);
    std::string word;

    while (ss >> word)
    {
        try
        {
            double value = std::stod(word);
            data.push_back(value);
        }
        catch (const std::invalid_argument&)
        {
            // Ignore words that are not numbers
        }
        catch (const std::out_of_range&)
        {
            // Ignore numbers that are too large
        }
    }

    ocr.End();

    std::cout << "Successfully extracted "
              << data.size()
              << " values from image."
              << std::endl;

    return data;
}



// Function to plot data using Gnuplot
void plotDataWithGnuplot(const std::vector<double>& data, const std::string& title) {
   FILE *gnuplot = popen("gnuplot -persistent", "w");
   if (!gnuplot) {
       std::cerr << "Error: Gnuplot not available.\n";
       return;
   }
   fprintf(gnuplot, "set title '%s'\n", title.c_str());
   fprintf(gnuplot, "plot '-' with lines title 'Data'\n");
   for (size_t i = 0; i < data.size(); ++i) {
       fprintf(gnuplot, "%zu %f\n", i + 1, data[i]);
   }
   fprintf(gnuplot, "e\n");
   pclose(gnuplot);
}


// Function to prompt the user for a valid file path
std::string getValidFilePath(const std::string& prompt) {
   std::string filePath;

   while (true) {
       std::cout << prompt;
       std::getline(std::cin, filePath);

       // Check if the file exists
       std::ifstream file(filePath);
       if (file) {
           file.close();
           break; // Exit the loop if the file is valid
       } else {

       }
   }

   return filePath;
}
// Function to plot data using Gnuplot
void plotGraph(const std::vector<double>& data) {
   FILE *gnuplot = popen("gnuplot -persistent", "w");
   if (!gnuplot) {
       std::cerr << "Error: Gnuplot not available.\n";
       return;
   }

   // Set up Gnuplot for plotting
   fprintf(gnuplot, "set title 'Graph of Data'\n");
   fprintf(gnuplot, "plot '-' with lines title 'Data'\n");

   // Loop through data and send to Gnuplot
   for (size_t i = 0; i < data.size(); ++i) {
       fprintf(gnuplot, "%zu %f\n", i + 1, data[i]);
   }

   fprintf(gnuplot, "e\n");
   pclose(gnuplot);
}
void compareData(const std::vector<double>& data1, const std::vector<double>& data2) {
   if (data1.empty() || data2.empty()) {
       std::cout << "Error: One or both datasets are empty. Cannot perform comparison.\n";
       return;
   }

   FILE *gnuplot = popen("gnuplot -persistent", "w");
   if (!gnuplot) {
       std::cerr << "Error: Gnuplot not available.\n";
       return;
   }
   fprintf(gnuplot, "set title 'Data Comparison'\n");
   fprintf(gnuplot, "plot '-' with lines title 'Dataset 1', '-' with lines title 'Dataset 2'\n");

   for (size_t i = 0; i < data1.size(); ++i) {
       fprintf(gnuplot, "%zu %f\n", i + 1, data1[i]);
   }
   fprintf(gnuplot, "e\n");

   for (size_t i = 0; i < data2.size(); ++i) {
       fprintf(gnuplot, "%zu %f\n", i + 1, data2[i]);
   }
   fprintf(gnuplot, "e\n");

   pclose(gnuplot);
}

