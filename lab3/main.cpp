//
//  main.cpp
//  k nearest neighbour
//
//  Created by hell 'n silence on 11/15/18.
//  Copyright © 2018 Bohdan Podvirnyi. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;

struct Leaf
{
    int group;
    int width, height;
    int distance;
};

bool comparison(Leaf a, Leaf b)
{
    if (a.distance == b.distance)
    {
        return (a.group < b.group);
    }
    return (a.distance < b.distance);
}

int knn(Leaf study[], int n, int k, Leaf leaf, int ni)
{
    for (int i = 0; i < ni; i++)
    {
        study[i].distance = max( abs(study[i].width - leaf.width), abs(study[i].height - leaf.height) );
    }
    
    sort(study, study + ni, comparison);
    
    int *freq = new int[ni];
    for (int i = 0; i < ni; i++)
    {
        freq[i] = 0;
    }
    
    Leaf *array = new Leaf[ni];
    
    if (n < k) {
        for (int i = 0; i < ni; i++)
        {
            freq[study[i].group]++;
        }

    } else {
        for (int i = 0; i < k; i++)
        {
            freq[study[i].group]++;
            array[i] = study[i];
        }
        for (int i = k; i < ni; i++)
        {
            if (array[i - 1].distance == study[i].distance)
            {
                array[i] = study[i];
                freq[study[i].group]++;
            } else {
                break;
            }
        }
    }
    
    int max = -1;
    int j = -1;
    for (int i = 0; i < ni; i++)
    {
        if (freq[i] > max)
        {
            max = freq[i];
            j = i;
        }
    }
    
    return j + 1;
}

int main()
{
//    cout << "n,k,m:" << endl;
    int n, k, m;
    cin >> n >> k >> m;
    
    Leaf *study = new Leaf[n+m];
    Leaf *test = new Leaf[m];
    
    for (int i = 0; i < n; i++)
    {
        cin >> study[i].width >> study[i].height;
        study[i].group = i;
    }
    
    for (int i = 0; i < m; i++)
    {
        cin >> test[i].width >> test[i].height;
    }
    
    for (int i = 0; i < m; i++)
    {
        int j = knn(study, n, k, test[i], n+i);
        cout << j << " ";
        test[i].group = j-1;
        study[n+i] = test[i];
    }
    
    cout << endl;
    return 0;
}
