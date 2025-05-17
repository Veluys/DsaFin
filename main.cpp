#include <iostream>
#include <vector>
using namespace std;

void showAlgMenu(int op)
{
    vector<vector<string>> algorithms = {{"Binary Search", "Interpolation Search", "Linear Search"},
                                         {"Bubble Sort", "Insertion Sort", "Selection Sort"}};

    op == 1 ? cout << "Select a searching algorithm:" : cout << "Select a sorting algorithm:";
    cout << "\n";

    for (int i = 0; i < algorithms[op - 1].size(); i++)
    {
        cout << "\t" << i + 1 << ". " << algorithms[op - 1][i] << endl;
    }
}

class ProblemSet
{
protected:
    vector<int> nums;

    ProblemSet()
    {
        int sizeArr;
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
    }
};

class SortProblem : public ProblemSet
{
private:
    void swap(int &num1, int &num2)
    {
        int temp = num1;
        num1 = num2;
        num2 = temp;
    }

protected:
    int algChoice;
    void bubSort()
    {
        for (int i = 0; i < nums.size(); i++)
        {
            bool unchanged = true;
            for (int j = 0; j < nums.size() - i - 1; j++)
            {
                if (nums[j + 1] < nums[j])
                {
                    swap(nums[j], nums[j + 1]);
                    unchanged = false;
                }
            }
            if (unchanged)
                break;
        }
    }

    void insSort()
    {
        for (int i = 1; i < nums.size(); i++)
        {
            for (int j = i; j > 0; j--)
            {
                if (nums[j - 1] > nums[j])
                {
                    swap(nums[j], nums[j - 1]);
                }
            }
        }
    }

    void selSort()
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

            swap(nums[i], nums[indexMin]);
        }
    }

public:
    SortProblem(int algChoice) : ProblemSet(), algChoice(algChoice) {}
    void arrange()
    {
        switch (algChoice)
        {
        case 1:
            bubSort();
            break;
        case 2:
            insSort();
            break;
        case 3:
            selSort();
            break;
        default:
            cout << "Invalid choice!";
            break;
        }

        cout << "Sorted Array: ";
        for (int num : nums)
        {
            cout << num << " ";
        }
        cout << endl;
    }
};

class SearchProblem : public SortProblem
{
private:
    int target;

    void binSearch()
    {
        int low = 0;
        int high = nums.size() - 1;

        while (low <= high)
        {
            int mid = (low + high) / 2;

            if (nums[mid] == target)
            {
                cout << "Element found at index: " << mid << endl;
                return;
            }

            if (nums[mid] > target)
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        cout << "Element not found." << endl;
    }

    void interpolSearch()
    {
        int low = 0;
        int high = nums.size() - 1;

        while (low <= high && target >= nums[low] && target <= nums[high])
        {
            int mid = low + ((high - low) * (target - nums[low])) / (nums[high] - nums[low]);

            if (nums[mid] == target)
            {
                cout << "Element found at index: " << mid << endl;
                return;
            }

            if (nums[mid] > target)
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        cout << "Element not found." << endl;
    }

    void linSearch()
    {
        for (int i = 0; i < nums.size(); i++)
        {
            if (target == nums[i])
            {
                cout << "Element found at index: " << i << endl;
                return;
            }
        }
        cout << "Element not found." << endl;
    }

public:
    SearchProblem(int algChoice) : SortProblem(algChoice)
    {
        cout << "Enter value to search: ";
        cin >> target;
    }

    void search()
    {
        this->insSort();
        switch (algChoice)
        {
        case 1:
            binSearch();
            break;
        case 2:
            interpolSearch();
            break;
        case 3:
            linSearch();
            break;
        default:
            cout << "Invalid choice!";
            break;
        }
    }
};

int main()
{
    while (true)
    {
        int op;
        cout << "Select an option:" << endl;
        cout << "\t" << "1. Searching Algorithm" << endl;
        cout << "\t" << "2. Sorting Algorithm" << endl;
        cout << "\t" << "3. Exit" << endl;
        cout << "Enter option here: ";
        cin >> op;

        if (op == 3)
        {
            break;
        }

        cout << "\n";

        showAlgMenu(op);
        int alg;
        cout << "Enter option here: ";
        cin >> alg;

        cout << "\n";

        if (op == 1)
        {
            SearchProblem s = SearchProblem(alg);
            s.search();
        }
        else if (op == 2)
        {
            SortProblem p = SortProblem(alg);
            p.arrange();
        }
        else
        {
            cout << "Invalid option!" << endl;
        }
    }
}