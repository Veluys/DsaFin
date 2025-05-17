#include <iostream>
#include <vector>
#include <limits>
using namespace std;

vector<vector<string>> algorithms = {
    {"Binary Search", "Interpolation Search", "Linear Search"},
    {"Bubble Sort", "Insertion Sort", "Selection Sort"}
};

void printHeader(const string &heading){
    string divider(70, '*');
    cout << divider << "\n\t\t\t" << heading << "\n" << divider << endl;
}

void showAlgMenu(int op){
    printHeader(op == 1 ? "Searching Algorithms" : "Sorting Algorithms");
    cout << "How would you like to sort?\n";
    for (int i = 0; i < algorithms[op - 1].size(); i++){
    	cout << "\t [" << i + 1 << "] " << algorithms[op - 1][i] << endl;
	}
}

bool isValidNum(int &num, int lower = INT_MIN, int upper = INT_MAX){
    cin >> num;
    if (cin.fail() || num < lower || num > upper){
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
    vector<int> nums;
    bool isValidSet = true;
    
    ProblemSet(int op, int algChoice){
        printHeader(algorithms[op - 1][algChoice - 1]);
        cout << "Enter number of elements: ";
        int sizeArr;
        
        if (!isValidNum(sizeArr, 1)){isValidSet = false; return;}

        cout << "\n";
        for (int i = 0; i < sizeArr; i++){
            int num;
            cout << "Element " << i + 1 << ": ";
            if (!isValidNum(num)){isValidSet = false; return;}
            nums.push_back(num);
        }
    }
};

class SortProblem : public ProblemSet{
protected:
    int algChoice;

    void bubSort(){
        for (int i = 0; i < nums.size(); i++){
            bool unchanged = true;
            for (int j = 0; j < nums.size() - i - 1; j++){
                if (nums[j + 1] < nums[j]){
                    swap(nums[j], nums[j + 1]);
                    unchanged = false;
                }
            }
            if (unchanged) {break;}
        }
    }

    void selSort(){
        for (int i = 0; i < nums.size(); i++){
            int indexMin = i;
            for (int j = i + 1; j < nums.size(); j++){
                if (nums[j] < nums[indexMin]) {indexMin = j;}
            }
            swap(nums[i], nums[indexMin]);
        }
    }

public:
    SortProblem(int op, int choice) : ProblemSet(op, choice), algChoice(choice) {}

    void arrange(){
        if (!isValidSet){return;}

        switch (algChoice){
	        case 1: bubSort(); break;
	        case 2: insSort(); break;
	        case 3: selSort(); break;
	        default: cout << "Invalid choice!"; return;
        }

        cout << "Sorted Array: ";
        for (int num : nums){cout << num << " ";}
        cout << endl;
    }

    void insSort(){
        for (int i = 1; i < nums.size(); i++){
            for (int j = i; j > 0 && nums[j - 1] > nums[j]; j--){
            	swap(nums[j], nums[j - 1]);
			}
        }
    }
};

class SearchProblem : public SortProblem{
    int target;

    void binSearch(){
        int low = 0, high = nums.size() - 1;
        while (low <= high){
            int mid = (low + high) / 2;
            if (nums[mid] == target){
                cout << "Element found at index: " << mid << endl;
                return;
            }
            nums[mid] > target ? high = mid - 1 : low = mid + 1;
        }
        cout << "Element not found." << endl;
    }

    void interpolSearch(){
        int low = 0, high = nums.size() - 1;
        while (low <= high && target >= nums[low] && target <= nums[high]){
            if (nums[high] == nums[low]) {break;}

            int mid = low + ((high - low) * (target - nums[low])) / (nums[high] - nums[low]);

            if (nums[mid] == target){
                cout << "Element found at index: " << mid << endl;
                return;
            }
            
            nums[mid] > target ? high = mid - 1 : low = mid + 1;
        }
        cout << "Element not found." << endl;
    }

    void linSearch(){
        for (int i = 0; i < nums.size(); i++){
            if (nums[i] == target){
                cout << "Element found at index: " << i << endl;
                return;
            }
        }
        cout << "Element not found." << endl;
    }

public:
    SearchProblem(int op, int choice) : SortProblem(op, choice){
        if (!isValidSet) {return;}

        cout << "Enter value to search: ";
        if (!isValidNum(target)){isValidSet = false;}
    }

    void search(){
        if (!isValidSet){return;}

        insSort();

        switch (algChoice){
	        case 1: binSearch(); break;
	        case 2: interpolSearch(); break;
	        case 3: linSearch(); break;
	        default: cout << "Invalid choice!"; break;
        }
    }
};

int main(){
    while (true){
        printHeader("Search & Sort Program");
        
        cout << "What operation would you like to do?" << endl;
        cout << "\t" << "[1] Searching Algorithm" << endl;
        cout << "\t" << "[2] Sorting Algorithm" << endl;
        cout << "\t" << "[3] Exit" << endl;
        cout << "Enter option here: ";
        
        int op;
        if (!isValidNum(op, 1, 3)){continue;}

        if (op == 3){
            cout << "\n" <<"Thank you for using the Search & Sort Program";
            break;
        }

        cout << "\n";
        
        showAlgMenu(op);
        int alg;
        cout << "Enter option here: ";
        
        if (!isValidNum(alg, 1, 3)){continue;}
        cout << "\n";

        op == 1 ? SearchProblem(op, alg).search() : SortProblem(op, alg).arrange();
    }
    return 0;
}
