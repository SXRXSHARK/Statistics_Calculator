#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <unordered_map>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>
#include "leptonica/allheaders.h"
#include "funcs.h"




int main() {
   char rerun;
   char compareChoice;
   std::vector<double> data1, data2;
   int choice;


   // Prompt for data input choice with validation
   do {
       while (true) {
           std::cout << "\n----------- Main menu -----------\n";
           std::cout << "| Choose an option                 |\n";
           std::cout << "| 1. Input Data Manually           |\n";
           std::cout << "| 2. Input Data from CSV file      |\n";
           std::cout << "| 3. Input Data from Image file    |\n";
           std::cout << "|                                  |\n";
           std::cout << "-----------------------------------\n";
           std::cout << "Enter your choice: ";


           std::cin >> choice;


           if (std::cin.fail() || choice < 1 || choice > 3) {
               std::cin.clear(); // Clear error state
               std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
               std::cout << "Invalid choice. Please enter a valid option (1, 2, or 3).\n";
           } else {
               break;
           }
       }


       // Handle data input based on choice
       if (choice == 1) {
           data1 = inputDataManually();
       } else {
           std::string filename;
           bool validFile = false;


           // Prompt for a valid file path
           while (!validFile) {
               std::cout << "Enter the " << (choice == 2 ? "CSV" : "image") << " file path: ";
               std::cin >> filename;


               if (choice == 2) {
                   data1 = readDataFromCSV(filename);
               } else {
                   data1 = readDataFromImage(filename);
               }


               if (data1.empty()) {
                   std::cout << "Invalid file path or empty data..\n";
               } else {
                   validFile = true;
               }
           }
       }


       // Check if data is successfully loaded
       if (!data1.empty()) {
           std::cout << "Data loaded successfully.\n";
       }


       do {
           std::cout << "Do you want to compare this dataset with another? (Y/N): ";
           std::cin >> compareChoice;


           if (compareChoice != 'Y' && compareChoice != 'N' && compareChoice != 'y' && compareChoice != 'n') {
               std::cout << "Invalid input. Please enter 'Y' for yes or 'N' for no.\n";
           } else if (compareChoice == 'N' || compareChoice == 'n') {
               // User doesn't want to compare datasets, so perform an operation on the first dataset
               while (true) {
                   std::cout << "\n------- Choose an operation -------\n";
                   std::cout << "|                                   |\n";
                   std::cout << "|   1. Calculate Mean               |\n";
                   std::cout << "|   2. Calculate Median             |\n";
                   std::cout << "|   3. Calculate Mode               |\n";
                   std::cout << "|   4. Calculate Variance           |\n";
                   std::cout << "|   5. Calculate Standard Deviation |\n";
                   std::cout << "|   6. Plot Graph                   |\n";
                   std::cout << "|                                   |\n";
                   std::cout << "-------------------------------------\n";
                   std::cout << "Enter your choice: ";


                   std::cin >> choice;


                   if (std::cin.fail() || choice < 1 || choice > 6) {
                       std::cin.clear(); // Clear error state
                       std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                       std::cout << "Invalid choice. Please enter a number between 1 and 6.\n";
                   } else {
                       break;
                   }
               }


               switch (choice) {
                   case 1: std::cout << "Mean of dataset: " << calculateMean(data1) << std::endl; break;
                   case 2: std::cout << "Median of dataset: " << calculateMedian(data1) << std::endl; break;
                   case 3: std::cout << "Mode of dataset: " << calculateMode(data1) << std::endl; break;
                   case 4: std::cout << "Variance of dataset: " << calculateVariance(data1, calculateMean(data1)) << std::endl; break;
                   case 5: std::cout << "Standard Deviation of dataset: " << calculateStandardDeviation(calculateVariance(data1, calculateMean(data1))) << std::endl; break;
                   case 6: plotDataWithGnuplot(data1, "Dataset Plot"); break;
               }
           }
       } while (compareChoice != 'Y' && compareChoice != 'y' && compareChoice != 'N' && compareChoice != 'n');


       if (compareChoice == 'Y' || compareChoice == 'y') {
           while (true) {
               std::cout << "\n----------- Main menu -----------\n";
               std::cout << "| Choose an option                 |\n";
               std::cout << "| 1. Input Data Manually           |\n";
               std::cout << "| 2. Input Data from CSV file      |\n";
               std::cout << "| 3. Input Data from Image file    |\n";
               std::cout << "|                                  |\n";
               std::cout << "-----------------------------------\n";
               std::cout << "Enter your choice: ";


               std::cin >> choice;


               if (std::cin.fail() || choice < 1 || choice > 3) {
                   std::cin.clear(); // Clear error state
                   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                   std::cout << "Invalid choice. Please enter a valid option (1, 2, or 3).\n";
               } else {
                   break;
               }
           }


           // Handle data input based on choice
           if (choice == 1) {
               data2 = inputDataManually();
           } else {
               std::string filename;
               bool validFile = false;


               // Prompt for a valid file path
               while (!validFile) {
                   std::cout << "Enter the " << (choice == 2 ? "CSV" : "image") << " file path: ";
                   std::cin >> filename;


                   if (choice == 2) {
                       data2 = readDataFromCSV(filename);
                   } else {
                       data2 = readDataFromImage(filename);
                   }


                   if (data2.empty()) {
                       std::cout << "Invalid file path or empty data..\n";
                   } else {
                       validFile = true;
                   }
               }
           }


           // Check if data is successfully loaded
           if (!data2.empty()) {
               std::cout << "Data loaded successfully.\n";
           }


           while (true) {
               std::cout << "\n------- Choose an operation -------\n";
               std::cout << "|                                   |\n";
               std::cout << "|   1. Calculate Mean               |\n";
               std::cout << "|   2. Calculate Median             |\n";
               std::cout << "|   3. Calculate Mode               |\n";
               std::cout << "|   4. Calculate Variance           |\n";
               std::cout << "|   5. Calculate Standard Deviation |\n";
               std::cout << "|   6. Plot Graph                   |\n";
               std::cout << "|                                   |\n";
               std::cout << "-------------------------------------\n";
               std::cout << "Enter your choice: ";


               std::cin >> choice;


               if (std::cin.fail() || choice < 1 || choice > 6) {
                   std::cin.clear(); // Clear error state
                   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                   std::cout << "Invalid choice. Please enter a number between 1 and 6.\n";
               } else {
                   break;
               }
           }


           switch (choice) {
               case 1:
                   std::cout << "Mean of dataset 1: " << calculateMean(data1) << " , "
                             << "Mean of dataset 2: " << calculateMean(data2) << std::endl;
               break;
               case 2:
                   std::cout << "Median of dataset 1: " << calculateMedian(data1) << " , "
                             << "Median of dataset 2: " << calculateMedian(data2)  << std::endl;
               break;
               case 3:
                   std::cout << "Mode of dataset 1: " << calculateMode(data1) << " , "
                             << "Mode of dataset 2: " << calculateMode(data2) << std::endl;
               break;
               case 4:
                   std::cout << "Variance of dataset 1: " << calculateVariance(data1, calculateMean(data1)) << " , "
                             << "Variance of dataset 2: " << calculateVariance(data2, calculateMean(data2)) << std::endl;
               break;
               case 5:
                   std::cout << "Standard Deviation of dataset 1: " << calculateStandardDeviation(calculateVariance(data1, calculateMean(data1))) << " , "
                             << "Standard Deviation of dataset 2: " << calculateStandardDeviation(calculateVariance(data2, calculateMean(data2))) << std::endl;
               break;
               case 6:
                   compareData(data1, data2);
               break;
           }
       }




           std::cout << "Do you want to rerun the program? (Y/N): ";
           std::cin >> rerun;


           // Convert input to uppercase to handle lowercase inputs
           rerun = toupper(rerun);


           // Input validation loop
           while (rerun != 'Y' && rerun != 'N') {
               std::cout << "Invalid input. Please enter 'Y' or 'N': ";
               std::cin >> rerun;
               rerun = toupper(rerun); // Ensure uppercase
           }


       } while (rerun == 'Y'); // Continue if the user enters 'Y'


       std::cout << "Program exited. Have a nice day!" << std::endl;
       return 0;
   }
