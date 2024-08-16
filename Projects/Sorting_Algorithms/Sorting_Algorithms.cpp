#include <iostream>
#include <conio.h>
#include <fstream>
#include <ctime>
#include <vector>
using namespace std;

void Random_Number_Maker(int lowest, int highest,int Arr_Length,vector<int> &Array)
{
	srand((int)time(0));
	int random_integer;
	int range = (highest - lowest) + 1;
	for (int index = 0; index < Arr_Length; index++) {
		random_integer = lowest + (rand() % (range));
		Array.push_back(random_integer);
	}
}

class MyArray
{
private:
	vector<int> _Array;
public:
	MyArray(int, int, int);
	~MyArray();
	vector<int>& get_Array();
	void Print_Arr(vector<int> &);
	void BubbleSort(int &,int &);
	void InsertionSort(int &, int &);
	void merge(vector<int> &, vector<int> &, vector<int> &, int &, int &);
	void MergeSort(int &, int &);
	void do_MergeSort(vector<int> &, int &, int &);
	void swap(vector<int> &, int, int);
	int partition(vector<int> &, int, int, int &, int &);
	void QuickSort(int &, int &);
	void do_QuickSort(vector<int> &, int, int, int &, int &);
	void SelectionSort(int &, int &);
	void heapify(vector<int> &, int, int, int &, int &);
	void HeapSort(int &, int &);
};

MyArray::MyArray(int lowest, int highest, int Length)
{
	Random_Number_Maker(lowest, highest, Length,_Array);
}

MyArray::~MyArray()
{
	if (_Array.empty()!=true)
		_Array.clear();
	_Array.~vector();
}

vector<int>& MyArray::get_Array()
{
	return _Array;
}

void MyArray::Print_Arr(vector<int> &Array)
{
	for (int i = 0; i < (unsigned)(Array.size()); i++)
	{
		cout << Array.at(i) << " ";
	}
	cout << endl;
}

void MyArray::BubbleSort(int &Swap,int &Check)
{
	vector<int> Result(_Array);
	int Arr_size = (unsigned)(Result.size());
	for (int i = Arr_size - 1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (Result.at(j) > Result.at(j + 1))
			{
				swap(Result, j, j + 1);
				Swap++;
			}
			Check++;
		}
	}
}

void MyArray::InsertionSort(int &Swap, int &Check)
{
	int key, j;
	bool quit;
	vector<int> Result(_Array);
	int Arr_size = (unsigned)(Result.size());
	for (int i = 1; i < Arr_size; i++)
	{
		j = i - 1;
		while (j >= 0)
		{
			Check++;
			if (Result.at(j) > Result.at(j + 1))
			{
				swap(Result, j, j + 1);
				Swap++;
				j--;
			}
			else
			{
				break;
			}			
		}
	}
}

void MyArray::merge(vector<int> &Result, vector<int> &Left_Arr, vector<int> &Right_Arr, int &Swap, int &Check)
{
	int n1 = (unsigned)(Left_Arr.size());
	int n2 = (unsigned)(Right_Arr.size());
	int Arr_size = n1 + n2;
	int i = 0;
	int j = 0;
	while (i < n1 && j < n2)
	{
		if (Left_Arr[i] <= Right_Arr[j])
		{
			Result.push_back(Left_Arr.at(i));
			Swap++;
			i++;
		}
		else
		{
			Result.push_back(Right_Arr.at(j));
			Swap++;
			j++;
		}
		Check++;
	}

	while (i < n1)
	{
		Result.push_back(Left_Arr.at(i));
		Swap++;
		i++;
	}
	while (j < n2)
	{
		Result.push_back(Right_Arr.at(j));
		Swap++;
		j++;
	}
}

void MyArray::MergeSort(int &Swap, int &Check)
{
	vector<int> Result(_Array);
	do_MergeSort(Result, Swap, Check);
}

void MyArray::do_MergeSort(vector<int> &Array, int &Swap, int &Check)
{
	int Arr_size = (unsigned)(Array.size());
	if (Arr_size <= 1)
	{
		return;
	}
	vector<int> Left_Arr;
	vector<int> Right_Arr;
	for (int i = 0; i < Arr_size; i++)
	{
		if (i < (Arr_size / 2))
		{
			Left_Arr.push_back(Array.at(i));
		}
		else
		{
			Right_Arr.push_back(Array.at(i));
		}
	}
	do_MergeSort(Left_Arr, Swap, Check);
	do_MergeSort(Right_Arr, Swap, Check);
	vector<int> Result;
	merge(Result, Left_Arr, Right_Arr, Swap, Check);
}

void MyArray::swap(vector<int> &Array, int p, int q)
{
	int temp = Array.at(p);
	Array.at(p) = Array.at(q);
	Array.at(q) = temp;
}

int MyArray::partition(vector<int> &Array, int Low, int High, int &Swap, int &Check)
{
	int pivot = Array.at(High);
	int i = (Low - 1);
	for (int j = Low; j <= (High - 1); j++)
	{
		if (Array.at(j) <= pivot)
		{
			i++;
			swap(Array, i, j);
			Swap++;
		}
		Check++;
	}
	swap(Array, i + 1, High);
	Swap++;
	return (i + 1);
}

void MyArray::QuickSort(int &Swap, int &Check)
{
	vector<int> Result(_Array);
	int Low = 0;
	int High = ((unsigned)(Result.size())) - 1;
	do_QuickSort(Result, Low, High, Swap, Check);
}

void MyArray::do_QuickSort(vector<int> &Array, int Low, int High, int &Swap, int &Check)
{
	if (Low < High)
	{
		int Partition_Index = partition(Array, Low, High, Swap, Check); // find pivote location
		do_QuickSort(Array, Low, Partition_Index-1, Swap, Check); // Quick Sort left sub array
		do_QuickSort(Array, Partition_Index + 1 , High, Swap, Check); // Quick Sort right sub array
	}
}

void MyArray::SelectionSort(int &Swap, int &Check)
{
	int i, j, min_idx;
	vector<int> Result(_Array);
	int Arr_size = (unsigned)(Result.size());
	for (i = 0; i < (Arr_size -1); i++)
	{
		// Find the minimum element in unsorted array
		min_idx = i;
		for (j = i + 1; j < Arr_size; j++)
		{
			if (Result.at(j) < Result.at(min_idx))
			{
				min_idx = j;
			}
			Check++;
		}
		// Swap the found minimum element with the first element
		swap(Result,min_idx, i);
		Swap++;
	}
}

void MyArray::heapify(vector<int> &Array, int Heap_Size, int index, int &Swap, int &Check)
{
	int largest = index;  // Initialize root as largest
	int Left_child = 2 * index + 1;  // left = 2*i + 1
	int Right_child = 2 * index + 2;  // right = 2*i + 2
	
	// If left child is larger than root
	if (Left_child < Heap_Size && Array.at(Left_child) > Array.at(largest))
	{
		largest = Left_child;
	}
	Check++;		

	// If right child is larger than largest so far
	if (Right_child < Heap_Size && Array.at(Right_child) > Array.at(largest))
	{
		largest = Right_child;
	}
	Check++;

	// If largest is not root
	if (largest != index)
	{
		swap(Array, index, largest);
		Swap++;
		// Recursively heapify the affected sub-tree
		heapify(Array, Heap_Size, largest, Swap, Check);
	}
}

void MyArray::HeapSort(int &Swap, int &Check)
{
	int Size_Arr = (unsigned)(_Array.size());
	vector<int> Result(_Array);
	for (int i = (((Size_Arr) / 2) - 1); i >= 0; i--)
		heapify(Result, Size_Arr, i, Swap, Check);

	// One by one extract an element from heap
	for (int i = ((Size_Arr) - 1); i >= 0; i--)
	{
		// Move current root to end
		swap(Result,0,i);
		Swap++;
		// call max heapify on the reduced heap
		heapify(Result, i, 0, Swap, Check);
	}
}
//************************************************************************************************

int main()
{
	cout << endl;
	int s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0, s6 = 0;
	int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0;
	MyArray Array_20(1, 1000, 20);
	Array_20.BubbleSort(s1, c1);
	Array_20.InsertionSort(s2, c2);
	Array_20.MergeSort(s3, c3);
	Array_20.QuickSort(s4, c4);
	Array_20.SelectionSort(s5, c5);
	Array_20.HeapSort(s6, c6);
	cout << "\t Array with size 20: \t" << endl;
	cout << "\t\t Bubble: \t" << "swap= " << s1 << "\tcheck= " << c1 << endl;
	cout << "\t\t Insertion: \t" << "swap= " << s2 << "\tcheck= " << c2 << endl;
	cout << "\t\t Merge: \t" << "swap= " << s3 << "\tcheck= " << c3 << endl;
	cout << "\t\t Quick: \t" << "swap= " << s4 << "\tcheck= " << c4 << endl;
	cout << "\t\t Selection: \t" << "swap= " << s5 << "\tcheck= " << c5 << endl;
	cout << "\t\t Heap:      \t" << "swap= " << s6 << "\tcheck= " << c6 << endl;
	cout << endl;

	s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0, s6 = 0;
	c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0;
	MyArray Array_40(1, 1000, 40);
	Array_40.BubbleSort(s1, c1);
	Array_40.InsertionSort(s2, c2);
	Array_40.MergeSort(s3, c3);
	Array_40.QuickSort(s4, c4);
	Array_40.SelectionSort(s5, c5);
	Array_40.HeapSort(s6, c6);
	cout << "\t Array with size 40: \t" << endl;
	cout << "\t\t Bubble: \t" << "swap= " << s1 << "\tcheck= " << c1 << endl;
	cout << "\t\t Insertion: \t" << "swap= " << s2 << "\tcheck= " << c2 << endl;
	cout << "\t\t Merge: \t" << "swap= " << s3 << "\tcheck= " << c3 << endl;
	cout << "\t\t Quick: \t" << "swap= " << s4 << "\tcheck= " << c4 << endl;
	cout << "\t\t Selection: \t" << "swap= " << s5 << "\tcheck= " << c5 << endl;
	cout << "\t\t Heap:      \t" << "swap= " << s6 << "\tcheck= " << c6 << endl;
	cout << endl;

	s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0, s6 = 0;
	c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0;
	MyArray Array_80(1, 1000, 80);
	Array_80.BubbleSort(s1, c1);
	Array_80.InsertionSort(s2, c2);
	Array_80.MergeSort(s3, c3);
	Array_80.QuickSort(s4, c4);
	Array_80.SelectionSort(s5, c5);
	Array_80.HeapSort(s6, c6);
	cout << "\t Array with size 80: \t" << endl;
	cout << "\t\t Bubble: \t" << "swap= " << s1 << "\tcheck= " << c1 << endl;
	cout << "\t\t Insertion: \t" << "swap= " << s2 << "\tcheck= " << c2 << endl;
	cout << "\t\t Merge: \t" << "swap= " << s3 << "\tcheck= " << c3 << endl;
	cout << "\t\t Quick: \t" << "swap= " << s4 << "\tcheck= " << c4 << endl;
	cout << "\t\t Selection: \t" << "swap= " << s5 << "\tcheck= " << c5 << endl;
	cout << "\t\t Heap:      \t" << "swap= " << s6 << "\tcheck= " << c6 << endl;
	cout << endl;

	s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0, s6 = 0;
	c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0;
	MyArray Array_100(1, 1000, 100);
	Array_100.BubbleSort(s1, c1);
	Array_100.InsertionSort(s2, c2);
	Array_100.MergeSort(s3, c3);
	Array_100.QuickSort(s4, c4);
	Array_100.SelectionSort(s5, c5);
	Array_100.HeapSort(s6, c6);
	cout << "\t Array with size 100: \t" << endl;
	cout << "\t\t Bubble: \t" << "swap= " << s1 << "\tcheck= " << c1 << endl;
	cout << "\t\t Insertion: \t" << "swap= " << s2 << "\tcheck= " << c2 << endl;
	cout << "\t\t Merge: \t" << "swap= " << s3 << "\tcheck= " << c3 << endl;
	cout << "\t\t Quick: \t" << "swap= " << s4 << "\tcheck= " << c4 << endl;
	cout << "\t\t Selection: \t" << "swap= " << s5 << "\tcheck= " << c5 << endl;
	cout << "\t\t Heap:      \t" << "swap= " << s6 << "\tcheck= " << c6 << endl;
	cout << endl;

	s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0, s6 = 0;
	c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0;
	MyArray Array_200(1, 1000, 200);
	Array_200.BubbleSort(s1, c1);
	Array_200.InsertionSort(s2, c2);
	Array_200.MergeSort(s3, c3);
	Array_200.QuickSort(s4, c4);
	Array_200.SelectionSort(s5, c5);
	Array_200.HeapSort(s6, c6);
	cout << "\t Array with size 200: \t" << endl;
	cout << "\t\t Bubble: \t" << "swap= " << s1 << "\tcheck= " << c1 << endl;
	cout << "\t\t Insertion: \t" << "swap= " << s2 << "\tcheck= " << c2 << endl;
	cout << "\t\t Merge: \t" << "swap= " << s3 << "\tcheck= " << c3 << endl;
	cout << "\t\t Quick: \t" << "swap= " << s4 << "\tcheck= " << c4 << endl;
	cout << "\t\t Selection: \t" << "swap= " << s5 << "\tcheck= " << c5 << endl;
	cout << "\t\t Heap:      \t" << "swap= " << s6 << "\tcheck= " << c6 << endl;
	cout << endl;

	s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0, s6 = 0;
	c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0;
	MyArray Array_500(1, 1000, 500);
	Array_500.BubbleSort(s1, c1);
	Array_500.InsertionSort(s2, c2);
	Array_500.MergeSort(s3, c3);
	Array_500.QuickSort(s4, c4);
	Array_500.SelectionSort(s5, c5);
	Array_500.HeapSort(s6, c6);
	cout << "\t Array with size 500: \t" << endl;
	cout << "\t\t Bubble: \t" << "swap= " << s1 << "\tcheck= " << c1 << endl;
	cout << "\t\t Insertion: \t" << "swap= " << s2 << "\tcheck= " << c2 << endl;
	cout << "\t\t Merge: \t" << "swap= " << s3 << "\tcheck= " << c3 << endl;
	cout << "\t\t Quick: \t" << "swap= " << s4 << "\tcheck= " << c4 << endl;
	cout << "\t\t Selection: \t" << "swap= " << s5 << "\tcheck= " << c5 << endl;
	cout << "\t\t Heap:      \t" << "swap= " << s6 << "\tcheck= " << c6 << endl;
	cout << endl;

	s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0, s6 = 0;
	c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0;
	MyArray Array_1000(1, 1000, 1000);
	Array_1000.BubbleSort(s1, c1);
	Array_1000.InsertionSort(s2, c2);
	Array_1000.MergeSort(s3, c3);
	Array_1000.QuickSort(s4, c4);
	Array_1000.SelectionSort(s5, c5);
	Array_1000.HeapSort(s6, c6);
	cout << "\t Array with size 1000: \t" << endl;
	cout << "\t\t Bubble: \t" << "swap= " << s1 << "\tcheck= " << c1 << endl;
	cout << "\t\t Insertion: \t" << "swap= " << s2 << "\tcheck= " << c2 << endl;
	cout << "\t\t Merge: \t" << "swap= " << s3 << "\tcheck= " << c3 << endl;
	cout << "\t\t Quick: \t" << "swap= " << s4 << "\tcheck= " << c4 << endl;
	cout << "\t\t Selection: \t" << "swap= " << s5 << "\tcheck= " << c5 << endl;
	cout << "\t\t Heap:      \t" << "swap= " << s6 << "\tcheck= " << c6 << endl;
	cout << endl;

	_getch();
	
	return 0;
}