using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;
using System.Timers;
using System.Threading;
using System.Threading.Tasks;

public class EnvironmentController : MonoBehaviour
{

    /*
    // Explications préalables
    // COULEURS UTILISES
    // 7 couleurs d'une même palette, voir palette.png dans le dossier source
    // Elles sont stockés dans un tableau "lightsArray" en RGB
    // Traduction En Hexadecimal
    // 0 : 112130 (Gunmetal)
    // 1 : 5B748B (Dark electric blue)
    // 2 : ABC8DD (Beau blue)
    // 3 : F0EDD1 (Beige)
    // 4 : EED1D0 (Pale pink)
    // 5 : D5DFDAE (Teag green)
    // 6 : FAF35C (Icterine)
    // Si il y a besoin de changer les couleurs, il faut changer le RGB dans le tableau lightsArray et re-exporter 7 images
    // de splat dans le dfossier Assets/Textures avec respectivement du plus foncé au plus clair : Splat_0_Decal.PNG, Splat_1...
    // Les images doivent posséder un channel alpha pour la transparence
    */
    
    UIController uiController;
    /*
    // PARTIE PEINTURE/SPLATS
    */
    const float max = 1.0f; //Valeur max des sliders
    const float min = 0.0f; //valeurs min des sliders
    const float YStart = -2.5f; //Coordonnée y du Bas du mur en face du joueur
    const float YEnd = 5.5f; //Coordonnée y du Haut du mur en face du joueur
    const float XStart = -8.0f;//Coordonnée x du Coté gauche du mur en face du joueur
    const float XEnd = 8.0f;//Coordonnée x du Coté droit du mur en face du joueur
    const float z = 9.54f; //Coordonnée z du mur en face du joueur

    private static readonly System.Random random = new System.Random();

    // Splat de peintures de 0 à 7 du plus foncé au plus clair
    public GameObject Splat0;
    public GameObject Splat1;
    public GameObject Splat2;
    public GameObject Splat3;
    public GameObject Splat4;
    public GameObject Splat5;
    public GameObject Splat6;
    GameObject[] splat;

    //temps à attendre entre chaque splat
    int timeBetweenSplat;

    //lock qui permet de controler la creation de splat
    bool canCreate;

    //durée d'affichage du splat de peinture
    int splatDuration;

    //taille d'un splat
    float splatScaleFactor;

    //Step de fade d'un splat, plus la valeur est petite, plus c'est lent (voir Splatnimation.cs)
    float splatFadeStep; 

    /*
    // PARTIE LUMIERE
    */
    public Light lumiereGauche;
    public Light lumiereDroite;

    //Contient les 7 couleurs possibles
    Color[] lightsArray;

    //L'environment se base sur les slider
    void Start()
    {
        /*
        // PARTIE PEINTURE/SPLATS
        */
        
        //assigne l'uicontroller
        this.uiController = (UIController)GameObject.Find("Canvas").GetComponent("UIController");
        
        //mets les différents splat de peinture dans tableau de taille 7
        splat = new GameObject[7]; 
        splat[0] = Splat0;
        splat[1] = Splat1;
        splat[2] = Splat2;
        splat[3] = Splat3;
        splat[4] = Splat4;
        splat[5] = Splat5;
        splat[6] = Splat6;

        //True si on peut creer un splat
        canCreate = true; 

        /*
        // PARTIE LUMIERE (RGB)
        */
        lightsArray = new Color[7];
        lightsArray[0] = new Color(17/255f, 33/255f, 48/255f);
        lightsArray[1] = new Color(91/255f, 116/255f, 139/255f);
        lightsArray[2] = new Color(171/255f, 200/255f, 221/255f);
        lightsArray[3] = new Color(240/255f, 237/255f, 209/255f);
        lightsArray[4] = new Color(238/255f, 209/255f, 208/255f);
        lightsArray[5] = new Color(213/255f, 253/255f, 174/255f);
        lightsArray[6] = new Color(250/255f, 243/255f, 92/255f);
    }


    void Update()
    {
        if(canCreate){
            print("--------------------- DEBUT UPDATE ---------------------");
            float tempo = this.uiController.getTempoSliderValue(); 
            float volume = this.uiController.getVolumeSliderValue();
            float attack = this.uiController.getAttackSliderValue();
            float frequency = this.uiController.getFrequencySliderValue();
            
            int index = findIndex(frequency);   
            setTimeBetweenSplat(tempo); //met à jour le temps entre chaque splat en fonction du tempo
            setSplatDuration(tempo); //determine la durée d'affichage d'un splat
            setScaleFactor(volume);
            setLightAmbience(index, tempo);
            setsplatFadeStep(attack);

            syncTempoAndSplat(index);
            print("--------------------- FIN UPDATE ---------------------");
        }
    }

    /*
    // Determine le temps que mets un splat à apparaitre en fonction de l'attack
    */
    void setsplatFadeStep(float attack){
        attack = attack + 0.1f;//pas de division par 0 merci
        splatFadeStep = attack / 2.0f;
        print("EnvironmentController Script - setsplatFadeStep(float attack)  " + splatFadeStep);
    }

    /*
    // Influence la couleur de la scène en fonction de l'index
    //reste toujours sur 2 couleurs pour rendre un peu plus dynamique
    */
    void setLightAmbience(int index, float tempo){
        tempo = 1.01f-tempo;
        float dureeTransition = tempo*3.0f; //plus la valeur est grande plus c'est long

        Color oldColor = lumiereDroite.GetComponent<Light>().color;
        Color newColor = lightsArray[index];

        float time = Mathf.PingPong(Time.time, dureeTransition) / dureeTransition;
        lumiereDroite.color = Color.Lerp(oldColor, newColor, time);
        lumiereGauche.color = Color.Lerp(oldColor, newColor, time);
        print("EnvironmentController Script - setLightAmbience(int index, float tempo) : " + index);
    }

    /*
    //Determine le facteur d'agrandissement de la tache
    //max x2
    //min normal
    */
    void setScaleFactor(float volume){
        float factor = 1.01f + volume;
        splatScaleFactor = factor;
        print("EnvironmentController Script - setScaleFactor(float volume) = : " + splatScaleFactor);
    }

    /*
    // recoit un tempo entre 0 et 1 et calcul le temps d'affichae d'un splat
    //max est 1200 d'affichage
    //min est 12000 ms d'affichage
    */
    void setSplatDuration(float tempo){
        tempo = (1 - tempo) * 10.0f;
        splatDuration = Convert.ToInt32(tempo * 4800.0f);
        print("EnvironmentController Script - setSplatDuration(float tempo) = : " + splatDuration);
    }

    //recoit un tempo entre 0 et 1 et calcul le temps qui doit séparer chaque apparitions
    //max est 8 fois par secondes soit tous les 200 ms
    //min est 1 fois toute les 2 secondes 2000 ms
    void setTimeBetweenSplat(float tempo){
        tempo = (1 - tempo) * 10;
        timeBetweenSplat = Convert.ToInt32(tempo * 200);
        print("EnvironmentController Script - timeBetweenSplat(flaot tempo) = " + timeBetweenSplat);
    }

    /*
        Creer un splat tous les X millisecondes, 
        X est contenu dans la variable global timeToWait
    */
    public async Task syncTempoAndSplat(int index)  
    {  
        canCreate = false;
        createSplat(index);
        await Task.Delay(timeBetweenSplat);  
        canCreate = true;
    }

    /*
    //determine la couleur à donner au splat en fonction de la fréquence
    */
    int findIndex(float frequency)
    {
        frequency = frequency * 100.0f;
        //7 couleurs disponibles donc 100/7 = 14.28
        int index = (int)(frequency / 14.29f);
        print("EnvironmentController Script - findIndex(flaot frequency) = " + index);
        return index;
    }

    /*
    //Creer un nouveau splat à des corrodonées aléatoires
    */
    void createSplat(int index){
        //si le splat précédent à été créé il y a moins de "timeToWait", alors on fait rien
            print("EnvironmentController Script - createSplat(int index) : nouveau clone de ");

            //pour une rotation autour de z
            Quaternion rotation = Quaternion.Euler(0, 0, randomBetween(0.0,360.0));

            //création du clone du splat à l'index "index" de splat[]
            GameObject SplatClone = Instantiate(splat[index], 
                new Vector3(
                    randomBetween(XStart,XEnd), 
                    randomBetween(YStart,YEnd), 
                    z
                ),
                rotation
               );
            print(" ->splat[" + index + "]");

            SplatClone.transform.localScale *= splatScaleFactor;
            print(" ->augmenté d'un facteur " + splatScaleFactor);
            SplatClone.GetComponent<PaintSplatAnimation>().isOriginal = false;
            print(" ->est Original false");
            SplatClone.GetComponent<PaintSplatAnimation>().duration = this.splatDuration;
            print(" ->durée d'affichage " + this.splatDuration + "ms");
            SplatClone.GetComponent<PaintSplatAnimation>().step = this.splatFadeStep;
            print(" ->durée de fade in/out " + this.splatFadeStep);   
   }

    /*
    // Génere un nombre aléaoitre entre deux double
    */
    float randomBetween(double min, double max){
        var next = random.NextDouble();
        return Convert.ToSingle(min + (next * (max - min)));
    }

}
