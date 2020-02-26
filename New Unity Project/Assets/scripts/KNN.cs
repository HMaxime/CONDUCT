using System.Collections;
using UnityEngine;
using System;
using System.IO;
//DONE
public class KNN : MonoBehaviour
{
    public Transform leftHand;
    public Transform rightHand;
    public StreamWriter sw;
    public Boolean isRecording = false;
    public float[][] datas;

    Transform thumbLeft;
    Transform indexLeft;
    Transform middleLeft;
    Transform pinkLeft;
    Transform ringLeft;
    Transform palmLeft;


    Transform thumbRight;
    Transform indexRight;
    Transform middleRight;
    Transform pinkRight;
    Transform ringRight;
    Transform palmRight;

    public class DistancesSorter : IComparer
    {

        public int Compare(int[] p1, int[] p2)
        {
            return p1[0] > p2[0] ? 1 : 0;
        }

        public int Compare(object x, object y)
        {
            throw new NotImplementedException();
        }
    }


    // Start is called before the first frame update
    void Start()
    {
        leftHand = this.gameObject.transform.GetChild(1);
        rightHand = this.gameObject.transform.GetChild(1);

        thumbLeft = leftHand.GetChild(0).GetChild(0);
        indexLeft = leftHand.GetChild(1).GetChild(0);
        middleLeft = leftHand.GetChild(2).GetChild(0);
        pinkLeft = leftHand.GetChild(3).GetChild(0);
        ringLeft = leftHand.GetChild(4).GetChild(0);
        palmLeft = leftHand.GetChild(5);


        thumbRight = rightHand.GetChild(0).GetChild(0);
        indexRight = rightHand.GetChild(1).GetChild(0);
        middleRight = rightHand.GetChild(2).GetChild(0);
        pinkRight = rightHand.GetChild(3).GetChild(0);
        ringRight = rightHand.GetChild(4).GetChild(0);
        palmRight = rightHand.GetChild(5);
        var path = @"C:\Users\MaximeHamon\Documents\Cours\UBS\twoFingers.txt";
        sw = File.AppendText(path);
    }

    // Update is called once per frame
    void Update()
    {
        if (isRecording)
        {
            float[] palmPosition = posTransformToArray(palmLeft);
            string line = "";
            line+=" "+ComputeDistance(posTransformToArray(thumbLeft),palmPosition);
            line += " " + ComputeDistance(posTransformToArray(indexLeft), palmPosition);
            line += " " + ComputeDistance(posTransformToArray(middleLeft), palmPosition);
            line += " " + ComputeDistance(posTransformToArray(pinkLeft), palmPosition);
            line += " " + ComputeDistance(posTransformToArray(ringLeft), palmPosition);

            sw.WriteLine(line);
        }
    }

    float[] posTransformToArray(Transform tr) => new float[3] { tr.position.x, tr.position.y, tr.position.z };

    float ComputeDistance(float[] p1, float[] p2)
    {
        float res = 0;
        for (int i = 0; i < p1.Length; i++)
        {
            res += Mathf.Pow(p1[i] - p2[i], 2);
        }
        return res;
    }

    int knn(int K, float[][] datas, int[] target, float[][] data)
    {
        float[][] distances = new float[target.Length][];
        for (int i = 0; i < datas.Length; i++)
        {
            distances[i] = new float[] { ComputeDistance(datas[i], data[i]), target[i] };
        }
        Array.Sort(distances, new DistancesSorter());
        int[] classes = getFirstKcolumn(K, 1, distances);

        return getMostFrequenElement(classes);
    }

    int getMostFrequenElement(int[] tab_)
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

    int[] getFirstKcolumn(int k_, int i_, float[][] tab_)
    {
        int[] res = new int[tab_[0].Length];
        for (int i = 0; i < k_; i++)
        {
            res[i] = (int)tab_[i][i_];
        }

        return res;
    }

    private void OnGUI()
    {
        if (GUI.Button(new Rect(10, 10, 150, 100), "Click to record"))
        {
            isRecording = !isRecording;
            if (!isRecording)
            {
                print("You are not recording !");
            }
            else
            {
                print("You are recording !");
            }
        }
    }
}
