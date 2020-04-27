using System.IO;
using System.Linq;
using UnityEngine;
using System.Collections.Generic;
using System.Linq;

/*
 * DataSet est une classe qui nous permet d'enregistrer des jeux de données.
 * 
 */ 
public class DataSet
{
    List<List<float>> datas;
    List<int> target;

    public List<List<float>> Datas { get => datas; }
    public List<int> Target { get => target; }
    public List<string> files;
    public DataSet(string folderPath)
    {
        files = new List<string>(Directory.GetFiles(folderPath,"*.txt"));
        //int nbElt= File.ReadLines(files[0]).Count() + File.ReadLines(files[1]).Count()+ File.ReadLines(files[2]).Count();
        datas = new List<List<float>>();
        target = new List<int>();
        int k = 0;
        foreach (string file in files)
        {
            StreamReader reader = File.OpenText(file);
            string line;
            while ((line = reader.ReadLine()) != null)
            {
                List<string> stringDistances = line.Split(' ').ToList();
                List<float> floatDistance = new List<float>();
                foreach (string distance in stringDistances)
                {
                    floatDistance.Add(float.Parse(distance));
                }
                datas.Add(floatDistance);
                target.Add(k);
            }
            k++;
            reader.Close();
        }  
    }
}
