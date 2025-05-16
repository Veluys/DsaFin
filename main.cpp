#include <iostream>
#include <vector>
using namespace std;

vector<int> bubSort(vector<int> &nums)
{
    for (int i = 0; i < nums.size(); i++)
    {
        bool unchanged = true;
        for (int j = 0; j < nums.size() - i - 1; j++)
        {
            if (nums[j + 1] < nums[j])
            {
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
                unchanged = false;
            }
        }
        if (unchanged)
            break;
    }
    return nums;
}

vector<int> insSort(vector<int> &nums)
{
    for (int i = 1; i < nums.size(); i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (nums[j - 1] > nums[j])
            {
                int temp = nums[j - 1];
                nums[j - 1] = nums[j];
                nums[j] = temp;
            }
        }
    }
    return nums;
}

vector<int> selSort(vector<int> &nums)
{
    for (int i = 0; i < nums.size(); i++)
    {
        int indexMin = i;
        for (int j = i + 1; j < nums.size(); j++)
        {
            if (nums[j] < nums[indexMin])
            {
                indexMin = j;
            }
        }
        if (indexMin == i)
            continue;
        int temp = nums[i];
        nums[i] = nums[indexMin];
        nums[indexMin] = temp;
    }
    return nums;
}

int binSearch(vector<int> &nums, int target)
{
    int low = 0;
    int high = nums.size() - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (nums[mid] == target)
            return mid;

        if (nums[mid] > target)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return -1;
}

int interpolSearch(vector<int> &nums, int target)
{
    int low = 0;
    int high = nums.size() - 1;

    while (low <= high && target >= nums[low] && target <= nums[high])
    {
        int mid = low + ((high - low) * (target - nums[low])) / (nums[high] - nums[low]);

        if (nums[mid] == target)
            return mid;

        if (nums[mid] > target)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return -1;
}

int linSearch(vector<int> &nums, int target)
{
    for (int i = 0; i < nums.size(); i++)
    {
        if (target == nums[i])
            return i;
    }
    return -1;
}

int getAlgo(int op)
{
    vector<vector<string>> algorithms = {{"Binary Search", "Interpolation Search", "Linear Search"},
                                         {"Bubble Sort", "Insertion Sort", "Selection Sort"}};

    op == 1 ? cout << "Select a searching algorithm:" : cout << "Select a sorting algorithm:";
    cout << "\n";

    for (int i = 0; i < algorithms[op - 1].size(); i++)
    {
        cout << "\t" << i + 1 << ". " << algorithms[0][i] << endl;
    }

    int alg;
    cout << "Enter option here: ";
    cin >> alg;
    return alg;
}

vector<int> getNumValues()
{
    int sizeArr;
    vector<int> nums;

    cout << "Enter number of elements: ";
    cin >> sizeArr;
    cout << "\n";

    for (int i = 0; i < sizeArr; i++)
    {
        int num;
        cout << "Element " << i + 1 << ": ";
        cin >> num;
        nums.push_back(num);
    }
    return nums;
}

int main()
{
    /* int op;
    cout << "Select an option:" << endl;
    cout << "\t" << "1. Searching Algorithm" << endl;
    cout << "\t" << "2. Sorting Algorithm" << endl;
    cout << "Enter option here: ";
    cin >> op;

    int alg = getAlgo(op); */
    vector<int> nums = getNumValues();
    nums = insSort(nums);

    int target;
    cout << "Enter the value to search: ";
    cin >> target;

    cout << "Element found at index: " << binSearch(nums, target);
}