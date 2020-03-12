using System.Diagnostics;
using System.IO;
using UnityEngine;
//DONE
public class CreateDatas : MonoBehaviour
{
    Mouvement hands;
    public StreamWriter sw;
    string path;
    string folder;
    bool isRecording;


    public CreateDatas()
    {
        this.folder = Directory.GetCurrentDirectory()+@"\Assets\scripts\Datas";
        isRecording = false;
    }

    // Start is called before the first frame update
    void Start()
    {
        this.hands = (Mouvement)GetComponent("Mouvement");
    }

    // Update is called once per frame
    void Update()
    {
        if (isRecording)
        {
            Transform palm = hands.PalmLeft;
            string line = "";
            line += hands.getDistanceBetween(hands.ThumbLeft, palm);
            line += " " + hands.getDistanceBetween(hands.IndexLeft, palm);
            line += " " + hands.getDistanceBetween(hands.MiddleLeft, palm);
            line += " " + hands.getDistanceBetween(hands.PinkLeft, palm);
            line += " " + hands.getDistanceBetween(hands.RingLeft, palm);
            sw.WriteLine(line);
        }
    }

    private void OnGUI()
    {
        if (isRecording)
        {
            if (GUI.Button(new Rect(10, 10, 150, 100), "Click to Stop record !"))
            {
                isRecording = !isRecording;
                sw.Close();
            }
        }
        else
        {
            if (GUI.Button(new Rect(10, 10, 300, 100), "Click to record for clenched fist !"))
            {
                path = folder + @"\0.txt";
                sw = File.AppendText(path);
                isRecording = !isRecording;
            }

            if (GUI.Button(new Rect(340, 10, 300, 100), "Click to record for Open hand !"))
            {
                path = folder + @"\1.txt";
                sw = File.AppendText(path);
                isRecording = !isRecording;
            }

            if (GUI.Button(new Rect(680, 10, 300, 100), "Click to record for two Fingers !"))
            {
                path = folder + @"\2.txt";
                sw = File.AppendText(path);
                isRecording = !isRecording;
            }

            if (GUI.Button(new Rect(1020, 10, 300, 100), "Click to record for one Finger !"))
            {
                path = folder + @"\3.txt";
                sw = File.AppendText(path);
                isRecording = !isRecording;
            }
        }
    }

}
