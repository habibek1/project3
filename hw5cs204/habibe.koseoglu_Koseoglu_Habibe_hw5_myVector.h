//Fall 2023 CS204 HW#5 -- myVector.h
//  Habibe Koseoglu
/*******************************************************************************************************
    IMPLEMENT FOLLOWING CLASSES
    YOU CAN ADD ANY FUNCTION/STRUCT/CLASS THAT YOU WILL USE HOWEVER YOU CANNOT TOUCH MAIN FUNCTION
*******************************************************************************************************/
#include <string>
#include <vector>
#include <iostream>
#include <type_traits>
#include <cmath>
template <typename T1, typename T2>
class myVector {
public:
    struct st {          // to store two value in a vector
        T1 value;
        T2 key;
    };
    myVector(){    //default constructor
        vec = std::vector<st>();
        size = 0;
    }
    myVector(const myVector & copied){    //copy constructor
        vec = copied.vec;
    }
    std::string setName(std::string a) { // to get a name and set it
        name=a;
        return name;
    }
    myVector * begin(){
        return this;
    }
    void push_back(T1 value, T2 key){ // to add elements in the vector
        st values;
        values.value= value;
        values.key= key;
        vec.push_back(values);
        size++;
    }
    void remove(T2 key){        // to remove key
        for (int i=0; i< vec.size(); i++) {
            if (vec[i].key == key) {
                typename std::vector<st>::iterator itr = vec.begin();
                vec.erase(i+itr);
                size--;
            }
        }
    }
    T1 * & operator [] (const T2 & findkey){ // to find pointer of a key
        ptrfindkey = nullptr;
        for (int i=0; i<vec.size(); i++) {
            if (findkey == vec[i].key) {
                ptrfindkey = & vec[i].value;
                return ptrfindkey;
            }
        }
        return ptrfindkey;
    }
    bool operator == (const myVector & rhs){    // to check whether two myVector element is equal or not
        bool alltrue= false;   // to check if all elements are eqaul
        if ((*this).size != rhs.size) {
            return false;
        }
        else {
            for (int m=0; m < rhs.size; m++) {
                if ( ( (((*this).vec)[m]).key == (rhs.vec)[m].key ) && ( (((*this).vec)[m]).value == (rhs.vec)[m].value ) ) {
                    alltrue = true;
                }
                else {            // if one of the elements is not equal return value must be false
                    alltrue= false;
                    return false;
                    break;
                }
            }
            if (alltrue==true) {   // if all of them is equal return true
                return true;
            }
        }
        return false;
    }
    bool isEmpty(){
        if (size==0) {
            return true;
        }
        return false;
    }
    std::string getName(){
        return name;
    }
    int indexfinder(std::vector<T1> a, T1 w){   // a function for process_data
        for (int i=0; i<a.size(); i++) {
            if (a[i]== w) {
                return i;
                break;
            }
        }
        return -1;
    }
    double Mean(const std::vector<st>& vect) {  //gets the vector of Myvector, returns mean
        double sum = 0;
        for (int i=0; i<vect.size(); i++) {
            sum += vect[i].value ;
        }
        return static_cast<double>(sum / vect.size());
    }
    double Median(const std::vector<st>& vect) {   //gets the vector of Myvector, returns median
        std::vector<T1> data;
        for (int i=0; i<vect.size(); i++) {
            data.push_back(vect[i].value);
        }
        std::vector<T1> sortedData = data;
        
        for (int i = 0; i < sortedData.size() - 1; ++i) {
            for (int j = 0; j < sortedData.size() - i - 1; ++j) {
                if (sortedData[j] > sortedData[j + 1]) {
                    std::swap(sortedData[j], sortedData[j + 1]);
                }
            }
        }

        if (sortedData.size() % 2 == 0) {
            T1 mid1 = sortedData[sortedData.size() / 2 - 1];
            T1 mid2 = sortedData[sortedData.size() / 2];
            return (mid1 + mid2) / 2.0;
        } else {
            return sortedData[sortedData.size() / 2];
        }
    }
    double StandardDeviation(const std::vector<st>& vect, double mean) { //gets the vector of Myvector and mean, returns standard deviation
        double variance = 0.0;
        for (int i=0; i< vect.size(); i++) {
            variance += pow(vect[i].value - mean, 2);
        }
        variance /= vect.size();
        return sqrt(variance);
    }
    T1 Mode(const std::vector<st>& vec) {       //gets the vector of Myvector returns mode
        std::vector<T1> nums;
        std::vector<int> freq ;
        for (int k=0; k<vec.size(); k++) {
            bool aa=false;
            for (int i=0; i<nums.size(); i++) {
                if (nums[i]== vec[k].value) {
                    aa= true;
                }
            }
            if (aa==false) {
                nums.push_back(vec[k].value);
                freq.push_back(1);
            }
            else if (aa== true) {
                int kk= indexfinder(nums,vec[k].value);
                freq[kk]++;
            }
        }
        int maxoccurrence = 0;
        for (int i=0; i<freq.size(); i++) {
            if (freq[i] > freq[maxoccurrence] || (freq[i] == freq[maxoccurrence] && nums[i] < nums[maxoccurrence])) {
                maxoccurrence = i;
            }
        }
        return nums[maxoccurrence];
    }
    T1 Max(const std::vector<st>& vect) {     //gets the vector of Myvector returns max
        T1 max = vect[0].value;
        for (int i=0; i< vect.size(); i++) {
            if (vect[i].value > max) {
                max = vect[i].value;
            }
        }
        return max;
    }
    void process_data(){
        if constexpr (std::is_same_v<T1, std::string>) {            // if the value type is string
            std::vector<T1> words;                  // to store words
            std::vector<int> freq ;                    // to store frequency of words
            std::string totalletters;                    // to include all letters
            std::vector<char> letters;                     // to store different letters
            std::vector<int> freqletters ;                    // to store frequency of letters
            
            for (int k=0; k<vec.size(); k++) {             // to check max occurred word
                bool aa=false;
                for (int i=0; i<words.size(); i++) {
                    if (words[i]== vec[k].value) {
                        aa= true;
                    }
                }
                if (aa==false) {
                    words.push_back(vec[k].value);
                    freq.push_back(1);
                }
                else if (aa== true) {
                    int kk= indexfinder(words,vec[k].value);
                    freq[kk]++;
                }
            }
            int maxoccurrence = 0; // index of maxoccurrence
            for (int i=0; i<freq.size(); i++) {
                if (freq[i] > freq[maxoccurrence] || (freq[i] == freq[maxoccurrence] && words[i] < words[maxoccurrence])) { //to update maxoccurance
                    maxoccurrence = i;
                }
            }
            
            for (int k=0; k<vec.size(); k++) {              // to check max occurred letter
                totalletters= totalletters + vec[k].value;
            }
            for (int i=0; i< totalletters.length(); i++) {
                bool bb= false;
                for (int j=0; j<letters.size(); j++) {
                    if (totalletters.at(i)== letters[j]) {
                        bb = true;
                    }
                }
                if (bb==false) {
                    letters.push_back(totalletters.at(i));
                    freqletters.push_back(1);
                }
                else if (bb== true) {
                    int kk=0;     //index
                    for (int jj=0; jj< letters.size(); jj++) {
                        if (totalletters.at(i)== letters[jj]) {
                            kk= jj;
                        }
                    }
                    freqletters[kk]++;
                }
            }

            int maxoccurrencelet = 0; //index of maxoccurance
            for (int i=0; i<freqletters.size(); i++) { //to update maxoccurance
                if (freqletters[i] > freqletters[maxoccurrencelet]) {
                    maxoccurrencelet = i;
                }
                else if (freqletters[i] == freqletters[maxoccurrencelet]){
                    if (letters[i] < letters[maxoccurrence]) {
                        maxoccurrencelet = i;
                    }
                }
            }
            std::cout << "Most Frequent Character: '"<< letters[maxoccurrencelet] << "' (Frequency: "<< freqletters[maxoccurrencelet] << ")"<< std::endl;
            std::cout << "Most Frequent Word: \"" << words[maxoccurrence] << "\" (Frequency: " << freq[maxoccurrence] << ")"<< std::endl;
        }
        else{
            double mean = Mean(vec);
            double median = Median(vec);
            double standardD = StandardDeviation(vec, mean);
            T1 mode = Mode(vec);
            T1 max = Max(vec);
            std::cout << "Mean: " << mean << std::endl << "Median: " << median<< std::endl << "Standard Deviation: " << standardD << std::endl << "Max: " << max << std::endl << "Mode: " << mode << std::endl;
        }
    }
    class Iterator {
    public:
        Iterator(myVector * a){ // constructor
            myvec = a;
        }
        bool find(T2 oldKeyInt, const myVector & myvec ){  // find function of the iterator class
            for (int i=0; i<myvec.vec.size(); i++) {
                if (oldKeyInt== myvec.vec[i].key) {
                    keyposition=i;
                    return true;
                }
            }
            return false;
        }
        void replaceKey(T2 newKeyInt){
            (*myvec).vec[keyposition].key= newKeyInt;
        }
        void printVector(){
            for (int k=0; k< (*myvec).vec.size(); k++) {
                std::cout << "Value: " << (*myvec).vec[k].value << ", Key: " << (*myvec).vec[k].key << std::endl;
            }
        }
    private:
        myVector * myvec;
        int keyposition;
        
    };
private:
    T1 * ptrfindkey;
    std::vector<st> vec;
    std::string name;
    st mystruct;
    int size;
};
/*******************************************************************************************************/
