using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ParticleSystemManager : MonoBehaviour
{
    public GameObject LeftPalm;
    public GameObject RightPalm;
    public ParticleSystem RightPalmParticles;
    public ParticleSystem LeftPalmParticles;
    public Light RightLight;
    public Light LeftLight;

    // Start is called before the first frame update
    void Start()
    {
        updateTransformCoord();
    }

    // Update is called once per frame
    void Update()
    {
        updateTransformCoord();
        RightPalmParticles.startColor = RightLight.color;
        LeftPalmParticles.startColor = LeftLight.color;
    }

    void updateTransformCoord(){
        LeftPalmParticles.transform.position = LeftPalm.transform.position;
        RightPalmParticles.transform.position = RightPalm.transform.position;

        //on affecte la rotation au systeme de particule
        LeftPalmParticles.transform.rotation = LeftPalm.transform.rotation;
        RightPalmParticles.transform.rotation = RightPalm.transform.rotation;
    }
}
