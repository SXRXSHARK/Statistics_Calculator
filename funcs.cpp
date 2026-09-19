#include "funcs.h"


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
std::vector<double> readDataFromCSV(const std::string& filename) {
   std::vector<double> data;
   std::ifstream file(filename);
   if (!file.is_open()) {
       return data;  // Return empty vector if file cannot be opened
   }
   std::string line;
   while (std::getline(file, line)) {
       std::stringstream ss(line);
       std::string value;
       while (std::getline(ss, value, ',')) {
           data.push_back(std::stod(value));
       }
   }
   file.close();
   return data;
}




// Function to extract numbers from an image using OCR
std::vector<double> readDataFromImage(const std::string& filename) {
   std::vector<double> data;
   cv::Mat image = cv::imread(filename, cv::IMREAD_GRAYSCALE);


   if (image.empty()) {
       std::cout << "Error: Could not open or find the image.\n";
       return data;
   }


   // Initialize Tesseract API
   tesseract::TessBaseAPI ocr;
   if (ocr.Init("/users/slayra/desktop/CLionProjects/Calculator/cmake-build-debug/tesseract/tessdata", "eng", tesseract::OEM_LSTM_ONLY)) {
       std::cout << "Error: Could not initialize Tesseract OCR.\n";
       return data;
   }


   // Set image data for OCR
   ocr.SetImage(image.data, image.cols, image.rows, 1, image.step);
   ocr.Recognize(0);


   // Get OCR result as a string
   std::string text = std::string(ocr.GetUTF8Text());


   // Extract numbers from OCR result
   std::istringstream ss(text);
   std::string word;
   while (ss >> word) {
       try {
           double value = std::stod(word); // Convert word to double if it's a number
           data.push_back(value);
       } catch (const std::invalid_argument&) {
           // Skip non-numeric words
       }
   }


   ocr.End();
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
