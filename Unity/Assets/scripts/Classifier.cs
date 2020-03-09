using System;
using UnityEngine;
using static Util;
//DONE
public class Classifier
{
    static DistancesSorter sorter = new DistancesSorter();
    public int knn(int K, float[][] datas, int[] target, float[] data)
    {
        float[][] distances = new float[target.Length][];
        for (int i = 0; i < datas.Length; i++)
        {
            distances[i] = new float[] { ComputeDistance(datas[i], data), target[i] };
        }
        Array.Sort(distances, sorter);
        int[] classes = getFirstKcolumn(K, 1, distances);
        return getMostFrequentElement(classes);
    }
}
