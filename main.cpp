/*************************************************************************************
 *  Name: Akardet Sam Tancharoensuksavai
 *  Course: 4110.002 - Algorithms
 *  Assignment: Homework 1
 *  Date: 09/29/16
 *  Description: Implement a counting sort as explained in Section 8.2 of CLRS. 
 *               The input should be in a text file whose name is passed as a 
 *               command line argument (not redirected).
 *************************************************************************************/
 

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

int findMax(vector<int> numbers);
vector<int> openFile(int argc, const char * argv[]);
void countingSort(vector<int> input, vector<int> & count, vector<int> & sumCount, vector<int> & sortedInput);
void print(vector<int> input, vector<int> & count, vector<int> & sumCount, vector<int> & sortedInput);
void printInput(vector<int> input);
void printCount(vector<int> array);

int MAX_INT = 0;
size_t INPUT_SIZE = 0;

int main(int argc, const char * argv[]) {
    
    vector<int> numbers;
    
    numbers = openFile(argc, argv);
    INPUT_SIZE = numbers.size(); //number of digits read from the file
    MAX_INT = findMax(numbers); //largest integer from the file
    
    vector<int> count, sumCount, sortedInput;
    count.resize(MAX_INT+1);
    sumCount.resize(MAX_INT+1);
    sortedInput.resize(INPUT_SIZE);
    
    countingSort(numbers, count, sumCount, sortedInput);
    print(numbers, count, sumCount, sortedInput);
    
    return 0;
}

/*
 countingSort - Order digits from smallest to largest
 @params - vector<int> input - unsorted vector of digits from input file
           vector<int> & count - vector array to keep count of the frequency of each digit
           vector<int> & sumCount - vector array used to sort digits based on count
           vector<int> & sortedInput - populate elements in array in sorted order using count and sumCount vecor arrays
 */
void countingSort(vector<int> input, vector<int> & count, vector<int> & sumCount, vector<int> & sortedInput) {
   
    //increment count[] at position input[i]
    for (int i=0; i < INPUT_SIZE; i++)
    {
        count[input[i]]++;
    }

    //each element at each index stores the sum of the previous counts
    sumCount[0] += count[0];
    for (int i=1; i <= MAX_INT; i++)
    {
        sumCount[i] = sumCount[i-1] + count[i];
    }
    
    //output each number from the input sequence and decrement
    for (int i=0; i < INPUT_SIZE; i++)
    {
        sortedInput[sumCount[input[i]]-1] = input[i];
        --sumCount[input[i]];
    }
    
}

/*
 openFile - opens file from commandline
 @params - int argc - number of arguments
           const char * argv[] - each argument string from commandline
 @returns - vector<int> - vector array of digits from input file
*/
vector<int> openFile(int argc, const char * argv[]) {
    vector<int> numbers;
   
    //check if user passed filename
    if (argc != 2)
        cout<<"usage: "<< argv[0] <<" <filename>\n";
    else {
        ifstream File (argv[1]);
        
        //check if file opened properly
        if (!File.is_open())
            cout << "Could not open file\n";
        else {
            //read each number into number vector
            int number;
            while (File >> number)
                numbers.push_back(number);
        }
        
        File.close();
    }
    
    return numbers;
}

/*
 findMax - find the largest digit in the input file
 @params - vector<int> numbers - vector array of digits from input file
 @returns - int - largest digit
*/
int findMax(vector<int> numbers) {
    int MAX = 0;

    //traverse through vector array,
    //if current index is greater than MAX, set MAX to current index
    for (int i=0; i < INPUT_SIZE; i++)
    {
        if (numbers[i] > MAX)
            MAX = numbers[i];
    }
    
    return MAX;
}

/*
 print - print all vector lists
 @params - vector<int> input - unsorted vector of digits from input file
           vector<int> & count - vector array to keep count of the frequency of each digit
           vector<int> & sumCount - vector array used to sort digits based on count
           vector<int> & sortedInput - populate elements in array in sorted order using count and sumCount vecor arrays
*/
void print(vector<int> input, vector<int> & count, vector<int> & sumCount, vector<int> & sortedInput) {
    cout << "Unsorted List: \n";
    printInput(input);
    
    cout << "\nFrequency List: \n";
    printCount(count);
    
    cout << "\nCount Total: \n";
    printCount(sumCount);
    
    cout << "\n-------------------------------------\n\nSorted List: \n";
    printInput(sortedInput);

}

void printInput(vector<int> input) {
    for (int i=0; i < INPUT_SIZE; i++)
        cout << input[i] << " ";
    cout << endl;
}

void printCount(vector<int> array) {
    int newline = 0;
    
    for (int i=1; i <= MAX_INT; i++)
    {
        //break array in 10 number increments
        if (newline == 10) {
            cout << endl;
            newline = 0;
        }
        cout << setw(2) << array[i] << " ";
        newline++;
    }
    cout << endl;
}

