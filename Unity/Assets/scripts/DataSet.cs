using System.IO;
using System.Linq;
using UnityEngine;
using System.Collections.Generic;

/*
 * DataSet est une classe qui nous permet d'enregistrer des jeux de données.
 * 
 */
public class DataSet
{
    List<List<float>> datasStatic;
    List<List<List<float>>> datasDynamic;

    List<int> targetStatic;
    List<int> targetDynamic;

    public List<List<float>> DatasStatic { get => datasStatic; }
    public List<List<List<float>>> DatasDynamic { get => datasDynamic; }

    public List<int> TargetStatic { get => targetStatic; }
    public List<int> TargetDynamic { get => targetDynamic; }


    public List<string> files;
    public DataSet(string folderPath, bool isCurve)
    {
        files = new List<string>(Directory.GetFiles(folderPath, "*.txt"));
        int k = 0;
        StreamReader reader;
        //int nbElt= File.ReadLines(files[0]).Count() + File.ReadLines(files[1]).Count()+ File.ReadLines(files[2]).Count();
        if (!isCurve)
        {
            datasStatic = new List<List<float>>();
            targetStatic = new List<int>();
            foreach (string file in files)
            {
                reader = File.OpenText(file);
                string line;
                while ((line = reader.ReadLine()) != null)
                {
                    List<float> distances = line.Split(' ').Select(float.Parse).ToList();
                    datasStatic.Add(distances);
                    targetStatic.Add(k);
                }
                k++;
                reader.Close();
            }
        }
        else
        {
            datasDynamic = new List<List<List<float>>>();
            targetDynamic = new List<int>();
            foreach (string file in files)
            {
                reader = File.OpenText(file);
                string line;
                List<List<float>> gesture = new List<List<float>>();
                while ((line = reader.ReadLine()) != null)
                {
                    List<float> point = line.Split(' ').Select(float.Parse).ToList();
                    gesture.Add(point);
                }
                targetDynamic.Add(k);
                datasDynamic.Add(gesture);
                k++;
                reader.Close();
            }
        }
    }
}
