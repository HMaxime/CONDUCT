using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//DONE
public class DistancesSorter : IComparer<float[]>
{

    public int Compare(float[] x, float[] y)
    {
        return  x[0]> y[0] ? 1 : -1;
    }
}
