#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <sstream>
//#include <vectorv2.hpp>

//if possible change our vectors to this vector and don't include the above 
//this code compiles but im not sure if it works quite the same. 

int* stringToInt(std::string line) {
    // checks to make sure the entered string is valid
    if(line.length() == 0 || line[0] == ' ' || line[0] == '0') {
        std::cout << "Error. Invalid entry for argument line.\n";
        return 0;
    }
    
    // easiest way I could think to properly get the size of the polynomial
    std::vector<int> size; // vector to store the ints from the first number in the string
    int length = 0; // int to store the size of the polynomial
    int it = 0; // iterator for the while loop
    while(line[it] != ' ') { // stop when the character is a space
        // make sure none of the characters aren't non-number characters
        if(line[it] < '0' || line[it] > '9') {
            std::cout << "Error. Invalid character!\n";
            return 0;
        }
        size.push_back(line[it]-'0'); // put the number at the index it in the vector
        it++; // increment the iterator
    }
    
    int vec_size = size.size(); // will store the original size of the vector
    for(int i = 0; i < vec_size; i++) {
        length += size.back() * pow(10,i); // adds the single digit numbers multiplied by their power of 10 to the
        //                                    ength
        size.pop_back(); // removes the last element of the vector
    }
    
    // make sure the length is a Natural Number
    if(length <= 0) {
        std::cout << "Error. Expected non-zero positive integer for polynomial length.\n";
        return 0;
    }
    
    int *output = new int [length+1], tens = 0, temp_num = 0;
    output[0] = length;
    int j = 1;
    //use ascii values to get actual numbers so we can add them easily
    for(int i = line.length()-1; i >= 0; i--) {
        // make sure all characters entered are valid
        if(line[i] != ' ' && line[i] != '-' && (line[i] < '0' || line[i] > '9')) {
            std::cout << "Error. Invalid character entered.\n";
            return 0;
        }
        
        // use the ascii values to get the actual int value
        if(line[i] != ' ') {
            if(line[i] == '-') {
                temp_num *= -1;
            } else if(temp_num < 0) {
                std::cout << "Error. Invalid format for input data.\n";
                return 0;
            } else {
                temp_num += (line[i]-'0') * pow(10,tens); // multiply the current number by the correct power of 10
                //                                           then add it to the total number that will be added
                tens++; // the power of ten to multiply the number by
            }
        } 
        else {
            // Error check for too many numbers entered
            if(j == length+1) {
                std::cout << "Error. Too many numbers entered.\n";
                return 0;
            }
            
            output [j] = temp_num;
            j++;
            tens = 0;
            temp_num = 0;
        }
    }
    
    if(j < length) {
        std::cout << "Error. Incorrect Length Entered.\n";
        return 0;
    }
    
    return output;
}

/** 
 * @input: two strings of polynomials
 * @output: two polynomialds added into an int array
 * */
int* polyadder(std::string poly1, std::string poly2){
    // create int arrays for each string polynomial given
    int *poly1_ints = stringToInt(poly1);
    int *poly2_ints = stringToInt(poly2);
    // create ints representing the lengths of each polynomial
    int poly1_len = poly1_ints[0]+1, poly2_len = poly2_ints[0]+1; 
    // create an empty int pointer for the output array
    int *output; 
    //checks for invalid entry
    if(poly1_ints == 0 || poly2_ints == 0) {
        std::cout << "Error. Invalid entry for one of the arguments.\n";
        return 0;
    }
    // checks to make sure first coefficient is not zero
    if(poly1_ints[poly1_len-1] == 0 || poly2_ints[poly2_len-1] == 0) {
        std::cout << "Error. Expected a non-zero integer for the highest degree.\n";
        return 0;
    }
    if(poly1_len == poly2_len) {// check if the polynomials are the same length
        output = new int [poly1_len]; // make the output an array that contains the length of the polynomials + 1 to store the length
        output[0] = poly1_len-1; // set the first index of the output to be the length of the polynomial
        
        // adds the polynomials together
        for(int i = 1; i < poly1_len; i++) {
            output[i] = poly1_ints[i]+poly2_ints[i]; // since output is 1 index longer than the poly_ints you do i-1 to get the correct indexes
        }
    } 
    else if(poly1_len > poly2_len) {// check if poly1 is longer than poly2
        output = new int [poly1_len]; // make the output an array that contains the length of poly1 + 1 to store the length
        output[0] = poly1_len-1; // set the first index of the output to be the length of the polynomial
        
        // adds the polynomials together up until the last index of poly2
        for(int i = 1; i < poly2_len; i++) {
            output[i] = poly1_ints[i]+poly2_ints[i]; // since output is 1 index longer than the poly_ints you do i-1 to get the correct indexes
        }
        
        // copies over the remaining elements from poly1
        for(int i = poly2_len; i < poly1_len; i++) {
            output[i] = poly1_ints[i];
        }
    } 
    else {// if the other two conditions aren't met, then logic goes to show that poly2 is longer than poly1
        output = new int [poly2_len]; // make the output an array that contains the length of poly2 + 1 to store the length
        output[0] = poly2_len-1; // set the first index of the output to be the length of the polynomial
        
        // adds the polynomials together up until the last index of poly1
        for(int i = 1; i < poly1_len; i++) {
            output[i] = poly1_ints[i]+poly2_ints[i]; // since output is 1 index longer than the poly_ints you do i-1 to get the correct indexes
        }
        
        // copies over the remaining elements from poly2
        for(int i = poly1_len; i < poly2_len; i++) {
            output[i] = poly2_ints[i];
        }
    }
    // frees the allocated memory used for the arrays (not needed)
    delete[] poly1_ints;
    delete[] poly2_ints;
    
    return output;
}
/** Prints the polynomial with variables and corresponding degree
 * @input: a polynomial as an int array
 * */
void print_polynomial(int*poly_ints) {
    // check to make sure the entered array is valid
    if(poly_ints == 0 || poly_ints[0] == 0) {
        std::cout << "Error. Invalid entry for argument poly_ints.\n";
        return;
    }
    
    // if the polynomaial has any powers of x e.g. its size 2 or above, print it from here
    else if(poly_ints[0] >= 2) {
        // step through the array in reverse so the polynomial prints in the correct order
        for(int i = poly_ints[0]; i > 2; i--) {
            if(poly_ints[i] == 0) continue; // if the number is a 0 we don't need to print anything
            else if(poly_ints[i] == 1) std::cout << "x^" << i-1 << " + "; // if the number is a 1 we don't need a coefficient
            else std::cout << poly_ints[i] << "x^" << i-1 << " + "; // general print line
        }
        
        if(poly_ints[2] == 1) std::cout << "x" << " + "; // if the number is a 1 we don't need to print the  
        //                                                  coefficient
        else if(poly_ints[2] != 0) std::cout << poly_ints[2] << "x" << " + "; // prints it normally
    }
    
    if(poly_ints[1] == 0) return;
    std::cout << poly_ints[1] << std::endl; // prints the constant value
}

/** prints the polynomial without variables (only length and coefficients)
 * @input: polynomial as int array
 * */
void simplePrint(int* poly){
    // check to make sure the entered array is valid
    if(poly == 0 || poly[0] == 0) {
        std::cout << "Error. Invalid entry for argument poly_ints.\n";
        return;
    }
    std::cout << poly[0] << " ";
    for(int i = poly[0]; i>0 ; i--){
        std::cout << poly[i] << " ";
    }
    std::cout << std::endl;
}
/** 
 * @input: two strings of polynomials
 * @output: two polynomialds multiplied into an int array
 * */
int* polymult(std::string poly1, std::string poly2){
    // create int arrays for each string polynomial given
    int *poly1_ints = stringToInt(poly1);
    int *poly2_ints = stringToInt(poly2);
    if(poly1_ints == 0 || poly2_ints == 0) {
        std::cout << "Error. Invalid entry for one of the arguments.\n";
        return 0;
    }
    //create ints representing the lengths of each
    int poly1_len = poly1_ints[0]+1;
    int poly2_len = poly2_ints[0]+1;  
    //checks first coefficient to see if it's zero
    if(poly1_ints[poly1_len-1] == 0 || poly2_ints[poly2_len-1] == 0) {
        std::cout << "Error. Expected a non-zero integer for the highest degree.\n";
        return 0;
    }
    
    int *output = new int [poly1_len + poly2_len - 2]; // make the output an array that contains the length of the polynomials + 1 to store the length
    //set all values equal to zero in the output to start
    //besides the first index, which is the length
    output[0] = (poly1_len + poly2_len - 3);
    for(int i = 1; i < output[0]+1; i++){
        output[i] = 0;
    }
    //multiplies the polynomials together
    for(int i = 1; i <= poly2_len; i++) {//loop through both polynomials lengths 
        for(int j = 0; j <= poly1_len; j++) {
            //replace current value at output with 
            //addition of value at index added to the 
            //value of the multiplied polynomials
            output[i+j] += (poly1_ints[j+1] * poly2_ints[i]);
        }
    }
    
    // frees the allocated memory used for the un needed arrays
    delete[] poly1_ints;
    delete[] poly2_ints;
    
    return output;
}

int main(int len, char **args) {
    std::string poly1, poly2;
    
    std::ifstream ifs1(args[1]);
    poly1.assign((std::istreambuf_iterator<char>(ifs1)), (std::istreambuf_iterator<char>()));
    std::ifstream ifs2(args[2]);
    poly2.assign((std::istreambuf_iterator<char>(ifs2)), (std::istreambuf_iterator<char>()));
    
    int *added_poly = polyadder(poly1, poly2);
    int *mult_poly = polymult(poly1,poly2);
    
    //if you want a fancier print
    //print_polynomial(added_poly);
    //print_polynomial(mult_poly);
    
    //if you want a simple print 
    simplePrint(added_poly);
    simplePrint(mult_poly);
    
    delete[] added_poly;
    delete[] mult_poly;
}
