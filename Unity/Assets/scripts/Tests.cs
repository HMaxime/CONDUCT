using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using UnityEngine;
using UnityEngine.UI;

/*
 * La méthode Tests nous permet de tester les différents algorithmes de classification, tout en permettant l'envoie de message OSC vers PureData.
 */
public class Tests : MonoBehaviour {
    Mouvement hands;
    DataSet staticDataset;

    DataSet dynamicDataset;

    Transform palmLeft;
    Transform palmRight;
    Classifier classifier;
    UIController uiController;

    List<float> currentLeftHandDistances;
    List<float> currentRightHandDistances;
    LinkedList<List<float>> currentRightHandMouvement;

    float miniHorizontal = 20;
    float maxiHorizontal = -20;
    float miniVertical = 20;
    float maxiVertical = -20;

    int staticLeftHandClass = -1;
    int staticRightHandClass = -1;
    int dynamicRighthandClass = -1;
    OscMessage message;
    OSC osc;
    bool calibration = false;
    bool calibrationVertical = false;
    float volume, tempo, vibrato, frequency = 0;

    bool canDetectMouvement = true;

    Text staticLeftHandStatus;
    Text dynamicRightHandStatus;

    Text staticRightHandStatus;

    public Tests () {
        this.currentLeftHandDistances = new List<float> (5);
        this.currentRightHandDistances = new List<float> (5);
        this.currentRightHandMouvement = new LinkedList<List<float>> ();;
    }

    /*
     * On initialise tous les champs dont nous allons avoir besoin par la suite.
     */
    private void Start () {
        this.osc = (OSC) GetComponent ("OSC");
        UnityEngine.Debug.Log ("LOGGGG : " + Directory.GetCurrentDirectory ());
        this.staticDataset = new DataSet ("\\Datas\\gestes_statiques", false);
        this.dynamicDataset = new DataSet ("\\Datas\\gestes_dynamiques", true);

        this.classifier = new Classifier ();
        this.hands = (Mouvement) GetComponent ("Mouvement");
        this.uiController = (UIController) GameObject.Find ("Canvas").GetComponent ("UIController");

        this.staticLeftHandStatus = GameObject.Find ("Canvas/ImageStaticLeftHandStatus/staticLeftHandStatus").GetComponent<Text> ();
        this.staticRightHandStatus = GameObject.Find ("Canvas/ImageStaticRightHandStatus/staticRightHandStatus").GetComponent<Text> ();

        this.dynamicRightHandStatus = GameObject.Find ("Canvas/ImageDynamicRightHandStatus/dynamicRightHandStatus").GetComponent<Text> ();

    }

    // Update is called once per frame
    /*
     * On met à jour les mains, ainsi que la distance entre les différents doigts de la main gauche.
     */
    void Update () {
        this.hands = (Mouvement) GetComponent ("Mouvement");
        palmLeft = this.hands.PalmLeft;
        palmRight = this.hands.PalmRight;

        this.currentLeftHandDistances.Add (this.hands.getDistanceBetween (hands.ThumbLeft, palmLeft));
        this.currentLeftHandDistances.Add (this.hands.getDistanceBetween (hands.IndexLeft, palmLeft));
        this.currentLeftHandDistances.Add (this.hands.getDistanceBetween (hands.MiddleLeft, palmLeft));
        this.currentLeftHandDistances.Add (this.hands.getDistanceBetween (hands.PinkLeft, palmLeft));
        this.currentLeftHandDistances.Add (this.hands.getDistanceBetween (hands.RingLeft, palmLeft));

        this.currentRightHandDistances.Add (this.hands.getDistanceBetween (hands.ThumbRight, palmRight));
        this.currentRightHandDistances.Add (this.hands.getDistanceBetween (hands.IndexRight, palmRight));
        this.currentRightHandDistances.Add (this.hands.getDistanceBetween (hands.MiddleRight, palmRight));
        this.currentRightHandDistances.Add (this.hands.getDistanceBetween (hands.PinkRight, palmRight));
        this.currentRightHandDistances.Add (this.hands.getDistanceBetween (hands.RingRight, palmRight));

        this.currentRightHandMouvement.AddLast (new List<float> () { palmRight.position.x, palmRight.position.y, palmRight.position.z });
        if (this.currentRightHandMouvement.Count >= 50) {
            this.currentRightHandMouvement.RemoveFirst ();
        }

        this.staticRightHandClass = classifier.knn (3, staticDataset.DatasStatic, staticDataset.TargetStatic, currentRightHandDistances);

        if (calibration && this.staticRightHandClass == 0 && canDetectMouvement) {
            this.canDetectMouvement = false;
            StartCoroutine (enableMouvementDetection ());
            this.dynamicRighthandClass = classifier.knn (3, dynamicDataset.DatasDynamic, dynamicDataset.TargetDynamic, new List<List<float>> (currentRightHandMouvement));
        }
        this.staticLeftHandClass = classifier.knn (3, staticDataset.DatasStatic, staticDataset.TargetStatic, currentLeftHandDistances);

        this.currentLeftHandDistances.Clear ();
        this.currentRightHandDistances.Clear ();
    }

    /*
     * OnGui nous permet d'avoir une interface graphique.
     */
    private void OnGUI () {
        GUIStyle style = new GUIStyle ("Box");
        style.fontSize = 25;
        float value;
        //On fait la calibration
        if (!calibration) {
            //On fait la calibration vertical
            if (!calibrationVertical) {
                if (this.hands.PalmRight.position.y < miniVertical) {
                    miniVertical = this.hands.PalmRight.position.y;
                } else if (this.hands.PalmRight.position.y > maxiVertical) {
                    maxiVertical = this.hands.PalmRight.position.y;
                }
                GUI.Label (new Rect (10, 10, 500, 40), "Minimum Vertical = " + miniVertical, style);
                GUI.Label (new Rect (520, 10, 500, 40), "maximum Vertical = " + maxiVertical, style);
                GUI.Label (new Rect (1, 60, 1000, 40), "2 doigts => fin de la calibration vertical", style);

                //Fin de la calibration vertical
                if (this.staticLeftHandClass == 2) {
                    calibrationVertical = true;
                }
            }
            //On fait la calibration horizontal
            else {
                if (this.hands.PalmRight.position.x < miniHorizontal) {
                    miniHorizontal = this.hands.PalmRight.position.x;
                } else if (this.hands.PalmRight.position.x > maxiHorizontal) {
                    maxiHorizontal = this.hands.PalmRight.position.x;
                }

                GUI.Label (new Rect (10, 10, 500, 40), "Minimum Vertical = " + miniVertical, style);
                GUI.Label (new Rect (520, 10, 500, 40), "Maximum Vertical = " + maxiVertical, style);
                GUI.Label (new Rect (10, 60, 500, 40), "Minimum horizontal = " + miniHorizontal, style);
                GUI.Label (new Rect (520, 60, 500, 40), "Maximum horizontal = " + maxiHorizontal, style);
                GUI.Label (new Rect (1, 110, 1000, 40), "Poings fermés => fin de la calibration", style);

                //Fin de la calibration horizontal et fin de la calibration générale
                if (this.staticLeftHandClass == 0) {
                    calibration = true;
                }
            }
        } else {
            //Pour avoir les valeurs dans le bon interval : new_x=(x-M)/(N-M)
            message = new OscMessage ();
            switch (this.staticLeftHandClass) {
                case 0:
                    this.staticLeftHandStatus.text = "Poing fermé !";
                    value = (this.hands.PalmRight.position.x - miniHorizontal) / (maxiHorizontal - miniHorizontal);
                    tempo = value;
                    uiController.setTempoSliderValue (tempo);
                    break;
                case 1:
                    this.staticLeftHandStatus.text = "Main ouverte !";
                    break;

                case 2:
                    this.staticLeftHandStatus.text = "Deux doigts !";
                    value = (this.hands.PalmRight.position.y - miniVertical) / (maxiVertical - miniVertical);
                    volume = value;
                    uiController.setVolumeSliderValue (volume);
                    break;

                case 3:
                    this.staticLeftHandStatus.text = "Un doigt !";
                    value = (this.hands.PalmRight.position.x - miniHorizontal) / (maxiHorizontal - miniHorizontal);
                    vibrato = value;
                    uiController.setVibratoSlider (vibrato);
                    break;

                case 4:
                    this.staticLeftHandStatus.text = "Téléphone !";
                    value = (this.hands.PalmRight.position.y - miniVertical) / (maxiVertical - miniVertical);
                    frequency = value;
                    uiController.setFrequencySliderValue (frequency);
                    break;
            }

            switch (this.staticRightHandClass) {
                case 0:
                    this.staticRightHandStatus.text = "Poing fermé !";
                    break;
                case 1:
                    this.staticRightHandStatus.text = "Main ouverte !";
                    break;

                case 2:
                    this.staticRightHandStatus.text = "Deux doigts !";
                    break;

                case 3:
                    this.staticRightHandStatus.text = "Un doigt !";
                    break;

                case 4:
                    this.staticRightHandStatus.text = "Téléphone !";
                    break;
            }
            if (this.dynamicRighthandClass != -1) {
                switch (dynamicRighthandClass) {
                    case 0:
                        this.dynamicRightHandStatus.text = "Le huit !";
                        break;
                    case 1:
                        this.dynamicRightHandStatus.text = "Le finish !";
                        volume = 0;
                        uiController.setVolumeSliderValue (volume);
                        break;
                    case 2:
                        this.dynamicRightHandStatus.text = "Le high !";
                        frequency = 1;
                        uiController.setFrequencySliderValue (frequency);
                        break;
                }
                this.dynamicRighthandClass = -1;
            }

            message.address = "/127.0.0.1:5000";
            message.values.Add (volume);
            message.values.Add (tempo);
            message.values.Add (frequency);
            message.values.Add (vibrato);
            osc.Send (message);
        }
    }

    IEnumerator enableMouvementDetection () {
        yield return new WaitForSeconds (1);
        this.canDetectMouvement = true;
    }
}