using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using UnityEngine;
using UnityEngine.UI;

/*
 * Create datas est un script qui va nous permettre de créer des jeux de données pour nos différents gestes/mouvements.
 */
public class CreateDatas : MonoBehaviour {
    Mouvement hands;
    public StreamWriter sw;
    string path;
    string folder;
    bool isRecording;
    bool isCurve;
    int currentIndex;

    Button goToPlaySceneButton;
    Dropdown staticGesturesDropdown;

    GameObject[] disabledButtonWhenRecord;
    GameObject[] enabledButtonWhenRecord;

    /*
     * Le constructeur de createDatas va initialiser les champs dont nous aurons besoin par la suite.
     */
    public CreateDatas () {
        this.folder = Directory.GetCurrentDirectory () + @"\\Datas";
        isRecording = false;
        currentIndex=0;
    }

    // Start is called before the first frame update
    /*
     * Initialisation des mains captées par le leapmotion
     */
    void Start () {
        this.hands = (Mouvement) GetComponent ("Mouvement");
        staticGesturesDropdown = GameObject.Find ("Canvas/GesturesDropdown").GetComponent<Dropdown> ();
        staticGesturesDropdown.onValueChanged.AddListener (delegate {
            changeParametersGestures (staticGesturesDropdown.value);
        });
        disabledButtonWhenRecord = GameObject.FindGameObjectsWithTag ("DisableWhenRecord");
        enabledButtonWhenRecord = GameObject.FindGameObjectsWithTag ("EnableWhenRecord");

        setButtonStateWhenNotRecord ();
    }

    // Update is called once per frame
    /*
     * A chaque frame, on enregistre les données que l'ont reçois du leapMotion dans le fichier de données.
     */
    void Update () {
        if (isRecording) {
            Transform palm = hands.PalmLeft;
            string line = "";
            if (!isCurve) {

                line += hands.getDistanceBetween (hands.ThumbLeft, palm);
                line += " " + hands.getDistanceBetween (hands.IndexLeft, palm);
                line += " " + hands.getDistanceBetween (hands.MiddleLeft, palm);
                line += " " + hands.getDistanceBetween (hands.PinkLeft, palm);
                line += " " + hands.getDistanceBetween (hands.RingLeft, palm);
                sw.WriteLine (line);
            } else {
                List<float> positions = hands.getPositionsOfHands (0);
                line += hands.PalmRight.position.x + " " + hands.PalmRight.transform.position.y + " " + hands.PalmRight.transform.position.z;
                sw.WriteLine (line);
            }
        }
    }

    /*
     * changeParametersGestures est appelé à chaque fois que l'élément de selection est modifié.
     * Elle permet de mettre à jour le chemin du fichier dans lequel on veut enregitrer et de dire 
     * si oui ou non on enregistre une courbe (geste dynamique)
     */

    private void changeParametersGestures (int gestureIndex) {
        Guid guid = Guid.NewGuid ();
        switch (gestureIndex) {
            case 0:
                isCurve = false;
                this.path = this.folder + @"\gestes_statiques\0.txt";
                break;

            case 1:
                isCurve = false;
                this.path = this.folder + @"\gestes_statiques\1.txt";
                break;

            case 2:
                isCurve = false;
                this.path = this.folder + @"\gestes_statiques\2.txt";
                break;

            case 3:
                isCurve = false;
                this.path = this.folder + @"\gestes_statiques\3.txt";
                break;

            case 4:
                isCurve = false;
                this.path = this.folder + @"\gestes_statiques\4.txt";
                break;

            case 5:
                isCurve = true;
                this.path = this.folder + @"\gestes_dynamiques\curve8" + "-" + guid + ".txt";
                break;

            case 6:
                isCurve = true;
                this.path = this.folder + @"\gestes_dynamiques\curvefinish" + "-" + guid + ".txt";
                break;

            case 7:
                isCurve = true;
                this.path = this.folder + @"\gestes_dynamiques\curvehighLevel" + "-" + guid + ".txt";
                break;
        }
        currentIndex=gestureIndex;
    }

    /*
    * Cette méthode lance l'enregistrement des gestes    
    */
    public void launchRecord () {
        setButtonStateWhenRecord ();
        changeParametersGestures(currentIndex);
        UnityEngine.Debug.Log (this.path);
        sw = File.AppendText (this.path);
        isRecording = true;
    }

    /*
    * Cette méthode permet de stopper l'enregistrement des gestes
    */
    public void stopRecord () {
        setButtonStateWhenNotRecord ();
        sw.Close ();
        isRecording=false;
    }

    /*
    * Cette méthode permet de changer l'état des boutons de la scène
    */
    private void setButtonStateWhenNotRecord () {
        foreach (GameObject o in disabledButtonWhenRecord) {
            o.SetActive (true);
        }

        foreach (GameObject o in enabledButtonWhenRecord) {
            o.SetActive (false);
        }
    }
    /*
    * Cette méthode permet de changer l'état des boutons de la scène
    */
    private void setButtonStateWhenRecord () {
        foreach (GameObject o in disabledButtonWhenRecord) {
            o.SetActive (false);
        }

        foreach (GameObject o in enabledButtonWhenRecord) {
            o.SetActive (true);
        }
    }

}