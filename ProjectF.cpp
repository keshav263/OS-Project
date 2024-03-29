#include <iostream>
#include<vector>
#include <bits/stdc++.h>
#include <string>
#include <queue>
#include <stdio.h>
#include<cstdio>

using namespace std;
const int T_S = 200;
class HashTableEntry {
   public:
      int k;
      int v;
      HashTableEntry(int k, int v) {
         this->k= k;
         this->v = v;
      }
};
class HashMapTable {
   private:
      HashTableEntry **t;
   public:
      HashMapTable() {
         t = new HashTableEntry * [T_S];
         for (int i = 0; i< T_S; i++) {
            t[i] = NULL;
         }
      }
      int HashFunc(int k) {
         return k % T_S;
      }
      void Insert(int k, int v) {
         int h = HashFunc(k);
         while (t[h] != NULL && t[h]->k != k) {
            h = HashFunc(h + 1);
         }
         if (t[h] != NULL)
            delete t[h];
         t[h] = new HashTableEntry(k, v);
      }
      int SearchKey(int k) {
         int h = HashFunc(k);
         while (t[h] != NULL && t[h]->k != k) {
            h = HashFunc(h + 1);
         }
         if (t[h] == NULL)
            return -1;
         else
            return t[h]->v;
      }
      void Remove(int k) {
         int h = HashFunc(k);
         while (t[h] != NULL) {
            if (t[h]->k == k)
               break;
            h = HashFunc(h + 1);
         }
         if (t[h] == NULL) {
            cout<<"No Element found at key "<<k<<endl;
            return;
         } else {
            delete t[h];
         }
         cout<<"Element Deleted"<<endl;
      }
      ~HashMapTable() {
         for (int i = 0; i < T_S; i++) {
            if (t[i] != NULL)
               delete t[i];
               delete[] t;
         }
      }
};


bool searchIfPageAlreadyExistsInFrames(int key, vector<int>& frames)
{
	for (int i = 0; i < frames.size(); i++)
		if (frames[i] == key)
			return true;
	return false;
}

int predict(int pages[], vector<int>& frames, int pageSize, int index)
{
	int frameIndex = -1, farthestPage = index;
	for (int i = 0; i < frames.size(); i++) {
        int j;
        for (j = index; j < pageSize; j++) {
			if (frames[i] == pages[j]) {
				if (j > farthestPage) {
					farthestPage = j;
					frameIndex = i;
				}
				break;
			}
		}

		if (j == pageSize)
			return i;
	}

	if (frameIndex==-1){
        return 0;
    }else{
        return frameIndex;
    }

}

void optimalPage()
{

    cout << "\t\t\t\tWe will be using Optimal Page Replacement for Memory Management in Network OS"<<endl;
    int frameSize, pages[100],pageSize;

    cout << "Number of frames:";
    cin >> frameSize;

    cout << "Number of Pages:";
    cin >> pageSize;

    cout << "Pages Stream:";
    for (int i = 0; i < pageSize; i++)
    {
        cin >> pages[i];
    }

	vector<int> frames;


	int hit = 0;
	cout << "Frames are as follows:"<<endl;
    for (int i = 0; i < pageSize; i++) {
        cout << "Step"<<"["<<i<<"]:"<<endl;
        for (int i = 0; i < frames.size(); i++)
        {
            if (frames.size()==0)
            {
                cout << "Empty"<<endl;
                break;
            }

            cout <<" "<< frames[i]<<endl;
            cout << "---"<<endl;
        }



        if (searchIfPageAlreadyExistsInFrames(pages[i], frames)) {
			hit++;
			continue;
		}


		if (frames.size() < frameSize)
			frames.push_back(pages[i]);


		else {
			int j = predict(pages, frames, pageSize, i + 1);
			frames[j] = pages[i];
		}
	}
	cout << "No. of hits:" << hit << endl;
	cout << "No. of misses:" << pageSize - hit << endl;
    cout << "Hit Percentage:" << (hit / pageSize) * 100 << "%"<<endl;
    cout << "Miss Percentage:" << ((pageSize - hit) / pageSize) * 100 << "%" << endl;
}



int size = 8;
int disk_size = 200;
void scan()
{
    int arr[size] = { 176, 79, 34, 60, 92, 11, 41, 114 };
    int head;
    cout<<"\nEnter read/write head position: ";
    cin>>head;

    string direction;
    cout<<"\nEnter direction: l/L for left and r/R for right: ";
    cin>>direction;

    if(direction=="l" || direction == "L")
        direction = "left";
    else
        direction = "right";

     int seek_count = 0;
    int distance, cur_track;
    vector<int> left, right;
    vector<int> seek_sequence;

    if (direction == "left")
        left.push_back(0);
    else if (direction == "right")
        right.push_back(disk_size - 1);

    for (int i = 0; i < size; i++) {
        if (arr[i] < head)
            left.push_back(arr[i]);
        if (arr[i] > head)
            right.push_back(arr[i]);
    }

    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    int run = 2;
    while (run--) {
        if (direction == "left") {
            for (int i = left.size() - 1; i >= 0; i--) {
                cur_track = left[i];
                seek_sequence.push_back(cur_track);
                distance = abs(cur_track - head);
                seek_count += distance;
                head = cur_track;
            }
            direction = "right";
        }
        else if (direction == "right") {
            for (int i = 0; i < right.size(); i++) {
                cur_track = right[i];
                seek_sequence.push_back(cur_track);
                distance = abs(cur_track - head);
                seek_count += distance;
                head = cur_track;
            }
            direction = "left";
        }
    }

    cout << "Total number of seek operations = "
         << seek_count << endl;

    cout << "Seek Sequence is" << endl;

    for (int i = 0; i < seek_sequence.size(); i++) {
        cout << seek_sequence[i] << endl;
    }
}



int main()
{
    int ch = 0;
    do
    {

        cout << "Choose one from the following:"<<endl;
        cout << "\n1.Memory Management";
        cout << "\n2.I/O Management";
        cout <<"\n3.File Management";
        cout << "\n5.Exit";

        cout << "\n\nEnter your choice:";
        cin >> ch;
        switch (ch)
        {
        case 1:
            optimalPage();
            break;

        case 2:
            scan();
        case 3:
        {
        HashMapTable hash;
       int k, v;
       int c;
       while (1) {
          cout<<"1.Insert element into the table"<<endl;
          cout<<"2.Search element from the key"<<endl;
          cout<<"3.Delete element at a key"<<endl;
          cout<<"4.Exit"<<endl;
          cout<<"Enter your choice: ";
          cin>>c;
          switch(c) {
             case 1:
                cout<<"Enter element to be inserted: ";
                cin>>v;
                cout<<"Enter key at which element to be inserted: ";
                cin>>k;
                hash.Insert(k, v);
             break;
             case 2:
                cout<<"Enter key of the element to be searched: ";
                cin>>k;
                if (hash.SearchKey(k) == -1) {
                   cout<<"No element found at key "<<k<<endl;
                   continue;
                } else {
                   cout<<"Element at key "<<k<<" : ";
                   cout<<hash.SearchKey(k)<<endl;
                }
             break;
             case 3:
                cout<<"Enter key of the element to be deleted: ";
                cin>>k;
                hash.Remove(k);
             break;
             case 4:
                exit(1);
             default:
                cout<<"\nEnter correct option\n";
      }
   }
   break;
        }


        default:
            break;
        }

        if (ch<1 || ch>5)
        {
            cout << "Wrong Input!!" << endl;
            continue;
        }


    } while (ch!=5);



}





/*void displayGraph(vector<vector<int>> wait_graph)
{
	int n = wait_graph.at(0).size();
	int m = wait_graph.size();


	cout << "\t";
	for (int j = 0; j < m; j++) {
		cout << "S" << (j + 1) << "\t";
	}
	cout << endl;

	for (int i = 0; i<m; i++)
	{
		cout << "S" << (i + 1) << "\t";
		for (int j = 0; j<n; j++)
		{
			cout << wait_graph.at(i).at(j) << "\t";
		}
		cout << "\n";
	}
}

void detectDeadlock(vector<std::vector<int>> &graph, int init, int dest)
{
	int end = no_proccesses;
	for (int col = 0; col < end; col++)
	{
		if (graph[dest][col] == 1)
		{
			if (init == col)
			{
				cout << " S" << (dest + 1) << " --> S" << (col + 1) <<"     (" << (init + 1) << "," << (dest + 1) << "," << (col + 1) << ")" << " --------> DEADLOCK DETECTED HERE" << endl;
				deadlock_flag = 1;
				break;
			}
			cout << " S" << (dest + 1) << " --> S" << (col + 1) << "     (" << (init + 1) << "," << (dest + 1) << "," << (col + 1) << ")" << endl;
			detectDeadlock(graph, init, col);
		}
	}
}*/
