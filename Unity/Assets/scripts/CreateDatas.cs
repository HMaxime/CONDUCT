using System.Diagnostics;
using System.IO;
using UnityEngine;
//DONE
/*
 * Create datas est un script qui va nous permettre de créer des jeux de données pour nos différents gestes/mouvements.
 */
public class CreateDatas : MonoBehaviour
{
    Mouvement hands;
    public StreamWriter sw;
    string path;
    string folder;
    bool isRecording;
    bool isCurve;

    /*
     * Le constructeur de createDatas va initialiser les champs dont nous aurons besoin par la suite.
     */
    public CreateDatas()
    {
        this.folder = Directory.GetCurrentDirectory() + @"\Assets\scripts\Datas";
        isRecording = false;
    }

    // Start is called before the first frame update
    /*
     * Initialisation des mains captées par le leapmotion
     */
    void Start()
    {
        this.hands = (Mouvement)GetComponent("Mouvement");
    }

    // Update is called once per frame
    /*
     * A chaque frame, on enregistre les données que l'ont reçois du leapMotion dans le fichier de données.
     */
    void Update()
    {
        if (isRecording)
        {
            Transform palm = hands.PalmLeft;
            string line = "";
            if (!isCurve)
            {

                line += hands.getDistanceBetween(hands.ThumbLeft, palm);
                line += " " + hands.getDistanceBetween(hands.IndexLeft, palm);
                line += " " + hands.getDistanceBetween(hands.MiddleLeft, palm);
                line += " " + hands.getDistanceBetween(hands.PinkLeft, palm);
                line += " " + hands.getDistanceBetween(hands.RingLeft, palm);
                sw.WriteLine(line);
            }
            else
            {
                float[] positions = hands.getPositionsOfHands(0);
                line += hands.PalmLeft.position.x + " " + hands.PalmLeft.transform.position.y + " " + hands.PalmLeft.transform.position.z;
                sw.WriteLine(line);
            }

        }
    }

    /*
     * OnGui est une méthode qui permet d'avoir accès à une interface graphique, facilitant l'enregistrement de données.
     */
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
                isCurve = false;
                path = folder + @"\0.txt";
                sw = File.AppendText(path);
                isRecording = !isRecording;
            }

            if (GUI.Button(new Rect(340, 10, 300, 100), "Click to record for Open hand !"))
            {
                isCurve = false;
                path = folder + @"\1.txt";
                sw = File.AppendText(path);
                isRecording = !isRecording;
            }

            if (GUI.Button(new Rect(680, 10, 300, 100), "Click to record for two Fingers !"))
            {
                isCurve = false;
                path = folder + @"\2.txt";
                sw = File.AppendText(path);
                isRecording = !isRecording;
            }

            if (GUI.Button(new Rect(1020, 10, 300, 100), "Click to record for one Finger !"))
            {
                isCurve = false;
                path = folder + @"\3.txt";
                sw = File.AppendText(path);
                isRecording = !isRecording;
            }

            if (GUI.Button(new Rect(1340, 10, 300, 100), "Click to record curve !"))
            {
                isCurve = true;
                path = folder + @"\curve.txt";
                sw = File.AppendText(path);
                isRecording = !isRecording;
            }
        }
    }

}
