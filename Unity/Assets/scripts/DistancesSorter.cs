using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//DONE
/*
 * DataSorter est une classe héritant de IComparer qui nous permet de trier les données pour les différents algorithmes de classifications.
 */ 
public class DistancesSorter : IComparer<List<float>>
{

    public int Compare(List<float> x, List<float> y)
    {
    
        return  x[0] > y[0] ? 1 : -1;
    }
}
