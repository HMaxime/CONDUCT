﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class changeSceneScript : MonoBehaviour
{
    public void GoToScene(string nameScene){
        SceneManager.LoadScene(nameScene);
    }
}
