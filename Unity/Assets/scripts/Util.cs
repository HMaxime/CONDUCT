using UnityEngine;
//DONE
public class Util
{
    public static int getMostFrequentElement(int[] tab_)
    {
        int currentValue = tab_[0];
        int count = 1;
        int maxCount = 1;

        for (int i = 1; i < tab_.Length; i++)
        {
            if (tab_[i] == tab_[i - 1])
            {
                count += 1;
            }
            else
            {
                if (count > maxCount)
                {
                    maxCount = count;
                    currentValue = tab_[i - 1];
                }
                count = 1;
            }
        }
        if (count > maxCount)
        {
            maxCount = count;
            currentValue = tab_[tab_.Length - 1];
        }
        return currentValue;
    }

    public static int[] getFirstKcolumn(int k_, int i_, float[][] tab_)
    {
        int[] res = new int[k_];
        for (int i = 0; i < k_; i++)
        {
            res[i] = (int)tab_[i][i_];
        }

        return res;
    }

    public static float ComputeDistance(float[] p1, float[] p2)
    {
        float res = 0;
        for (int i = 0; i < p1.Length; i++)
        {
            res += Mathf.Pow(p1[i] - p2[i], 2);
        }
        return res;
    }


    public static float[] posTransformToArray(Transform tr) => new float[3] { tr.position.x, tr.position.y, tr.position.z };

}
