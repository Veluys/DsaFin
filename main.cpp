#include <iostream>	//For input and output
#include <vector>   //For storing array of numbers
#include <limits>	//For validation checking
using namespace std;

//Arrays of algorithms, 1st array for searching, 2nd for sorting
const vector<vector<string>> algorithms = {	
    {"Binary Search", "Interpolation Search", "Linear Search"},
    {"Bubble Sort", "Insertion Sort", "Selection Sort"}
};

//For printing the name of the current process
void printHeader(const string &heading){
    string divider(70, '*');
    cout << divider << "\n\t\t\t" << heading << "\n" << divider << endl;
}

//For displaying the menu of algorithms
void showAlgMenu(int op){
    printHeader(op == 1 ? "Searching Algorithms" : "Sorting Algorithms");
    cout << "How would you like to sort?\n";
    for (size_t i = 0; i < algorithms[op - 1].size(); i++){
    	cout << "\t [" << i + 1 << "] " << algorithms[op - 1][i] << endl;
	}
}

//For numeric validation
template <typename T>
bool isValidNum(T &num, T lower = numeric_limits<T>::lowest(), T upper = numeric_limits<T>::max()){
    cin >> num;
    if (cin.fail() || num < lower || num > upper){ //Input is invalid if it is not numeric or its value goes out of bounds
        cout << "Invalid input!\n\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;
}

class ProblemSet{
protected:
    vector<double> nums;
    size_t arrSize;
    bool isValidArr = true;	//For checking if the array contains valid numeric values
    
    ProblemSet(int op, int algChoice){
        printHeader(algorithms[op - 1][algChoice - 1]);
        cout << "Enter number of elements: ";
        
        if (!isValidNum<size_t>(arrSize, 1)){isValidArr = false; return;} //The array must have atleast 1 element to be valid

        cout << "\n" << "Enter the values for" << endl;
        for (size_t i = 0; i < arrSize; i++){	//For loop for populating the array
            double num;
            cout << "\t" <<"Element " << i + 1 << ": ";
            if (!isValidNum<double>(num)){	//Checks if a num is valid before pushing it to the arry
                isValidArr = false; return;
            }
            nums.push_back(num);
        }
    }
};

class SortProblem : public ProblemSet{
protected:
    int algChoice;	//Determine the chosen algorithm to be used

    void bubSort(){	//Bubble Sort
        for (size_t i = 0; i < arrSize; i++){
            bool unchanged = true;
            for (size_t j = 0; j < arrSize - i - 1; j++){
                if (nums[j + 1] < nums[j]){
                    swap(nums[j], nums[j + 1]);
                    unchanged = false;
                }
            }
            if (unchanged) {break;}
        }
    }
    
    void insSort(){	//Insertion Sort
        for (size_t i = 1; i < arrSize; i++){
            for (size_t j = i; j > 0 && nums[j - 1] > nums[j]; j--){
            	swap(nums[j], nums[j - 1]);
			}
        }
    }

    void selSort(){	//Selection Sort
        for (size_t i = 0; i < arrSize; i++){
            int indexMin = i;
            for (size_t j = i + 1; j < arrSize; j++){
                if (nums[j] < nums[indexMin]) {indexMin = j;}
            }
            swap(nums[i], nums[indexMin]);
        }
    }

public:
	//Populating the array and getting the chosen algorithm of the user
    SortProblem(int op, int choice) : ProblemSet(op, choice), algChoice(choice) {} 

    void arrange() {	//Function that executes the chosen sorting algorithm of the user
        if (!isValidArr){return;}

        switch (algChoice){
	        case 1: bubSort(); break;
	        case 2: insSort(); break;
	        case 3: selSort(); break;
	        default: cout << "Invalid choice!"; return;
        }

		//Prints out the sorted array
        cout << "\n" <<"Sorted Array: " << endl;
        for (size_t i = 0; i < arrSize; i++){cout << "\t" <<"Element " << i + 1 << ": " << nums[i] << endl;}
        cout << "\n";
    }
};

//Inherit from SortProblem, since every SearchProblem is a Sorting Problem, as it must be sorted first
class SearchProblem : public SortProblem{	
    double target;
	int low = 0, high = arrSize - 1;
	
    void binSearch(){	//Binary Search
        while (low <= high){
            int mid = (low + high) / 2;
            if (nums[mid] == target){
                cout << "Element found at index: " << mid << endl << endl;
                return;
            }
            nums[mid] > target ? high = mid - 1 : low = mid + 1;
        }
        cout << "Element not found." << endl << endl;
    }

    void interpolSearch(){	//Interpolation Search
        while (low <= high && target >= nums[low] && target <= nums[high]){
            if (nums[high] == nums[low]) {break;}

            int mid = low + ((high - low) * (target - nums[low])) / (nums[high] - nums[low]);

            if (nums[mid] == target){
                cout << "Element found at index: " << mid << endl << endl;
                return;
            }
            
            nums[mid] > target ? high = mid - 1 : low = mid + 1;
        }
        cout << "Element not found." << endl << endl;
    }

    void linSearch() const{	//Linear Search
        for (size_t i = 0; i < arrSize; i++){
            if (nums[i] == target){
                cout << "Element found at index: " << i << endl << endl;
                return;
            }
        }
        cout << "Element not found." << endl << endl;
    }

public:
    SearchProblem(int op, int choice) : SortProblem(op, choice){
        if (!isValidArr) {return;}	//Prevents further prompts is ProblemSet is marked invalid

        cout << "Enter value to search: ";
        if (!isValidNum<double>(target)){isValidArr = false;}	//Invalid target results in invalid set
    }

	//Function that executes the chosen sorting algorithm of the user
    void search(){
        if (!isValidArr){return;}	//Prevents executing the sorting and searching if array is invalid;

        insSort();	//Sort first before searching to be properly executed

        switch (algChoice){
	        case 1: binSearch(); break;
	        case 2: interpolSearch(); break;
	        case 3: linSearch(); break;
	        default: cout << "Invalid choice!" << endl << endl; break;
        }
    }
};

int main(){
    while (true){ //Endless Loop
        printHeader("Search & Sort Program");
        
        cout << "What operation would you like to do?" << endl;
        cout << "\t" << "[1] Searching Algorithm" << endl;
        cout << "\t" << "[2] Sorting Algorithm" << endl;
        cout << "\t" << "[3] Exit" << endl;
        cout << "Enter option here: ";
        
        int op;
        if (!isValidNum<int>(op, 1, 3)){continue;} //Input for option must be between 1-3;

        if (op == 3){
            cout << "\n" <<"Thank you for using the Search & Sort Program";
            break;	//Exit loop/prgram
        }

        cout << "\n";
        
        showAlgMenu(op);	//Display the algorithm menu
        int alg;
        cout << "Enter option here: ";
        
        if (!isValidNum<int>(alg, 1, 3)){continue;}	//Input for option must be between 1-3;
        cout << "\n";

		//Creates the appropriate object and executes either a search or a sort
        op == 1 ? SearchProblem(op, alg).search() : SortProblem(op, alg).arrange();
    }
    return 0;
}
