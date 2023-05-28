#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

void s_bubble_sort(int * array,int SIZE)
{
	int * arr = new int[SIZE];
	for(int i=0; i<SIZE; i++)
	{
		arr[i] = array[i];
	}
	
	double start,end;
	start = omp_get_wtime();
	//bubble sort code
	for(int i=0; i<SIZE; i++)
	{
		for(int j=0; j<SIZE-i-1; j++)
		{
			if(arr[j] > arr[j+1])
			{
				swap(arr[j], arr[j+1]);
				//int temp = arr[j];
				//arr[j] = arr[j+1];
				//arr[j+1] = arr[j]
			}
		}
	}
	end = omp_get_wtime();
	
	cout<<"\n\nSequential Time = "<<(end - start)<<" sec";
	
//	cout<<"\nSorted Array\n";
//	for(int i=0; i<SIZE; i++)
//	{
//		cout<<" "<<arr[i];
//	}	
}

void p_bubble_sort(int * array,int SIZE)
{
	int * arr = new int[SIZE];
	for(int i=0; i<SIZE; i++)
	{
		arr[i] = array[i];
	}
	
	double start,end;
	start = omp_get_wtime();
	//bubble sort code
	for(int i=0; i<SIZE; i++)
	{
		#pragma omp parallel for
		for(int j=0; j<SIZE-i-1; j++)
		{
			if(arr[j] > arr[j+1])
			{
				#pragma omp critical
				{
					swap(arr[j], arr[j+1]);
					//int temp = arr[j];
					//arr[j] = arr[j+1];
					//arr[j+1] = arr[j]
				}
			}
		}
	}
	end = omp_get_wtime();
	
	cout<<"\n\nParallel Time = "<<(end - start)<<" sec";
	
//	cout<<"\nSorted Array\n";
//	for(int i=0; i<SIZE; i++)
//	{
//		cout<<" "<<arr[i];
//	}	
}


int main()
{
	int SIZE;
	cout<<"Enter the size of array : ";
	cin>>SIZE;
	
	int * array = new int[SIZE];
	
	//initialize array elements
	for(int i=0; i<SIZE; i++)
	{
		array[i] = rand()%1000;
	}

//	cout<<"\nArray\n";
//	for(int i=0; i<SIZE; i++)
//	{
//		cout<<" "<<array[i];
//	}
	
	s_bubble_sort(array, SIZE);
	
	p_bubble_sort(array, SIZE);
	
	return 0;
}
