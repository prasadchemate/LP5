#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

void merge(int * arr,int low,int mid,int up)
{
	int * temp = new int[(up-low)+2];
	int i,j,k;
	i = low;
	j = mid+1;
	k = 0;
	
	while(i<=mid && j<=up)
	{
		if(arr[i] < arr[j])
		{
			temp[k] = arr[i];
			i++;
			k++;
		}
		else
		{
			temp[k] = arr[j];
			j++;
			k++;
		}
	}
	while(i<=mid)
	{
		temp[k] = arr[i];
		i++;
		k++;
	}
	while(j<=up)
	{
		temp[k] = arr[j];
		j++;
		k++;
	}
	
	k=0;
	for(int i=low; i<=up; i++)
	{
		arr[i] = temp[k];
		k++;
	}
}

void p_mergesort(int * arr,int low,int up)
{
	if(low < up)
	{
		int mid = (low+up)/2;
		#pragma omp parallel sections
		{
			#pragma omp section
			{
				p_mergesort(arr,low,mid);
			}
			#pragma omp section
			{
				p_mergesort(arr,mid+1,up);
			}
		}
		merge(arr,low,mid,up);
	}
}

void perform_parallel_mergesort(int * array,int SIZE)
{
	int * arr = new int[SIZE];
	for(int i=0; i<SIZE; i++)
		arr[i] = array[i];
	
	double start, end;
	start = omp_get_wtime();
	p_mergesort(arr, 0, SIZE-1);
	end = omp_get_wtime();
	
	cout<<"\nTime Required for Parallel MergeSort = "<<(end-start)<<" sec";

//	cout<<"\n\nSorted Array\n";
//	for(int i=0; i<SIZE; i++)
//	{
//		cout<<" "<<array[i];
//	}
}

void s_mergesort(int * arr,int low,int up)
{
	if(low < up)
	{
		int mid = (low+up)/2;
		s_mergesort(arr,low,mid);
		s_mergesort(arr,mid+1,up);
		merge(arr,low,mid,up);
	}
}

void perform_seq_mergesort(int * array,int SIZE)
{
	int * arr = new int[SIZE];
	for(int i=0; i<SIZE; i++)
		arr[i] = array[i];
	
	double start, end;
	start = omp_get_wtime();
	s_mergesort(arr, 0, SIZE-1);
	end = omp_get_wtime();
	
	cout<<"\nTime Required for Sequential MergeSort = "<<(end-start)<<" sec";
	
//	cout<<"\n\nSorted Array\n";
//	for(int i=0; i<SIZE; i++)
//	{
//		cout<<" "<<array[i];
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
	
	perform_seq_mergesort(array, SIZE);
	
	perform_parallel_mergesort(array, SIZE);
	
	return 0;
}
