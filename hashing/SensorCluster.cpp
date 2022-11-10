#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "SensorCluster.hpp"

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

// function to return the hash value based on the first digit
unsigned int hashfct1(unsigned int nic) {nic /= 100000; return nic %= 10;}

// function to return the hash value based on the second digit
unsigned int hashfct2(unsigned int nic) {nic /= 10000; return nic %= 10;}

// function to return the hash value based on the third digit
unsigned int hashfct3(unsigned int nic) {nic /= 1000; return nic %= 10;}

// function to return the hash value based on the fourth digit
unsigned int hashfct4(unsigned int nic) {nic /= 100; return nic %= 10;}

// function to return the hash value based on the fifth digit
unsigned int hashfct5(unsigned int nic) { nic /= 10; return nic %= 10;}

// function to return the hash value based on the fourth digit
unsigned int hashfct6(unsigned int nic) {return nic % 10;}

// Constructor for struct Item
Item::Item(string itemName, unsigned int nic):itemName_(itemName), nic_(nic)
{};

// Load information from a text file with the given filename
// THIS FUNCTION IS COMPLETE
void SensorNIC::readTextfile(string filename) {
  ifstream myfile(filename);

  if (myfile.is_open()) {
    cout << "Successfully opened file " << filename << endl;
    string itemName;
    unsigned int nic;
    while (myfile >> itemName >> nic) {
			if (itemName.size() > 0)
      	addItem(itemName, nic);
    }
    myfile.close();
  }
  else
    throw std::invalid_argument("Could not open file " + filename);
}

void SensorNIC::addItem(string itemName, unsigned int nic) {
  // function that adds the specified NIC to the sensor network (i.e., to all hash tables)
  Item newItem(itemName, nic);
  hT1[nic] = newItem;
  hT2[nic] = newItem;
  hT3[nic] = newItem;
  hT4[nic] = newItem;
  hT5[nic] = newItem;
  hT6[nic] = newItem;
}

bool SensorNIC::removeItem(unsigned int nic) {
  // function that removes the sensor specified by the nic value from the network
  // if sensor is found, then it is removed and the function returns true
  // else returns false
  while(hT1.find(nic) != hT1.end()) {
   hT1.erase(nic);
   hT2.erase(nic);
   hT3.erase(nic);
   hT4.erase(nic);
   hT5.erase(nic);
   hT6.erase(nic);
   return true;
 }
 return false;
}

unsigned int SensorNIC::bestHashing() {
  // function that decides the best hash function, i.e. the ones among
  // fct1-fct6 that creates the most balanced sensor network for the current
  // set of NIC addresses, i.e. data member allItems

int bal = 0;
int temp = 0;
int best = 1;

// hT1
int smallest = hT1.bucket_size(0);
int largest = 0;

for (unsigned i = 0; i < 10; ++i) {
 int size = hT1.bucket_size(i);
 if (size > largest)
   largest = size;
 else if (size < smallest)
   smallest = size;
 }

bal = largest - smallest;

// hT2
smallest = hT2.bucket_size(0);
largest = 0;

for (unsigned i = 0; i < 10; ++i) {
 int size = hT2.bucket_size(i);
 if (size > largest)
   largest = size;
 else if (size < smallest)
   smallest = size;
 }

 temp = largest - smallest;
 if (temp < bal) {
   bal = temp;
   best = 2;
 }

// hT3
smallest = hT3.bucket_size(0);
largest = 0;

for (unsigned i = 0; i < 10; ++i) {
  int size = hT3.bucket_size(i);
  if (size > largest)
    largest = size;
  else if (size < smallest)
    smallest = size;
}

  temp = largest - smallest;
  if (temp < bal) {
    bal = temp;
    best = 3;
  }

// hT4
smallest = hT4.bucket_size(0);
largest = 0;

  for (unsigned i = 0; i < 10; ++i) { // i = index
    int size = hT4.bucket_size(i);
    if (size > largest)
      largest = size;
    else if (size < smallest)
      smallest = size;
  }

  temp = largest - smallest;
  if (temp < bal) {
    bal = temp;
    best = 4;
  }

// hT5
smallest = hT5.bucket_size(0);
largest = 0;

  for (unsigned i = 0; i < 10; ++i) {
    int size = hT5.bucket_size(i);
    if (size > largest)
      largest = size;
    else if (size < smallest)
      smallest = size;
    }

  temp = largest - smallest;
  if (temp < bal) {
    bal = temp;
    best = 5;
  }

// hT6
smallest = hT6.bucket_size(0);
largest = 0;

  for (unsigned i = 0; i < 10; ++i) {
    int size = hT6.bucket_size(i);
    if (size > largest)
      largest = size;
    else if (size < smallest)
      smallest = size;
    }

  temp = largest - smallest;
  if (temp < bal) {
    bal = temp;
    best = 6;
  }

  return best;
}

// ALREADY COMPLETED
size_t SensorNIC::size() {
    if ((hT1.size() != hT2.size()) || (hT1.size() != hT3.size()) || (hT1.size() != hT4.size()) || (hT1.size() != hT5.size())|| (hT1.size() != hT6.size()) ) {
  	throw std::length_error("Hash table sizes are not the same");
  }
	return hT1.size();
}
